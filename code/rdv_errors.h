#pragma once

#include "rdv_headers.h"

class rdv_errors
{
public:
	explicit rdv_errors();
	~rdv_errors();
    void addError(const QString& _error);
    void addErrors(const rdv_errors& _obj);
	void addProblem();

	bool hasErrors() const  {return !m_errors.empty();}

private:
	QVector<QString> m_errors;
};
