#include "rdv_scene.h"
#include "rdv_coin.h"
#include "rdv_question_box.h"

rdv_scene::rdv_scene(QObject* _parent)
: QGraphicsScene(_parent)
{
    initPlayField();
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

rdv_pixmap_painter::rdv_pixmap_painter(const QPixmap &pixmap, QGraphicsItem * parent)
: QGraphicsPixmapItem(pixmap, parent)
{

}

QPainterPath rdv_pixmap_painter::shape() const
{
    return QPainterPath();
}
