//Paul Willam 44093 Bachelor 062

/*
Implementationsfile der Personenklasse zur Verwaltung der Kunden
*/

#include "person.h"
#include <iostream>

inline Person::Person(QString KNr,QString KName, QString KVorname)
{
    this->KuNr=KNr;
    this->KuName=KName;
    this->KuVorname=KVorname;
}

Person::~Person()
{

}

/*int Person::loeschen()
{

}
*/
inline QString Person::getNr() const
{
    return this->KuNr;
}

inline QString Person::getName() const
{
    return this->KuName;
}

inline QString Person::getVorname() const
{
    return this->KuVorname;
}

int Person::setNr(QString Nr)
{
    this->KuNr=Nr;
    std::cout << "Kundennummer erfolgreich geändert" <<  std::endl;
    return 0;
}

int Person::setName(QString Name)
{
    this->KuName=Name;
    std::cout << "Kundenname erfolgreich geändert" << std::endl;
    return 0;
}

int Person::setVorname(QString Vorname)
{
    this->KuVorname=Vorname;
    std::cout << "Kundenvorname erfolgreich geändert" << std::endl;
    return 0;
}

/*void Person::show() const
{
    std::cout << "Kundennummer:  " << this->KuNr << std::endl;
    std::cout << "Kundenname:    " << this->KuName << std::endl;
    std::cout << "Kundenvorname: " << this->KuVorname << std::endl;
}*/
