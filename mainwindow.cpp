#include "mainwindow.h"
#include "ui_mainwindow.h"
#include"fournisseur.h"
#include<QMessageBox>
#include "conge.h"
#include "employe.h"

#include<QIntValidator>
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
    Employe E;
    Conge C;

ui->tabWidget->hide();
ui->comboBox_3->setModel(temFacture.afficher());
ui->comboBox_5->setModel(temFacture.afficher());
  ui->tableView_3->setModel(temFacture.afficher());
    ui->le_id->setValidator(new QIntValidator(0, 9999999, this));
    ui->le_num->setValidator(new QIntValidator(0, 99999999, this));
    ui->NumFacAj_2->setValidator(new QIntValidator(0,99999,this));//numfactureproduit//

    ui->tab_fournisseur->setModel(f.afficher());

    connect(ui->exitBtn_6, SIGNAL(clicked()),this, SLOT(close()));
    connect(ui->exitBtn_2, SIGNAL(clicked()),this, SLOT(close()));
    connect(ui->exitBtn_3, SIGNAL(clicked()),this, SLOT(close()));
    connect(ui->exitBtn_4, SIGNAL(clicked()),this, SLOT(close()));
    connect(ui->exitBtn_8, SIGNAL(clicked()),this, SLOT(close()));



    //employe
    ui->le_age->setValidator(new QIntValidator(0,99,this));
    ui->le_cin->setValidator(new QIntValidator(0,9999999,this));
    ui->tab_employe->setModel(E.afficher());
    ui->tab_tri->setModel(E.afficher());
    //conge
    ui->lecin_c->setValidator(new QIntValidator(0,9999999,this));
    ui->leid_c->setValidator(new QIntValidator(0,9999999,this));

    ui->tab_conge->setModel(C.afficher_c());


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
            ui->tabWidget->show();

setCentralWidget(ui->tabWidget) ;




        }}
    else {
        QMessageBox::warning(this, "Login","Desole Vous n'etes pas un Admin");
}

}


void MainWindow::on_pushButton_5_clicked()
{


    QTableView *table;
               table = ui->tableView_3;

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
void MainWindow::on_ajoutFacture_2_clicked()
{facture temFacture;

    int numfacture=ui->NumFacAj_2->text().toInt();
    int prixachat=ui->PrixachatAj_2->text().toInt();
    int prixvente=ui->PrixVenteFacAj_2->text().toInt();
    facture F(numfacture,prixachat,prixvente);
    bool test=F.ajouter();
    QMessageBox msgBox;
    if(test)
    { ui->tableView_3->setModel(temFacture.afficher());
        ui->comboBox_3->setModel(temFacture.afficher());
        ui->comboBox_5->setModel(temFacture.afficher());

        msgBox.setText("ajouter avec succés");}
    else
        msgBox.setText("echeck d'ajout");
    msgBox.exec();
}






void MainWindow::on_SuppFacture_2_clicked()
{

    int numfacture=ui->comboBox_5->currentText().toInt();
    facture F;
    bool test=F.supprimer(numfacture);
    if(ui->comboBox_5->currentText().contains(QRegExp("^[1-9]"))==0){
     (tr("Notification"),tr(" liste vide"));
        QMessageBox::information(nullptr, QObject::tr("ERREUR"),
                               QObject::tr("ERREUR.\n"
                                           "Click Cancel to exit."), QMessageBox::Cancel);
    }
    else {
    if (test)
    {    (tr("Notification"),tr("Facture supprimée"));
        ui->tableView_3->setModel(F.afficher());
        QMessageBox::information(nullptr, QObject::tr("suppression facture"),
                    QObject::tr("facture supprimé.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
        ui->comboBox_3->setModel(F.afficher());
        ui->comboBox_5->setModel(F.afficher());


    }

    }
}

void MainWindow::on_ModiFacture_2_clicked()

{
    int numfacture =ui->comboBox_3->currentText().toInt();
    int prixachat=ui->PrixachatModpr_2->text().toInt();
    int prixvente=ui->PrixventeModfac_2->text().toInt();

      facture F( numfacture,prixachat,prixvente);
      bool test=F.modifier(numfacture);
      if(ui->comboBox_3->currentText().contains(QRegExp("^[1-9]"))==0){
      (tr("Notification"),tr(" liste vide"));
          QMessageBox::information(nullptr, QObject::tr("ERREUR"),
                                 QObject::tr("ERREUR.\n"
                                             "Click Cancel to exit."), QMessageBox::Cancel);
      }
      else{
      if(test)
    { (tr("Notification"),tr(" Modification validée"));
          ui->comboBox_3->setModel(F.afficher());
          ui->tableView_3->setModel(F.afficher());
          ui->comboBox_5->setModel(F.afficher());

    QMessageBox::information(nullptr, QObject::tr("modifier une facture"),
                      QObject::tr("Facture modifiée.\n"
                                  "Click Cancel to exit."), QMessageBox::Cancel);
ui->comboBox_3->setModel(F.afficher());
    }
}
}


void MainWindow::on_tabWidget_33_currentChanged(int index)
{fournisseur f;
    // background //
              QLinearGradient gradient(0, 0, 0, 400);
              gradient.setColorAt(0, QColor(90, 90, 90));
              gradient.setColorAt(0.38, QColor(105, 105, 105));
              gradient.setColorAt(1, QColor(70, 70, 70));
              ui->plot->setBackground(QBrush(gradient));

              QCPBars *amande = new QCPBars(ui->plot->xAxis, ui->plot->yAxis);
              amande->setAntialiased(false);
              amande->setStackingGap(1);
               //couleurs
              amande->setName("Repartition des voitures selon fournisseur");
              amande->setPen(QPen(QColor(0, 168, 140).lighter(130)));
              amande->setBrush(QColor(0, 168, 140));

               //axe des abscisses
              QVector<double> ticks;
              QVector<QString> labels;
              f.statistique(&ticks,&labels);

              QSharedPointer<QCPAxisTickerText> textTicker(new QCPAxisTickerText);
              textTicker->addTicks(ticks, labels);
              ui->plot->xAxis->setTicker(textTicker);
              ui->plot->xAxis->setTickLabelRotation(60);
              ui->plot->xAxis->setSubTicks(false);
              ui->plot->xAxis->setTickLength(0, 4);
              ui->plot->xAxis->setRange(0, 8);
              ui->plot->xAxis->setBasePen(QPen(Qt::white));
              ui->plot->xAxis->setTickPen(QPen(Qt::white));
              ui->plot->xAxis->grid()->setVisible(true);
              ui->plot->xAxis->grid()->setPen(QPen(QColor(130, 130, 130), 0, Qt::DotLine));
              ui->plot->xAxis->setTickLabelColor(Qt::white);
              ui->plot->xAxis->setLabelColor(Qt::white);

              // axe des ordonnées
              ui->plot->yAxis->setRange(0,10);
              ui->plot->yAxis->setPadding(5);
              ui->plot->yAxis->setLabel("Statistiques");
              ui->plot->yAxis->setBasePen(QPen(Qt::white));
              ui->plot->yAxis->setTickPen(QPen(Qt::white));
              ui->plot->yAxis->setSubTickPen(QPen(Qt::white));
              ui->plot->yAxis->grid()->setSubGridVisible(true);
              ui->plot->yAxis->setTickLabelColor(Qt::white);
              ui->plot->yAxis->setLabelColor(Qt::white);
              ui->plot->yAxis->grid()->setPen(QPen(QColor(130, 130, 130), 0, Qt::SolidLine));
              ui->plot->yAxis->grid()->setSubGridPen(QPen(QColor(130, 130, 130), 0, Qt::DotLine));

              // ajout des données  (statistiques du fournisseur)//

              QVector<double> PlaceData;
              QSqlQuery q1("select id  from FOURNISSEUR");
              while (q1.next()) {
                            int  nbr_fautee = q1.value(0).toInt();
                            PlaceData<< nbr_fautee;
                              }
              amande->setData(ticks, PlaceData);

              ui->plot->legend->setVisible(true);
              ui->plot->axisRect()->insetLayout()->setInsetAlignment(0, Qt::AlignTop|Qt::AlignHCenter);
              ui->plot->legend->setBrush(QColor(255, 255, 255, 100));
              ui->plot->legend->setBorderPen(Qt::NoPen);
              QFont legendFont = font();
              legendFont.setPointSize(5);
              ui->plot->legend->setFont(legendFont);
              ui->plot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
}

void MainWindow::on_pushButton_4_clicked()
{
    QString link="https://mail.google.com/mail/u/0/#inbox?compose=new";
    QDesktopServices::openUrl(link);



}

void MainWindow::on_pushButton_3_clicked()
{
    fournisseur F;
        QString crit=ui->comboBox->currentText();
        if(crit=="Type_produit")
        {
            ui->tableView_tri->setModel(F.trietype_voiture());
        }
        else
        {
            ui->tableView_tri->setModel(F.trieid());
        }

}
/*gestion des employes*/
void MainWindow::on_pb_ajouter_2_clicked()
{
    int cin=ui->le_cin->text().toInt();

    QString Nom=ui->le_nom->text();
    QString Prenom=ui->le_prenom->text();
    int age=ui->le_age->text().toInt();
    QString Type=ui->le_type->text();
    Employe E(cin,Nom,Prenom,age,Type);
    bool test=E.ajouter();
    QMessageBox msgBox;

    if(test)
{
        ui->tab_employe->setModel(E.afficher());
        msgBox.setText("Ajout avec succes.");

    }else
        msgBox.setText("Echec d'ajout");
        msgBox.exec();

}


void MainWindow::on_pb_supprimer_2_clicked()
{
    Employe E; E.setcin(ui->le_cin_supp->text().toInt());
    bool test=E.supprimer(E.getcin());
     QMessageBox msgBox;
     if(test)
 {
         ui->tab_employe->setModel(E.afficher());
         msgBox.setText("Suppression avec succes.");

     }else
         msgBox.setText("Echec de suppression");
         msgBox.exec();
}



void MainWindow::on_pb_modifier_2_clicked()
{
    int cin=ui->le_cin2->text().toInt();



    QString Nom=ui->le_nom2->text();
    QString Prenom=ui->le_prenom2->text();
    int age=ui->le_age2->text().toInt();
     QString Type=ui->le_type2->text();



   Employe E(cin,Nom,Prenom,age,Type);
     bool test=E.modifier(cin);
     if(test)
   {

         ui->tab_employe->setModel(E.afficher());
   QMessageBox::information(nullptr, QObject::tr("modifier un employe"),
                     QObject::tr("employe modifié.\n"
                                 "Click Cancel to exit."), QMessageBox::Cancel);

   }
     else
         QMessageBox::critical(nullptr, QObject::tr("modifier un employe"),
                     QObject::tr("Erreur !.\n"
                                 "Click Cancel to exit."), QMessageBox::Cancel);
}



void MainWindow::on_pb_rechercher_clicked()
{
    class Employe E ;
        ui->tab_employe1->setModel(E.afficher());


           E.recherche(ui);

}

void MainWindow::on_ajouter_conge_clicked()
{
    int cin_c=ui->lecin_c->text().toInt();

    int id_c=ui->leid_c->text().toInt();

    QString duree=ui->leduree_c->text();
    QString date=ui->ledate_c->text();
    QString etat=ui->leetat_c->text();
    Conge C(cin_c,id_c,duree,date,etat);
    bool test=C.ajouter_c();
    QMessageBox msgBox;

    if(test)
{
        ui->tab_conge->setModel(C.afficher_c());
        msgBox.setText("Ajout avec succes.");

    }else
        msgBox.setText("Echec d'ajout");
        msgBox.exec();
}

void MainWindow::on_supp_conge_clicked()
{ Conge C1; C1.setcin_c(ui->lecin_c->text().toInt());//convertir la chaine saisie en un entier car lattribut id est de type int
    bool test=C1.supprimer_c(C1.getcin_c());

    QMessageBox msgBox;
   if (test)
   {
       ui->tab_conge->setModel(C1.afficher_c());
       msgBox.setText("Suppression avec succes");

   }
   else
     msgBox.setText("Echec de suppression");
   msgBox.exec();
}


void MainWindow::on_pb_pdf_clicked()
{
    QString strStream;
            QTextStream out(&strStream);



            const int rowCount = ui->tab_conge->model()->rowCount();
            const int columnCount = ui->tab_conge->model()->columnCount();

            out <<  "<html>\n"
                "<head>\n"

                "<meta Content=\"Text/html; charset=Windows-1251\">\n"
                <<  QString("<title>%60 les postes</title>\n").arg("poste")
                <<  "</head>\n"
                "<body bgcolor=#ffffff link=#5000A0>\n"
                "<table border=1 cellspacing=0 cellpadding=2>\n";
            out << "<thead><tr bgcolor=#f0f0f0>";
            for (int column = 0; column < columnCount; column++)
                if (! ui->tab_conge->isColumnHidden(column))
                    out << QString("<th>%1</th>").arg(ui->tab_conge->model()->headerData(column, Qt::Horizontal).toString());
            out << "</tr></thead>\n";

            for (int row = 0; row < rowCount; row++) {
                out << "<tr>";
                for (int column = 0; column < columnCount; column++) {
                    if (!ui->tab_conge->isColumnHidden(column)) {
                        QString data = ui->tab_conge->model()->data(ui->tab_conge->model()->index(row, column)).toString().simplified();
                        out << QString("<td bkcolor=0>%1</td>").arg((!data.isEmpty()) ? data : QString("&nbsp;"));
                    }
                }
                out << "</tr>\n";
            }
            out <<  "</table>\n"
                "</body>\n"
                "</html>\n";

            QTextDocument *document = new QTextDocument();
            document->setHtml(strStream);

            QPrinter printer;

            QPrintDialog *dialog = new QPrintDialog(&printer, NULL);
            if (dialog->exec() == QDialog::Accepted) {
                document->print(&printer);
            }

            delete document;
}


void MainWindow::on_pb_imp_clicked()
{QString strStream;
    QTextStream out(&strStream);



    const int rowCount = ui->tab_employe->model()->rowCount();
    const int columnCount = ui->tab_employe->model()->columnCount();

    out <<  "<html>\n"
        "<head>\n"

        "<meta Content=\"Text/html; charset=Windows-1251\">\n"
        <<  QString("<title>%60 les postes</title>\n").arg("poste")
        <<  "</head>\n"
        "<body bgcolor=#ffffff link=#5000A0>\n"
        "<table border=1 cellspacing=0 cellpadding=2>\n";
    out << "<thead><tr bgcolor=#f0f0f0>";
    for (int column = 0; column < columnCount; column++)
        if (! ui->tab_employe->isColumnHidden(column))
            out << QString("<th>%1</th>").arg(ui->tab_employe->model()->headerData(column, Qt::Horizontal).toString());
    out << "</tr></thead>\n";

    for (int row = 0; row < rowCount; row++) {
        out << "<tr>";
        for (int column = 0; column < columnCount; column++) {
            if (!ui->tab_employe->isColumnHidden(column)) {
                QString data = ui->tab_employe->model()->data(ui->tab_employe->model()->index(row, column)).toString().simplified();
                out << QString("<td bkcolor=0>%1</td>").arg((!data.isEmpty()) ? data : QString("&nbsp;"));
            }
        }
        out << "</tr>\n";
    }
    out <<  "</table>\n"
        "</body>\n"
        "</html>\n";

    QTextDocument *document = new QTextDocument();
    document->setHtml(strStream);

    QPrinter printer;

    QPrintDialog *dialog = new QPrintDialog(&printer, NULL);
    if (dialog->exec() == QDialog::Accepted) {
        document->print(&printer);
    }

    delete document;

}



void MainWindow::on_modifier_conge_clicked()
{int cin_c=ui->le_cin_modif->text().toInt();

    int id_c=ui->le_id_modif->text().toInt();
    QString date =ui->la_date_modif->text();
    QString duree=ui->la_duree_modif->text();

     QString etat=ui->leetat_c->text();



   Conge C(cin_c,id_c,duree,date,etat);
     bool test=C.modifier_c(cin_c);
     if(test)
   {

         ui->tab_conge->setModel(C.afficher_c());
   QMessageBox::information(nullptr, QObject::tr("modifier un employe"),
                     QObject::tr("employe modifié.\n"
                                 "Click Cancel to exit."), QMessageBox::Cancel);

   }
     else
         QMessageBox::critical(nullptr, QObject::tr("modifier un employe"),
                     QObject::tr("Erreur !.\n"
                                 "Click Cancel to exit."), QMessageBox::Cancel);

}



void MainWindow::on_pb_tri_clicked()
{
    Employe E;

    ui->tab_tri->setModel(E.afficher_Nom());
    }



void MainWindow::on_pushButton_clicked()
{
        QString link="https://mail.google.com/mail/u/0/#inbox";
        QDesktopServices::openUrl(QUrl (link)) ;
    }


void MainWindow::on_pb_type_clicked()
{ Employe E;
    ui->tab_tri->setModel(E.afficher_SERVICE());
}

void MainWindow::on_pb_cin_clicked()
{Employe E;
    ui->tab_tri->setModel(E.afficher_CIN());

}













