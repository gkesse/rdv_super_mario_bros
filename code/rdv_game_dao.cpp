#include "rdv_game_dao.h"
#include "rdv_db_mysql.h"

rdv_game_dao::rdv_game_dao()
{

}

rdv_game_dao::~rdv_game_dao()
{

}

void rdv_game_dao::registerUser(const QString& _username, const QString& _password)
{
    if(!checkUser(_username))
    {
        if(m_errors.hasErrors()) return;

        QString password = _username + "|" + _password;

        rdv_db_mysql dbSQL;
        dbSQL.addParam(":username", _username);
        dbSQL.addParam(":password", password);
        dbSQL.insertQuery(""
                "insert into _users "
                "(_username, _password) values "
                "(:username, SHA1 (:password))"
                "");
        m_errors.addErrors(dbSQL.getErrors());
        if(m_errors.hasErrors()) return;
    }
}

QString rdv_game_dao::getUsername() const
{
    rdv_db_mysql dbSQL;
    rdv_db_mysql_map dataMap = dbSQL.readQuery(""
            "select _username from _users "
            ""
            "");
    return "";
}

bool rdv_game_dao::checkUser(const QString& _username)
{
    rdv_db_mysql dbSQL;
    dbSQL.addParam(":username", _username);
    dbSQL.readQuery(""
            "select _username from _users "
            "where _username = :username"
            "");
    m_errors.addErrors(dbSQL.getErrors());
    if(m_errors.hasErrors()) return false;

    if(dbSQL.getCountRows() == 1)
    {
        qDebug() << "Ce nom d'utilisateur existe deja."
        "|username=" << _username;
        m_errors.addProblem();
        return true;
    }
    if(dbSQL.getCountRows() > 1)
    {
        qDebug() << "Plusieurs utilisateurs possedent le meme identifiant."
        "|username=" << _username;
        m_errors.addProblem();
        return true;
    }
    return false;
}

