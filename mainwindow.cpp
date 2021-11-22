#include "conge.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "employe.h"
#include <QMessageBox>
#include <QIntValidator>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QListWidget>
#include <QtPrintSupport/QPrinter>
#include <QPixmap>
#include "QMessageBox"
#include <QIntValidator>
#include <QSqlQueryModel>
#include <QPrintDialog>
#include <QSqlError>
#include <iostream>
#include <QDebug>
#include <QRadioButton>
#include <QPdfWriter>
#include <QPainter>
#include <QFileDialog>
#include <QTextDocument>
#include <QTextEdit>
#include <QtSql/QSqlQueryModel>
#include <QtPrintSupport/QPrinter>
#include <QVector2D>
#include <QVector>
#include<QDesktopServices>
#include<QUrl>
#include <QPixmap>
#include <QTabWidget>
#include <QValidator>

#include<QtSql/QSqlQuery>
#include<QVariant>
#include <QDateTime>
#include <QPrintDialog>

#include <QRadioButton>
#include <QtPrintSupport/QPrinter>
#include <QPdfWriter>
#include <QFileDialog>
#include <QTextDocument>
#include <QTextEdit>
#include <QtSql/QSqlQueryModel>
#include <QVector2D>
#include <QVector>

#include<QDesktopServices>
#include<QUrl>
#include <QPixmap>
#include <QTabWidget>
#include <QValidator>
#include <QPrintDialog>
#include<QtSql/QSqlQuery>
#include<QVariant>
#include <QDateTime>
#include <QPrinter>
#include  "smtp.h"




MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    Employe E;
    Conge C;
    ui->setupUi(this);
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


void MainWindow::on_pb_supprimer_clicked()
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



void MainWindow::on_pb_modifier_clicked()
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

void MainWindow::sendMail()
{
    Smtp* smtp = new Smtp("mohamedamine.abdessayed@esprit.tn",ui->mail_pass->text(), "smtp.gmail.com");
    connect(smtp, SIGNAL(status(QString)), this, SLOT(mailSent(QString)));

    if( !files.isEmpty() )
        smtp->sendMail("mohamedamine.abdessayed@esprit.tn", ui->rcpt->text() , ui->subject->text(),ui->msg->toPlainText(), files );
    else
        smtp->sendMail("mohamedamine.abdessayed@esprit.tn",ui->rcpt->text() , ui->subject->text(),ui->msg->toPlainText());
}


void MainWindow::mailSent(QString status)
{
    if(status == "Message sent")
        QMessageBox::warning( nullptr, tr( "Qt Simple SMTP client" ), tr( "Message sent!\n\n" ) );
    ui->rcpt->clear();
    ui->subject->clear();
    ui->file->clear();
    ui->msg->clear();
    ui->mail_pass->clear();
}



void MainWindow::browse()
{
    files.clear();

    QFileDialog dialog(this);
    dialog.setDirectory(QDir::homePath());
    dialog.setFileMode(QFileDialog::ExistingFiles);

    if (dialog.exec())
        files = dialog.selectedFiles();

    QString fileListString;
    foreach(QString file, files)
        fileListString.append( "\"" + QFileInfo(file).fileName() + "\" " );

    ui->file->setText( fileListString );
}
void MainWindow::on_sendBtn_clicked()
{
    connect(ui->sendBtn, SIGNAL(clicked()),this, SLOT(sendMail()));
    QMessageBox::warning( 0, tr( "Qt Simple SMTP client" ), tr( "Message sent!\n\n" ) );



}

/* void MainWindow::on_pushButton_clicked()
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
*/

