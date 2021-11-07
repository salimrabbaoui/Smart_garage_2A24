#include "connection.h"
//test tutoriel git


Connection::Connection()
{

}

bool Connection::createconnect()
{bool test=false;
QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
db.setDatabaseName("test_db");//inserer le nom de la source de données ODBC
db.setUserName("salim");//inserer nom de l'utilisateur
db.setPassword("esprit1");//inserer mot de passe de cet utilisateur

if (db.open())
test=true;





    return  test;
}
