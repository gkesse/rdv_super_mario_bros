#pragma once

#include "rdv_objects.h"

using rdv_db_mysql_params   = QMap<QString, QVariant>;
using rdv_db_mysql_list     = QVector<QString>;
using rdv_db_mysql_map      = QVector<rdv_db_mysql_list>;

class rdv_db_mysql
{
public:
	explicit rdv_db_mysql();
	~rdv_db_mysql();
	void addParam(const QString& _key, const QVariant& _value);
	rdv_db_mysql_map readQuery(const QString& _sql);
    void execQuery(const QString& _sql);
    void insertQuery(const QString& _sql);

    int getLastInsertId() const             {return m_lastInsertId;}
    int getCountRows() const                {return m_countRows;}
    const rdv_errors& getErrors() const     {return m_errors;}

private:
    QString m_hostname;
    int m_port;
    QString m_username;
    QString m_password;
    QString m_database;
    rdv_db_mysql_params m_params;
    int m_lastInsertId;
    int m_countRows;
    rdv_errors m_errors;
};
