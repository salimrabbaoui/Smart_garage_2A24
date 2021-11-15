#include "facture.h"
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QPrinter>
#include <QPrintDialog>
#include <QTextStream>
#include <QPainter>
#include <QTextStream>


facture::facture()
{
    this->numfacture=0;
    this->prixachat=0;
    this->prixvente=0;
}

facture::facture(int numfacture,int prixachat,int prixvente )
{
    this->numfacture=numfacture;
    this->prixachat=prixachat;
    this->prixvente=prixvente;

}
int facture:: getNum()
{
     return this->numfacture;
}

int facture::getPrixAchat()
{
    return this->prixachat;
}
int facture:: getPrixVente()
{
    return this->prixvente;
}
int facture::  calcul(int prixachat,int prixvente)
{
    int gain;
    gain= prixvente -prixachat;
    return gain;

}
bool facture::ajouter()
{
    QSqlQuery query;
    QString res=QString ::number(numfacture);//res=sid//
    QString resPA=QString ::number(prixachat);
    QString resPV=QString ::number(prixvente);
    int gain=calcul(prixachat,prixvente);
    QString resG=QString ::number(gain);
    query.prepare("INSERT INTO  facture(NUMFACTURE,PRIXACHAT,PRIXVENTE,GAIN_PERTE)"
                  "VALUES(:numfacture,:prixachat,:prixvente,:gain_perte)");

 query.bindValue(":numfacture",res);
 query.bindValue(":prixachat",resPA);
 query.bindValue(":prixvente",resPV);
 query.bindValue(":gain_perte",resG);
 return query.exec();


}
QSqlQueryModel *facture:: afficher()
{

QSqlQueryModel * model =new QSqlQueryModel();
model->setQuery ("select * from facture");
model->setHeaderData(0,Qt::Horizontal,QObject::tr("NUMFACTURE"));
model->setHeaderData(1,Qt::Horizontal,QObject::tr("PRIXACHAT"));
model->setHeaderData(2,Qt::Horizontal,QObject::tr("PRIXVENTE"));
model->setHeaderData(3,Qt::Horizontal,QObject::tr("GAIN_PERTE"));
return model;

}

bool facture:: supprimer(int idF)
{
    QSqlQuery query;
    QString resF=QString::number(idF);
    query.prepare("Delete from facture where NUMFACTURE= :numfacture");
    query.bindValue(":numfacture",resF);

      return query.exec();

}


bool facture::modifier(int idf)
{

QSqlQuery query;
QString resF= QString::number(idf);
int gain=calcul(prixachat,prixvente);
QString resG=QString ::number(gain);
query.prepare("Update facture set PRIXACHAT = :prixachat,PRIXVENTE=:prixvente,GAIN_PERTE=:gain_perte    where NUMFACTURE = :numfacture ");
query.bindValue(":numfacture",resF);
query.bindValue(":prixachat",prixachat);
query.bindValue(":prixvente",prixvente);
query.bindValue(":gain_perte",resG);


return    query.exec();
}
