//Paul Willam 44093 Bachelor 062

/*
Headerfile der abgeleiteten Klasse für CD Medien
*/

#ifndef CD_H
#define CD_H

#include <QString>
#include "medien.h"


class CD: public Medien    //abgeleitet von der Medien-Klasse
{
    private:
                   //keine weiteren Variablen
    public:
    CD(QString,QString,QString,QString); //Konstruktor der Klasse. Kein Defaultkonstruktor spezifiziert, da dieser nicht genutzt wird
    ~CD(); // Destruktor der CD Klasse
    QString getInfo() const; //ähnlich Buch::getInfo() -> gibt Informationen des Mediums zurück als QString, der über QMessageBox ausgegeben wird.
};


#endif
