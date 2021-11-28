#include "conge.h"
#include "employe.h"
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QtDebug>
#include <QObject>
#include "ui_mainwindow.h"
#include "mainwindow.h"
Conge::Conge()
{
    cin_c=0;
    id_c=0;
    duree="";
    date="";
    etat="";
}
//ok
Conge::Conge(int cin_c ,int id_c,QString duree,QString date,QString etat)
{this->cin_c=cin_c;this->id_c=id_c; this->duree=duree; this->date=date;this->etat=etat;}
int Conge::getcin_c(){return cin_c;}
int Conge::getid_c(){return id_c;}
QString Conge::getduree(){return duree;}
QString Conge:: getdate(){return date;}
QString Conge:: getetat(){return etat;}


void Conge::setcin_c(int cin_c){this->cin_c=cin_c;}
void Conge::setid_c(int id_c){this->id_c=id_c;}

void Conge::setduree(QString duree){this->duree=duree;}
void Conge::setdate(QString date){this->date=date;}
void Conge::setetat(QString etat){this->etat=etat;}

bool Conge::ajouter_c()
{
    QSqlQuery query;

         query.prepare("select * from TAB_CONGE where (CIN_Employe=:cin_c )");
         query.bindValue(":cin_c",cin_c);

         query.exec();
         int existe=0 ;
         while (query.next()) {
                existe=1;
                return 0;
             }
         if(existe==0)
         {
    QSqlQuery query;
    QString cin_c_string= QString::number(cin_c);
    QString id_c_string= QString::number(id_c);
         query.prepare("INSERT INTO TAB_CONGE (CIN_EMPLOYE, ID_CONGE,DUREE,DATE_C, ETAT) "
                       "VALUES (:CIN_EMPLOYE,:ID_CONGE,:DUREE,:DATE_C,:ETAT)");
         query.bindValue(0,cin_c_string);
         query.bindValue(1, id_c_string);
         query.bindValue(2, duree);
         query.bindValue(3, date);
         query.bindValue(4, etat);

  return query.exec();
}
         return 1 ;
}
bool Conge::modifier_c(int cin_c)
{

QSqlQuery query;
QString res= QString::number(cin_c);
query.prepare("Update TAB_CONGE set CIN_EMPLOYE = :cin_c , ID_CONGE = :id_c , DUREE = :duree ,DATE_C = :date,  ETAT= :etat  where CIN_EMPLOYE = :cin_c ");

query.bindValue(":cin_c", res);
query.bindValue(":id_c", id_c);
query.bindValue(":duree", duree);
query.bindValue(":date", date);
query.bindValue(":etat",etat);



return    query.exec();


}

QSqlQueryModel* Conge::afficher_c()
{
    QSqlQueryModel* model=new QSqlQueryModel();


           model->setQuery("SELECT * FROM TAB_CONGE ");
           model->setHeaderData(0, Qt::Horizontal, QObject::tr("CIN_EMPLOYE"));
           model->setHeaderData(1, Qt::Horizontal,QObject:: tr("ID_CONGE"));
           model->setHeaderData(2, Qt::Horizontal,QObject:: tr("DUREE"));
           model->setHeaderData(3, Qt::Horizontal,QObject:: tr("DATE_C"));
           model->setHeaderData(4, Qt::Horizontal,QObject:: tr("ETAT"));
return model;
}





bool Conge::supprimer_c(int cinn)
{ QSqlQuery query;
    QString s = QString::number(cinn);
          query.prepare("Delete from TAB_CONGE where CIN_EMPLOYE = :cin_c");
          query.bindValue(0,s);

    return query.exec();


}
