#include "rdv_db_mysql_run.h"

rdv_db_mysql_run::rdv_db_mysql_run(const QSqlDatabase& _dbSQL, const rdv_db_mysql_params& _params)
: m_dbSQL           (_dbSQL)
, m_params          (_params)
, m_lastInsertId    (0)
, m_countRows       (0)
{

}

rdv_db_mysql_run::~rdv_db_mysql_run()
{
    m_dbSQL.close();
}

rdv_db_mysql_map rdv_db_mysql_run::readQuery(const QString& _sqlQuery)
{
    QSqlQuery sqlQuery(m_dbSQL);
    sqlQuery.prepare(_sqlQuery);
    auto it = m_params.keyValueBegin();
    for(; it != m_params.keyValueEnd(); ++it)
    {
        sqlQuery.bindValue(it->first, it->second);
    }
    if(!sqlQuery.exec())
    {
        qDebug() << "L'insertion de la donnee a echoue."
        "|erreurMsg=" << m_dbSQL.lastError().text();
        m_errors.addProblem();
        return rdv_db_mysql_map();
    }

    m_countRows = sqlQuery.size();

    if(!m_countRows)
    {
        return rdv_db_mysql_map();
    }

    rdv_db_mysql_map dataMap;
    int nCols = sqlQuery.record().count();

    while (sqlQuery.next())
    {
        rdv_db_mysql_list dataList;
        for(int iCol = 0; iCol < nCols; iCol++)
        {
            QString data = sqlQuery.value(iCol).toString();
            dataList.push_back(data);
        }
        dataMap.push_back(dataList);
    }

    return dataMap;
}

void rdv_db_mysql_run::execQuery(const QString& _sqlQuery)
{
    QSqlQuery sqlQuery(m_dbSQL);
    sqlQuery.prepare(_sqlQuery);
    auto it = m_params.keyValueBegin();
    for(; it != m_params.keyValueEnd(); ++it)
    {
        sqlQuery.bindValue(it->first, it->second);
    }
    if(!sqlQuery.exec())
    {
        qDebug() << "L'insertion de la donnee a echoue."
        "|erreurMsg=" << sqlQuery.lastError().text();
        m_errors.addProblem();
        return;
    }
}

void rdv_db_mysql_run::insertQuery(const QString& _sqlQuery)
{
    QSqlQuery sqlQuery(m_dbSQL);
    sqlQuery.prepare(_sqlQuery);
    auto it = m_params.keyValueBegin();
    for(; it != m_params.keyValueEnd(); ++it)
    {
        sqlQuery.bindValue(it->first, it->second);
    }
    if(!sqlQuery.exec())
    {
        qDebug() << "L'insertion de la donnee a echoue."
        "|erreurMsg=" << sqlQuery.lastError().text();
        m_errors.addProblem();
        return;
    }
    m_lastInsertId = sqlQuery.lastInsertId().toInt();
}
