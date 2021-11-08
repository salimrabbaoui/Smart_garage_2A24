#include "client.h"
#include<QSqlQuery>
#include <QSqlQueryModel>
#include<QObject>
#include<QDebug>
Client::Client()
{
Cin=0;
nom="";
prenom="";
Num=0;
adresse="";
adresse_mail="";
}


Client::Client(int Cin,QString nom,QString prenom,int Num,QString adresse,QString adresse_mail)
{
    this->Cin=Cin;
    this->nom=nom;
    this->prenom=prenom;
    this->Num=Num;
    this->adresse=adresse;
    this->adresse_mail=adresse_mail;
}
int Client::getCin(){return Cin;}
QString Client::getnom(){return nom;}
QString Client:: getprenom(){return prenom;}
int Client::getNum(){return Num;}
QString Client::getadresse(){return adresse;}
QString Client::getadresse_mail(){return adresse_mail;}
void Client::setCin(int Cin){this->Cin = Cin;}
void Client::setnom(QString nom){this->nom=nom;}
void Client::setprenom(QString prenom){this->prenom=prenom;}
void Client::setNum(int Num){this->Num = Num;}
void Client::setadresse(QString adresse){this->adresse=adresse;}
void Client::setadresse_mail(QString adresse_mail){this->adresse_mail=adresse_mail;}

bool Client::ajouter()
{

    QSqlQuery query;
    QString cin_string=QString::number(Cin);
    QString num_string=QString::number(Num);
          query.prepare("INSERT INTO client (CIN, NOM, PRENOM,NUM_CLIENT,ADRESSE_CLIENT,ADRESSE_MAIL) "
                        "VALUES (:id, :forename, :surname, :num, :adr, :adr_mail)");
          query.bindValue(":id", cin_string);
          query.bindValue(":forename", nom);
          query.bindValue(":surname", prenom);
          query.bindValue(":num", num_string);
           query.bindValue(":adr", adresse);
           query.bindValue(":adr_mail", adresse_mail);
          return query.exec();

}
QSqlQueryModel * Client::afficher()
{QSqlQueryModel * model= new QSqlQueryModel();

model->setQuery("select * from Client");
model->setHeaderData(0, Qt::Horizontal, QObject::tr("CIN"));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM "));
model->setHeaderData(2, Qt::Horizontal, QObject::tr("PRENOM"));
model->setHeaderData(3, Qt::Horizontal, QObject::tr("ADRESSE_MAIL"));
model->setHeaderData(5, Qt::Horizontal, QObject::tr("ADRESSE_CLIENT"));
model->setHeaderData(4, Qt::Horizontal, QObject::tr("NUM_CLIENT"));
    return model;
}
bool Client::supprimer(int cin)
{
    QSqlQuery query;
    query.prepare("DELETE from CLIENT Where CIN=:c");
    query.bindValue(":c", cin);
    return query.exec();

}
bool Client::modifier(int cin)
{
QSqlQuery query;
QString cin_string= QString::number(cin);
QString num_string=QString::number(Num);
query.prepare("Update Client set CIN = :id,NOM =:n, PRENOM = :pr ,NUM_CLIENT = :nm ,ADRESSE_CLIENT = :ac ,ADRESSE_MAIL=:am where CIN = :id ");
query.bindValue(":id", cin_string);
query.bindValue(":n", nom);
query.bindValue(":pr", prenom);
query.bindValue(":nm",num_string );
query.bindValue(":ac", adresse);
query.bindValue(":am", adresse_mail);
return    query.exec();
}
QSqlQueryModel * Client::rechercher(QString rech)
{
    QSqlQueryModel * model= new QSqlQueryModel();
    QString recher="select * from Client where NOM like '%"+rech+"%' or PRENOM like '%"+rech+"%'";
    model->setQuery(recher);
    return model;
}

QSqlQueryModel * Client::tri()
{
    QSqlQueryModel * model= new QSqlQueryModel();
        model->setQuery("SELECT * FROM Client ORDER BY CIN");
        return model;
}
