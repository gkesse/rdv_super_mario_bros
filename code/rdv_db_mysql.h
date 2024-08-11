#pragma once

#include "rdv_objects.h"

class rdv_db_mysql
{
public:
	explicit rdv_db_mysql();
	~rdv_db_mysql();
	void run();

private:
    QString m_hostname;
    QString m_username;
    QString m_password;
    QString m_database;
};
