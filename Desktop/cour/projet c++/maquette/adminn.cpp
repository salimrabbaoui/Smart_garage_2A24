#include "adminn.h"
#include "ui_adminn.h"
#include<QMessageBox>
#include "profil.h"
#include<QSqlQueryModel>
#include<QDebug>
#include <QPdfWriter>
#include <QPainter>
#include <QTextDocument>
#include<QFileDialog>
#include "connection.h"
QString filePh="";
int idp;
Adminn::Adminn(QWidget *fournisseur) :

    ui(new Ui::Adminn)
{

    ui->setupUi(this);


ui->tabWidget->setCurrentIndex(0);

}

Adminn::~Adminn()
{
    delete ui;
}

void Adminn::on_ajouter_profil_clicked()
{
    if(verif_profil()==1)
    {
    profil p;
    p.setLOGIN(ui->edit_login->text());
    p.setMDP( ui->edit_nmdp->text());

   bool b = p.ajouter();
   if(b==1)
   {
       p.recuperer_2(ui->edit_login->text());
       idp=p.getID();
       ui->ajouter_profil->setEnabled(false);
  ui->modifier_profil->setEnabled(true);
  ui->supprimer_profil->setEnabled(true);


       QMessageBox::information(nullptr,QObject::tr("ajout"),"Ajout avec succès",QMessageBox::Cancel);
       vider_profil();
       ui->tabWidget_profil->setCurrentIndex(1);

   }
   else if (b==0)
   {QMessageBox::information(nullptr,QObject::tr("ajout"),"Ce profil existe déjà",QMessageBox::Cancel);}
    }

   }

   bool Adminn::verif_profil()
   {
       QString log,mp,cmp;
     //login
       log=ui->edit_login->text();

       if ((log.length()<4)||(log.length()>8))
       {
        QMessageBox::warning(nullptr,QObject::tr("Vérification"),"La taille du login doit etre entre 4 et 8 caractères",QMessageBox::Cancel);
        return 0;
       }
       for(int i=0;i<log.length();i++)
       {
           if(((log[i].toUpper()<"A")||(log[i].toUpper()>"Z"))&&((log[i]<"0")||(log[i]>"9"))&&(log[i]!="_"))
            {
               QMessageBox::warning(nullptr,QObject::tr("Vérification"),"Le login doit contenir des lettres ou bien des chiffres ou bien _",QMessageBox::Cancel);
               return 0;
           }
       }
       //mdp

       mp=ui->edit_nmdp->text();

       if ((mp.length()<4)||(mp.length()>8))
       {
        QMessageBox::warning(nullptr,QObject::tr("Vérification"),"La taille du mot de passe doit etre entre 4 et 8 caractères",QMessageBox::Cancel);
        return 0;
       }
       for(int i=0;i<mp.length();i++)
       {
           if(((mp[i].toUpper()<"A")||(mp[i].toUpper()>"Z"))&&((mp[i]<"0")||(mp[i]>"9"))&&(mp[i]!="_"))
            {
               QMessageBox::warning(nullptr,QObject::tr("Vérification"),"Le mot de passe doit contenir des lettres ou bien des chiffres ou bien _",QMessageBox::Cancel);
               return 0;
           }
       }
       //cmdp
       cmp=ui->edit_cnmdp->text();

       if (cmp!=mp)
       {
        QMessageBox::warning(nullptr,QObject::tr("Vérification"),"Les mots de passes ne sont pas identiques ",QMessageBox::Cancel);
        return 0;
       }

       return 1;


   }













void Adminn::on_nouveau_profil_clicked()
{

    ui->ajouter_profil->setEnabled(true);
 ui->modifier_profil->setEnabled(false);
 ui->supprimer_profil->setEnabled(false);
 ui->edit_login->setText("");
 ui->edit_nmdp->setText("");
 ui->edit_cnmdp->setText("");
 filePh="";
 QPixmap pic(filePh);

}


