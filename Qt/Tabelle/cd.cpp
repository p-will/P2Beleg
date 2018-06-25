//Paul Willam 44093 Bachelor 062

/*
Implementationsfile der CD Klasse
*/

#include "cd.h"
#include <iostream>

CD::CD(QString K,QString T,QString J,QString ID)
{
    this->Kuenstler=K;
    this->Titel=T;
    this->Jahr=J;
    this->ISBN=ID;
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
*/
    QString ret{""};
    ret.append(this->Kuenstler+"\n");
    ret.append(this->Titel+"\n");
    ret.append(this->Jahr+"\n");
    ret.append(this->ISBN+"\n");

    return ret;
}

/*int CD::ausleihen()
{
    
}
*/
