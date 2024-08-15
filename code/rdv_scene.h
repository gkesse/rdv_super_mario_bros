#pragma once

#include "rdv_objects.h"

class rdv_pixmap_painter;
class rdv_coin;
class rdv_question_box;
class rdv_mushroom_box;
class rdv_flower_box;
class rdv_brick_platform;
class rdv_wall_platform;
class rdv_note_box;
class rdv_goomba;
class rdv_turtle;
class rdv_piranha;
class rdv_flag;
class rdv_score;
class rdv_stretch;
class rdv_conveyor;
class rdv_giant_goomba;
class rdv_warp_tube;
class rdv_stair_block;
class rdv_bomb;
class rdv_red_turtle;
class rdv_spiny;
class rdv_small_mario;
class rdv_coin_counter;
class rdv_timer;
class rdv_castle;
class rdv_player;
class rdv_fire_mario;
class rdv_sound_manager;
class rdv_fire_ball;
class rdv_mushroom;
class rdv_flower;

class rdv_scene : public QGraphicsScene
{
	Q_OBJECT
    Q_PROPERTY(qreal jumpFactor READ jumpFactor WRITE setJumpFactor NOTIFY jumpFactorChanged)

public:
	explicit rdv_scene(QScrollBar *_scroll, QObject* _parent = nullptr);
	~rdv_scene();
	void timerEvent([[maybe_unused]] QTimerEvent *event);
    void setJumpFactor(const qreal &jumpFactor);

    qreal jumpFactor() const                {return m_jumpFactor;}
	const rdv_errors& getErrors() const     {return m_errors;}

protected:
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);

private:
	void initPlayField();
    QGraphicsItem* collidingPlatforms();
    bool handleCollisionWithPlatform();

private slots:
	void setMarioSize(int);
	void checkTimer();
	void movePlayer();
	void fallPlayer();
	void jumpPlayer();
    void jumpStatusChanged(QAbstractAnimation::State newState, QAbstractAnimation::State oldState);
    void checkCollidingCoin();
    void checkCollidingMushroomQuestBox();
    void checkCollidingFlowerQuestBox();
    void checkCollidingQuestBox();
    void checkCollidingStairBlock();
    void checkCollidingFlag();
    void checkCollidingWarpTube();
    void controlMushroom();
    void controlFlower();

signals:
    void playSound(QString);
    void jumpFactorChanged(qreal);
    void spawnMushroom();
    void spawnFlower();

private:
    qreal m_groundLevel;

    rdv_pixmap_painter *m_sky;
    rdv_pixmap_painter *gameover;
    rdv_pixmap_painter *courseclear;
    rdv_pixmap_painter *m_ground;
    rdv_pixmap_painter *m_Scene;
    rdv_pixmap_painter *m_countLogo;
    rdv_pixmap_painter *m_scoreLogo;
    rdv_pixmap_painter *m_timerLogo;
    rdv_pixmap_painter *m_wall2;
    rdv_pixmap_painter *m_wall;
    rdv_pixmap_painter *m_wall3;
    rdv_pixmap_painter *m_flag;
    rdv_pixmap_painter *m_castle;

    rdv_coin  *m_coins;
    rdv_coin  *m_coins2;
    rdv_coin  *m_coins3;
    rdv_coin  *m_coins4;
    rdv_coin  *m_coins5;
    rdv_coin  *m_coins6;
    rdv_coin  *m_coins7;
    rdv_coin  *m_coins8;
    rdv_coin  *m_coins9;
    rdv_coin  *m_coins10;
    rdv_coin  *m_coins11;
    rdv_coin  *m_coins12;
    rdv_coin  *m_coins13;
    rdv_coin  *m_coins14;
    rdv_coin  *m_coins15;
    rdv_coin  *m_coins16;
    rdv_coin  *m_coins17;
    rdv_coin  *m_coins18;
    rdv_coin  *m_coins19;
    rdv_coin  *m_coins20;
    rdv_coin  *m_coins21;
    rdv_coin  *m_coins22;
    rdv_coin  *m_coins23;
    rdv_coin  *m_coins24;
    rdv_coin  *m_coins25;
    rdv_coin  *m_coins26;

    rdv_coin  *m_coins27;
    rdv_coin  *m_coins28;
    rdv_coin  *m_coins29;
    rdv_coin  *m_coins30;

    rdv_coin  *m_coins32;
    rdv_coin  *m_coins33;
    rdv_coin  *m_coins34;
    rdv_coin  *m_coins35;
    rdv_coin  *m_coins36;

    rdv_coin  *m_coins37;
    rdv_coin  *m_coins38;
    rdv_coin  *m_coins39;
    rdv_coin  *m_coins40;
    rdv_coin  *m_coins41;

    rdv_coin  *m_coins42;
    rdv_coin  *m_coins43;
    rdv_coin  *m_coins44;
    rdv_coin  *m_coins45;
    rdv_coin  *m_coins46;
    rdv_coin  *m_coins47;

    rdv_coin  *m_coins48;
    rdv_coin  *m_coins49;
    rdv_coin  *m_coins50;
    rdv_coin  *m_coins51;
    rdv_coin  *m_coins52;

    rdv_coin  *m_coins53;
    rdv_coin  *m_coins54;
    rdv_coin  *m_coins55;
    rdv_coin  *m_coins56;

    rdv_coin  *m_coins57;
    rdv_coin  *m_coins58;
    rdv_coin  *m_coins59;
    rdv_coin  *m_coins60;

    rdv_coin  *m_coins61;
    rdv_coin  *m_coins62;
    rdv_coin  *m_coins63;
    rdv_coin  *m_coins64;
    rdv_coin  *m_coins65;
    rdv_coin  *m_coins66;
    rdv_coin  *m_coins67;
    rdv_coin  *m_coins68;

    rdv_coin  *m_coins69;
    rdv_coin  *m_coins70;
    rdv_coin  *m_coins71;

    rdv_coin  *m_coins72;
    rdv_coin  *m_coins73;
    rdv_coin  *m_coins74;

    rdv_coin  *m_coins75;
    rdv_coin  *m_coins76;
    rdv_coin  *m_coins77;
    rdv_coin  *m_coins78;
    rdv_coin  *m_coins79;
    rdv_coin  *m_coins80;

    rdv_coin  *m_coins81;
    rdv_coin  *m_coins82;
    rdv_coin  *m_coins83;
    rdv_coin  *m_coins84;
    rdv_coin  *m_coins85;
    rdv_coin  *m_coins86;

    rdv_coin  *m_coins87;
    rdv_coin  *m_coins88;
    rdv_coin  *m_coins89;
    rdv_coin  *m_coins90;
    rdv_coin  *m_coins91;
    rdv_coin  *m_coins92;
    rdv_coin  *m_coins93;
    rdv_coin  *m_coins94;
    rdv_coin  *m_coins95;
    rdv_coin  *m_coins96;
    rdv_coin  *m_coins97;
    rdv_coin  *m_coins98;
    rdv_coin  *m_coins99;
    rdv_coin  *m_coins100;

    rdv_question_box *m_questbox;
    rdv_question_box *m_questbox2;
    rdv_question_box *m_questbox3;
    rdv_question_box *m_questbox4;
    rdv_question_box *m_questbox5;
    rdv_question_box *m_questbox6;
    rdv_question_box *m_questbox7;
    rdv_question_box *m_questbox8;

    rdv_question_box *m_questbox9;
    rdv_question_box *m_questbox10;
    rdv_question_box *m_questbox11;

    rdv_question_box *m_questbox12;

    rdv_mushroom_box *mushroomQuestBox;
    rdv_flower_box *flowerQuestBox;

    rdv_brick_platform *mBrickPlatform;
    rdv_brick_platform *mBrickPlatform2;
    rdv_brick_platform *mBrickPlatform3;
    rdv_brick_platform *mBrickPlatform4;
    rdv_brick_platform *mBrickPlatform5;
    rdv_brick_platform *mBrickPlatform6;
    rdv_brick_platform *mBrickPlatform7;
    rdv_brick_platform *mBrickPlatform8;

    rdv_wall_platform *m_wallPlatform;
    rdv_wall_platform *m_wallPlatform2;
    rdv_wall_platform *m_wallPlatform3;
    rdv_wall_platform *m_wallPlatform4;
    rdv_wall_platform *m_wallPlatform5;
    rdv_wall_platform *m_wallPlatform6;
    rdv_wall_platform *m_wallPlatform7;
    rdv_wall_platform *m_wallPlatform8;
    rdv_wall_platform *m_wallPlatform9;
    rdv_wall_platform *m_wallPlatform10;
    rdv_wall_platform *m_wallPlatform11;

    rdv_note_box *m_NoteBox;
    rdv_note_box *m_NoteBox2;
    rdv_note_box *m_NoteBox3;
    rdv_note_box *m_NoteBox4;
    rdv_note_box *m_NoteBox5;
    rdv_note_box *m_NoteBox6;

    rdv_goomba *m_goomba;

    rdv_turtle *m_turtle;
    rdv_turtle *m_turtle2;

    rdv_piranha *m_piranha;
    rdv_piranha *m_piranha2;
    rdv_piranha *m_piranha3;

    rdv_flag *m_flag2;

    rdv_coin_counter *m_count;
    rdv_score *m_score;
    rdv_timer *m_gameTimer;
    rdv_stretch *m_stretch;

    rdv_pixmap_painter *m_sign;

    rdv_conveyor *m_conveyor;
    rdv_conveyor *m_conveyor2;
    rdv_conveyor *m_conveyor3;

    rdv_giant_goomba *m_giantgoomba;
    rdv_giant_goomba *m_giantgoomba2;
    rdv_giant_goomba *m_giantgoomba3;

    rdv_warp_tube *m_warpTube1;
    rdv_warp_tube *m_warpTube2;
    rdv_warp_tube *m_warpTube3;

    rdv_stair_block *m_stairBlock;
    rdv_stair_block *m_stairBlock2;
    rdv_stair_block *m_stairBlock3;
    rdv_stair_block *m_stairBlock4;
    rdv_stair_block *m_stairBlock5;
    rdv_stair_block *m_stairBlock6;
    rdv_stair_block *m_stairBlock7;
    rdv_stair_block *m_stairBlock8;

    rdv_goomba *m_goomba2;
    rdv_bomb *m_bomb2;
    rdv_red_turtle *m_redTurtle;
    rdv_spiny *m_spiny;
    rdv_small_mario *m_smallPlayer;
    rdv_castle *h_castle;

    rdv_player *m_player;
    rdv_fire_mario *fireMario;
    rdv_fire_ball *fireBall;

    bool f_ireMario;
    bool bigMario;
    bool littleMario;
    bool falling;
    bool jumping;

    QTimer m_timer;
    QTimer mFallTimer;
    QPropertyAnimation *m_jumpAnimation;
    rdv_sound_manager *soundManager;

    QGraphicsItem *m_platform;
    QScrollBar *scroll;
    int m_velocity;
    qreal m_jumpFactor;
    rdv_mushroom *m_mushroom2;
    rdv_flower* flower;

    rdv_errors m_errors;
};
