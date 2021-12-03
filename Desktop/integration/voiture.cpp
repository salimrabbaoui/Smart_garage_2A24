#include "voiture.h"
#include <QSqlQuery>
#include <QtDebug>
#include <QObject>
Voiture::Voiture()
{
matricule=0; type=""; date="";prix=0;
}
Voiture::Voiture(int matricule,QString type,QString date,int prix)
{this->matricule=matricule;
    this->type=type;
    this->date=date;
this->prix=prix;}
int Voiture::getmatricule(){return matricule;}
QString Voiture::gettype(){return type;}
QString Voiture::getdate(){return date;}
int Voiture::getprix(){return prix;}
void Voiture::setmatricule(int matricule){this->matricule=matricule;}
void Voiture::settype(QString type){this->type=type;}
void Voiture::setdate(QString date){this->date=date;}
void Voiture::setprix(int prix){this->prix=prix;}


bool Voiture::ajouter()
{
    //bool test=false;

QSqlQuery query;
QString matricule_string= QString::number(matricule);
      query.prepare("INSERT INTO VOITURE (MATRICULE, TYPE, DATES,PRIX) "
               "VALUES (:matricule, :type, :date, :prix)");
      query.bindValue(":matricule", matricule_string);
      query.bindValue(":type", type);
      query.bindValue(":date", date);
      query.bindValue(":prix", prix);
return query.exec();
}
      bool Voiture::supprimer(int matricule)
      {

          QSqlQuery query;
          QString matricule_string= QString::number(matricule);
          query.prepare("Delete from voiture where MATRICULE=:matricule");
          query.bindValue(":matricule", matricule_string);
        return query.exec();
      }

QSqlQueryModel* Voiture::afficher()
{
    QSqlQueryModel* model=new QSqlQueryModel();


         model->setQuery("SELECT* FROM voiture");
         model->setHeaderData(0, Qt::Horizontal, QObject::tr("matricule"));
         model->setHeaderData(1, Qt::Horizontal, QObject::tr("type"));
         model->setHeaderData(2, Qt::Horizontal, QObject::tr("date"));
           model->setHeaderData(3, Qt::Horizontal, QObject::tr("prix"));

    return model;
}

/*
bool Voiture::modifier()
{   QSqlQuery query;
    query.prepare( "UPDATE Visiteur SET  matricule=:matricule,type=:type,date=:date,prix=:prix");
    query.bindValue(":matricule",matricule);
    query.bindValue(":type",type);
    query.bindValue(":date", date);
    query.bindValue(":prix",prix);
 return query.exec();
}*/


QSqlQueryModel * Voiture::tricroissant()
{QSqlQueryModel * model= new QSqlQueryModel();

model->setQuery("select * FROM Voiture ORDER BY matricule ASC");
model->setHeaderData(0, Qt::Horizontal, QObject::tr("matricule"));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("type"));
model->setHeaderData(2, Qt::Horizontal, QObject::tr("date"));
model->setHeaderData(3, Qt::Horizontal, QObject::tr("prix"));

    return model;
}

QSqlQueryModel * Voiture::trideccroissant()
{QSqlQueryModel * model= new QSqlQueryModel();

model->setQuery("select * FROM Voiture ORDER BY matricule DESC");
model->setHeaderData(0, Qt::Horizontal, QObject::tr("matricule"));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("type"));
model->setHeaderData(2, Qt::Horizontal, QObject::tr("date"));
model->setHeaderData(3, Qt::Horizontal, QObject::tr("prix"));
return model;
}


/*
QSqlQueryModel * Voiture::recherche(int matricule)
{
QString matricule_string= QString::number(matricule);
QSqlQueryModel * model= new QSqlQueryModel();
model->setQuery("select * FROM Voiture WHERE  MATRICULE=:matricule");
model->setHeaderData(0, Qt::Horizontal, QObject::tr("matricule"));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("type"));
model->setHeaderData(2, Qt::Horizontal, QObject::tr("date"));
model->setHeaderData(3, Qt::Horizontal, QObject::tr("prix"));
return model;
}
*/


void Voiture::recherche(Ui::MainWindow *ui)
{
    QSqlQuery q;
    QSqlQueryModel *modal=new QSqlQueryModel();
    QString mot =ui->lineEdit_recherche->text();
    q.prepare("SELECT* FROM voiture where (matricule LIKE '%"+mot+"%' or type LIKE '%"+mot+"%' or prix LIKE '%"+mot+"%' )");

    q.exec() ;
    modal->setQuery(q);
    ui->tab_voiture_5->setModel(modal);

}










