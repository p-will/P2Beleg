//Paul Willam 44093 Bachelor 062

/*
 * Header File für Datenliste, die für die Infos der ausgeliehenen Medien,sowie zur Überprüfung der Datenkonsistenz genutzt wird
 */

#ifndef DATALIST_H
#define DATALIST_H

#include <list>
#include <vector>
#include "medien.h"
#include "person.h"
#include "cd.h"          //Header benötigt um Daten zu halten
#include "buch.h"


class datalist
{
public:
    datalist();   //Defaultkonstruktor der Klasse wird genutzt; keine Parameter nötig
    ~datalist();  //Destruktor der Klasse;
    void leeren(); //leert die einzelnen Listen und Vektoren, ohne die Datalist zu löschen.
    std::list<Medien*> data;    //enthält alle Medien, wobei dann durch data->getInfo() const die jeweiligen Medien-Informationen ausgegeben werden
    std::vector<QString> pID;   //enthält alle bekannten Kundennummern; notwendig für Datenkonsistenz im Personendatenbestand
    //std::list<Person*> pdata;
    std::vector<QString> ID;  //enthält die ISBNs der Medien in Data in der selben Reihenfolge, wie sie in data vorzufinden sind.
                              //ermöglicht einfachere suche und gewährleistung der Datenkonsistenz im Medien- und Ausleihdatenbestand
private:
};
#endif // DATALIST_H
