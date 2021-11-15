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


void MainWindow::on_tabWidget_4_currentChanged(int index)
{fournisseur f;
    // background //
              QLinearGradient gradient(0, 0, 0, 400);
              gradient.setColorAt(0, QColor(90, 90, 90));
              gradient.setColorAt(0.38, QColor(105, 105, 105));
              gradient.setColorAt(1, QColor(70, 70, 70));
              ui->plott->setBackground(QBrush(gradient));

              QCPBars *amande = new QCPBars(ui->plott->xAxis, ui->plott->yAxis);
              amande->setAntialiased(false);
              amande->setStackingGap(1);
               //couleurs
              amande->setName("Repartition des produit selon fournisseur");
              amande->setPen(QPen(QColor(0, 168, 140).lighter(130)));
              amande->setBrush(QColor(0, 168, 140));

               //axe des abscisses
              QVector<double> ticks;
              QVector<QString> labels;
              f.statistique(&ticks,&labels);

              QSharedPointer<QCPAxisTickerText> textTicker(new QCPAxisTickerText);
              textTicker->addTicks(ticks, labels);
              ui->plott->xAxis->setTicker(textTicker);
              ui->plott->xAxis->setTickLabelRotation(60);
              ui->plott->xAxis->setSubTicks(false);
              ui->plott->xAxis->setTickLength(0, 4);
              ui->plott->xAxis->setRange(0, 8);
              ui->plott->xAxis->setBasePen(QPen(Qt::white));
              ui->plott->xAxis->setTickPen(QPen(Qt::white));
              ui->plott->xAxis->grid()->setVisible(true);
              ui->plott->xAxis->grid()->setPen(QPen(QColor(130, 130, 130), 0, Qt::DotLine));
              ui->plott->xAxis->setTickLabelColor(Qt::white);
              ui->plott->xAxis->setLabelColor(Qt::white);

              // axe des ordonnées
              ui->plott->yAxis->setRange(0,10);
              ui->plott->yAxis->setPadding(5);
              ui->plott->yAxis->setLabel("Statistiques");
              ui->plott->yAxis->setBasePen(QPen(Qt::white));
              ui->plott->yAxis->setTickPen(QPen(Qt::white));
              ui->plott->yAxis->setSubTickPen(QPen(Qt::white));
              ui->plott->yAxis->grid()->setSubGridVisible(true);
              ui->plott->yAxis->setTickLabelColor(Qt::white);
              ui->plott->yAxis->setLabelColor(Qt::white);
              ui->plott->yAxis->grid()->setPen(QPen(QColor(130, 130, 130), 0, Qt::SolidLine));
              ui->plott->yAxis->grid()->setSubGridPen(QPen(QColor(130, 130, 130), 0, Qt::DotLine));

              // ajout des données  (statistiques du fournisseur)//

              QVector<double> PlaceData;
              QSqlQuery q1("select * from FOURNISSEUR");
              while (q1.next()) {
                            int  nbr_fautee = q1.value(0).toInt();
                            PlaceData<< nbr_fautee;
                              }
              amande->setData(ticks, PlaceData);

              ui->plott->legend->setVisible(true);
              ui->plott->axisRect()->insetLayout()->setInsetAlignment(0, Qt::AlignTop|Qt::AlignHCenter);
              ui->plott->legend->setBrush(QColor(255, 255, 255, 100));
              ui->plott->legend->setBorderPen(Qt::NoPen);
              QFont legendFont = font();
              legendFont.setPointSize(5);
              ui->plott->legend->setFont(legendFont);
              ui->plott->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
}
