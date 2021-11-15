#include "fournisseur.h"
#include<QtDebug>
#include<QObject>
#include<QSqlQuery>
#include "ui_mainwindow.h"



fournisseur::fournisseur()
{
num=0; nom_societe=" ";adresse=" ";id=0;type_voiture=" ";email=" ";
}

fournisseur::fournisseur (  int id,QString nom_societe ,QString adresse , QString email  , QString type_voiture,int num)
{ this->id=id; this->nom_societe=nom_societe; this->adresse=adresse;this->email=email;this->type_voiture=type_voiture;this->num=num; }
int fournisseur :: getnum() {return num ;}
int fournisseur :: getid() {return id ;}

 QString fournisseur::  getnom_societe() {return nom_societe;}
 QString fournisseur ::  getadresse() { return adresse; }
 void fournisseur :: setnum(int num ) {this->num=num;}
 void fournisseur ::  setadresse(QString adresse ) { this->adresse=adresse;}
 void  fournisseur ::setnom_societe(QString nom_societe) {this->nom_societe=nom_societe;}
  QString fournisseur::  gettype_voiture() {return type_voiture;}
  QString fournisseur ::  getemail() { return email; }
  void fournisseur ::  setid(int id ) { this->id=id;}
  void fournisseur ::  setemail(QString email ) { this->email=email;}
  void  fournisseur ::settype_voiture(QString type_voiture) {this->type_voiture=type_voiture;}
 bool fournisseur :: ajouter()
 {
     QSqlQuery query;
     //Vérifier si le fournisseur exite déjà
     query.prepare("select * from fournisseur where (ID=:id or NUM =:num  )");
     query.bindValue(":id",id);
      query.bindValue(":num",num);
     query.exec();
     int existe=0 ;
     while (query.next()) {
            existe=1;
            return 0;
         }
     if(existe==0)
     {

QString id_string=QString ::number(id);
QString num_string=QString ::number(num);
     QSqlQuery query;

     query.prepare("INSERT INTO FOURNISSEUR (ID,EMAIL,ADRESSE,TYPE_VOITURE,NOM_SOCIETE,NUM) "
                   "VALUES (:ID,:EMAIL,:ADRESSE,:TYPE_VOITURE,:NOM_SOCIETE,  :NUM)");

 query.bindValue(0, id_string);
query.bindValue(1,nom_societe);

     query.bindValue(2,email);
     query.bindValue(3,adresse);
     query.bindValue(4,type_voiture);
     query.bindValue(5,num_string);

     return query.exec();
     }
     return 1;



 }
QSqlQueryModel* fournisseur :: afficher()
{
    QSqlQueryModel *model = new QSqlQueryModel;
         model->setQuery("SELECT *from FOURNISSEUR");
         model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
         model->setHeaderData(1, Qt::Horizontal, QObject::tr("NUM"));
         model->setHeaderData(2, Qt::Horizontal, QObject::tr("EMAIL"));
         model->setHeaderData(3, Qt::Horizontal, QObject::tr("ADRESSE"));
         model->setHeaderData(4, Qt::Horizontal, QObject::tr("TYPE_VOITURE"));
         model->setHeaderData(5, Qt::Horizontal, QObject::tr("NOM_SOCIETE"));





    return model;

}
bool fournisseur::supprimer(int id)
{

    QSqlQuery query;

    query.prepare("Delete from FOURNISSEUR where ID=:id");
    query.bindValue(0, id);

    return query.exec();






}
bool fournisseur::modifier(int idd)
{
QString res= QString::number(idd);

    QSqlQuery query;
    //Vérifier si le fournisseur exite déjà
    query.prepare("select * from fournisseur where (ID!=:idd )");
    query.bindValue(":id",res);
    query.exec();
    int existe=0 ;
    while (query.next()) {
           existe=1;
           return 0;
        }
    if(existe==0)
    {


QSqlQuery query;
query.prepare("Update FOURNISSEUR set ID = :id , NOM_SOCIETE = :nom_societe , ADRESSE = :adresse , TYPE_VOITURE = :type_voiture ,  EMAIL = :email,NUM = :num  where ID = :id ");

query.bindValue(":id", res);
query.bindValue(":nom_societe", nom_societe);
query.bindValue(":email", email);
query.bindValue(":adresse", adresse);
query.bindValue(":type_voiture", type_voiture);
query.bindValue(":num",num );


return    query.exec();
    }
return 1;

}

void fournisseur::recherche(Ui::MainWindow *ui)
{
    QSqlQuery q;
    QSqlQueryModel *modal=new QSqlQueryModel();
    QString mot =ui->lineEdit_recherche->text();
    q.prepare("select * from FOURNISSEUR where (NUM LIKE '%"+mot+"%' or ID LIKE '%"+mot+"%' or TYPE_VOITURE LIKE '%"+mot+"%' )");

    q.exec() ;
    modal->setQuery(q);
    ui->tab_fournisseur_1->setModel(modal);

}

void fournisseur::statistique(QVector<double>* ticks,QVector<QString> *labels)
{
    QSqlQuery q;
    int i=0;
    q.exec("select * from FOURNISSEUR");
    while (q.next())
    {
        QString identifiant = q.value(0).toString();
        i++;
        *ticks<<i;
        *labels <<identifiant;
    }
}
