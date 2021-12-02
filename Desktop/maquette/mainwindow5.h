#ifndef MAINWINDOW5_H
#define MAINWINDOW5_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow5; }
QT_END_NAMESPACE

class MainWindow5 : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow5(QWidget *parent = nullptr);
    ~MainWindow5();
private slots:
 void on_connecter_clicked();
private:
    Ui::MainWindow5 *ui;
};
#endif // MAINWINDOW5_H
