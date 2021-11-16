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
#include <QtNetwork>
#include <QSslSocket>
#include "smtp.h"
using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->le_Cin->setValidator(  new QIntValidator(11111111, 99999999, this));
    ui->le_Num->setValidator(  new QIntValidator(11111111, 99999999, this));
    QRegularExpression rx1("\\b[A-Z._%+-]+@[A-Z.-]+\\.[A-Z]\\b",QRegularExpression::CaseInsensitiveOption);
    ui->le_nom->setValidator(new QRegularExpressionValidator(rx1 , this));
    ui->le_prenom->setValidator(new QRegularExpressionValidator(rx1 , this));
    ui->tab_Client->setModel(C.afficher());
    ui->tab_Client_modif->setModel(C.afficher());
    QSqlQueryModel * model= new QSqlQueryModel();
    model->setQuery("select * from CLIENT");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("CIN"));
    ui->comboBox_CIN->setModel(model);
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
        ui->tab_Client_modif->setModel(C.afficher());
        msgBox.setText("suppression avec succés");

    }
    else
        msgBox.setText("echec de suppression");
    msgBox.exec();
}


void MainWindow::on_pushButton_2_clicked()
{

    int id = ui->lineEdit_CIN->text().toInt();
        QString adresse= ui->lineEdit_AD->text();
        QString nom= ui->lineEdit_NOM->text();
        QString prenom= ui->lineEdit_PR->text();
        int num = ui->lineEdit_NUM->text().toInt();
        QString adresse_Mail= ui->lineEdit_AM->text();
    if(num == 0 || nom == NULL || prenom == NULL || adresse == NULL || adresse_Mail == NULL) {
        QMessageBox::warning(nullptr, QObject::tr("modifier un client"),
                          QObject::tr("Les informations saisies sont manquantes. Veuillez verifié !"), QMessageBox::Cancel);
    } else {

     Client c(id,nom,prenom,num,adresse,adresse_Mail);
     bool mail=c.Email_validation(adresse_Mail);
     QMessageBox msgBox;
     if(mail) {
        bool test=c.modifier(id);
        if(test) {
          ui->tab_Client_modif->setModel(C.afficher());
          ui->tab_Client->setModel(C.afficher());
          QMessageBox::information(nullptr, QObject::tr("modifier un client"),
                            QObject::tr("client modifié.\n"
                                        "Click Cancel to exit."), QMessageBox::Cancel);
        } else {
          QMessageBox::critical(nullptr, QObject::tr("modifier un client"),
                            QObject::tr("Erreur !.\n"
                                        "Click Cancel to exit."), QMessageBox::Cancel);
        }
       } else
              QMessageBox::critical(nullptr, QObject::tr("Not Ok"),
                                QObject::tr("Erreur Check Mail!.\n"
                                            "Click Cancel to exit."), QMessageBox::Cancel);
    }
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

/*void MainWindow::on_pushButton_7_clicked()
{
    ui->tab_Client->setModel(C.stat());
}*/

void MainWindow::on_pushButton_8_clicked()
{
   QString num=ui->comboBox_CIN->currentText();
   QString voiture=ui->le_PC_typevoiture->text();
   QSqlQuery findClient;
   QString nom_client;
   QSqlQuery findCar;
   findClient.prepare("select ADRESSE_MAIL, NOM from CLIENT Where CIN=:n");
   findClient.bindValue(":n", num);
   findClient.exec();
   findCar.prepare("select TYPE_VOITURE from VOITURE Where TYPE_VOITURE='"+voiture+"'");
   findCar.exec();
   if (findClient.next() && findCar.next()) {
       const char* email = new char { };
       email = findClient.value(0).toString().toStdString().c_str();
       nom_client = findClient.value(1).toString();
       QMessageBox::information(nullptr, QObject::tr("Passer une commande"),
                                QObject::tr("La commande est validée. Un courrier a été envoyé à cet email: ")+
                         QObject::tr(email), QMessageBox::Ok);
       Smtp* smtp = new Smtp("aura.forgetpass@gmail.com","Service100a","smtp.gmail.com",465);
              connect(smtp, SIGNAL(status(QString)), this, SLOT(mailSent(QString)));

              smtp->sendMail("aura.forgetpass@gmail.com",findClient.value(0).toString(),
                             "Validation de commande",
                             "Bonjour Monsieur/Madame "+nom_client+", \n\nVotre commande pour la voiture de type "+voiture+" a été validée. \n\nCordialement, \nService client.");
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

void MainWindow::mailSent(QString status)
{
    if(status == "Message sent")
        QMessageBox::information(nullptr, tr( "Message Envoyé" ), tr( "Votre message a été envoyé" ) );
}

void MainWindow::on_tab_Client_modif_activated(const QModelIndex &index)
{
    ui->lineEdit_CIN->setText(ui->tab_Client_modif->model()->data(ui->tab_Client_modif->model()->index(index.row(),0)).toString());
    ui->lineEdit_NUM->setText(ui->tab_Client_modif->model()->data(ui->tab_Client_modif->model()->index(index.row(),4)).toString());
    ui->lineEdit_NOM->setText(ui->tab_Client_modif->model()->data(ui->tab_Client_modif->model()->index(index.row(),1)).toString());
    ui->lineEdit_PR->setText(ui->tab_Client_modif->model()->data(ui->tab_Client_modif->model()->index(index.row(),2)).toString());
    ui->lineEdit_AM->setText(ui->tab_Client_modif->model()->data(ui->tab_Client_modif->model()->index(index.row(),5)).toString());
    ui->lineEdit_AD->setText(ui->tab_Client_modif->model()->data(ui->tab_Client_modif->model()->index(index.row(),3)).toString());
}

/*void MainWindow::on_pushButton_11_clicked()
{
    ui->tab_Client_modif->setModel(C.afficher());
}*/

void MainWindow::on_tabWidget_2_currentChanged(int index)
{
    Client C;
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
                  amande->setName("Repartition des voitures selon fournisseur");
                  amande->setPen(QPen(QColor(0, 168, 140).lighter(130)));
                  amande->setBrush(QColor(0, 168, 140));

                   //axe des abscisses


                  QSharedPointer<QCPAxisTickerText> textTicker(new QCPAxisTickerText);
                  ui->plott->xAxis->setTicker(textTicker);
                  ui->plott->xAxis->setTickLabelRotation(60);
                  ui->plott->xAxis->setSubTicks(false);
                  ui->plott->xAxis->setTickLength(0, 4);
                  ui->plott->xAxis->setRange(0, 100);
                  ui->plott->xAxis->setBasePen(QPen(Qt::white));
                  ui->plott->xAxis->setTickPen(QPen(Qt::white));
                  ui->plott->xAxis->grid()->setVisible(true);
                  ui->plott->xAxis->grid()->setPen(QPen(QColor(130, 130, 130), 0, Qt::DotLine));
                  ui->plott->xAxis->setTickLabelColor(Qt::white);
                  ui->plott->xAxis->setLabelColor(Qt::white);

                  // axe des ordonnées
                  ui->plott->yAxis->setRange(0,100);
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
                  QVector<double> ticks;
                  QVector<QString> labels;
                  QSqlQuery q1("select ADRESSE_CLIENT,(count(ADRESSE_CLIENT)*100/ (select count(*)from Client)) as pourcentage from CLIENT group by ADRESSE_CLIENT");
                  while (q1.next()) {
                                int  nbr_fautee = q1.value(1).toInt();
                                PlaceData<< nbr_fautee;
                                QString label = q1.value(0).toString();
                                labels << label;
                  }
                  textTicker->addTicks({10,20,30,40,50,60,70,80,90,100}, labels);
                  amande->setData({10,20,30,40,50,60,70,80,90,100}, PlaceData);

                  ui->plott->legend->setVisible(true);
                  ui->plott->axisRect()->insetLayout()->setInsetAlignment(0, Qt::AlignTop|Qt::AlignHCenter);
                  ui->plott->legend->setBrush(QColor(255, 255, 255, 100));
                  ui->plott->legend->setBorderPen(Qt::NoPen);
                  QFont legendFont = font();
                  legendFont.setPointSize(5);
                  ui->plott->legend->setFont(legendFont);
                  ui->plott->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
}
