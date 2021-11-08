#include "mainwindow.h"
#include "ui_mainwindow.h"
#include"client.h"
#include <QMessageBox>
#include<QIntValidator>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->le_Cin->setValidator(  new QIntValidator(11111111, 99999999, this));
    ui->le_Num->setValidator(  new QIntValidator(11111111, 99999999, this));
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
    bool test=c.ajouter();
        QMessageBox msgBox;
        if(test){
            msgBox.setText("ajouter avec succés");
        ui->tab_Client->setModel(C.afficher());}
        else
            msgBox.setText("echeck d'ajout");
        msgBox.exec();
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

    int id = ui->lineEdit_id1->text().toInt();
        QString adresse= ui->lineEdit_AD->text();
        QString nom= ui->lineEdit_NOM->text();
        QString prenom= ui->lineEdit_PR->text();
        int num = ui->lineEdit_NUM->text().toInt();
        QString adresse_Mail= ui->lineEdit_AM->text();
     Client c(id,nom,prenom,num,adresse,adresse_Mail);
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
