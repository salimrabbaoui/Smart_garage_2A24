#ifndef VOITURE_H
#define VOITURE_H
#include "mainwindow.h"
#include "ui_mainwindow.h"
 #include <QString>
#include <QSqlQueryModel>
class Voiture
{
public:
    Voiture();
    Voiture(int,QString,QString,int);
    int getmatricule();
    QString gettype();
    QString getdate();
     int getprix();
    void setmatricule(int);
    void settype(QString);
    void setdate(QString);
    void setprix(int);
    bool ajouter();
    QSqlQueryModel* afficher() ;
    bool supprimer(int);
    bool modifier();
    QSqlQueryModel * tricroissant();
    QSqlQueryModel * trideccroissant();
    QSqlQueryModel * recherche(int matricule);
    void recherche(Ui::MainWindow *ui);


private:
    int matricule;
    QString type,date;
    int prix;
};

#endif // VOITURE_H
