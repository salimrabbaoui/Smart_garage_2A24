#ifndef ADMINN_H
#define ADMINN_H
#include <QMainWindow>
#include <QDialog>

namespace Ui {
class Adminn;
}

class Adminn : public QDialog
{
    Q_OBJECT

public:
    explicit Adminn(QWidget *parent = nullptr);
    ~Adminn();

    bool verif_profil();
    void vider_profil();

private slots:
    void on_ajouter_profil_clicked();


    void on_nouveau_profil_clicked();



private:
    Ui::Adminn *ui;
};

#endif // ADMINN_H
