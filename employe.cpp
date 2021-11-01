#include "employe.h"
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QtDebug>
#include <QObject>

Employe::Employe()
{
cin=0;
age=0;
Nom="";
Prenom="";
Type="";
}




Employe::Employe(int cin ,int age,QString Nom,QString Prenom,QString Type)
{this->cin=cin; this->Nom=Nom; this->Prenom=Prenom;}
int Employe::getcin(){return cin;}
QString Employe::getNom(){return Nom;}
QString Employe:: getPrenom(){return Prenom;}
void Employe::setcin(int id){this->cin=cin;}
void Employe::setNom(QString nom){this->Nom=Nom;}
void Employe::setPrenom(QString Prenom){this->Prenom=Prenom;}
bool Employe::ajouter()
{
    QSqlQuery query;
    QString cin_string= QString::number(cin);
         query.prepare("INSERT INTO etudiant (cin, Nom, Prenom,Age, type) "
                       "VALUES (:id, :forename, :surname)");
         query.bindValue(0,cin_string);
         query.bindValue(1, Nom);
         query.bindValue(2, Prenom);
         query.bindValue(3, Age);
         query.bindValue(4, Type);

  return query.exec();
}
bool Employe::supprimer(int cin)
{
    QSqlQuery query;
    QString cin_string= QString::number(cin);
         query.prepare("Delete from employe where cin=:cin");
         query.bindValue(0,cin);

         return   query.exec();

}

QSqlQueryModel* Employe::afficher()
{
    QSqlQueryModel* model=new QSqlQueryModel();


          model->setQuery("SELECT * FROM employe ");
          model->setHeaderData(0, Qt::Horizontal, QObject::tr("cin"));
          model->setHeaderData(1, Qt::Horizontal,QObject:: tr("Nom"));
           model->setHeaderData(1, Qt::Horizontal,QObject:: tr("Prenom"));
           model->setHeaderData(1, Qt::Horizontal,QObject:: tr("Age"));
           model->setHeaderData(1, Qt::Horizontal,QObject:: tr("Type"));
return model;
}
