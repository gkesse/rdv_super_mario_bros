#include "rdv_globals.h"

rdv_globals::rdv_globals()
{

}

rdv_globals::~rdv_globals()
{

}

bool rdv_globals::isValidEmail(const QString& _username)
{
   QRegularExpression regExp("^([a-z0-9_\\.-]+)@([\\da-z\\.-]+)\\.([a-z\\.]{2,6})$");
   QRegularExpressionMatch regMatch(regExp.match(_username));
   return regMatch.hasMatch();
}

bool rdv_globals::isValidPassword(const QString& _password)
{
   QRegularExpression regExp("^[a-zA-Z0-9_-]{7,20}$");
   QRegularExpressionMatch regMatch(regExp.match(_password));
   return regMatch.hasMatch();
}
