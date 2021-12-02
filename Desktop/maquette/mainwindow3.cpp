#include "mainwindow3.h"
#include"ui_mainwindow3.h"
#include <QPixmap>
#include <QMessageBox>

MainWindow3::MainWindow3(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow3)
{



    ui->setupUi(this);

    ui->statusbar->showMessage("V 1.4.10");
    ui->label_login->setPixmap(pix.scaled(150,150,Qt::KeepAspectRatio));
    ui->line_username->setPlaceholderText("Nom D'utilisateur");
    ui->line_password->setPlaceholderText("Mot de Passe");
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton3_clicked()
{
    QString username = ui->line_username->text();
    QString password = ui->line_password->text();

    if(username == "admin" && password=="admin"){
        ui->line_username->clear();
        ui->line_password->clear();
        hide();
        home = new class home(this);
        home->show();
    } else {
        ui->incorrect->setText("Nom d'utilisateur ou mot de passe est incorrect ");
        ui->line_username->clear();
        ui->line_password->clear();
    }

}
