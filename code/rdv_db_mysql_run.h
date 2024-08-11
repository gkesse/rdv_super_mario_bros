#pragma once

#include "rdv_objects.h"

class rdv_db_mysql_run
{
    friend class rdv_db_mysql;

private:
	explicit rdv_db_mysql_run(const QSqlDatabase& _dbSQL);
	~rdv_db_mysql_run();
	void run();

private:
    QSqlDatabase m_dbSQL;
};
