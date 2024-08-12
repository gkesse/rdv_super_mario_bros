#pragma once

#include "rdv_objects.h"

class rdv_pixmap_painter;
class rdv_coin;
class rdv_question_box;

class rdv_pixmap_painter : public QGraphicsPixmapItem
{
public:
    explicit rdv_pixmap_painter(const QPixmap &pixmap, QGraphicsItem *parent = 0);

public:
    virtual QPainterPath shape() const;
};

class rdv_scene : public QGraphicsScene
{
	Q_OBJECT

public:
	explicit rdv_scene(QObject* _parent = nullptr);
	~rdv_scene();
	void timerEvent([[maybe_unused]] QTimerEvent *event);

	const rdv_errors& getErrors() const     {return m_errors;}

private:
	void initPlayField();

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

    rdv_errors m_errors;
};
