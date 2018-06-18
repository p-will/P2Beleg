//Paul Willam 44093 Bachelor 062

/*
Implementationsfile der abgeleiteten Buch Klasse
*/

#include "buch.h"

Buch::Buch(std::string K,std::string T,std::string J,std::string ID,std::size_t Nr)
{
    this->Auflage=Nr;
    Medien::Medien(K,T,J,ID);
}

Buch::~Buch()
{

}

void Buch::show() const
{
    std::cout<<"Künstler:       " << this->Kuenstler << std::endl;
    std::cout<<"Titel:          " << this->Titel << std::endl;
    std::cout<<"Jahr:           " << this->Jahr << std::endl;
    std::cout<<"ISBN:           " << this->ISBN << std::endl;
    std::cout<<"Auflage:        " << this->Auflage << std::endl;
    if(!this->Rueckgabe.empty())
    std::cout<<"Rueckgabedatum: " << this->Rueckgabe << std::endl;
}

int Buch::ausleihen()
{
    
}
