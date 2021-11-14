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
#include<iostream>
#include <QPdfWriter>
#include <QPainter>
#include <QDesktopServices>
#include <QUrl>
using namespace std;

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
   QString num=ui->le_PC_CIN->text();
   QString voiture=ui->le_PC_typevoiture->text();
   QSqlQuery findClient;
   QSqlQuery findCar;
   findClient.prepare("select ADRESSE_MAIL from CLIENT Where CIN=:n");
   findClient.bindValue(":n", num);
   findClient.exec();
   findCar.prepare("select TYPE_VOITURE from VOITURE Where TYPE_VOITURE='"+voiture+"'");
   findCar.exec();
   if (findClient.next() && findCar.next()) {
       const char* email = new char { };
       email = findClient.value(0).toString().toStdString().c_str();
       QMessageBox::information(nullptr, QObject::tr("Passer une commande"),
                                QObject::tr("La commande est validée. Un courrier a été envoyé à cet email: ")+
                         QObject::tr(email), QMessageBox::Ok);
   } else {
       QMessageBox::warning(nullptr, QObject::tr("Passer une commande"),
                         QObject::tr("Veuillez verifier les informations saisis"), QMessageBox::Cancel);
   }

}

void MainWindow::on_pushButton_9_clicked()
{
    QPdfWriter pdf("PdfCLient.pdf");
                  QPainter painter(&pdf);
                 int i = 4000;
                      painter.setPen(Qt::blue);
                      painter.setFont(QFont("Arial", 30));
                      painter.drawText(2300,1200,"Liste Des Clients");
                      painter.setPen(Qt::black);
                      painter.setFont(QFont("Arial", 50));
                      painter.drawRect(1500,200,7300,2600);
                      painter.drawRect(0,3000,9600,500);
                      painter.setFont(QFont("Arial", 9));
                      painter.drawText(300,3300,"cin");
                      painter.drawText(2300,3300,"nom");
                      painter.drawText(4300,3300,"prenom");
                      painter.drawText(6300,3300,"adresse");



                      QSqlQuery query;
                      query.prepare("select * from CLIENT");
                      query.exec();
                      while (query.next())
                      {
                          painter.drawText(300,i,query.value(0).toString());
                          painter.drawText(2300,i,query.value(1).toString());
                          painter.drawText(4300,i,query.value(2).toString());
                          painter.drawText(6300,i,query.value(3).toString());



                         i = i +500;
                      }
                      int reponse = QMessageBox::question(this, "Génerer PDF", "<PDF Enregistré>...Vous Voulez Affichez Le PDF ?", QMessageBox::Yes |  QMessageBox::No);
                          if (reponse == QMessageBox::Yes)
                          {
                              QDesktopServices::openUrl(QUrl::fromLocalFile("PdfCLient.pdf"));

                              painter.end();
                          }
                          if (reponse == QMessageBox::No)
                          {
                               painter.end();
                          }
}

void MainWindow::on_pushButton_10_clicked()
{
    QString recherche=ui->le_recherche->text();
    ui->tab_Client->setModel(C.rechercher(recherche));
}

void MainWindow::on_le_recherche_textChanged(const QString &recherche)
{
    ui->tab_Client->setModel(C.rechercher(recherche));
}
