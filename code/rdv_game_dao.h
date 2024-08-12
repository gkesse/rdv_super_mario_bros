#pragma once

#include "rdv_db_mysql.h"

class rdv_game_dao
{
public:
	explicit rdv_game_dao();
	~rdv_game_dao();
	void registerUser(const QString& _username, const QString& _password);
	bool loginUser(const QString& _username, const QString& _password);

    const rdv_errors& getErrors() const     {return m_errors;}

private:
	bool checkUser(const QString& _username);

private:
	rdv_errors m_errors;
};
