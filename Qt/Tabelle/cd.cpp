//Paul Willam 44093 Bachelor 062

/*
Implementationsfile der CD Klasse
*/

#include "cd.h"
#include <iostream>

CD::CD(QString K,QString T,QString J,QString ID)
{
    Medien(K,J,T,ID);
}

CD::~CD()
{

}

QString CD::getInfo() const
{/*
    std::cout<<"Künstler:       " << this->Kuenstler << std::endl;
    std::cout<<"Titel:          " << this->Titel << std::endl;
    std::cout<<"Jahr:           " << this->Jahr << std::endl;
    std::cout<<"ISBN:           " << this->ISBN << std::endl;
    if(!this->Rueckgabe.empty())
    std::cout<<"Rueckgabedatum: " << this->Rueckgabe << std::endl;
*/}

/*int CD::ausleihen()
{
    
}
*/
