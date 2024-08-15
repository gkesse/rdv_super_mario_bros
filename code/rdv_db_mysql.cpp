#include "rdv_db_mysql.h"
#include "rdv_db_mysql_run.h"

rdv_db_mysql::rdv_db_mysql()
: m_hostname        (RDV_MYSQL_HOSTNAME)
, m_port            (RDV_MYSQL_PORT)
, m_username        (RDV_MYSQL_USERNAME)
, m_password        (RDV_MYSQL_PASSWORD)
, m_database        (RDV_MYSQL_DATABASE)
, m_lastInsertId    (0)
, m_countRows       (0)
{

}

rdv_db_mysql::~rdv_db_mysql()
{
    QSqlDatabase::removeDatabase(RDV_MYSQL_CONNECTION_NAME);
}


void rdv_db_mysql::addParam(const QString& _key, const QVariant& _value)
{
    m_params[_key] = _value;
}

rdv_db_mysql_map rdv_db_mysql::readQuery(const QString& _sqlQuery)
{
    QSqlDatabase dbSQL = QSqlDatabase::addDatabase("QMYSQL", RDV_MYSQL_CONNECTION_NAME);
    dbSQL.setHostName(m_hostname);
    dbSQL.setPort(m_port);
    dbSQL.setUserName(m_username);
    dbSQL.setPassword(m_password);
    dbSQL.setDatabaseName(m_database);

    if(!dbSQL.open()) {
        qDebug() << "La connexion au serveur de donnees a echoue."
        "|erreurMsg=" << dbSQL.lastError().text();
        m_errors.addProblem();
        return rdv_db_mysql_map();
    }

    rdv_db_mysql_run dbRun(dbSQL, m_params);
    rdv_db_mysql_map dataMap = dbRun.readQuery(_sqlQuery);
    m_countRows = dbRun.getCountRows();
    return dataMap;
}

void rdv_db_mysql::execQuery(const QString& _sqlQuery)
{
    QSqlDatabase dbSQL = QSqlDatabase::addDatabase("QMYSQL", RDV_MYSQL_CONNECTION_NAME);
    dbSQL.setHostName(m_hostname);
    dbSQL.setPort(m_port);
    dbSQL.setUserName(m_username);
    dbSQL.setPassword(m_password);
    dbSQL.setDatabaseName(m_database);

    if(!dbSQL.open()) {
        qDebug() << "La connexion au serveur de donnees a echoue."
        "|erreurMsg=" << dbSQL.lastError().text();
        m_errors.addProblem();
        return;
    }

    rdv_db_mysql_run dbRun(dbSQL, m_params);
    dbRun.execQuery(_sqlQuery);
}

void rdv_db_mysql::insertQuery(const QString& _sqlQuery)
{
    QSqlDatabase dbSQL = QSqlDatabase::addDatabase("QMYSQL", RDV_MYSQL_CONNECTION_NAME);
    dbSQL.setHostName(m_hostname);
    dbSQL.setPort(m_port);
    dbSQL.setUserName(m_username);
    dbSQL.setPassword(m_password);
    dbSQL.setDatabaseName(m_database);

    if(!dbSQL.open()) {
        qDebug() << "La connexion au serveur de donnees a echoue."
        "|erreurMsg=" << dbSQL.lastError().text();
        m_errors.addProblem();
        return;
    }

    rdv_db_mysql_run dbRun(dbSQL, m_params);
    dbRun.insertQuery(_sqlQuery);
    m_lastInsertId = dbRun.getLastInsertId();
}
