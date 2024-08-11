#pragma once

#include "rdv_objects.h"

class rdv_sound_manager : public QObject
{
	Q_OBJECT

public:
	explicit rdv_sound_manager(QWidget* _parent = nullptr);
	~rdv_sound_manager();

public slots:
    void playSoundEffect(QString);

private:
    QSoundEffect *select;
    QSoundEffect *coin;
    QSoundEffect *mario_jump;
    QSoundEffect *mario_death;
    QSoundEffect *levelClear;
    QSoundEffect *ghost;
    QSoundEffect *shrink;
    QSoundEffect *powerup;
    QSoundEffect *sprout;
    QSoundEffect *fsprout;
    QSoundEffect *kick;
    QSoundEffect *fireball;
    QSoundEffect *hitWarptube;
    QMediaPlayer *level1;
    QMediaPlayer *soundPlayer;
    QAudioOutput *audioOutput;
};
