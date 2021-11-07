#ifndef CLIENT_H
#define CLIENT_H
#include <QSqlQueryModel>
#include<QString>
class Client
{
public:
    Client();
    Client(int,QString,QString,int,QString,QString);
    int getCin();
    QString getnom();
    QString getprenom();
    int getNum();
    QString getadresse();
    QString getadresse_mail();
    void setCin(int);
    void setnom(QString);
    void setprenom(QString);
    void setNum(int );
    void setadresse(QString );
    void setadresse_mail(QString );
    bool ajouter();
    bool supprimer(int);
    bool modifier(int);
     QSqlQueryModel * afficher();

private:
    int Cin,Num;
    QString nom,prenom,adresse,adresse_mail;

};

#endif // CLIENT_H
