#include "rdv_db_mysql_run.h"

rdv_db_mysql_run::rdv_db_mysql_run(const QSqlDatabase& _dbSQL)
: m_dbSQL(_dbSQL)
{

}

rdv_db_mysql_run::~rdv_db_mysql_run()
{
    m_dbSQL.close();
}

void rdv_db_mysql_run::run()
{

}
