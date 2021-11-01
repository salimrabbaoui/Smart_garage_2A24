
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "employe.h"
#include <QMessageBox>
#include <QIntValidator>



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tab_employe->setModel(E.afficher());
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pb_ajouter_clicked()
{
    int cin=ui->le_cin->text().toInt();
    int age=ui->le_age->text().toInt();
    QString nom=ui->le_nom->text();
    QString prenom=ui->le_prenom->text();
    QString prenom=ui->le_type->text();
    Etudiant E(id,nom,prenom);
    bool test=E.ajouter();
    QMessageBox msgBox;

    if(test)
{
        msgBox.setText("Ajout avec succes.");
    ui->tab_employe->setModel(E.afficher());
    }else
        msgBox.setText("Echec d'ajout");
        msgBox.exec();

}

void MainWindow::on_pb_supprimer_clicked()
{
    Employe E1; E1.setcin(ui->le_cin_supp->text().toInt());
    bool test=E1.supprimer(E1.getcin());
     QMessageBox msgBox;
     if(test)
 {
         msgBox.setText("SUPPRESSION avec succes.");
     ui->tab_employe->setModel(E.afficher());
     }else
         msgBox.setText("Echec DE SUPPRESSION");
         msgBox.exec();
}
