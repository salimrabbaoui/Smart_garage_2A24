#ifndef FOURNISSEUR_H
#define FOURNISSEUR_H
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
class fournisseur
{
public:
    fournisseur();
    fournisseur(int, QString,QString,QString,QString ,int);
    int getnum();
    QString getnom_societe();
    QString getemail();
    QString getadresse ();
    QString gettype_voiture();
    int getid();
    void setnum(int);
    void setnom_societe(QString);
    void setemail(QString);
    void setadresse(QString);
    void setid(int);
    void settype_voiture(QString);
    bool ajouter ();
   QSqlQueryModel * afficher();
   bool supprimer(int);
    bool modifier(int);
    void recherche(Ui::MainWindow *ui) ;

private:
    int num ,id;
    QString nom_societe , email , adresse   , type_voiture;
};

#endif // FOURNISSEUR_H
