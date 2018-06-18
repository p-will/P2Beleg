//Paul Willam 44093 Bachelor 062

/*
Implementationsfile der Personenklasse zur Verwaltung der Kunden
*/

#include "person.h"
#include <iostream>

inline Person::Person(std::string KNr,std::string KName, std::string KVorname)
{
    this->KuNr=KNr;
    this->KuName=KName;
    this->KuVorname=KVorname;
}

Person::~Person()
{

}

int Person::loeschen()
{

}

inline std::string Person::getNr() const
{
    return this->KuNr;
}

inline std::string Person::getName() const
{
    return this->KuName;
}

inline std::string Person::getVorname() const
{
    return this->KuVorname;
}

int Person::setNr(std::string Nr)
{
    this->KuNr=Nr;
    std::cout << "Kundennummer erfolgreich geändert" <<  std::endl;
    return 0;
}

int Person::setName(std::string Name)
{
    this->KuName=Name;
    std::cout << "Kundenname erfolgreich geändert" << std::endl;
    return 0;
}

int Person::setVorname(std::string Vorname)
{
    this->KuVorname=Vorname;
    std::cout << "Kundenvorname erfolgreich geändert" << std::endl;
}

void Person::show() const
{
    std::cout << "Kundennummer:  " << this->KuNr << std::endl;
    std::cout << "Kundenname:    " << this->KuName << std::endl;
    std::cout << "Kundenvorname: " << this->KuVorname << std::endl;
}