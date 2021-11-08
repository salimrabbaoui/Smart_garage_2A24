#include "profil.h"
#include "adminn.h"
#include"QStandardItem"
#include<QMessageBox>
#include<QMessageBox>
#include<QTextDocument>
profil::profil()
{}
profil::profil(int id,QString login,QString mdp)
{
   this->id=id;
   this->login=login;
   this->mdp=mdp;
}
int profil::getID()
{
    return id;
               }
QString  profil::getLOGIN()
{
     return login;
               }
QString profil::getMDP()
{
     return mdp;
               }


void profil::setID(int id)
{
  this->id=id;
               }
void profil::setLOGIN(QString l)
{
  this->login=l;
               }
void profil::setMDP(QString m)
{
  this->mdp=m;
               }

bool profil::ajouter()
{
QSqlQuery query;
//Vérifier si le profil exite déjà
query.prepare("select login from profil where login=:login");
query.bindValue(":login",login);
query.exec();
int existe=0 ;
while (query.next()) {
       existe=1;
       return 0;
    }
if(existe==0)
{
//Ajouter Profil
query.prepare("insert into profil(id,login,motdepasse,photo) values(default,:login,:mdp,:photo)");
query.bindValue(":login",login);
query.bindValue(":mdp",mdp);
query.exec();
}
return 1;
}

