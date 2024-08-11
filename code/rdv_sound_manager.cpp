#include "rdv_sound_manager.h"

rdv_sound_manager::rdv_sound_manager(QWidget* _parent)
: QObject(_parent)
{
    audioOutput = new QAudioOutput(this);

    select = new QSoundEffect(this);
    select->setSource(QUrl("qrc:/audio/Select.wav"));
    select->setLoopCount(0);
    select->setVolume(.25f);

    coin = new QSoundEffect(this);
    coin->setSource(QUrl("qrc:/audio/coin.wav"));
    coin->setLoopCount(0);
    coin->setVolume(.25f);

    mario_jump = new QSoundEffect(this);
    mario_jump->setSource(QUrl("qrc:/audio/jump.wav"));
    mario_jump->setLoopCount(0);
    mario_jump->setVolume(.25f);

    mario_death = new QSoundEffect(this);
    mario_death->setSource(QUrl("qrc:/audio/death.wav"));
    mario_death->setLoopCount(0);
    mario_death->setVolume(.25f);

    levelClear = new QSoundEffect(this);
    levelClear->setSource(QUrl("qrc:/audio/levelclear.wav"));
    levelClear->setLoopCount(0);
    levelClear->setVolume(.25f);

    ghost = new QSoundEffect(this);
    ghost->setSource(QUrl("qrc:/audio/ghost.wav"));
    ghost->setLoopCount(0);
    ghost->setVolume(.25f);

    shrink = new QSoundEffect(this);
    shrink->setSource(QUrl("qrc:/audio/shrink.wav"));
    shrink->setLoopCount(0);
    shrink->setVolume(.25f);

    powerup = new QSoundEffect(this);
    powerup->setSource(QUrl("qrc:/audio/powerup.wav"));
    powerup->setLoopCount(0);
    powerup->setVolume(.25f);

    sprout = new QSoundEffect(this);
    sprout->setSource(QUrl("qrc:/audio/sprout.wav"));
    sprout->setLoopCount(0);
    sprout->setVolume(.25f);

    fsprout = new QSoundEffect(this);
    fsprout->setSource(QUrl("qrc:/audio/sprout.wav"));
    fsprout->setLoopCount(0);
    fsprout->setVolume(.25f);

    kick = new QSoundEffect(this);
    kick ->setSource(QUrl("qrc:/audio/kick.wav"));
    kick ->setLoopCount(0);
    kick ->setVolume(.25f);

    fireball = new QSoundEffect(this);
    fireball->setSource(QUrl("qrc:/audio/fireball.wav"));
    fireball->setLoopCount(0);
    fireball->setVolume(.25f);

    hitWarptube = new QSoundEffect(this);
    hitWarptube->setSource(QUrl("qrc:/audio/hitwarptube.wav"));
    hitWarptube->setLoopCount(0);
    hitWarptube->setVolume(.25f);

    level1 = new QMediaPlayer(this);
    level1->setSource(QUrl("qrc:/audio/level1.mp3"));
    level1->setAudioOutput(audioOutput);

    soundPlayer = new QMediaPlayer(this);
    soundPlayer->setSource(QUrl("qrc:/audio/ThemeSong.mp3"));
    soundPlayer->setAudioOutput(audioOutput);
}

rdv_sound_manager::~rdv_sound_manager()
{

}

void rdv_sound_manager::playSoundEffect(QString which)
{
    if(which == "mario_jump")
    {
        mario_jump->play();
    }
    else if(which == "mario_death")
    {
        level1->stop();
        mario_death->play();
    }
    else if(which == "coin")
    {
        coin->play();
    }
    else if(which == "select")
    {
        select->play();
    }
    else if(which == "theme")
    {
        level1->stop();
        soundPlayer->play();
    }
    else if(which == "level1")
    {
        level1->play();
    }
    else if(which == "stopMusic")
    {
        soundPlayer->stop();
    }
    else if(which == "stopLevelMusic")
    {
        level1->stop();
    }
    else if(which == "levelClear")
    {
        levelClear->play();
    }
    else if(which == "ghost")
    {
        ghost->play();
    }
    else if(which == "shrink"){

        shrink->play();
    }
    else if(which == "powerup")
    {
        powerup->play();
    }
    else if(which == "sprout")
    {
        sprout->play();
    }
    else if(which == "fsprout")
    {
        fsprout->play();
    }
    else if(which == "kick")
    {
        kick->play();
    }
    else if(which == "fireball")
    {
        fireball->play();
    }
    else if(which == "hitWarptube")
    {
        hitWarptube->play();
    }
}
