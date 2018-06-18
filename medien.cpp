//Paul Willam 44093 Bachelor 062

/*
Implementationsfile der Basisklasse Medien
*/


#include "medien.h"
#include <iostream>

inline Medien::Medien(std::string K,std::string T,std::string J,std::string ID)
{
    this->Kuenstler=K;
    this->Titel=T;
    this->Jahr=J;
    this->ISBN=ID;
    this->Rueckgabe="";     //Rückgabe wird später mit stets festen 2 Wochen später berechnet
}

Medien::~Medien()
{
    
}

int Medien::loeschen()
{
     
}

void Medien::show() const
{
    std::cout << "Künstler:  " << this->Kuenstler << std::endl;
    std::cout << "Titel:     " << this->Titel << std::endl;
    std::cout << "Jahr:      " << this->Jahr << std::endl;
    std::cout << "ISBN:      " << this->ISBN << std::endl;
    if(!this->Rueckgabe.empty())
        std::cout << "Rueckgabe: " << this->Rueckgabe << std::endl;
}

inline std::string Medien::getKuenstler() const
{
    return this->Kuenstler;
}

inline std::string Medien::getTitel() const
{
    return this->Titel;
}

inline std::string Medien::getJahr() const
{
    return this->Jahr;
}

inline std::string Medien::getISBN() const
{
    return this->ISBN;
}

std::string Medien::getRueckgabe() const
{
   if(!this->Rueckgabe.empty())
       return this->Rueckgabe;
   std::cout << "Medium momentan nicht ausgeliehen" << std::endl;
}

int Medien::setKuenstler(std::string Name)
{
    this->Kuenstler=Name;
    std::cout << "Änderung des Künstlernamens erfolgreich." << std::endl;
    return 0;
}

int Medien::setTitel(std::string Name)
{
    this->Titel=Name;
    std::cout << "Änderung des Titels erfolgreich." << std::endl;
    return 0;
}

int Medien::setJahr(std::string J)
{
    this->Jahr=J;
    std::cout << "Änderung des Veröffentlichungsjahres erfolgreich." << std::endl;
    return 0;
}

int Medien::setISBN(std::string ID)
{
    this->ISBN=ID;
    std::cout << "Änderung der ISBN erfolgreich." << std::endl;
    return 0;
}

int Medien::setRueckgabe(std::string Datum)
{
    this->Rueckgabe=Datum;
    std::cout << "Änderung des Rückgabedatums erfolgreich." << std::endl;
    return 0;
}