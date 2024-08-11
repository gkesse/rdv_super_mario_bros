#include "rdv_db_mysql.h"
#include "rdv_db_mysql_run.h"

rdv_db_mysql::rdv_db_mysql()
: m_hostname("")
, m_username("")
, m_password("")
, m_database("")
{

}

rdv_db_mysql::~rdv_db_mysql()
{

}

void rdv_db_mysql::run()
{
    QSqlDatabase dbSQL = QSqlDatabase::addDatabase("QMYSQL");
    dbSQL.setHostName(m_hostname);
    dbSQL.setDatabaseName(m_database);
    dbSQL.setUserName(m_username);
    dbSQL.setPassword(m_password);

    if(!dbSQL.open()) {
        qDebug() << "La connexion au serveur de donnees a echoue."
        "|erreurMsg=" << dbSQL.lastError().text();
        return;
    }

    rdv_db_mysql_run dbRun(dbSQL);
    dbRun.run();
}
