#include "rdv_scene.h"
#include "rdv_coin.h"
#include "rdv_question_box.h"
#include "rdv_mushroom_box.h"
#include "rdv_flower_box.h"
#include "rdv_brick_platform.h"
#include "rdv_wall_platform.h"
#include "rdv_note_box.h"
#include "rdv_goomba.h"
#include "rdv_turtle.h"
#include "rdv_piranha.h"
#include "rdv_flag.h"
#include "rdv_score.h"
#include "rdv_stretch.h"
#include "rdv_conveyor.h"
#include "rdv_giant_goomba.h"
#include "rdv_warp_tube.h"
#include "rdv_stair_block.h"
#include "rdv_bomb.h"
#include "rdv_red_turtle.h"
#include "rdv_spiny.h"
#include "rdv_castle.h"
#include "rdv_small_mario.h"
#include "rdv_coin_counter.h"
#include "rdv_timer.h"
#include "rdv_player.h"
#include "rdv_fire_mario.h"
#include "rdv_sound_manager.h"
#include "rdv_fire_ball.h"
#include "rdv_pixmap_painter.h"
#include "rdv_level_complete_window.h"
#include "rdv_game_over_window.h"
#include "rdv_mushroom.h"
#include "rdv_flower.h"

rdv_scene::rdv_scene(QScrollBar *_scroll, QObject* _parent)
: QGraphicsScene    (_parent)
, f_ireMario        (false)
, bigMario          (false)
, littleMario       (true)
, jumping           (false)
, falling           (false)
, m_jumpAnimation   (new QPropertyAnimation(this))
, m_platform        (nullptr)
, scroll            (_scroll)
, m_velocity        (7)
{
    initPlayField();

    m_timer.setInterval(20);
    connect(&m_timer, &QTimer::timeout, this, &rdv_scene::movePlayer);

    mFallTimer.setInterval(20);
    connect(&mFallTimer, &QTimer::timeout, this, &rdv_scene::fallPlayer);

    m_jumpAnimation->setTargetObject(this);
    m_jumpAnimation->setPropertyName("jumpFactor");
    m_jumpAnimation->setStartValue(0);
    m_jumpAnimation->setKeyValueAt(0.5, 1);
    m_jumpAnimation->setEndValue(0);
    m_jumpAnimation->setDuration(800);
    m_jumpAnimation->setEasingCurve(QEasingCurve::OutInQuad);

    connect(this, &rdv_scene::jumpFactorChanged, this, &rdv_scene::jumpPlayer);
    connect(m_jumpAnimation, &QPropertyAnimation::stateChanged, this, &rdv_scene::jumpStatusChanged);

    f_ireMario = false;
    bigMario = false;
    littleMario = true;
    connect(this, SIGNAL(spawnMushroom()),this,SLOT(controlMushroom()));
    connect(this, SIGNAL(spawnFlower()),this,SLOT(controlFlower()));

    jumping = false;
    falling = false;
    m_smallPlayer->addStandingDirection(1);

    soundManager = new rdv_sound_manager;
    connect(this, &rdv_scene::playSound, soundManager, &rdv_sound_manager::playSoundEffect);
    emit playSound("level1");
}

rdv_scene::~rdv_scene()
{

}

void rdv_scene::initPlayField()
{
    setSceneRect(0, 0, RDV_SCENE_WIDTH, RDV_SCENE_HEIGHT);

    m_groundLevel = 660;

    m_sky = new rdv_pixmap_painter(QPixmap(":images/sky"));
    m_sky->setPos(0,0);
    addItem(m_sky);

    //Game over screen
    gameover = new rdv_pixmap_painter(QPixmap(":images/gameovers"));

    //Course clear screen
    courseclear = new rdv_pixmap_painter(QPixmap(":images/c2"));

    //add ground
    m_ground = new rdv_pixmap_painter(QPixmap(":images/ground"));
    addItem(m_ground);
    m_ground->setPos(0, m_groundLevel );

    //add scene image
    m_Scene = new rdv_pixmap_painter(QPixmap(":images/Scene"));
    m_Scene->setPos(0, m_groundLevel - m_Scene->boundingRect().height());
    addItem(m_Scene);

    //Image for counter
    m_countLogo = new rdv_pixmap_painter(QPixmap(":images/count"));
    m_countLogo->setPos(30, m_groundLevel -652 );
    addItem(m_countLogo);

    //Add Score Text
    m_scoreLogo = new rdv_pixmap_painter(QPixmap(":images/scoretext"));
    m_scoreLogo->setPos(900, m_groundLevel -647 );
    addItem(m_scoreLogo);

    //Image for game timer
    m_timerLogo = new rdv_pixmap_painter(QPixmap(":images/clock"));
    m_timerLogo->setPos(1100, m_groundLevel -654 );
    addItem(m_timerLogo);

    //Add wall structures
    m_wall2 = new rdv_pixmap_painter(QPixmap(":images/wallg.png"));
    m_wall2->setPos(3100, m_groundLevel - m_wall2->boundingRect().height());
    addItem(m_wall2);

    m_wall = new rdv_pixmap_painter(QPixmap(":images/wallf2.png"));
    m_wall->setPos(2900, m_groundLevel - m_wall->boundingRect().height());
    addItem(m_wall);

    m_wall3 = new rdv_pixmap_painter(QPixmap(":images/walli.png"));
    m_wall3->setPos(3350, m_groundLevel - m_wall3->boundingRect().height());
    addItem(m_wall3);

    //Add flag Pole
    m_flag = new rdv_pixmap_painter(QPixmap(":images/flag"));
    m_flag->setPos(7234, m_groundLevel - m_flag->boundingRect().height());
    addItem(m_flag);

    //Add Castle
    m_castle = new rdv_pixmap_painter(QPixmap(":images/castle"));
    m_castle->setPos(7637, m_groundLevel - m_castle->boundingRect().height());
    addItem(m_castle);

    //Add rdv_coins
    m_coins = new rdv_coin;
    m_coins->setPos(1300, m_groundLevel - m_coins->boundingRect().height()-200);
    addItem(m_coins);
    startTimer( 100 );

    m_coins2 = new rdv_coin;
    m_coins2->setPos(1300, m_groundLevel - m_coins2->boundingRect().height()-250);
    addItem(m_coins2);

    m_coins3 = new rdv_coin;
    m_coins3->setPos(1300, m_groundLevel - m_coins3->boundingRect().height()-300);
    addItem(m_coins3);

    m_coins4 = new rdv_coin;
    m_coins4->setPos(1300, m_groundLevel - m_coins4->boundingRect().height()-350);
    addItem(m_coins4);

    m_coins5 = new rdv_coin;
    m_coins5->setPos(1350, m_groundLevel - m_coins5->boundingRect().height()-350);
    addItem(m_coins5);

    m_coins6 = new rdv_coin;
    m_coins6->setPos(1400, m_groundLevel - m_coins6->boundingRect().height()-350);
    addItem(m_coins6);

    m_coins7 = new rdv_coin;
    m_coins7->setPos(1400, m_groundLevel - m_coins7->boundingRect().height()-300);
    addItem(m_coins7);

    m_coins8 = new rdv_coin;
    m_coins8->setPos(1350, m_groundLevel - m_coins8->boundingRect().height()-250);
    addItem(m_coins8);

    m_coins9 = new rdv_coin;
    m_coins9->setPos(1400, m_groundLevel - m_coins9->boundingRect().height()-200);
    addItem(m_coins9);

    m_coins10 = new rdv_coin;
    m_coins10->setPos(1500, m_groundLevel - m_coins10->boundingRect().height()-200);
    addItem(m_coins10);

    m_coins11 = new rdv_coin;
    m_coins11->setPos(1500, m_groundLevel - m_coins11->boundingRect().height()-250);
    addItem(m_coins11);

    m_coins12 = new rdv_coin;
    m_coins12->setPos(1500, m_groundLevel - m_coins12->boundingRect().height()-300);
    addItem(m_coins12);

    m_coins13 = new rdv_coin;
    m_coins13->setPos(1500, m_groundLevel - m_coins13->boundingRect().height()-350);
    addItem(m_coins13);

    m_coins14 = new rdv_coin;
    m_coins14->setPos(1550, m_groundLevel -  m_coins14->boundingRect().height()-350);
    addItem( m_coins14);

    m_coins15 = new rdv_coin;
    m_coins15->setPos(1600, m_groundLevel - m_coins15->boundingRect().height()-350);
    addItem(m_coins15);

    m_coins16 = new rdv_coin;
    m_coins16->setPos(1500, m_groundLevel - m_coins16->boundingRect().height()-200);
    addItem(m_coins16);

    m_coins17 = new rdv_coin;
    m_coins17->setPos(1550, m_groundLevel - m_coins17->boundingRect().height()-200);
    addItem(m_coins17);

    m_coins18 = new rdv_coin;
    m_coins18->setPos(1600, m_groundLevel - m_coins18->boundingRect().height()-200);
    addItem(m_coins18);

    m_coins19 = new rdv_coin;
    m_coins19->setPos(1700, m_groundLevel - m_coins19->boundingRect().height()-200);
    addItem(m_coins19);

    m_coins20 = new rdv_coin;
    m_coins20->setPos(1700, m_groundLevel - m_coins20->boundingRect().height()-250);
    addItem(m_coins20);

    m_coins21 = new rdv_coin;
    m_coins21->setPos(1700, m_groundLevel - m_coins21->boundingRect().height()-300);
    addItem(m_coins21);

    m_coins22 = new rdv_coin;
    m_coins22->setPos(1700, m_groundLevel - m_coins22->boundingRect().height()-350);
    addItem(m_coins22);

    m_coins23 = new rdv_coin;
    m_coins23->setPos(1750, m_groundLevel - m_coins23->boundingRect().height()-350);
    addItem(m_coins23);

    m_coins24 = new rdv_coin;
    m_coins24->setPos(1800, m_groundLevel - m_coins24->boundingRect().height()-350);
    addItem(m_coins24);

    m_coins25 = new rdv_coin;
    m_coins25->setPos(1750, m_groundLevel - m_coins25->boundingRect().height()-200);
    addItem(m_coins25);

    m_coins26 = new rdv_coin;
    m_coins26->setPos(1800, m_groundLevel - m_coins26->boundingRect().height()-200);
    addItem(m_coins26);

    //first wall structure coins
    m_coins27 = new rdv_coin;
    m_coins27->setPos(2970, m_groundLevel - m_coins27->boundingRect().height()-290);
    addItem(m_coins27);

    m_coins28 = new rdv_coin;
    m_coins28->setPos(3020, m_groundLevel - m_coins28->boundingRect().height()-290);
    addItem(m_coins28);

    m_coins29 = new rdv_coin;
    m_coins29->setPos(3070, m_groundLevel - m_coins29->boundingRect().height()-290);
    addItem(m_coins29);

    m_coins30 = new rdv_coin;
    m_coins30->setPos(2920, m_groundLevel - m_coins30->boundingRect().height()-290);
    addItem(m_coins30);

    //Bottom wall structure coins
    m_coins32 = new rdv_coin;
    m_coins32->setPos(4110, m_groundLevel - m_coins32->boundingRect().height()-150);
    addItem(m_coins32);

    m_coins33 = new rdv_coin;
    m_coins33->setPos(3360, m_groundLevel - m_coins33->boundingRect().height()-150);
    addItem(m_coins33);

    m_coins34 = new rdv_coin;
    m_coins34->setPos(3410, m_groundLevel - m_coins34->boundingRect().height()-150);
    addItem(m_coins34);

    m_coins35 = new rdv_coin;
    m_coins35->setPos(3460, m_groundLevel - m_coins35->boundingRect().height()-150);
    addItem(m_coins35);

    m_coins36 = new rdv_coin;
    m_coins36->setPos(3510, m_groundLevel - m_coins36->boundingRect().height()-150);
    addItem(m_coins36);

    m_coins37 = new rdv_coin;
    m_coins37->setPos(3560, m_groundLevel - m_coins37->boundingRect().height()-150);
    addItem(m_coins37);

    m_coins38 = new rdv_coin;
    m_coins38->setPos(3610, m_groundLevel - m_coins38->boundingRect().height()-150);
    addItem(m_coins38);

    m_coins39 = new rdv_coin;
    m_coins39->setPos(3660, m_groundLevel - m_coins39->boundingRect().height()-150);
    addItem(m_coins39);

    m_coins40 = new rdv_coin;
    m_coins40->setPos(3710, m_groundLevel - m_coins40->boundingRect().height()-150);
    addItem(m_coins40);

    m_coins41 = new rdv_coin;
    m_coins41->setPos(3760, m_groundLevel - m_coins41->boundingRect().height()-150);
    addItem(m_coins41);

    m_coins42 = new rdv_coin;
    m_coins42->setPos(3810, m_groundLevel - m_coins42->boundingRect().height()-150);
    addItem(m_coins42);

    m_coins43 = new rdv_coin;
    m_coins43->setPos(3860, m_groundLevel - m_coins43->boundingRect().height()-150);
    addItem(m_coins43);

    m_coins44 = new rdv_coin;
    m_coins44->setPos(3910, m_groundLevel - m_coins44->boundingRect().height()-150);
    addItem(m_coins44);

    m_coins45 = new rdv_coin;
    m_coins45->setPos(3960, m_groundLevel - m_coins45->boundingRect().height()-150);
    addItem(m_coins45);

    m_coins46 = new rdv_coin;
    m_coins46->setPos(4010, m_groundLevel - m_coins46->boundingRect().height()-150);
    addItem(m_coins46);

    m_coins47 = new rdv_coin;
    m_coins47->setPos(4060, m_groundLevel - m_coins47->boundingRect().height()-150);
    addItem(m_coins47);

    //Notebox coins
    m_coins48 = new rdv_coin;
    m_coins48->setPos(3995, m_groundLevel - m_coins48->boundingRect().height()-370);
    addItem(m_coins48);

    m_coins49 = new rdv_coin;
    m_coins49->setPos(4030, m_groundLevel - m_coins49->boundingRect().height()-440);
    addItem(m_coins49);

    m_coins50 = new rdv_coin;
    m_coins50->setPos(4108, m_groundLevel - m_coins50->boundingRect().height()-495);
    addItem(m_coins50);

    m_coins51 = new rdv_coin;
    m_coins51->setPos(4190, m_groundLevel - m_coins51->boundingRect().height()-450);
    addItem(m_coins51);

    m_coins52 = new rdv_coin;
    m_coins52->setPos(4240, m_groundLevel - m_coins52->boundingRect().height()-390);
    addItem(m_coins52);

    m_coins53 = new rdv_coin;
    m_coins53->setPos(4290, m_groundLevel - m_coins53->boundingRect().height()-465);
    addItem(m_coins53);

    m_coins54 = new rdv_coin;
    m_coins54->setPos(4360, m_groundLevel - m_coins54->boundingRect().height()-520);
    addItem(m_coins54);

    m_coins55 = new rdv_coin;
    m_coins55->setPos(4435, m_groundLevel - m_coins55->boundingRect().height()-465);
    addItem(m_coins55);

    m_coins56 = new rdv_coin;
    m_coins56->setPos(4490, m_groundLevel - m_coins56->boundingRect().height()-410);
    addItem(m_coins56);

    m_coins57 = new rdv_coin;
    m_coins57->setPos(4540, m_groundLevel - m_coins57->boundingRect().height()-490);
    addItem(m_coins57);

    m_coins58 = new rdv_coin;
    m_coins58->setPos(4610, m_groundLevel - m_coins58->boundingRect().height()-540);
    addItem(m_coins58);

    m_coins59 = new rdv_coin;
    m_coins59->setPos(4680, m_groundLevel - m_coins59->boundingRect().height()-500);
    addItem(m_coins59);

    m_coins60 = new rdv_coin;
    m_coins60->setPos(4730, m_groundLevel - m_coins60->boundingRect().height()-440);
    addItem(m_coins60);

    m_coins61 = new rdv_coin;
    m_coins61->setPos(650, m_groundLevel - m_coins61->boundingRect().height()-280);
    addItem(m_coins61);

    m_coins62 = new rdv_coin;
    m_coins62->setPos(2100, m_groundLevel - m_coins62->boundingRect().height()-250);
    addItem(m_coins62);

    m_coins63 = new rdv_coin;
    m_coins63->setPos(815, m_groundLevel - m_coins63->boundingRect().height()-320);
    addItem(m_coins63);

    m_coins64 = new rdv_coin;
    m_coins64->setPos(2155, m_groundLevel - m_coins64->boundingRect().height()-250);
    addItem(m_coins64);

    m_coins65 = new rdv_coin;
    m_coins65->setPos(2210, m_groundLevel - m_coins65->boundingRect().height()-250);
    addItem(m_coins65);

    m_coins66 = new rdv_coin;
    m_coins66->setPos(2265, m_groundLevel - m_coins66->boundingRect().height()-250);
    addItem(m_coins66);

    m_coins67 = new rdv_coin;
    m_coins67->setPos(2320, m_groundLevel - m_coins67->boundingRect().height()-250);
    addItem(m_coins67);

    m_coins68 = new rdv_coin;
    m_coins68->setPos(2375, m_groundLevel - m_coins68->boundingRect().height()-250);
    addItem(m_coins68);

    //End Level coins
    m_coins69 = new rdv_coin;
    m_coins69->setPos(5400, m_groundLevel - m_coins69->boundingRect().height()-250);
    addItem(m_coins69);

    m_coins70 = new rdv_coin;
    m_coins70->setPos(5400, m_groundLevel - m_coins70->boundingRect().height()-300);
    addItem(m_coins70);

    m_coins71 = new rdv_coin;
    m_coins71->setPos(5400, m_groundLevel - m_coins71->boundingRect().height()-350);
    addItem(m_coins71);

    m_coins72 = new rdv_coin;
    m_coins72->setPos(5350, m_groundLevel - m_coins72->boundingRect().height()-250);
    addItem(m_coins72);

    m_coins73 = new rdv_coin;
    m_coins73->setPos(5350, m_groundLevel - m_coins73->boundingRect().height()-300);
    addItem(m_coins73);

    m_coins74 = new rdv_coin;
    m_coins74->setPos(5350, m_groundLevel - m_coins74->boundingRect().height()-350);
    addItem(m_coins74);

    m_coins75 = new rdv_coin;
    m_coins75->setPos(5300, m_groundLevel - m_coins75->boundingRect().height()-250);
    addItem(m_coins75);

    m_coins76 = new rdv_coin;
    m_coins76->setPos(5300, m_groundLevel - m_coins76->boundingRect().height()-300);
    addItem(m_coins76);

    m_coins77 = new rdv_coin;
    m_coins77->setPos(5300, m_groundLevel - m_coins77->boundingRect().height()-350);
    addItem(m_coins77);

    m_coins78 = new rdv_coin;
    m_coins78->setPos(5250, m_groundLevel - m_coins78->boundingRect().height()-250);
    addItem(m_coins78);

    m_coins79 = new rdv_coin;
    m_coins79->setPos(5250, m_groundLevel - m_coins79->boundingRect().height()-300);
    addItem(m_coins79);

    m_coins80 = new rdv_coin;
    m_coins80->setPos(5250, m_groundLevel - m_coins80->boundingRect().height()-350);
    addItem(m_coins80);

    m_coins81 = new rdv_coin;
    m_coins81->setPos(5200, m_groundLevel - m_coins81->boundingRect().height()-250);
    addItem(m_coins81);

    m_coins82 = new rdv_coin;
    m_coins82->setPos(5200, m_groundLevel - m_coins82->boundingRect().height()-300);
    addItem(m_coins82);

    m_coins83 = new rdv_coin;
    m_coins83->setPos(5200, m_groundLevel - m_coins83->boundingRect().height()-350);
    addItem(m_coins83);

    m_coins84 = new rdv_coin;
    m_coins84->setPos(5150, m_groundLevel - m_coins84->boundingRect().height()-250);
    addItem(m_coins84);

    m_coins85 = new rdv_coin;
    m_coins85->setPos(5150, m_groundLevel - m_coins85->boundingRect().height()-300);
    addItem(m_coins85);

    m_coins86 = new rdv_coin;
    m_coins86->setPos(5150, m_groundLevel - m_coins86->boundingRect().height()-350);
    addItem(m_coins86);

    m_coins87 = new rdv_coin;
    m_coins87->setPos(5700, m_groundLevel - m_coins87->boundingRect().height()-350);
    addItem(m_coins87);

    m_coins88 = new rdv_coin;
    m_coins88->setPos(5750, m_groundLevel - m_coins88->boundingRect().height()-350);
    addItem(m_coins88);

    m_coins89 = new rdv_coin;
    m_coins89->setPos(5800, m_groundLevel - m_coins89->boundingRect().height()-350);
    addItem(m_coins89);

    m_coins90 = new rdv_coin;
    m_coins90->setPos(5850, m_groundLevel - m_coins90->boundingRect().height()-350);
    addItem(m_coins90);

    m_coins91 = new rdv_coin;
    m_coins91->setPos(5900, m_groundLevel - m_coins91->boundingRect().height()-350);
    addItem(m_coins91);

    m_coins92 = new rdv_coin;
    m_coins92->setPos(5950, m_groundLevel - m_coins92->boundingRect().height()-350);
    addItem(m_coins92);

    m_coins93 = new rdv_coin;
    m_coins93->setPos(6000, m_groundLevel - m_coins93->boundingRect().height()-350);
    addItem(m_coins93);

    m_coins94 = new rdv_coin;
    m_coins94->setPos(6050, m_groundLevel - m_coins94->boundingRect().height()-350);
    addItem(m_coins94);

    m_coins95 = new rdv_coin;
    m_coins95->setPos(6100, m_groundLevel - m_coins95->boundingRect().height()-350);
    //addItem(m_coins95);

    m_coins96 = new rdv_coin;
    m_coins96->setPos(6140, m_groundLevel - m_coins96->boundingRect().height()-350);
    addItem(m_coins96);

    m_coins97 = new rdv_coin;
    m_coins97->setPos(6105, m_groundLevel - m_coins97->boundingRect().height()-300);
    addItem(m_coins97);

    m_coins98 = new rdv_coin;
    m_coins98->setPos(6060, m_groundLevel - m_coins98->boundingRect().height()-250);
    addItem(m_coins98);

    m_coins99 = new rdv_coin;
    m_coins99->setPos(6105, m_groundLevel - m_coins99->boundingRect().height()-400);
    addItem(m_coins99);

    m_coins100 = new rdv_coin;
    m_coins100->setPos(6060, m_groundLevel - m_coins100->boundingRect().height()-450);
    addItem(m_coins100);

    //Add Questionbox
    m_questbox = new rdv_question_box(1);
    m_questbox->setPos(643, m_groundLevel - m_questbox->boundingRect().height()-100);
    addItem(m_questbox);

    m_questbox2 = new rdv_question_box(1);
    m_questbox2->setPos(2755, m_groundLevel - m_questbox2->boundingRect().height()-150);
    addItem(m_questbox2);

    m_questbox3 = new rdv_question_box(1);
    m_questbox3->setPos(2658, m_groundLevel - m_questbox3->boundingRect().height()-100);
    addItem(m_questbox3);

    //Wall scructure questbox
    m_questbox4 = new rdv_question_box(1);
    m_questbox4->setPos(3250, m_groundLevel - m_questbox4->boundingRect().height()-450);
    addItem(m_questbox4);

    m_questbox5 = new rdv_question_box(1);
    m_questbox5->setPos(3750, m_groundLevel - m_questbox5->boundingRect().height()-250);
    addItem(m_questbox5);

    //Rcc Coin area Questbox
    m_questbox6 = new rdv_question_box(1);
    m_questbox6->setPos(1745, m_groundLevel - m_questbox6->boundingRect().height()-130);
    addItem(m_questbox6);

    m_questbox7 = new rdv_question_box(1);
    m_questbox7->setPos(1545, m_groundLevel - m_questbox7->boundingRect().height()-130);
    addItem(m_questbox7);

    m_questbox8 = new rdv_question_box(1);
    m_questbox8->setPos(1345, m_groundLevel - m_questbox8->boundingRect().height()-130);
    addItem(m_questbox8);

    m_questbox9 = new rdv_question_box(1);
    m_questbox9->setPos(6240, m_groundLevel - m_questbox9->boundingRect().height()-350);
    addItem(m_questbox9);

    m_questbox10 = new rdv_question_box(1);
    m_questbox10->setPos(5600, m_groundLevel - m_questbox10->boundingRect().height()-350);
    addItem(m_questbox10);

    m_questbox11 = new rdv_question_box(1);
    m_questbox11->setPos(5153, m_groundLevel - m_questbox11->boundingRect().height()-200);
    addItem(m_questbox11);

    m_questbox12 = new rdv_question_box(1);
    m_questbox12->setPos(7200, m_groundLevel - m_questbox11->boundingRect().height()-100);
    addItem(m_questbox12);

    mushroomQuestBox = new rdv_mushroom_box(1);
    mushroomQuestBox->setPos(200, m_groundLevel - mushroomQuestBox->boundingRect().height()-100);
    mushroomQuestBox->setZValue(1);
    addItem(mushroomQuestBox);

    flowerQuestBox = new rdv_flower_box(1);
    flowerQuestBox->setPos(1085, m_groundLevel - flowerQuestBox->boundingRect().height()-250);
    flowerQuestBox->setZValue(3);
    addItem(flowerQuestBox);

    //Add brick platforms
    mBrickPlatform = new rdv_brick_platform(5);
    mBrickPlatform->setPos(404, m_groundLevel - mBrickPlatform->boundingRect().height()-100);
    addItem(mBrickPlatform);

    mBrickPlatform2 = new rdv_brick_platform(1);
    mBrickPlatform2->setPos(648, m_groundLevel - mBrickPlatform2->boundingRect().height()-225);
    addItem(mBrickPlatform2);

    mBrickPlatform3 = new rdv_brick_platform(1);
    mBrickPlatform3->setPos(810, m_groundLevel - mBrickPlatform3->boundingRect().height()-270);
    addItem(mBrickPlatform3);

    mBrickPlatform4 = new rdv_brick_platform(5);
    mBrickPlatform4->setPos(1000, m_groundLevel - mBrickPlatform4->boundingRect().height()-100);
    addItem(mBrickPlatform4);

    mBrickPlatform5 = new rdv_brick_platform(5);
    mBrickPlatform5->setPos(5500, m_groundLevel - mBrickPlatform5->boundingRect().height()-150);
    addItem(mBrickPlatform5);

    mBrickPlatform6 = new rdv_brick_platform(5);
    mBrickPlatform6->setPos(5200, m_groundLevel - mBrickPlatform6->boundingRect().height()-200);
    addItem(mBrickPlatform6);

    mBrickPlatform7 = new rdv_brick_platform(1);
    mBrickPlatform7->setPos(5900, m_groundLevel - mBrickPlatform7->boundingRect().height()-150);
    addItem(mBrickPlatform7);

    mBrickPlatform8 = new rdv_brick_platform(7);
    mBrickPlatform8->setPos(6100, m_groundLevel - mBrickPlatform8->boundingRect().height()-150);
    addItem(mBrickPlatform8);

    //Add wall platform
    m_wallPlatform = new rdv_wall_platform(6);
    m_wallPlatform->setPos(2910, m_groundLevel - m_wallPlatform->boundingRect().height()-240);
    addItem(m_wallPlatform);

    m_wallPlatform2  = new rdv_wall_platform(8);
    m_wallPlatform2->setPos(3115, m_groundLevel - m_wallPlatform2->boundingRect().height()-300);
    addItem(m_wallPlatform2);

    m_wallPlatform3 = new rdv_wall_platform(16);
    m_wallPlatform3->setPos(3370, m_groundLevel - m_wallPlatform3->boundingRect().height()-103);
    addItem(m_wallPlatform3);

    m_wallPlatform4 = new rdv_wall_platform(20);
    m_wallPlatform4->setPos(5000, m_groundLevel );
    addItem(m_wallPlatform4);

    m_wallPlatform5 = new rdv_wall_platform(10);
    m_wallPlatform5->setPos(1345, m_groundLevel );
    addItem(m_wallPlatform5);

    m_wallPlatform6 = new rdv_wall_platform(3);
    m_wallPlatform6->setPos(404, m_groundLevel );
    addItem(m_wallPlatform6);

    m_wallPlatform7 = new rdv_wall_platform(3);
    m_wallPlatform7->setPos(1000, m_groundLevel );
    addItem(m_wallPlatform7);

    m_wallPlatform8 = new rdv_wall_platform(4);
    m_wallPlatform8->setPos(3115, m_groundLevel );
    addItem(m_wallPlatform8);

    m_wallPlatform9 = new rdv_wall_platform(3);
    m_wallPlatform9->setPos(4960, m_groundLevel );
    addItem(m_wallPlatform9);

    m_wallPlatform10 = new rdv_wall_platform(3);
    m_wallPlatform10->setPos(6100, m_groundLevel );
    addItem(m_wallPlatform10);

    m_wallPlatform11 = new rdv_wall_platform(3);
    m_wallPlatform11->setPos(2100, m_groundLevel- m_wallPlatform11->boundingRect().height()-150 );
    addItem(m_wallPlatform11);

    //Add Notebox
    m_NoteBox = new rdv_note_box(5);
    m_NoteBox->setPos(2100, m_groundLevel - m_NoteBox->boundingRect().height()-130);
    addItem(m_NoteBox);

    m_NoteBox2 = new rdv_note_box(1);
    m_NoteBox2->setPos(3980, m_groundLevel - m_NoteBox2->boundingRect().height()-300);
    addItem(m_NoteBox2);

    m_NoteBox3 = new rdv_note_box(1);
    m_NoteBox3->setPos(4230, m_groundLevel - m_NoteBox3->boundingRect().height()-325);
    addItem(m_NoteBox3);

    m_NoteBox4 = new rdv_note_box(1);
    m_NoteBox4->setPos(4480, m_groundLevel - m_NoteBox4->boundingRect().height()-340);
    addItem(m_NoteBox4);

    m_NoteBox5 = new rdv_note_box(1);
    m_NoteBox5->setPos(4720, m_groundLevel - m_NoteBox5->boundingRect().height()-365);
    addItem(m_NoteBox5);

    m_NoteBox6 = new rdv_note_box(5);
    m_NoteBox6->setPos(4940, m_groundLevel - m_NoteBox6->boundingRect().height()-400);
    addItem(m_NoteBox6);

    //Add Goomba
    m_goomba = new rdv_goomba(QRectF(m_wallPlatform6 ->pos(), m_wallPlatform6 ->boundingRect().size()), -1);
    m_goomba->setPos(400, m_groundLevel - m_goomba->boundingRect().height()-150);
    addItem(m_goomba);
    connect(this->m_goomba, SIGNAL(marioSizeStatus(int)),this, SLOT(setMarioSize(int)));

    //Add Turtle
    m_turtle = new rdv_turtle(QRectF(m_wallPlatform7->pos(), m_wallPlatform7->boundingRect().size()), -1);
    m_turtle->setPos(995, m_groundLevel - m_turtle->boundingRect().height()-150);
    addItem(m_turtle);
    connect(this->m_turtle, SIGNAL(marioSizeStatus(int)),this, SLOT(setMarioSize(int)));

    m_turtle2 = new rdv_turtle(QRectF(m_wallPlatform8->pos(), m_wallPlatform8->boundingRect().size()), -1);
    m_turtle2->setPos(3250, m_groundLevel - m_turtle2->boundingRect().height()-345);
    addItem(m_turtle2);
    connect(this->m_turtle2, SIGNAL(marioSizeStatus(int)),this, SLOT(setMarioSize(int)));

    //Add piranha plant
    m_piranha = new rdv_piranha;
    m_piranha->setPos(773, m_groundLevel - m_piranha->boundingRect().height()-95);
    addItem(m_piranha);

    m_piranha2 = new rdv_piranha;
    m_piranha2->setPos(2975, m_groundLevel - m_piranha2->boundingRect().height()-95);
    addItem(m_piranha2);

    m_piranha3= new rdv_piranha;
    m_piranha3->setPos(4850, m_groundLevel - m_piranha2->boundingRect().height()-95);
    addItem(m_piranha3);

    //Add Flag Animation
    m_flag2 = new rdv_flag;
    m_flag2->setPos(7320, m_groundLevel - m_flag2->boundingRect().height()-285);
    addItem(m_flag2);

    //Add coin counter
    m_count = new rdv_coin_counter;
    m_count->setPos(65, m_groundLevel - m_count->boundingRect().height()-602);
    addItem(m_count);

    //Add Score counter
    m_score = new rdv_score;
    m_score->setPos(980, m_groundLevel - m_score->boundingRect().height()-610);
    addItem(m_score);

    //Add Game Timer
    m_gameTimer = new rdv_timer;
    m_gameTimer->setPos(1140, m_groundLevel - m_gameTimer->boundingRect().height()-610);
    addItem(m_gameTimer);

    //Add stretch
    m_stretch = new rdv_stretch;
    m_stretch->setPos(2100, m_groundLevel - m_stretch->boundingRect().height()-20);
    addItem(m_stretch);

    //Add sign
    m_sign = new rdv_pixmap_painter(QPixmap(":images/sign.png"));
    m_sign->setPos(250, m_groundLevel - m_sign->boundingRect().height());
    addItem(m_sign);

    //Add conveyor
    m_conveyor = new rdv_conveyor;
    m_conveyor->setPos(4160, m_groundLevel - m_conveyor->boundingRect().height()-100);
    addItem(m_conveyor);

    m_conveyor2 = new rdv_conveyor;
    m_conveyor2->setPos(4370, m_groundLevel - m_conveyor2->boundingRect().height()-100);
    addItem(m_conveyor2);

    m_conveyor3 = new rdv_conveyor;
    m_conveyor3->setPos(4580, m_groundLevel - m_conveyor3->boundingRect().height()-100);
    addItem(m_conveyor3);

    //Add giant goomba
    m_giantgoomba = new rdv_giant_goomba;
    m_giantgoomba->setPos(4210, m_groundLevel - m_giantgoomba->boundingRect().height()-150);
    addItem(m_giantgoomba);

    m_giantgoomba2 = new rdv_giant_goomba;
    m_giantgoomba2->setPos(4420, m_groundLevel - m_giantgoomba2->boundingRect().height()-150);
    addItem(m_giantgoomba2);

    m_giantgoomba3 = new rdv_giant_goomba;
    m_giantgoomba3->setPos(4630, m_groundLevel - m_giantgoomba3->boundingRect().height()-150);
    addItem(m_giantgoomba3);

    //Add warp tube
    m_warpTube1 = new rdv_warp_tube();
    m_warpTube1->setPos(800, m_groundLevel - m_warpTube1->boundingRect().height());
    addItem(m_warpTube1);

    m_warpTube2 = new rdv_warp_tube();
    m_warpTube2->setPos(3000, m_groundLevel - m_warpTube2->boundingRect().height());
    addItem(m_warpTube2);

    m_warpTube3 = new rdv_warp_tube();
    m_warpTube3->setPos(4880, m_groundLevel - m_warpTube3->boundingRect().height());
    addItem(m_warpTube3);

    //Add Stair blocks
    m_stairBlock = new rdv_stair_block(9);
    m_stairBlock->setPos(6750, m_groundLevel - m_stairBlock->boundingRect().height());
    addItem(m_stairBlock);

    m_stairBlock2 = new rdv_stair_block(8);
    m_stairBlock2->setPos(6798, m_groundLevel - m_stairBlock2->boundingRect().height()-48);
    addItem(m_stairBlock2);

    m_stairBlock3 = new rdv_stair_block(7);
    m_stairBlock3->setPos(6846, m_groundLevel - m_stairBlock3->boundingRect().height()-96);
    addItem(m_stairBlock3);

    m_stairBlock4 = new rdv_stair_block(6);
    m_stairBlock4->setPos(6894, m_groundLevel - m_stairBlock4->boundingRect().height()-144);
    addItem(m_stairBlock4);

    m_stairBlock5 = new rdv_stair_block(5);
    m_stairBlock5->setPos(6942, m_groundLevel - m_stairBlock5->boundingRect().height()-192);
    addItem(m_stairBlock5);

    m_stairBlock6 = new rdv_stair_block(4);
    m_stairBlock6->setPos(6990, m_groundLevel - m_stairBlock6->boundingRect().height()-240);
    addItem(m_stairBlock6);

    m_stairBlock7 = new rdv_stair_block(3);
    m_stairBlock7->setPos(7038, m_groundLevel - m_stairBlock7->boundingRect().height()-288);
    addItem(m_stairBlock7);

    m_stairBlock8 = new rdv_stair_block(2);
    m_stairBlock8->setPos(7086, m_groundLevel - m_stairBlock8->boundingRect().height()-336);
    addItem(m_stairBlock8);

    //Add goomba
    m_goomba2 = new rdv_goomba(QRectF(m_wallPlatform9->pos(), m_wallPlatform9->boundingRect().size()), -1);
    m_goomba2->setPos(5100, m_groundLevel - m_goomba2->boundingRect().height()-465);
    addItem(m_goomba2);
    connect(this->m_goomba2, SIGNAL(marioSizeStatus(int)),this, SLOT(setMarioSize(int)));

    //Add bomb
    m_bomb2 = new rdv_bomb(QRectF(m_wallPlatform10->pos(), m_wallPlatform10->boundingRect().size()), -1);
    m_bomb2->setPos(6100, m_groundLevel - m_bomb2->boundingRect().height()-190);
    addItem(m_bomb2);

    //Add Red Turtle
    m_redTurtle = new rdv_red_turtle(QRectF(m_wallPlatform4->pos(), m_wallPlatform4->boundingRect().size()), -1);
    m_redTurtle->setPos(5100, m_groundLevel - m_redTurtle->boundingRect().height()+4);
    addItem(m_redTurtle);

    //Add Spiny
    m_spiny = new rdv_spiny(QRectF(m_wallPlatform5->pos(), m_wallPlatform5->boundingRect().size()), -1);
    m_spiny->setPos(1345, m_groundLevel - m_spiny->boundingRect().height()+4);
    addItem(m_spiny);

    //add player
    m_smallPlayer = new rdv_small_mario;
    m_smallPlayer->setPos(50, m_groundLevel - m_smallPlayer->boundingRect().height() );
    addItem(m_smallPlayer);

    //Add half castle to make it look like mario can walk inside of castle
    h_castle = new rdv_castle;
    h_castle->setPos(7637, m_groundLevel - h_castle->boundingRect().height());
    addItem(h_castle);
}

QGraphicsItem* rdv_scene::collidingPlatforms()
{
    if(bigMario)
    {
        QList<QGraphicsItem*> items =  collidingItems(m_player);
        foreach(QGraphicsItem *item, items)
        {
            if(rdv_brick_platform *brickplatform = qgraphicsitem_cast<rdv_brick_platform *>(item))
            {
                return brickplatform;
            }
            if(rdv_question_box *questbox = qgraphicsitem_cast<rdv_question_box *>(item))
            {
                return questbox;
            }
            if(rdv_note_box *notebox = qgraphicsitem_cast<rdv_note_box *>(item))
            {
                return notebox;
            }
            if(rdv_wall_platform *wallplatform = qgraphicsitem_cast<rdv_wall_platform *>(item))
            {
                return wallplatform;
            }
            if(rdv_stair_block *stairblock = qgraphicsitem_cast<rdv_stair_block *>(item))
            {
                return stairblock;
            }
            if(rdv_mushroom_box *mushquestbox = qgraphicsitem_cast<rdv_mushroom_box *>(item))
            {
                return mushquestbox;
            }
            if(rdv_flower_box *flowquestbox = qgraphicsitem_cast<rdv_flower_box *>(item))
            {
                return flowquestbox;
            }
        }
        return 0;
    }
    else if(littleMario)
    {
        QList<QGraphicsItem*> items =  collidingItems(m_smallPlayer);
        foreach(QGraphicsItem *item, items)
        {
            if(rdv_brick_platform *brickplatform = qgraphicsitem_cast<rdv_brick_platform *>(item))
            {
                return brickplatform;
            }
            if(rdv_question_box *questbox = qgraphicsitem_cast<rdv_question_box *>(item))
            {
                return questbox;
            }
            if(rdv_note_box *notebox = qgraphicsitem_cast<rdv_note_box *>(item)){
                return notebox;
            }
            if(rdv_wall_platform *wallplatform = qgraphicsitem_cast<rdv_wall_platform *>(item))
            {
                return wallplatform;
            }
            if(rdv_stair_block *stairblock = qgraphicsitem_cast<rdv_stair_block *>(item))
            {
                return stairblock;
            }
            if(rdv_mushroom_box *mushquestbox = qgraphicsitem_cast<rdv_mushroom_box *>(item))
            {
                return mushquestbox;
            }
            if(rdv_flower_box *flowquestbox = qgraphicsitem_cast<rdv_flower_box *>(item))
            {
                return flowquestbox;
            }
        }
        return 0;
    }
    else if(f_ireMario)
    {
        QList<QGraphicsItem*> items =  collidingItems(fireMario);
        foreach(QGraphicsItem *item, items)
        {
            if(rdv_brick_platform *brickplatform = qgraphicsitem_cast<rdv_brick_platform *>(item))
            {
                return brickplatform;
            }
            if(rdv_question_box *questbox = qgraphicsitem_cast<rdv_question_box *>(item))
            {
                return questbox;
            }
            if(rdv_note_box *notebox = qgraphicsitem_cast<rdv_note_box *>(item))
            {
                return notebox;
            }
            if(rdv_wall_platform *wallplatform = qgraphicsitem_cast<rdv_wall_platform *>(item))
            {
                return wallplatform;
            }
            if(rdv_stair_block *stairblock = qgraphicsitem_cast<rdv_stair_block *>(item))
            {
                return stairblock;
            }
            if(rdv_mushroom_box *mushquestbox = qgraphicsitem_cast<rdv_mushroom_box *>(item))
            {
                return mushquestbox;
            }
            if(rdv_flower_box *flowquestbox = qgraphicsitem_cast<rdv_flower_box *>(item))
            {
                return flowquestbox;
            }
        }
        return 0;
    }
    return 0;
}

bool rdv_scene::handleCollisionWithPlatform()
{
    if(bigMario)
    {
        QGraphicsItem* platform =  collidingPlatforms();
        if(platform)
        {
            QPointF platformPos = platform->pos();
            if(m_player->isTouchingFoot(platform))
            {
                m_player->setPos(m_player->pos().x(), platformPos.y() - m_player->boundingRect().height());
                m_platform = platform;
                m_jumpAnimation->stop();
                return true;
            }
        }
        else
        {
            m_platform = 0;
        }
        return false;
    }
    else if(littleMario)
    {
        QGraphicsItem* platform =  collidingPlatforms();
        if(platform)
        {
            QPointF platformPos = platform->pos();
            if(m_smallPlayer->isTouchingFoot(platform))
            {
                m_smallPlayer->setPos(m_smallPlayer->pos().x(), platformPos.y() - m_smallPlayer->boundingRect().height());
                m_platform = platform;
                m_jumpAnimation->stop();
                return true;
            }
        }
        else
        {
            m_platform = 0;
        }
        return false;
    }
    else if(f_ireMario)
    {
        QGraphicsItem* platform = collidingPlatforms();
        if(platform)
        {
            QPointF platformPos = platform->pos();
            if(fireMario->isTouchingFoot(platform))
            {
                fireMario->setPos(fireMario->pos().x(), platformPos.y() - fireMario->boundingRect().height());
                m_platform = platform;
                m_jumpAnimation->stop();
                return true;
            }
        }
        else
        {
            m_platform = 0;
        }
        return false;
    }
    return 0;
}

void rdv_scene::timerEvent([[maybe_unused]] QTimerEvent *event)
{
    m_coins->nextFrame2();
    m_coins2->nextFrame2();
    m_coins3->nextFrame2();
    m_coins4->nextFrame2();
    m_coins5->nextFrame2();
    m_coins6->nextFrame2();
    m_coins7->nextFrame2();
    m_coins8->nextFrame2();
    m_coins9->nextFrame2();
    m_coins10->nextFrame2();
    m_coins11->nextFrame2();
    m_coins12->nextFrame2();
    m_coins13->nextFrame2();
    m_coins14->nextFrame2();
    m_coins15->nextFrame2();
    m_coins16->nextFrame2();
    m_coins17->nextFrame2();
    m_coins18->nextFrame2();
    m_coins19->nextFrame2();
    m_coins20->nextFrame2();
    m_coins21->nextFrame2();
    m_coins22->nextFrame2();
    m_coins23->nextFrame2();
    m_coins24->nextFrame2();
    m_coins25->nextFrame2();
    m_coins26->nextFrame2();

    m_coins27->nextFrame2();
    m_coins28->nextFrame2();
    m_coins29->nextFrame2();
    m_coins30->nextFrame2();

    m_coins32->nextFrame2();
    m_coins33->nextFrame2();
    m_coins34->nextFrame2();
    m_coins35->nextFrame2();
    m_coins36->nextFrame2();

    m_coins37->nextFrame2();
    m_coins38->nextFrame2();
    m_coins39->nextFrame2();
    m_coins40->nextFrame2();
    m_coins41->nextFrame2();
    m_coins42->nextFrame2();
    m_coins43->nextFrame2();
    m_coins44->nextFrame2();
    m_coins45->nextFrame2();
    m_coins46->nextFrame2();
    m_coins47->nextFrame2();

    m_coins48->nextFrame2();
    m_coins49->nextFrame2();
    m_coins50->nextFrame2();
    m_coins51->nextFrame2();
    m_coins52->nextFrame2();

    m_coins53->nextFrame2();
    m_coins54->nextFrame2();
    m_coins55->nextFrame2();
    m_coins56->nextFrame2();

    m_coins57->nextFrame2();
    m_coins58->nextFrame2();
    m_coins59->nextFrame2();
    m_coins60->nextFrame2();

    m_coins61->nextFrame2();
    m_coins62->nextFrame2();
    m_coins63->nextFrame2();
    m_coins64->nextFrame2();
    m_coins65->nextFrame2();
    m_coins66->nextFrame2();
    m_coins67->nextFrame2();
    m_coins68->nextFrame2();

    m_coins69->nextFrame2();
    m_coins70->nextFrame2();
    m_coins71->nextFrame2();

    m_coins72->nextFrame2();
    m_coins73->nextFrame2();
    m_coins74->nextFrame2();

    m_coins75->nextFrame2();
    m_coins76->nextFrame2();
    m_coins77->nextFrame2();
    m_coins78->nextFrame2();
    m_coins79->nextFrame2();
    m_coins80->nextFrame2();

    m_coins81->nextFrame2();
    m_coins82->nextFrame2();
    m_coins83->nextFrame2();
    m_coins84->nextFrame2();
    m_coins85->nextFrame2();
    m_coins86->nextFrame2();

    m_coins87->nextFrame2();
    m_coins88->nextFrame2();
    m_coins89->nextFrame2();
    m_coins90->nextFrame2();
    m_coins91->nextFrame2();
    m_coins92->nextFrame2();
    m_coins93->nextFrame2();
    m_coins94->nextFrame2();
    m_coins95->nextFrame2();
    m_coins96->nextFrame2();
    m_coins97->nextFrame2();
    m_coins98->nextFrame2();
    m_coins99->nextFrame2();
    m_coins100->nextFrame2();

    m_questbox->nextFrame4();
    m_questbox2->nextFrame4();
    m_questbox3->nextFrame4();
    m_questbox4->nextFrame4();
    m_questbox5->nextFrame4();
    m_questbox6->nextFrame4();
    m_questbox7->nextFrame4();
    m_questbox8->nextFrame4();
    m_questbox9->nextFrame4();
    m_questbox10->nextFrame4();
    m_questbox11->nextFrame4();
    m_questbox12->nextFrame4();
}

void rdv_scene::setMarioSize(int n)
{
    int number = n;
    if(number == 0)
    {
        m_smallPlayer = new rdv_small_mario;
        m_smallPlayer->setPos(m_player->pos().x(),m_player->pos().y()+28);
        m_smallPlayer->addDirection(m_player->direction());
        emit playSound("shrink");
        addItem(m_smallPlayer);
        bigMario = false;
        littleMario = true;
        f_ireMario = false;
    }
    else if(number == 1)
    {
        bigMario = false;
        littleMario = false;
        f_ireMario = false;
        emit playSound("stopLevelMusic");
        emit playSound("mario_death");
        addItem(gameover);
        QSharedPointer<rdv_game_over_window> gameOverWindow(new rdv_game_over_window);
        gameOverWindow->setFixedSize(557,355);
        gameOverWindow->setWindowFlags(((gameOverWindow->windowFlags()|Qt::CustomizeWindowHint)& ~Qt::WindowCloseButtonHint));
        gameOverWindow->exec();
    }
    else if(number == 2)
    {
        emit playSound("powerup");
        m_player = new rdv_player;
        m_player->setPos(m_smallPlayer->pos().x(),m_smallPlayer->pos().y()-27);
        m_player->addDirection(m_smallPlayer->direction());
        addItem(m_player);
        bigMario = true;
        f_ireMario = false;
        littleMario = false;
    }
    else if(number == 3)
    {
        emit playSound("powerup");
        bigMario = true;
        f_ireMario = false;
        littleMario = false;
    }
    else if(number == 4)
    {
        emit playSound("powerup");
        fireMario = new rdv_fire_mario;
        fireMario->setPos(m_player->pos().x(),m_player->pos().y());
        fireMario->addDirection(m_player->direction());
        addItem(fireMario);
        f_ireMario = true;
        bigMario = false;
        littleMario = false;
    }
    else if(number == 5)
    {
        emit playSound("powerup");
        f_ireMario = true;
        bigMario = false;
        littleMario = false;
    }
    else if(number == 6)
    {
        emit playSound("shrink");
        m_smallPlayer = new rdv_small_mario;
        m_smallPlayer->setPos(fireMario->pos().x(),fireMario->pos().y()+28);
        m_smallPlayer->addDirection(fireMario->direction());
        addItem(m_smallPlayer);
        bigMario = false;
        f_ireMario = false;
        littleMario = true;
    }
    else
    {
        return;
    }
}

void rdv_scene::checkTimer()
{
    if(bigMario)
    {
        if (0 == m_player->direction())
        {
            m_player->stand();
            m_timer.stop();
        }
        else if (!m_timer.isActive())
        {
            m_timer.start();
            m_player->walk();
        }
    }
    else if(littleMario)
    {
        if (0 == m_smallPlayer->direction())
        {
            m_smallPlayer->stand();
            m_timer.stop();
        }
        else if (!m_timer.isActive())
        {
            m_timer.start();
            m_smallPlayer->walk();
        }
    }
    else if(f_ireMario)
    {
        if (0 == fireMario->direction())
        {
            fireMario->stand();
            m_timer.stop();
        }
        else if (!m_timer.isActive())
        {
            m_timer.start();
            fireMario->walk();
        }
    }
}

void rdv_scene::movePlayer()
{
    checkCollidingCoin();
    checkCollidingMushroomQuestBox();
    checkCollidingFlowerQuestBox();
    checkCollidingQuestBox();
    checkCollidingStairBlock();
    checkCollidingFlag();
    checkCollidingWarpTube();

    if(bigMario)
    {
        if(m_player->isFalling())
        {
            return;
        }
    }
    else if(littleMario)
    {
        if(m_smallPlayer->isFalling())
        {
            return;
        }
    }
    else if(f_ireMario)
    {
        if(fireMario->isFalling())
        {
            return;
        }
    }

    if(bigMario)
    {
        m_player->nextFrame();
    }
    else if(littleMario)
    {
        m_smallPlayer->nextFrame();
    }
    else if(f_ireMario){

        fireMario->nextFrame();
    }

    if(bigMario)
    {
        int direction = m_player->direction();
        if (0 == direction)
            return;
    }
    else if(littleMario)
    {
        int direction = m_smallPlayer->direction();
        if (0 == direction)
            return;
    }
    else if(f_ireMario)
    {
        int direction = fireMario->direction();
        if (0 == direction)
            return;
    }

    if(bigMario){
        if(!(m_platform && m_player->isTouchingPlatform(m_platform))&& m_jumpAnimation->state() == QAbstractAnimation::Stopped){
            if(m_platform)
            {
                m_player->fall();
                mFallTimer.start();
            }
        }
    }
    else if(littleMario)
    {
        if(!(m_platform && m_smallPlayer->isTouchingPlatform(m_platform))&& m_jumpAnimation->state() == QAbstractAnimation::Stopped)
        {
            if(m_platform)
            {
                m_smallPlayer->fall();
                mFallTimer.start();
            }
        }
    }
    else if(f_ireMario)
    {
        if(!(m_platform && fireMario->isTouchingPlatform(m_platform))&& m_jumpAnimation->state() == QAbstractAnimation::Stopped)
        {
            if(m_platform){
                fireMario->fall();
                mFallTimer.start();
            }
        }
    }
    else
    {
        return;
    }

    if(bigMario)
    {
        int direction = m_player->direction();
        const int dx = direction * m_velocity;

        if (direction > 0){

            if(m_player->pos().x()==7956){
                return;
            }

            m_player->moveBy(dx, 0);
            int diff = m_player->pos().x() - scroll->value();

            if(diff > 800)
            {
                if(scroll->value() > 6720)
                {
                    qDebug()<<"6720";
                    return;
                }

                scroll->setValue(dx + scroll->value());
                m_sky->setPos(dx + m_sky->pos().x(), 0);
                m_Scene->setPos(dx + m_Scene->pos().x(), m_Scene->y());
                m_countLogo->setPos(dx + m_countLogo->pos().x(), m_countLogo->y());
                m_count->setPos(dx + m_count->pos().x(), m_count->y());
                m_score->setPos(dx + m_score->pos().x(), m_score->y());
                m_gameTimer->setPos(dx + m_gameTimer->pos().x(), m_gameTimer->y());
                m_scoreLogo->setPos(dx + m_scoreLogo->pos().x(), m_scoreLogo->y());
                m_timerLogo->setPos(dx + m_timerLogo->pos().x(), m_timerLogo->y());
                gameover->setPos(dx + gameover->pos().x(), gameover->y());
                courseclear->setPos(dx + courseclear->pos().x(), courseclear->y());
            }
        }

        if (direction < 0)
        {
            if(m_player->pos().x()<0)
            {
                return;
            }

            m_player->moveBy(dx, 0);
            int diff = m_player->pos().x() - scroll->value();

            if(diff < 600){

                if(m_sky->pos().x() == 0)
                {
                    return;
                }

                scroll->setValue(dx + scroll->value());
                m_sky->setPos(dx + m_sky->pos().x(), 0);
                m_Scene->setPos(dx + m_Scene->pos().x(), m_Scene->y());
                m_countLogo->setPos(dx + m_countLogo->pos().x(), m_countLogo->y());
                m_count->setPos(dx + m_count->pos().x(), m_count->y());
                m_score->setPos(dx + m_score->pos().x(), m_score->y());
                m_gameTimer->setPos(dx + m_gameTimer->pos().x(), m_gameTimer->y());
                m_scoreLogo->setPos(dx + m_scoreLogo->pos().x(), m_scoreLogo->y());
                m_timerLogo->setPos(dx + m_timerLogo->pos().x(), m_timerLogo->y());
                gameover->setPos(dx + gameover->pos().x(), gameover->y());
                courseclear->setPos(dx + courseclear->pos().x(), courseclear->y());
            }
        }
    }
    else if (littleMario)
    {
        int direction = m_smallPlayer->direction();
        const int dx = direction * m_velocity;

        if (direction > 0)
        {
            if(m_smallPlayer->pos().x()==7956)
            {
                return;
            }

            m_smallPlayer->moveBy(dx, 0);
            int diff2 = m_smallPlayer->pos().x() - scroll->value();

            if(diff2 > 800)
            {
                if(scroll->value() > 6720)
                {
                    qDebug()<<"6720";
                    return;
                }

                scroll->setValue(dx + scroll->value());
                m_sky->setPos(dx + m_sky->pos().x(), 0);
                m_Scene->setPos(dx + m_Scene->pos().x(), m_Scene->y());
                m_countLogo->setPos(dx + m_countLogo->pos().x(), m_countLogo->y());
                m_count->setPos(dx + m_count->pos().x(), m_count->y());
                m_score->setPos(dx + m_score->pos().x(), m_score->y());
                m_gameTimer->setPos(dx + m_gameTimer->pos().x(), m_gameTimer->y());
                m_scoreLogo->setPos(dx + m_scoreLogo->pos().x(), m_scoreLogo->y());
                m_timerLogo->setPos(dx + m_timerLogo->pos().x(), m_timerLogo->y());
                gameover->setPos(dx + gameover->pos().x(), gameover->y());
                courseclear->setPos(dx + courseclear->pos().x(), courseclear->y());
            }
        }

        if (direction < 0)
        {
            if(m_smallPlayer->pos().x()<0)
            {
                return;
            }

            m_smallPlayer->moveBy(dx, 0);
            int diff2 = m_smallPlayer->pos().x() - scroll->value();

            if(diff2 < 600)
            {
                if(m_sky->pos().x() == 0)
                {
                    return;
                }

                scroll->setValue(dx + scroll->value());
                m_sky->setPos(dx + m_sky->pos().x(), 0);
                m_Scene->setPos(dx + m_Scene->pos().x(), m_Scene->y());
                m_countLogo->setPos(dx + m_countLogo->pos().x(), m_countLogo->y());
                m_count->setPos(dx + m_count->pos().x(), m_count->y());
                m_score->setPos(dx + m_score->pos().x(), m_score->y());
                m_gameTimer->setPos(dx + m_gameTimer->pos().x(), m_gameTimer->y());
                m_scoreLogo->setPos(dx + m_scoreLogo->pos().x(), m_scoreLogo->y());
                m_timerLogo->setPos(dx + m_timerLogo->pos().x(), m_timerLogo->y());
                gameover->setPos(dx + gameover->pos().x(), gameover->y());
                courseclear->setPos(dx + courseclear->pos().x(), courseclear->y());
            }
        }
    }

    else if (f_ireMario)
    {
        int direction = fireMario->direction();
        const int dx = direction * m_velocity;
        if (direction > 0)
        {
            if(fireMario->pos().x()==7956)
            {
                return;
            }

            fireMario->moveBy(dx, 0);
            int diff2 = fireMario->pos().x() - scroll->value();

            if(diff2 > 800)
            {
                if(scroll->value() > 6720)
                {
                    qDebug()<<"6720";
                    return;
                }

                scroll->setValue(dx + scroll->value());
                m_sky->setPos(dx + m_sky->pos().x(), 0);
                m_Scene->setPos(dx + m_Scene->pos().x(), m_Scene->y());
                m_countLogo->setPos(dx + m_countLogo->pos().x(), m_countLogo->y());
                m_count->setPos(dx + m_count->pos().x(), m_count->y());
                m_score->setPos(dx + m_score->pos().x(), m_score->y());
                m_gameTimer->setPos(dx + m_gameTimer->pos().x(), m_gameTimer->y());
                m_scoreLogo->setPos(dx + m_scoreLogo->pos().x(), m_scoreLogo->y());
                m_timerLogo->setPos(dx + m_timerLogo->pos().x(), m_timerLogo->y());
                gameover->setPos(dx + gameover->pos().x(), gameover->y());
                courseclear->setPos(dx + courseclear->pos().x(), courseclear->y());
            }
        }

        if (direction < 0)
        {
            if(fireMario->pos().x()<0)
            {
                return;
            }

            fireMario->moveBy(dx, 0);
            int diff2 = fireMario->pos().x() - scroll->value();

            if(diff2 < 600)
            {
                if(m_sky->pos().x() == 0)
                {
                    return;
                }

                scroll->setValue(dx + scroll->value());
                m_sky->setPos(dx + m_sky->pos().x(), 0);
                m_Scene->setPos(dx + m_Scene->pos().x(), m_Scene->y());
                m_countLogo->setPos(dx + m_countLogo->pos().x(), m_countLogo->y());
                m_count->setPos(dx + m_count->pos().x(), m_count->y());
                m_score->setPos(dx + m_score->pos().x(), m_score->y());
                m_gameTimer->setPos(dx + m_gameTimer->pos().x(), m_gameTimer->y());
                m_scoreLogo->setPos(dx + m_scoreLogo->pos().x(), m_scoreLogo->y());
                m_timerLogo->setPos(dx + m_timerLogo->pos().x(), m_timerLogo->y());
                gameover->setPos(dx + gameover->pos().x(), gameover->y());
                courseclear->setPos(dx + courseclear->pos().x(), courseclear->y());
            }
        }
    }

    else
    {
        return;
    }
}

void rdv_scene::fallPlayer()
{
    if(bigMario)
    {
        m_player->setPos(m_player->pos().x(), m_player->pos().y() +30);
        QGraphicsItem* item = collidingPlatforms();
        if(item && handleCollisionWithPlatform())
        {
            mFallTimer.stop();
            m_player->walk();
        }
        else if(m_player->pos().y() + m_player->boundingRect().height() >= m_groundLevel)
        {
            m_player->setPos(m_player->pos().x(), m_groundLevel - m_player->boundingRect().height());
            mFallTimer.stop();
            m_player->walk();
            m_platform = 0;
        }
    }
    else if(littleMario)
    {
        m_smallPlayer->setPos(m_smallPlayer->pos().x(), m_smallPlayer->pos().y() +30);
        QGraphicsItem* item = collidingPlatforms();
        if(item && handleCollisionWithPlatform())
        {
            mFallTimer.stop();
            m_smallPlayer->walk();

        }
        else if(m_smallPlayer->pos().y() + m_smallPlayer->boundingRect().height() >= m_groundLevel)
        {
            m_smallPlayer->setPos(m_smallPlayer->pos().x(), m_groundLevel - m_smallPlayer->boundingRect().height());
            mFallTimer.stop();
            m_smallPlayer->walk();
            m_platform = 0;
        }
    }
    else if(f_ireMario)
    {
        fireMario->setPos(fireMario->pos().x(), fireMario->pos().y()+30);
        QGraphicsItem* item = collidingPlatforms();
        if(item && handleCollisionWithPlatform())
        {
            mFallTimer.stop();
            fireMario->walk();
        }
        else if(fireMario->pos().y() + fireMario->boundingRect().height() >= m_groundLevel)
        {
            fireMario->setPos(fireMario->pos().x(), m_groundLevel - fireMario->boundingRect().height());
            mFallTimer.stop();
            fireMario->walk();
            m_platform = 0;
        }
    }
}

void rdv_scene::jumpPlayer()
{

}

void rdv_scene::jumpStatusChanged(QAbstractAnimation::State newState, QAbstractAnimation::State oldState)
{

}

void rdv_scene::checkCollidingCoin()
{
    if(bigMario)
    {
        QList<QGraphicsItem*> items = collidingItems(m_player);
        foreach (QGraphicsItem* item, items){
            rdv_coin* c = qgraphicsitem_cast<rdv_coin*>(item);
            if(c)
            {
                removeItem(c);
                emit playSound("coin");
                m_count->increase();
                m_score->increase();
            }
        }
    }
    else if(littleMario)
    {
        QList<QGraphicsItem*> items = collidingItems(m_smallPlayer);
        foreach (QGraphicsItem* item, items){
            rdv_coin* c = qgraphicsitem_cast<rdv_coin*>(item);
            if(c)
            {
                removeItem(c);
                emit playSound("coin");
                m_count->increase();
                m_score->increase();
            }
        }
    }
    else if(f_ireMario)
    {
        QList<QGraphicsItem*> items = collidingItems(fireMario);
        foreach (QGraphicsItem* item, items){
            rdv_coin* c = qgraphicsitem_cast<rdv_coin*>(item);
            if(c){
                removeItem(c);
                emit playSound("coin");
                m_count->increase();
                m_score->increase();
            }
        }
    }
}

void rdv_scene::checkCollidingMushroomQuestBox()
{
    if(bigMario)
    {
        QList<QGraphicsItem*> items = collidingItems(m_player);
        foreach (QGraphicsItem* item, items)
        {
            rdv_mushroom_box* q = qgraphicsitem_cast<rdv_mushroom_box*>(item);
            if(q)
            {
                if(m_player->isTouchingHead(q))
                {
                    emit spawnMushroom();
                    emit playSound("sprout");
                    m_score->increase();
                }
            }
        }
    }
    else if(littleMario)
    {
        QList<QGraphicsItem*> items = collidingItems(m_smallPlayer);
        foreach (QGraphicsItem* item, items)
        {
            rdv_mushroom_box* qp = qgraphicsitem_cast<rdv_mushroom_box*>(item);
            if(qp){
                if(m_smallPlayer->isTouchingHead(qp))
                {
                    emit spawnMushroom();
                    emit playSound("sprout");
                    m_score->increase();
                }
            }
        }
    }
    else if(f_ireMario)
    {
        QList<QGraphicsItem*> items = collidingItems(fireMario);
        foreach (QGraphicsItem* item, items)
        {
            rdv_mushroom_box* fp = qgraphicsitem_cast<rdv_mushroom_box*>(item);
            if(fp)
            {
                if(fireMario->isTouchingHead(fp))
                {
                    //emit spawnMushroom();
                    emit playSound("coin");
                    m_score->increase();
                }
            }
        }
    }
}

void rdv_scene::checkCollidingFlowerQuestBox()
{
    if(bigMario)
    {
        QList<QGraphicsItem*> items = collidingItems(m_player);
        foreach (QGraphicsItem* item, items)
        {
            rdv_flower_box* f = qgraphicsitem_cast<rdv_flower_box*>(item);
            if(f)
            {
                if(m_player->isTouchingHead(f))
                {
                    emit spawnFlower();
                    emit playSound("fsprout");
                    m_score->increase();
                }
            }
        }
    }
    else if(littleMario)
    {
        QList<QGraphicsItem*> items = collidingItems(m_smallPlayer);
        foreach (QGraphicsItem* item, items)
        {
            rdv_flower_box* fp = qgraphicsitem_cast<rdv_flower_box*>(item);
            if(fp)
            {
                if(m_smallPlayer->isTouchingHead(fp))
                {
                    //emit spawnFlower();
                    emit playSound("coin");
                    m_score->increase();
                }
            }
        }
    }
    else if(f_ireMario)
    {
        QList<QGraphicsItem*> items = collidingItems(fireMario);
        foreach (QGraphicsItem* item, items)
        {
            rdv_flower_box* fp = qgraphicsitem_cast<rdv_flower_box*>(item);
            if(fp)
            {
                if(fireMario->isTouchingHead(fp))
                {
                    emit spawnFlower();
                    emit playSound("fsprout");
                    m_score->increase();
                }
            }
        }
    }
}

void rdv_scene::checkCollidingQuestBox()
{
    if(bigMario)
    {
        QList<QGraphicsItem*> items = collidingItems(m_player);
        foreach (QGraphicsItem* item, items)
        {
            rdv_question_box* q = qgraphicsitem_cast<rdv_question_box*>(item);
            if(q)
            {
                if(m_player->isTouchingHead(q))
                {
                    emit playSound("coin");
                    m_count->increase();
                    m_score->increase();
                }
            }
        }
    }
    else if(littleMario)
    {
        QList<QGraphicsItem*> items = collidingItems(m_smallPlayer);
        foreach (QGraphicsItem* item, items)
        {
            rdv_question_box* qs = qgraphicsitem_cast<rdv_question_box*>(item);
            if(qs)
            {
                if(m_smallPlayer->isTouchingHead(qs))
                {
                    emit playSound("coin");
                    m_count->increase();
                    m_score->increase();
                }
            }
        }
    }
    else if(f_ireMario)
    {
        QList<QGraphicsItem*> items = collidingItems(fireMario);
        foreach (QGraphicsItem* item, items){
            rdv_question_box* fs = qgraphicsitem_cast<rdv_question_box*>(item);
            if(fs)
            {
                if(fireMario->isTouchingHead(fs))
                {
                    emit playSound("coin");
                    m_count->increase();
                    m_score->increase();
                }
            }
        }
    }
}

void rdv_scene::checkCollidingStairBlock()
{
    if(bigMario)
    {
        QList<QGraphicsItem*> items = collidingItems(m_player);
        foreach (QGraphicsItem* item, items)
        {
            rdv_stair_block* x = qgraphicsitem_cast<rdv_stair_block*>(item);
            if(x)
            {
                if(x->pos().x())
                {
                    if(m_player->pos().x() < x->pos().x())
                        m_player->setPos(x->pos().x()- m_player->boundingRect().width()+5,m_player->pos().y());
                    if(m_player->pos().x() > x->pos().x())
                    {
                        //Bug here. I think mario is touching two different size items. This is causing a set position problem.
                        m_player->setPos(x->pos().x() + m_player->boundingRect().width()+370,m_player->pos().y());
                    }
                }

                if(x->pos().y())
                {
                    if(m_player->pos().y() <= x->pos().y())
                        m_player->setPos(m_player->pos().x(),x->pos().y() - m_player->boundingRect().height());
                }
                if(!x->pos().y())
                {
                    x=0;
                }
                if(m_player->pos().y() < m_groundLevel)
                {
                    m_player->fall();
                    mFallTimer.start();
                    return;
                }
                m_player->setPos(m_player->pos().x(), m_player->pos().y());
            }
        }
    }
    else if(littleMario)
    {
        QList<QGraphicsItem*> items = collidingItems(m_smallPlayer);
        foreach (QGraphicsItem* item, items) {
            rdv_stair_block* x = qgraphicsitem_cast<rdv_stair_block*>(item);
            if(x)
            {
                if(x->pos().x())
                {
                    if(m_smallPlayer->pos().x() < x->pos().x())
                        m_smallPlayer->setPos(x->pos().x()- m_smallPlayer->boundingRect().width()+5,m_smallPlayer->pos().y());
                    if(m_smallPlayer->pos().x() > x->pos().x()){
                        //Bug here. I think mario is touching two different size items. This is causing a set position problem.
                        m_smallPlayer->setPos(x->pos().x() + m_smallPlayer->boundingRect().width()+370,m_smallPlayer->pos().y());
                    }
                }

                if(x->pos().y())
                {
                    if(m_smallPlayer->pos().y() <= x->pos().y())
                        m_smallPlayer->setPos(m_smallPlayer->pos().x(),x->pos().y() - m_smallPlayer->boundingRect().height());
                }
                if(!x->pos().y())
                {
                    x=0;
                }
                if(m_smallPlayer->pos().y() < m_groundLevel)
                {
                    m_smallPlayer->fall();
                    mFallTimer.start();
                    return;
                }
                m_smallPlayer->setPos(m_smallPlayer->pos().x(), m_smallPlayer->pos().y());
            }
        }
    }
    else if(f_ireMario)
    {
        QList<QGraphicsItem*> items = collidingItems(fireMario);
        foreach (QGraphicsItem* item, items)
        {
            rdv_stair_block* x = qgraphicsitem_cast<rdv_stair_block*>(item);
            if(x)
            {
                if(x->pos().x())
                {
                    if(fireMario->pos().x() < x->pos().x())
                        fireMario->setPos(x->pos().x()- fireMario->boundingRect().width()+5,fireMario->pos().y());
                    if(fireMario->pos().x() > x->pos().x())
                    {
                        //Bug here. I think mario is touching two different size items. This is causing a set position problem.
                        fireMario->setPos(x->pos().x() + fireMario->boundingRect().width()+370,fireMario->pos().y());
                    }
                }

                if(x->pos().y())
                {
                    if(fireMario->pos().y() <= x->pos().y())
                        fireMario->setPos(fireMario->pos().x(),x->pos().y() - fireMario->boundingRect().height());
                }
                if(!x->pos().y())
                {
                    x=0;
                }
                if(fireMario->pos().y() < m_groundLevel)
                {
                    fireMario->fall();
                    mFallTimer.start();
                    return;
                }
                fireMario->setPos(fireMario->pos().x(), fireMario->pos().y());
            }
        }
    }
}

void rdv_scene::checkCollidingFlag()
{
    if(bigMario)
    {
        QList<QGraphicsItem*> items = collidingItems(m_player);
        foreach (QGraphicsItem* item, items)
        {
            rdv_flag* f = qgraphicsitem_cast<rdv_flag*>(item);
            if(f)
            {
                removeItem(f);
                addItem(courseclear);
                emit playSound("stopLevelMusic");
                emit playSound("levelClear");
                QSharedPointer<rdv_level_complete_window> levelCompleteWindow(new rdv_level_complete_window);
                levelCompleteWindow->setFixedSize(557,355);
                levelCompleteWindow->setWindowFlags(((levelCompleteWindow ->windowFlags() | Qt::CustomizeWindowHint)& ~Qt::WindowCloseButtonHint));
                levelCompleteWindow->exec();
            }
        }
    }
    else if(littleMario)
    {
        QList<QGraphicsItem*> items = collidingItems(m_smallPlayer);
        foreach (QGraphicsItem* item, items)
        {
            rdv_flag* f = qgraphicsitem_cast<rdv_flag*>(item);
            if(f)
            {
                removeItem(f);
                addItem(courseclear);
                emit playSound("stopLevelMusic");
                emit playSound("levelClear");
                QSharedPointer<rdv_level_complete_window> levelCompleteWindow(new rdv_level_complete_window);
                levelCompleteWindow->setFixedSize(557,355);
                levelCompleteWindow->setWindowFlags(((levelCompleteWindow ->windowFlags() | Qt::CustomizeWindowHint)& ~Qt::WindowCloseButtonHint));
                levelCompleteWindow->exec();
            }
        }
    }
    else if(f_ireMario)
    {
        QList<QGraphicsItem*> items = collidingItems(fireMario);
        foreach (QGraphicsItem* item, items)
        {
            rdv_flag* f = qgraphicsitem_cast<rdv_flag*>(item);
            if(f)
            {
                removeItem(f);
                addItem(courseclear);
                emit playSound("stopLevelMusic");
                emit playSound("levelClear");
                QSharedPointer<rdv_level_complete_window> levelCompleteWindow(new rdv_level_complete_window);
                levelCompleteWindow->setFixedSize(557,355);
                levelCompleteWindow->setWindowFlags(((levelCompleteWindow ->windowFlags() | Qt::CustomizeWindowHint)& ~Qt::WindowCloseButtonHint));
                levelCompleteWindow->exec();
            }
        }
    }
}

void rdv_scene::checkCollidingWarpTube()
{
    if(bigMario){
        QList<QGraphicsItem*> items = collidingItems(m_player);
        foreach (QGraphicsItem* item, items)
        {
            rdv_warp_tube* w = qgraphicsitem_cast<rdv_warp_tube*>(item);
            if(w)
            {
                if(w->pos().x())
                {
                    if(m_player->pos().x() < w->pos().x())
                        m_player->setPos(w->pos().x()- m_player->boundingRect().width(),m_player->pos().y());
                    if(m_player->pos().x() > w->pos().x())
                    {
                        m_player->setPos(w->pos().x() + m_player->boundingRect().width()+25,m_player->pos().y());
                    }
                }
            }
        }
    }
    else if(littleMario)
    {
        QList<QGraphicsItem*> items = collidingItems(m_smallPlayer);
        foreach (QGraphicsItem* item, items) {

            rdv_warp_tube* w = qgraphicsitem_cast<rdv_warp_tube*>(item);
            if(w)
            {
                if(w->pos().x())
                {
                    if(m_smallPlayer->pos().x() < w->pos().x())
                        m_smallPlayer->setPos(w->pos().x()- m_smallPlayer->boundingRect().width(),m_smallPlayer->pos().y());
                    if(m_smallPlayer->pos().x() > w->pos().x())
                    {
                        m_smallPlayer->setPos(w->pos().x() + m_smallPlayer->boundingRect().width()+25,m_smallPlayer->pos().y());
                    }
                }
            }
        }
    }
    else if(f_ireMario)
    {
        QList<QGraphicsItem*> items = collidingItems(fireMario);
        foreach (QGraphicsItem* item, items)
        {
            rdv_warp_tube* w = qgraphicsitem_cast<rdv_warp_tube*>(item);
            if(w){
                if(w->pos().x())
                {
                    if(fireMario->pos().x() < w->pos().x())
                        fireMario->setPos(w->pos().x()- fireMario->boundingRect().width(),fireMario->pos().y());
                    if(fireMario->pos().x() > w->pos().x())
                    {
                        fireMario->setPos(w->pos().x() + fireMario->boundingRect().width()+25,fireMario->pos().y());
                    }
                }
            }
        }
    }
}

void rdv_scene::controlMushroom()
{
    if(bigMario)
    {
        m_mushroom2 = new rdv_mushroom(QRectF(mushroomQuestBox->pos(), mushroomQuestBox->boundingRect().size()), 1);
        m_mushroom2->setPos(204, m_groundLevel - m_mushroom2->boundingRect().height()-100);
        m_mushroom2->setZValue(0);
        addItem(m_mushroom2);
        connect(this->m_mushroom2, SIGNAL(marioSizeStatus(int)),this, SLOT(setMarioSize(int)));
    }
    else if(littleMario)
    {
        m_mushroom2 = new rdv_mushroom(QRectF(mushroomQuestBox->pos(), mushroomQuestBox->boundingRect().size()), 1);
        m_mushroom2->setPos(204, m_groundLevel - m_mushroom2->boundingRect().height()-100);
        m_mushroom2->setZValue(0);
        addItem(m_mushroom2);
        connect(this->m_mushroom2, SIGNAL(marioSizeStatus(int)),this, SLOT(setMarioSize(int)));
    }
    else if(f_ireMario)
    {
        m_mushroom2 = new rdv_mushroom(QRectF(mushroomQuestBox->pos(), mushroomQuestBox->boundingRect().size()), 1);
        m_mushroom2->setPos(204, m_groundLevel - m_mushroom2->boundingRect().height()-100);
        m_mushroom2->setZValue(0);
        addItem(m_mushroom2);
        connect(this->m_mushroom2, SIGNAL(marioSizeStatus(int)),this, SLOT(setMarioSize(int)));
    }
    else
    {
        return;
    }
}

void rdv_scene::controlFlower()
{
    if(bigMario)
    {
        flower = new rdv_flower(QRectF(flowerQuestBox->pos(), flowerQuestBox->boundingRect().size()), 1);
        flower->setPos(1090, m_groundLevel - flower->boundingRect().height()-250);
        flower->setZValue(2);
        addItem(flower);
        connect(this->flower, SIGNAL(marioSizeStatusf(int)),this, SLOT(setMarioSize(int)));
    }
    else if(f_ireMario)
    {
        flower = new rdv_flower(QRectF(flowerQuestBox->pos(), flowerQuestBox->boundingRect().size()), 1);
        flower->setPos(1090, m_groundLevel - flower->boundingRect().height()-250);
        flower->setZValue(2);
        addItem(flower);
        connect(this->flower, SIGNAL(marioSizeStatusf(int)),this, SLOT(setMarioSize(int)));
    }
    else if(littleMario)
    {
        return;
    }
    else
    {
        return;
    }
}

void rdv_scene::setJumpFactor(const qreal &jumpFactor)
{
    if (m_jumpFactor == jumpFactor)
        return;

    m_jumpFactor = jumpFactor;
    emit jumpFactorChanged(m_jumpFactor);
}

void rdv_scene::keyPressEvent(QKeyEvent *event)
{
    if (event->isAutoRepeat())
        return;

    switch (event->key())
    {
    case Qt::Key_Right:
        if(bigMario)
        {
            m_player->addDirection(1);
            m_player->addStandingDirection(1);
            checkTimer();
            break;
        }
        else if(littleMario)
        {
            m_smallPlayer->addDirection(1);
            m_smallPlayer->addStandingDirection(1);
            checkTimer();
            break;
        }
        else if(f_ireMario)
        {
            fireMario->addDirection(1);
            fireMario->addStandingDirection(1);
            checkTimer();
            break;
        }
        else
        {
            break;
        }
    case Qt::Key_Left:
        if(bigMario)
        {
            m_player->addDirection(-1);
            m_player->addStandingDirection(-1);
            checkTimer();
            break;
        }
        else if(littleMario)
        {
            m_smallPlayer->addDirection(-1);
            m_smallPlayer->addStandingDirection(-1);
            checkTimer();
            break;
        }
        else if(f_ireMario)
        {
            fireMario->addDirection(-1);
            fireMario->addStandingDirection(-1);
            checkTimer();
            break;
        }
        else
        {
            break;
        }
    case Qt::Key_F:
        if(f_ireMario)
        {
            if((fireMario->direction() == 0) && (fireMario->standingDirection() == -1))
            {
                fireBall = new rdv_fire_ball(fireMario->standingDirection());
                fireMario->standShoot();
                fireBall->setPos(fireMario->pos().x()-30,  fireMario->pos().y()+20);
                addItem(fireBall);
                connect(this->fireBall, SIGNAL(increaseTheScore(int)),this, SLOT(scoreIncrease(int)));
                connect(this->fireBall, SIGNAL(fireballCollision()),this, SLOT(playHitWarp()));
                connect(this->fireBall, SIGNAL(collideGoomba()),this, SLOT(playHitWarp()));
                emit playSound("fireball");
                break;
            }
            else if((fireMario->direction() == 0) && (fireMario->standingDirection() != -1))
            {
                fireBall = new rdv_fire_ball(1);
                fireMario->standShoot();
                fireBall->setPos(fireMario->pos().x()+45,  fireMario->pos().y()+20);
                addItem(fireBall);
                connect(this->fireBall, SIGNAL(increaseTheScore(int)),this, SLOT(scoreIncrease(int)));
                connect(this->fireBall, SIGNAL(fireballCollision()),this, SLOT(playHitWarp()));
                connect(this->fireBall, SIGNAL(collideGoomba()),this, SLOT(playHitWarp()));
                emit playSound("fireball");
                break;
            }
            else if((fireMario->direction() == 1) && (fireMario->standingDirection() != -1))
            {
                fireBall = new rdv_fire_ball(1);
                fireMario->walk();
                fireBall->setPos(fireMario->pos().x()+70, fireMario->pos().y()+17);
                addItem(fireBall);
                connect(this->fireBall, SIGNAL(increaseTheScore(int)),this, SLOT(scoreIncrease(int)));
                connect(this->fireBall, SIGNAL(fireballCollision()),this, SLOT(playHitWarp()));
                connect(this->fireBall, SIGNAL(collideGoomba()),this, SLOT(playHitWarp()));
                emit playSound("fireball");
                break;
            }
            else if((fireMario->direction() == -1) && (fireMario->standingDirection() == -1))
            {
                fireBall = new rdv_fire_ball(fireMario->standingDirection());
                fireMario->walk();
                fireBall->setPos(fireMario->pos().x()-70,  fireMario->pos().y()+35);
                addItem(fireBall);
                connect(this->fireBall, SIGNAL(increaseTheScore(int)),this, SLOT(scoreIncrease(int)));
                connect(this->fireBall, SIGNAL(fireballCollision()),this, SLOT(playHitWarp()));
                connect(this->fireBall, SIGNAL(collideGoomba()),this, SLOT(playHitWarp()));
                emit playSound("fireball");
                break;
            }
        }
        else if(bigMario)
        {
            if((m_player->direction() == 0) && (m_player->standingDirection() == -1))
            {
                break;
            }
            else if((m_player->direction() == 0) && (m_player->standingDirection() != -1))
            {
                break;
            }
            else if((m_player->direction() == 1) && (m_player->standingDirection() != -1))
            {
                break;
            }
            else if((m_player->direction() == -1) && (m_player->standingDirection() == -1))
            {
                break;
            }
        }
        else if(littleMario)
        {
            if((m_smallPlayer->direction() == 0) && (m_smallPlayer->standingDirection() == -1))
            {
                break;
            }
            else if((m_smallPlayer->direction() == 0) && (m_smallPlayer->standingDirection() != -1))
            {
                break;
            }
            else if((m_smallPlayer->direction() == 1) && (m_smallPlayer->standingDirection() != -1))
            {
                break;
            }
            else if((m_smallPlayer->direction() == -1) && (m_smallPlayer->standingDirection() == -1))
            {
                break;
            }
        }
        break;
    case Qt::Key_Space:
        if(bigMario)
        {
            if(mFallTimer.isActive())
            {
                return;
            }
            else
            {
                if (QAbstractAnimation::Stopped == m_jumpAnimation->state())
                {
                    m_jumpAnimation->start();
                    emit playSound("mario_jump");
                }
            }
            break;
        }
        else if(littleMario)
        {
            if(mFallTimer.isActive())
            {
                return;
            }
            else{
                if (QAbstractAnimation::Stopped == m_jumpAnimation->state())
                {
                    m_jumpAnimation->start();
                    emit playSound("mario_jump");
                }
            }
            break;
        }
        else if(f_ireMario)
        {
            if(mFallTimer.isActive())
            {
                return;
            }
            else
            {
                if (QAbstractAnimation::Stopped == m_jumpAnimation->state())
                {
                    m_jumpAnimation->start();
                    emit playSound("mario_jump");
                }
            }
            break;
        }
        break;
    default:
        break;
    }
}

void rdv_scene::keyReleaseEvent(QKeyEvent *event)
{
    if (event->isAutoRepeat())
        return;

    switch (event->key())
    {
    case Qt::Key_Right:
        if(bigMario)
        {
            m_player->addDirection(-1);
            m_player->addStandingDirection(1);
            checkTimer();
            break;
        }
        else if(littleMario)
        {
            m_smallPlayer->addDirection(-1);
            checkTimer();
            break;
        }
        else if(f_ireMario)
        {
            fireMario->addDirection(-1);
            fireMario->addStandingDirection(1);
            checkTimer();
            break;
        }
        break;
    case Qt::Key_Left:
        if(bigMario)
        {
            m_player->addDirection(1);
            m_player->addStandingDirection(-1);
            checkTimer();
            break;
        }
        else if(littleMario)
        {
            m_smallPlayer->addDirection(1);
            checkTimer();
            break;
        }
        else if(f_ireMario)
        {
            fireMario->addDirection(1);
            fireMario->addStandingDirection(-1);
            checkTimer();
            break;
        }
        break;
    default:
        break;
    }
}
