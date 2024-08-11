#include "rdv_game_dao.h"
#include "rdv_db_mysql.h"

rdv_game_dao::rdv_game_dao()
{

}

rdv_game_dao::~rdv_game_dao()
{

}

QString rdv_game_dao::getUsername() const
{
    rdv_db_mysql dbSQL;
    dbSQL.run();
    return "";
}
