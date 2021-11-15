#include "mainwindow.h"
#include "ui_mainwindow.h"
#include"fournisseur.h"
#include<QMessageBox>
#include<QIntValidator>
#include "smtp.h"
#include <QPrinter>
#include <QPrintDialog>
#include <QtPrintSupport>
#include "facture.h"
#include "mainwindow.h"
#include<QMessageBox>
#include<QSqlQueryModel>
#include<QDebug>
#include <QPdfWriter>
#include <QPainter>
#include <QTextDocument>
#include<QFileDialog>
#include"smtp.h"
#include<QPrinter>
#include<QDialog>
#include<QVBoxLayout>
#include<QFileDialog>
#include<QPrintDialog>
#include <QtPrintSupport>
#include <QTimer>
#include <QDateTime>
#include <QMessageBox>
#include "QIntValidator"
#include <QDateEdit>
#include <QPlainTextEdit>
#include <QPrinter>
#include <QPrinterInfo>
#include <QPrintDialog>
#include <QTextStream>
#include <QPainter>
#include <QTextStream>
#include <QFileDialog>
#include <QTextDocument>
#include <QtPrintSupport/QPrinter>
#include <QFileDialog>
#include <QTextDocument>
#include <strstream>
#include <QSystemTrayIcon>
#include <QRegExpValidator>
#include <QDesktopServices>
#include <QUrl>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    fournisseur f;
    facture temFacture;

ui->tabWidget_33->hide();

ui->comboBox_2->setModel(temFacture.afficher());
ui->comboBox_4->setModel(temFacture.afficher());
  ui->tableView_2->setModel(temFacture.afficher());
    ui->le_id->setValidator(new QIntValidator(0, 9999999, this));
    ui->le_num->setValidator(new QIntValidator(0, 99999999, this));
    ui->NumFacAj->setValidator(new QIntValidator(0,99999,this));//numfactureproduit//

    ui->tab_fournisseur->setModel(f.afficher());

    connect(ui->exitBtn_6, SIGNAL(clicked()),this, SLOT(close()));
    connect(ui->exitBtn_2, SIGNAL(clicked()),this, SLOT(close()));
    connect(ui->exitBtn_3, SIGNAL(clicked()),this, SLOT(close()));
    connect(ui->exitBtn_4, SIGNAL(clicked()),this, SLOT(close()));

}

MainWindow::~MainWindow()
{
    delete ui;
}




void MainWindow::on_pb_ajouter_clicked()
{
    int id=ui->le_id->text().toInt();
    int num=ui->le_num->text().toInt();


    QString email=ui->le_mail->text();
    QString adresse=ui->le_adresse->text();
    QString type_voiture=ui->le_voiture->text();
      QString nom_societe=ui->le_nom->text();

    fournisseur f(id,email,adresse,type_voiture,nom_societe,num);
    bool test=f.ajouter();
    QMessageBox msgBox;
    if(test)
    {
        ui->tab_fournisseur->setModel(f.afficher());
        msgBox.setText("ajouter avec succés");}
    else
        msgBox.setText("echeck d'ajout");
    msgBox.exec();
}

void MainWindow::on_pb_supprimer_clicked()
{
    fournisseur f;f.setid(ui->le_id_sup->text().toInt());
    bool test=f.supprimer(f.getid());
    QMessageBox msgBox;
    if(test)
    {
         ui->tab_fournisseur->setModel(f.afficher());
        msgBox.setText("suppression avec succés");
    }
    else
        msgBox.setText("echeck de suppression");
    msgBox.exec();
}


void MainWindow::on_pb_modifier_clicked()
{
    int id=ui->le_id_2->text().toInt();



    QString email=ui->le_mail_2->text();
    QString adresse=ui->le_adresse_2->text();
    QString type_voiture=ui->le_voiture_2->text();
      QString nom_societe=ui->le_nom_2->text();
      int num=ui->le_num_2->text().toInt();


    fournisseur f(id,email,adresse,type_voiture,nom_societe,num);
     bool test=f.modifier(id);
     if(test)
   {

         ui->tab_fournisseur->setModel(f.afficher());
   QMessageBox::information(nullptr, QObject::tr("modifier un fournisseur"),
                     QObject::tr("fournisseur modifié.\n"
                                 "Click Cancel to exit."), QMessageBox::Cancel);

   }
     else
         QMessageBox::critical(nullptr, QObject::tr("modifier un fournisseur"),
                     QObject::tr("Erreur !.\n"
                                 "Click Cancel to exit."), QMessageBox::Cancel);
}






void MainWindow::on_lineEdit_recherche_1_clicked()
{class fournisseur f ;
    ui->tab_fournisseur->setModel(f.afficher());


       f.recherche(ui);

}







void MainWindow::on_connecter_clicked()
{
    QString username = ui->log->text();
    int password = ui->mdp->text().toInt();

    if ((username == "Admin" )||( username == "admin"))
    {
        if (password == 1234)
        { QMessageBox::information(this, "Login","Bienvenue");
            ui->tabWidget_33->show();

setCentralWidget(ui->tabWidget_33) ;




        }}
    else {
        QMessageBox::warning(this, "Login","Desole Vous n'etes pas un Admin");
}

}
void MainWindow::sendMail()
{
    Smtp* smtp = new Smtp(ui->uname->text(), ui->paswd->text(), ui->server->text(), ui->port->text().toInt());
    connect(smtp, SIGNAL(status(QString)), this, SLOT(mailSent(QString)));


    smtp->sendMail(ui->uname->text(), ui->rcpt->text() , ui->subject->text(),ui->msg->toPlainText());
}

void MainWindow::mailSent(QString status)
{
    if(status != "Message sent")
        QMessageBox::warning( 0, tr( "Qt Simple SMTP client" ), tr( "Message sent!\n\n" ) );
}



void MainWindow::browse()
{
ui->uname->setText("");
ui->rcpt->setText("");
ui->paswd->setText("");
ui->subject->setText("");
ui->msg->setPlainText("");
}
void MainWindow::on_sendBtn_clicked()
{
    QMessageBox::warning( 0, tr( "Qt Simple SMTP client" ), tr( "Message sent!\n\n" ) );
    connect(ui->sendBtn, SIGNAL(clicked()),this, SLOT(sendMail()));
    connect(ui->exitBtn, SIGNAL(clicked()),this, SLOT(close()));
    connect(ui->deconnexion, SIGNAL(clicked()), this, SLOT(browse()));

}

void MainWindow::on_pushButton_clicked()
{


    QTableView *table;
               table = ui->tableView_2;

               QString filters("CSV files (.csv);;All files (.*)");
               QString defaultFilter("CSV files (*.csv)");
               QString fileName = QFileDialog::getSaveFileName(0, "Save file", QCoreApplication::applicationDirPath(),
                                  filters, &defaultFilter);
               QFile file(fileName);

               QAbstractItemModel *model =  table->model();
               if (file.open(QFile::WriteOnly | QFile::Truncate)) {
                   QTextStream data(&file);
                   QStringList strList;
                   for (int i = 0; i < model->columnCount(); i++) {
                       if (model->headerData(i, Qt::Horizontal, Qt::DisplayRole).toString().length() > 0)
                           strList.append("\"" + model->headerData(i, Qt::Horizontal, Qt::DisplayRole).toString() + "\"");
                       else
                           strList.append("");
                   }
                   data << strList.join(";") << "\n";
                   for (int i = 0; i < model->rowCount(); i++) {
                       strList.clear();
                       for (int j = 0; j < model->columnCount(); j++) {

                           if (model->data(model->index(i, j)).toString().length() > 0)
                               strList.append("\"" + model->data(model->index(i, j)).toString() + "\"");
                           else
                               strList.append("");
                       }
                       data << strList.join(";") + "\n";
                   }
                   file.close();
                   QMessageBox::information(nullptr, QObject::tr("Import excel"),
                                             QObject::tr("Import avec succes .\n"
                                                         "Click OK to exit."), QMessageBox::Ok);
               }

}
void MainWindow::on_ajoutFacture_clicked()
{facture temFacture;

    int numfacture=ui->NumFacAj->text().toInt();
    int prixachat=ui->PrixachatAj->text().toInt();
    int prixvente=ui->PrixVenteFacAj->text().toInt();
    facture F(numfacture,prixachat,prixvente);
    bool test=F.ajouter();
    QMessageBox msgBox;
    if(test)
    { ui->tableView_2->setModel(temFacture.afficher());
        ui->comboBox_2->setModel(temFacture.afficher());
        ui->comboBox_4->setModel(temFacture.afficher());

        msgBox.setText("ajouter avec succés");}
    else
        msgBox.setText("echeck d'ajout");
    msgBox.exec();
}






void MainWindow::on_SuppFacture_clicked()
{

    int numfacture=ui->comboBox_4->currentText().toInt();
    facture F;
    bool test=F.supprimer(numfacture);
    if(ui->comboBox_4->currentText().contains(QRegExp("^[1-9]"))==0){
     (tr("Notification"),tr(" liste vide"));
        QMessageBox::information(nullptr, QObject::tr("ERREUR"),
                               QObject::tr("ERREUR.\n"
                                           "Click Cancel to exit."), QMessageBox::Cancel);
    }
    else {
    if (test)
    {    (tr("Notification"),tr("Facture supprimée"));
        ui->tableView_2->setModel(F.afficher());
        QMessageBox::information(nullptr, QObject::tr("suppression facture"),
                    QObject::tr("facture supprimé.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
        ui->comboBox_2->setModel(F.afficher());
        ui->comboBox_4->setModel(F.afficher());


    }

    }
}

void MainWindow::on_ModiFacture_clicked()

{
    int numfacture =ui->comboBox_2->currentText().toInt();
    int prixachat=ui->PrixachatModpr->text().toInt();
    int prixvente=ui->PrixventeModfac->text().toInt();

      facture F( numfacture,prixachat,prixvente);
      bool test=F.modifier(numfacture);
      if(ui->comboBox_2->currentText().contains(QRegExp("^[1-9]"))==0){
      (tr("Notification"),tr(" liste vide"));
          QMessageBox::information(nullptr, QObject::tr("ERREUR"),
                                 QObject::tr("ERREUR.\n"
                                             "Click Cancel to exit."), QMessageBox::Cancel);
      }
      else{
      if(test)
    { (tr("Notification"),tr(" Modification validée"));
          ui->comboBox_2->setModel(F.afficher());
          ui->tableView_2->setModel(F.afficher());
          ui->comboBox_4->setModel(F.afficher());

    QMessageBox::information(nullptr, QObject::tr("modifier une facture"),
                      QObject::tr("Facture modifiée.\n"
                                  "Click Cancel to exit."), QMessageBox::Cancel);
ui->comboBox_2->setModel(F.afficher());
    }
}
}

