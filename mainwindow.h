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

    void on_ajoutFacture_2_clicked();
    void on_SuppFacture_2_clicked();
    void on_ModiFacture_2_clicked();



    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();
    void on_pushButton_5_clicked();


    void on_tabWidget_33_currentChanged(int index);

    //////////////////////
    ///// Gestion ////////
    /////// des ////////
    /// employes //////
    /////////////////////


    void on_pb_ajouter_2_clicked();

    void on_pb_supprimer_2_clicked();

    void on_pb_modifier_2_clicked();



    void on_pb_rechercher_clicked();

    void on_ajouter_conge_clicked();

    void on_supp_conge_clicked();



    void on_pb_pdf_clicked();

    void on_pb_imp_clicked();

    void on_pushButton_clicked();


    void on_modifier_conge_clicked();


    void on_pb_tri_clicked();

    void on_pb_type_clicked();

    void on_pb_cin_clicked();





private:
    Ui::MainWindow *ui;
QStringList files;



};
#endif // MAINWINDOW_H
