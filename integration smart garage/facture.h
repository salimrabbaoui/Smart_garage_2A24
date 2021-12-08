#ifndef FACTURE_H
#define FACTURE_H
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>

class facture
{
public:
    facture();
    facture(int,int,int);
    int getNum();
    int getPrixAchat();
    int getPrixVente();
    QString getDate();
    bool ajouter();
    QSqlQueryModel *afficher();
    bool supprimer(int id );
    bool modifier(int);
    int calcul(int,int);
private:
   int numfacture,prixachat,prixvente,gain;



};

#endif // FACTURE_H
