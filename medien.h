//Paul Willam 44093 Bachelor 062

/*
Headerfile für die Übergeordnete Medienklasse
*/

#ifndef MEDIEN_H
#define MEDIEN_H

#include <string>
#include "path.h"

class Medien 
{
    protected:
    std::string Kuenstler; //enthält den Namen des Autors/Interpreten
    std::string Titel; //enthält Namen des Buchs/Songs/Albums
    std::string Jahr; //enthält Erscheinungs-/Veröffentlichungsjahr
    std::string ISBN; //enthält einmalige ISBN des Mediums
    std::string Rueckgabe; //enthält fälliges Rückgabedatum
    public:
    Medien(); //Defaultkonstruktor
    Medien(std::string,std::string,std::string,std::string); //Konstruktor; Rückgabedatum wird berechnet. Übergabe nicht nötig;
    ~Medien(); //Destruktor
    std::string getKuenstler() const; //Künstler getter
    std::string getTitel() const; //Titel getter
    std::string getJahr() const; //Veröffentlichungsjahr getter
    std::string getISBN() const; //ISBN getter
    std::string getRueckgabe() const; //Rückgabedatum getter
    int setKuenstler(std::string); //Künstler setter
    int setTitel(std::string); //Titel setter
    int setJahr(std::string); //Veröffentlichungsjahr setter
    int setISBN(std::string); //ISBN setter
    int setRueckgabe(std::string); //Rückgabedatum setter
    int loeschen(); //löscht Medium inklusive in Ausleihe befindlicher Medien
};

#endif