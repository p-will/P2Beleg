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
Medien::~Medien()
{
    
}

inline QString Medien::getKuenstler() const
{
    return this->Kuenstler;
}

inline QString Medien::getTitel() const
{
    return this->Titel;
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
    std::cout << "Änderung des Titels erfolgreich." << std::endl;
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
ret.append(this->Kuenstler+"\n");
ret.append(this->Titel+"\n");
ret.append(this->Jahr+"\n");
ret.append(this->ISBN+"\n");

return ret;
}

