#pragma once

#include "rdv_db_mysql.h"

class rdv_db_mysql_run
{
    friend class rdv_db_mysql;

private:
	explicit rdv_db_mysql_run(const QSqlDatabase& _dbSQL, const rdv_db_mysql_params& _params);
	~rdv_db_mysql_run();
	rdv_db_mysql_map readQuery(const QString& _sql);
    void execQuery(const QString& _sql);
    void insertQuery(const QString& _sql);

    int getLastInsertId() const             {return m_lastInsertId;}
    int getCountRows() const                {return m_countRows;}
    const rdv_errors& getErrors() const     {return m_errors;}

private:
    QSqlDatabase m_dbSQL;
    rdv_db_mysql_params m_params;
    int m_lastInsertId;
    int m_countRows;
    rdv_errors m_errors;
};
