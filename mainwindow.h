#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include "employe.h"
#include "conge.h"
QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pb_ajouter_clicked();

    void on_pb_supprimer_clicked();

    void on_pb_modifier_clicked();



    void on_pb_rechercher_clicked();

    void on_ajouter_conge_clicked();

    void on_supp_conge_clicked();



    void on_pb_pdf_clicked();

    void on_pb_imp_clicked();

    void on_pushButton_clicked();

    void on_sendBtn_clicked();

    void on_modifier_conge_clicked();

    void on_pushButton_2_clicked();

    void on_pb_tri_clicked();

    void on_pb_type_clicked();

    void on_pb_cin_clicked();

    void sendMail();
    void mailSent(QString);
    void browse();


    void on_tab_employe1_activated(const QModelIndex &index);

private:
    Ui::MainWindow *ui;
    QStringList files;


};




#endif // MAINWINDOW_H
