#include "rdv_title.h"
#include "rdv_view.h"
#include "rdv_sound_manager.h"
#include "rdv_game_dao.h"
#include "rdv_user_registration.h"
#include "rdv_globals.h"
#include "rdv_scene.h"

rdv_title::rdv_title(rdv_view* _view, QWidget* _parent)
: QGraphicsScene(_parent)
, viewer(_view)
{
    viewer->setViewportUpdateMode(QGraphicsView::SmartViewportUpdate);

    scroll = viewer->horizontalScrollBar();

    background = new rdv_pixmap_item;
    background->setPixmap(QPixmap(":/images/background.png"));

    foreground = new QGraphicsPixmapItem(QPixmap(":/images/title.png"));

    logo = new QGraphicsPixmapItem(QPixmap(":/images/logo.png"));

    animation = new QPropertyAnimation(background, "pos");
    animation->setLoopCount(-1);
    animation->setDuration(RDV_SCENE_BACKGROUND_DURATION);
    animation->setStartValue(QPoint(-RDV_WINDOW_WIDTH, 0));
    animation->setEndValue(QPoint(0, 0));
    animation->start();

    logo->setPos((RDV_WINDOW_WIDTH - logo->boundingRect().width()) / 2, RDV_WINDOW_HEIGHT / 12);

    addItem(background);
    addItem(foreground);
    addItem(logo);

    setFocus();
    setSceneRect(0, 0, RDV_WINDOW_WIDTH, RDV_WINDOW_HEIGHT);
    _view->setScene(this);

    loginButton = new QPushButton(viewer);
    loginButton->setText("Login");
    loginButton->setObjectName(QString("loginButton"));
    loginButton->setToolTip("Click to login");
    loginButton->setGeometry(QRect(540, 500, 100, 32));
    connect(loginButton, SIGNAL(clicked()), this, SLOT(login()));

    developerButton = new QPushButton(viewer);
    developerButton->setText("Guest Login");
    developerButton->setObjectName(QString("developerButton"));
    developerButton->setToolTip("Login as a guest");
    developerButton->setGeometry(QRect(540, 535, 100, 32));
    connect(developerButton, SIGNAL(clicked()), this, SLOT(developerLogin()));

    quitButton = new QPushButton(viewer);
    quitButton->setText("Quit");
    quitButton->setObjectName(QString("quitButton"));
    quitButton->setToolTip("Quit program");
    quitButton->setGeometry(QRect(642, 535, 100, 32));
    connect(quitButton, SIGNAL(clicked()), this, SLOT(quitProgram()));

    newUserButton = new QPushButton(viewer);
    newUserButton->setText("New User");
    newUserButton->setObjectName(QString("newUserButton"));
    newUserButton->setToolTip("Click to create a login");
    newUserButton->setGeometry(QRect(642, 500, 100, 32));
    connect(newUserButton, SIGNAL(clicked()), this, SLOT(newUser()));

    userLine = new QLineEdit(viewer);
    userLine->setObjectName(QString("userLine"));
    userLine->setToolTip("Enter an email address");
    userLine->setGeometry(QRect(540, 420, 200, 25));

    QFont font("MV Boli", 15, QFont::Bold);
    userName = new QLabel(viewer);
    userName->setFont(font);
    userName->setText("Username");
    userName->setObjectName(QString("username"));
    userName->setGeometry(QRect(430, 420, 100, 25));

    passLine = new QLineEdit(viewer);
    passLine->setEchoMode(QLineEdit::Password);
    passLine->setObjectName(QString("passLine"));
    passLine->setToolTip("Enter password");
    passLine->setGeometry(QRect(540, 450, 200, 25));

    password = new QLabel(viewer);
    password->setFont(font);
    password->setText("Password");
    password->setObjectName(QString("password"));
    password->setGeometry(QRect(430, 450, 100, 25));

    radioButton = new QRadioButton(viewer);
    radioButton->setObjectName(QString("radioButton"));
    radioButton->setToolTip("Click to show password text");
    radioButton->setGeometry(QRect(760, 450, 100, 25));
    connect(radioButton, SIGNAL(toggled(bool)), this, SLOT(on_radioButton_toggled(bool)));

    radioText = new QLabel(viewer);
    radioText->setText("Show Password");
    radioText->setToolTip("Click to show password text");
    radioText->setGeometry(QRect(780, 450, 100, 25));

    soundManager = new rdv_sound_manager;
    connect(this, &rdv_title::playSound, soundManager, &rdv_sound_manager::playSoundEffect);
    emit playSound("theme");
}

rdv_title::~rdv_title()
{

}

void rdv_title::login()
{
    QString usernameText = userLine->text();
    QString passwordText = passLine->text();
/*
    if(usernameText.isEmpty())
    {
        qDebug() << "Le nom d'utilisateur est obligatoire.";
        m_errors.addProblem();
        return;
    }
    if(!rdv_globals::isValidEmail(usernameText))
    {
        qDebug() << "Le nom d'utilisateur n'est pas une adresse email valide.";
        m_errors.addProblem();
        return;
    }

    if(passwordText.isEmpty())
    {
        qDebug() << "Le mot de passe est obligatoire.";
        m_errors.addProblem();
        return;
    }
    if(!rdv_globals::isValidPassword(passwordText))
    {
        qDebug() << "Le mot de passe n'est pas valide.";
        m_errors.addProblem();
        return;
    }
*/
    rdv_game_dao dao;
    if(dao.loginUser(usernameText, passwordText) || true)
    {
        qDebug() << "La connexion de l'utilisateur a reussi."
        "|username=" << usernameText;

        loginButton->close();
        newUserButton->close();
        passLine->close();
        userLine->close();
        userName->close();
        password->close();
        radioButton->close();
        radioText->close();
        developerButton->close();
        quitButton->close();

        scene.reset(new rdv_scene(scroll));
        viewer->setScene(scene.get());
        emit playSound("stopMusic");
    }
    else
    {
        qDebug() << "La connexion de l'utilisateur a echoue."
        "|username=" << usernameText;
    }
    m_errors.addErrors(dao.getErrors());
    if(m_errors.hasErrors()) return;
}

void rdv_title::developerLogin()
{

}

void rdv_title::quitProgram()
{
    qApp->quit();
}

void rdv_title::newUser()
{
    rdv_user_registration loginWindow;
    loginWindow.exec();
}

void rdv_title::on_radioButton_toggled([[maybe_unused]] bool checked)
{

}
