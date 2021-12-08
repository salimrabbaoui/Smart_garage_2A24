#ifndef EMPLOYE_H
#define EMPLOYE_H
#include<QString>
#include<QSqlQueryModel>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QString>
#include<QSqlDatabase>
#include "conge.h"
#include <QDate>
#include <QDateTime>
#include <QString>
#include <QDialog>
#include <QSqlQueryModel>
#include <QMessageBox>
#include <QSqlQuery>
#include <QFile>
#include <QTextStream>
#include <windows.h>



class Employe
{
public:
    Employe();
    Employe(int,QString,QString,int,QString);

    int getcin();
    int getage();
    QString getNom();
    QString getprenom();
    QString gettype();

    void setcin(int);
    void setNom(QString);
    void setPrenom(QString);
    void setage(int);
    void setType(QString);

    bool supprimer(int);
    bool ajouter();
    bool modifier(int);
     QSqlQueryModel*afficher();
     void recherche(Ui::MainWindow *ui);
    // QSqlQueryModel * afficherOrderedList();
     //QSqlQuery *afficherEmployeList();
     //QSqlQuery *trier_liste_Employe();

     void statistique(QVector<double>* ticks,QVector<QString> *labels);

    /* QSqlQueryModel * recherche(QString a);
     QSqlQueryModel * afficherOrderedList(); // planing */
     QSqlQueryModel* afficher_CIN();
     QSqlQueryModel* afficher_Nom();
     QSqlQueryModel* afficher_SERVICE();


private:
    int cin , age;
    QString Nom, Prenom, Type;
};

#endif // EMPLOYE_H



