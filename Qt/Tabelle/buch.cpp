//Paul Willam 44093 Bachelor 062

/*
Implementationsfile der abgeleiteten Buch Klasse
*/

#include "buch.h"

Buch::Buch(QString K,QString T,QString J,QString ID,std::size_t Nr)
{
    this->Auflage=Nr;
    this->Kuenstler=K;
    this->Titel=T;
    this->Jahr=J;
    this->ISBN=ID;
}

Buch::~Buch()
{

}

QString Buch::getInfo() const
{/*
    std::cout<<"Künstler:       " << this->Kuenstler << std::endl;
    std::cout<<"Titel:          " << this->Titel << std::endl;
    std::cout<<"Jahr:           " << this->Jahr << std::endl;
    std::cout<<"ISBN:           " << this->ISBN << std::endl;
    std::cout<<"Auflage:        " << this->Auflage << std::endl;
*/}
