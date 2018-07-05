//Paul Willam 44093 Bachelor 062

/*
Implementationsfile der Basisklasse Medien
*/


#include "medien.h"
#include <iostream>
/*
inline Medien::Medien()
{
    this->Kuenstler="";
    this->Titel="";
    this->Jahr="";
    this->ISBN="";
}

inline Medien::Medien(QString K,QString T,QString J,QString ID)
{
    this->Kuenstler=K;
    this->Titel=T;
    this->Jahr=J;
    this->ISBN=ID;
}
*/

//sowohl getter, als auch setter-Funktionen werden aufgrund der Funktionsweise der Qt-Tabelle nicht benötigt; wurden aber deklariert und definiert für den Fall, dass sie anderweitig
// gebraucht werden
Medien::~Medien()
{
    
}

inline QString Medien::getKuenstler() const
{
    return this->Kuenstler;
}

inline QString Medien::getTitel() const
{
    return this->Titel;                                    //getter Funktionen; aufgrund ihrer Kürze auch als inline definiert
}

inline QString Medien::getJahr() const
{
    return this->Jahr;
}

/*inline QString Medien::getISBN() const
{
    return this->ISBN;
}
*/
int Medien::setKuenstler(QString Name)
{
    this->Kuenstler=Name;
    std::cout << "Änderung des Künstlernamens erfolgreich." << std::endl;
    return 0;
}

int Medien::setTitel(QString Name)
{
    this->Titel=Name;
    std::cout << "Änderung des Titels erfolgreich." << std::endl;                //setter Funktionen
    return 0;
}

int Medien::setJahr(QString J)
{
    this->Jahr=J;
    std::cout << "Änderung des Veröffentlichungsjahres erfolgreich." << std::endl;
    return 0;
}

int Medien::setISBN(QString ID)
{
    this->ISBN=ID;
    std::cout << "Änderung der ISBN erfolgreich." << std::endl;
    return 0;
}

QString Medien::getInfo() const
{
QString ret{""};
ret.append(this->Kuenstler+"\n");                                  //identisch zur getInfo() const Funktion der CD-Klasse
ret.append(this->Titel+"\n");
ret.append(this->Jahr+"\n");
ret.append(this->ISBN+"\n");

return ret;
}

