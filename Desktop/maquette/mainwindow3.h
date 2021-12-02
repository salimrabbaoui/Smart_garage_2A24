#ifndef MAINWINDOW3_H
#define MAINWINDOW3_H

#include <QMainWindow>
#include "mainwindow.h"
#include "fournisseur.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow3; }
QT_END_NAMESPACE

class MainWindow3 : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow3(QWidget *parent = nullptr);
    ~MainWindow3();

private slots:
    void on_pushButton3_clicked();

private:
    Ui::MainWindow3 *ui;
    fournisseur *home;
};
#endif // MAINWINDOW3_H
