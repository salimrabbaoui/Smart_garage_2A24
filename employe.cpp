#include "employe.h"
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QtDebug>
#include <QObject>
#include "ui_mainwindow.h"
#include "mainwindow.h"
#include "conge.h"
Employe::Employe()
{
cin=0;
age=0;
Nom="";
Prenom="";
Type="";
}




Employe::Employe(int cin ,QString Nom,QString Prenom,int age,QString Type)
{this->cin=cin; this->Nom=Nom; this->Prenom=Prenom;this->age=age; this->Type=Type;}
int Employe::getcin(){return cin;}
QString Employe::getnom(){return Nom;}
QString Employe:: getprenom(){return Prenom;}
int Employe::getage(){return age;}
QString Employe:: gettype(){return Type;}
void Employe::setcin(int cin){this->cin=cin;}
void Employe::setage(int age){this->age=age;}

void Employe::setNom(QString Nom){this->Nom=Nom;}
void Employe::setPrenom(QString Prenom){this->Prenom=Prenom;}
void Employe::setType(QString Type){this->Type=Type;}


bool Employe::ajouter()
{
    QSqlQuery query;

         query.prepare("select * from EMP where (CIN=:cin )");
         query.bindValue(":cin",cin);

         query.exec();
         int existe=0 ;
         while (query.next()) {
                existe=1;
                return 0;
             }
         if(existe==0)
         {
    QSqlQuery query;
    QString cin_string= QString::number(cin);
         query.prepare("INSERT INTO EMP (CIN, NOM, PRENOM,AGE, TYPE) "
                       "VALUES (:CIN,:NOM,:PRENOM,:AGE,:TYPE)");
         query.bindValue(0,cin_string);
         query.bindValue(1, Nom);
         query.bindValue(2, Prenom);
         query.bindValue(3, age);
         query.bindValue(4, Type);

  return query.exec();
}
         return 1 ;
}
bool Employe::modifier(int idd)
{

QSqlQuery query;
QString res= QString::number(idd);
query.prepare("Update EMP set CIN = :cin , NOM = :Nom , PRENOM = :Prenom , AGE = :age ,  TYPE = :Type  where CIN= :cin ");

query.bindValue(":cin", res);
query.bindValue(":Nom", Nom);
query.bindValue(":Prenom", Prenom);
query.bindValue(":age", age);
query.bindValue(":Type",Type);



return    query.exec();


}

bool Employe::supprimer(int cin)
{
    QSqlQuery query;
         query.prepare("Delete from EMP where CIN=:cin");
         query.bindValue(0,cin);

         return   query.exec();

}


QSqlQueryModel* Employe::afficher()
{
    QSqlQueryModel* model=new QSqlQueryModel();


           model->setQuery("SELECT * FROM EMP ");
           model->setHeaderData(0, Qt::Horizontal, QObject::tr("CIN"));
           model->setHeaderData(1, Qt::Horizontal,QObject:: tr("NOM"));
           model->setHeaderData(2, Qt::Horizontal,QObject:: tr("PRENOM"));
           model->setHeaderData(3, Qt::Horizontal,QObject:: tr("AGE"));
           model->setHeaderData(4, Qt::Horizontal,QObject:: tr("TYPE"));
return model;
}







void Employe::recherche(Ui::MainWindow *ui)
{
    QSqlQuery q;
    QSqlQueryModel *modal=new QSqlQueryModel();
    QString mot =ui->lineEdit_recherche->text();
    q.prepare("select * from EMP where (NOM LIKE '%"+mot+"%' or CIN LIKE '%"+mot+"%' or TYPE LIKE '%"+mot+"%' )");

    q.exec() ;
    modal->setQuery(q);
    ui->tab_employe1->setModel(modal);

}



QSqlQueryModel *Employe:: afficher_CIN()
{
 QSqlQueryModel *model=new QSqlQueryModel();
       model->setQuery("SELECT * FROM EMP ORDER BY  CIN");
       model->setHeaderData(0, Qt::Horizontal, QObject::tr("CIN"));
       model->setHeaderData(1, Qt::Horizontal, QObject::tr(" NOM"));
       model->setHeaderData(2, Qt::Horizontal, QObject::tr("PRENOM"));
       model->setHeaderData(3, Qt::Horizontal, QObject::tr("AGE"));
       model->setHeaderData(4, Qt::Horizontal, QObject::tr(" TYPE "));

       return model;
}
QSqlQueryModel *Employe:: afficher_Nom()
{
 QSqlQueryModel *model=new QSqlQueryModel();
 model->setQuery("SELECT * FROM EMP ORDER BY  NOM");
 model->setHeaderData(0, Qt::Horizontal, QObject::tr("CIN"));
 model->setHeaderData(1, Qt::Horizontal, QObject::tr(" NOM"));
 model->setHeaderData(2, Qt::Horizontal, QObject::tr("PRENOM"));
 model->setHeaderData(3, Qt::Horizontal, QObject::tr("AGE"));
 model->setHeaderData(4, Qt::Horizontal, QObject::tr(" TYPE "));
       return model;
}

QSqlQueryModel *Employe:: afficher_SERVICE()
{
 QSqlQueryModel *model=new QSqlQueryModel();
 model->setQuery("SELECT * FROM EMP ORDER BY  TYPE");
 model->setHeaderData(0, Qt::Horizontal, QObject::tr("CIN"));
 model->setHeaderData(1, Qt::Horizontal, QObject::tr(" NOM"));
 model->setHeaderData(2, Qt::Horizontal, QObject::tr("PRENOM"));
 model->setHeaderData(3, Qt::Horizontal, QObject::tr("AGE"));
 model->setHeaderData(4, Qt::Horizontal, QObject::tr(" TYPE "));
       return model;
}









