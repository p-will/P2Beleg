//Paul Willam 44093 Bachelor 062

/*
Implementationsfile der abgeleiteten Buch Klasse
*/

#include "buch.h"

Buch::Buch(QString K,QString T,QString J,QString ID,QString Nr)
{
    this->Kuenstler=K;                                //Konstruktor befüllt die Variablen
    this->Titel=T;
    this->Jahr=J;
    this->ISBN=ID;
    this->Auflage=Nr;
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
*/
    QString ret{""};                                            //erzeugt leeren String, dem dann die Informationen mit Zeilenumbrüchen angehängt werden
    ret.append(this->Kuenstler+"\n");
    ret.append(this->Titel+"\n");
    ret.append(this->Jahr+"\n");
    ret.append(this->ISBN+"\n");
    ret.append(this->Auflage+"\n");

    return ret; //Rückgabe des Strings, damit dieser in der QMessageBox direkt genutzt werden kann
}

