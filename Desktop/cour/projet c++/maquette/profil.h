#ifndef PROFIL_H
#define PROFIL_H

#include <QSqlQuery>
#include <QSqlQueryModel>

#include "adminn.h"
/* #include "ui_admin.h"*/
#include <QStandardItemModel>
#include<QSqlDatabase>
#include<QSqlError>
#include<QFileInfo>
#include<QMessageBox>
#include<QDebug>
#include<QFileDialog>
#include<QDialog>
class profil
{
private:
    int id;
    QString login,mdp;
public:
    profil();
    profil(int id,QString login,QString mdp);
    int getID();
    QString getLOGIN();
    QString getMDP();

    void setID(int id);
    void setLOGIN(QString l);
    void setMDP(QString m);

    bool ajouter();
    bool modifier();
    bool supprimer(int id);

    bool se_connecter();
    bool recuperer(int idp);
    bool recuperer_2(QString login);
    /*
    void recherche(Ui::Admin *ui) ;
    void TRI1(Ui::Admin *ui);
    void afficher(Ui::Admin *ui);
    void TRI2(Ui::Admin *ui);
    void creationpdf() ;*/

};
#endif // PROFIL_H




