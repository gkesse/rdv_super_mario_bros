#include "rdv_user_registration.h"
#include "ui_rdv_user_registration.h"
#include "rdv_game_dao.h"
#include "rdv_globals.h"

rdv_user_registration::rdv_user_registration(QWidget* _parent)
: QDialog(_parent)
, ui(new Ui::rdv_user_registration)
{
    ui->setupUi(this);
}

rdv_user_registration::~rdv_user_registration()
{
    delete ui;
}

void rdv_user_registration::on_btnCancel_clicked()
{
    reject();
}

void rdv_user_registration::on_radPassword_clicked(bool checked)
{
    if(checked)
    {
        ui->edtPassword->setEchoMode(QLineEdit::Normal);
    }
    else
    {
        ui->edtPassword->setEchoMode(QLineEdit::Password);
    }
}

void rdv_user_registration::on_btnSubmit_clicked()
{
    QString username = ui->edtUsername->text();
    QString password = ui->edtPassword->text();

    if(username.isEmpty())
    {
        qDebug() << "Le nom d'utilisateur est obligatoire.";
        m_errors.addProblem();
        return;
    }

    if(!rdv_globals::isValidEmail(username))
    {
        qDebug() << "Le nom d'utilisateur n'est pas une adresse email valide.";
        m_errors.addProblem();
        return;
    }
    if(password.isEmpty())
    {
        qDebug() << "Le mot de passe est obligatoire.";
        m_errors.addProblem();
        return;
    }
    if(!rdv_globals::isValidPassword(password))
    {
        qDebug() << "Le mot de passe n'est pas valide.";
        m_errors.addProblem();
        return;
    }

    rdv_game_dao dao;
    dao.registerUser(username, password);
    m_errors.addErrors(dao.getErrors());
    if(m_errors.hasErrors()) return;

    qInfo() << "L'utilisateur a bien ete enregistre.";
    accept();
}
