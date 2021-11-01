#ifndef EMPLOYE_H
#define EMPLOYE_H
#include <QString>
#include <QSqlQueryModel>

class Employe
{
public:
    Employe();
    Employe(int,QString,QString,int,QString);

    int getcin();
    int getage();
    QString getnom();
    QString getprenom();
    QString gettype();

    void setcin(int);
    void setage(int);
    void setNom(QString);
    void setPrenom(QString);
    void setType(QString);

    bool ajouter();
     QSqlQueryModel*afficher();
     bool supprimer(int);


private:
    int cin , age;
    QString Nom, Prenom, Type;
};

#endif // EMPLOYE_H



