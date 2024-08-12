#include "rdv_errors.h"

rdv_errors::rdv_errors()
{

}

rdv_errors::~rdv_errors()
{

}

void rdv_errors::addError(const QString& _error)
{
    m_errors.push_back(_error);
}

void rdv_errors::addErrors(const rdv_errors& _obj)
{
    for(QString error : _obj.m_errors)
    {
        addError(error);
    }
}

void rdv_errors::addProblem()
{
    addError("Un probleme a ete rencontre.");
}
