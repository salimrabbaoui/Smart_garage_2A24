#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "fournisseur.h"
#include <QMainWindow>
#include <QDialog>
#include <QDebug>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QtWidgets/QMessageBox>
#include <QFileDialog>
#include "facture.h"
#include "qcustomplot.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:



    void on_pb_ajouter_clicked();

    void on_pb_supprimer_clicked();

    void on_pb_modifier_clicked();

    void on_lineEdit_recherche_1_clicked();

    void on_connecter_clicked();
    void on_sendBtn_clicked();

    void on_ajoutFacture_2_clicked();
    void on_SuppFacture_2_clicked();
    void on_ModiFacture_2_clicked();
    void on_pushButton_clicked();

    void on_tabWidget_4_currentChanged(int index);

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();
    void on_pushButton_5_clicked();


    void on_tabWidget_33_currentChanged(int index);

private:
    Ui::MainWindow *ui;




};
#endif // MAINWINDOW_H
