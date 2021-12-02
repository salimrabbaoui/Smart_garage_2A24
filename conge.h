#ifndef CONGE_H
#define CONGE_H
#include<QString>
#include<QSqlQueryModel>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QString>
#include<QSqlDatabase>
#include<QSqlError>
#include<QFileInfo>
#include<QMessageBox>
#include<QDebug>
#include<QFileDialog>
#include<QDialog>


class Conge
{
public:
    Conge();
    Conge(int,int,QString,QString,QString);

    int getcin_c();
    int getid_c();
    QString getduree();
    QString getdate();
    QString getetat();

    void setcin_c(int);
    void setid_c(int);
    void setduree(QString);
    void setdate(QString);
    void setetat(QString);

    bool supprimer_c(int);
    bool ajouter_c();
    bool modifier_c(int);
    QSqlQueryModel*afficher_c();






private:
    int cin_c , id_c;
    QString duree, date, etat;

};

#endif // CONGE_H
