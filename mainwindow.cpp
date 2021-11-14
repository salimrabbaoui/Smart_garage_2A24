#include "mainwindow.h"
#include "ui_mainwindow.h"
#include"client.h"
#include<QTabWidget>
#include<QSqlQueryModel>
#include <QMessageBox>
#include<QObject>
#include<QIntValidator>
#include <QSqlQuery>
#include <QDebug>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->le_Cin->setValidator(  new QIntValidator(11111111, 99999999, this));
    ui->le_Num->setValidator(  new QIntValidator(11111111, 99999999, this));
    QRegularExpression rx1("\\b[A-Z._%+-]+@[A-Z.-]+\\.[A-Z]\\b",QRegularExpression::CaseInsensitiveOption);
    ui->le_nom->setValidator(new QRegularExpressionValidator(rx1, this));
    ui->le_prenom->setValidator(new QRegularExpressionValidator(rx1, this));
    ui->tab_Client->setModel(C.afficher());
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    int Cin=ui->le_Cin->text().toInt();
    QString nom=ui->le_nom->text();
    QString prenom=ui->le_prenom->text();
    int Num=ui->le_Num->text().toInt();
    QString adr=ui->le_adresse->text();
    QString adr_mail=ui->le_ad_mail->text();
    Client c(Cin,nom,prenom,Num,adr,adr_mail);
    if (Cin==0 || nom==NULL || Num==0 || prenom==NULL || adr==NULL)
                {

                    QMessageBox::information(this," ERREUR "," Veuillez verifier que tous les champs sont valides") ;
                    QMessageBox::critical(0, qApp->tr("Ajout"),

                                    qApp->tr("Probleme d'ajout"), QMessageBox::Cancel);
    } else {


    bool mail=c.Email_validation(adr_mail);
     QMessageBox msgBox;
         if(mail)
                 {
                     QMessageBox::information(nullptr, QObject::tr("ajout "),
                                 QObject::tr("Email validee.\n"
                                             "Click Cancel to exit."), QMessageBox::Cancel);
    bool test=c.ajouter();

        if(test){
            msgBox.setText("ajouter avec succés");
        ui->tab_Client->setModel(C.afficher());
        }
        else
            msgBox.setText("echeck d'ajout");
         }
        else
              msgBox.setText("echeck d'adresse mail");

        msgBox.exec();
    }
}

void MainWindow::on_pb_supp_clicked()
{
    Client c1;
    c1.setCin(ui->le_cin_sup->text().toInt());
    bool test=c1.supprimer(c1.getCin());
    QMessageBox msgBox;
    if(test){
        ui->tab_Client->setModel(C.afficher());
        msgBox.setText("suppression avec succés");

    }
    else
        msgBox.setText("echeck d'suppression");
    msgBox.exec();
}


void MainWindow::on_pushButton_2_clicked()
{

    int id = ui->le_Cin->text().toInt();
        QString adresse= ui->le_adresse->text();
        QString nom= ui->le_nom->text();
        QString prenom= ui->le_prenom->text();
        int num = ui->le_Num->text().toInt();
        QString adresse_Mail= ui->le_ad_mail->text();

     Client c(id,nom,prenom,num,adresse,adresse_Mail);
     bool mail=c.Email_validation(adresse_Mail);
      QMessageBox msgBox;
          if(mail)
                  {
      bool test=c.modifier(id);
      if(test)
    {

          ui->tab_Client->setModel(C.afficher());
          QMessageBox::information(nullptr, QObject::tr("modifier un client"),
                            QObject::tr("client modifié.\n"
                                        "Click Cancel to exit."), QMessageBox::Cancel);
      }
      else
          QMessageBox::critical(nullptr, QObject::tr("modifier un client"),
                            QObject::tr("Erreur !.\n"
                                        "Click Cancel to exit."), QMessageBox::Cancel);
          }
          else

              QMessageBox::critical(nullptr, QObject::tr("Not Ok"),
                                QObject::tr("Erreur Check Mail!.\n"
                                            "Click Cancel to exit."), QMessageBox::Cancel);
}


void MainWindow::on_tab_Client_activated(const QModelIndex &index)
{

    ui->le_Cin->setText(ui->tab_Client->model()->data(ui->tab_Client->model()->index(index.row(),0)).toString());
    ui->le_Num->setText(ui->tab_Client->model()->data(ui->tab_Client->model()->index(index.row(),4)).toString());
    ui->le_nom->setText(ui->tab_Client->model()->data(ui->tab_Client->model()->index(index.row(),1)).toString());
    ui->le_prenom->setText(ui->tab_Client->model()->data(ui->tab_Client->model()->index(index.row(),2)).toString());
     ui->le_ad_mail->setText(ui->tab_Client->model()->data(ui->tab_Client->model()->index(index.row(),5)).toString());
     ui->le_adresse->setText(ui->tab_Client->model()->data(ui->tab_Client->model()->index(index.row(),3)).toString());
}

void MainWindow::on_pushButton_3_clicked()
{
    ui->tab_Client->setModel(C.afficher());
}

void MainWindow::on_pushButton_4_clicked()
{

    ui->tab_Client->setModel(C.tricroissant());
}

void MainWindow::on_pushButton_5_clicked()
{
    ui->tab_Client->setModel(C.trideccroissant());
}

void MainWindow::on_pushButton_6_clicked()
{
    ui->tab_Client->setModel(C.tri());
}

void MainWindow::on_pushButton_7_clicked()
{
    ui->tab_Client->setModel(C.stat());
}

void MainWindow::on_pushButton_8_clicked()
{
   QString cin=ui->le_PC_Cin->text();
   QString voiture=ui->le_PC_typevoiture->text();
   QSqlQuery findClient;
   QSqlQuery findCar;
   findClient.prepare("select CIN from CLIENT Where CIN=:c");
   findClient.bindValue(":c", cin);
   findClient.exec();
   findCar.prepare("select TYPE_VOITURE from VOITURE Where TYPE_VOITURE='"+voiture+"'");
   findCar.exec();
   if (findClient.next() && findCar.next()) {
       QMessageBox::information(nullptr, QObject::tr("Passer une commande"),
                         QObject::tr("La commande est validée"), QMessageBox::Cancel);
   } else {
       QMessageBox::warning(nullptr, QObject::tr("Passer une commande"),
                         QObject::tr("Veuillez verifier les informations saisis"), QMessageBox::Cancel);
   }

}
