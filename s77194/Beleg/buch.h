//Paul Willam 44093 Bachelor 062

/*
Header File für abgeleitete Buch Klasse
*/

#ifndef BUCH_H
#define BUCH_H

#include <iostream>
#include <QString>
#include "medien.h"


class Buch: public Medien //wird abgeleitet von der Medien-Klasse
{
    private:
        QString Auflage;  //gibt die Auflage des Buchs an, die zur Verfügung steht. als Qstring übergeben,da kein rechnen notwendig ist und daher kein Bedarf für int-Werte besteht
    public:
        Buch(QString,QString,QString,QString,QString);  //Konstruktor der Buch-Klasse. Kein Defaultkonstruktor spezifiziert, da dieser nicht genutzt wird
        ~Buch(); //Destruktor
        QString getInfo() const; //Funktion, die zur Informationsausgabe eines einzelnen Mediums genutzt wird. Liefert QString zurück, der dann angezeigt wird über QMessageBox
};

#endif
