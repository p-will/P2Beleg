//Paul Willam 44093 Bachelor 062

/*
Headerfile für die Übergeordnete Medienklasse
*/

#ifndef MEDIEN_H
#define MEDIEN_H

#include <string>

class Medien 
{
    private:
    std::string Kuenstler; //enthält den Namen des Autors/Interpreten
    std::string Titel; //enthält Namen des Buchs/Songs/Albums
    std::string Jahr; //enthält Erscheinungs-/Veröffentlichungsjahr
    std::string ISBN; //enthält einmalige ISBN des Mediums
    std::string Rueckgabe; //enthält fälliges Rückgabedatum
    public:
    Medien(); //Konstruktor
    ~Medien(); //Destruktor
    void show() const; //zeigt alle Informationen des Mediums an
    std::string getKuenstler() const; //Künstler getter
    std::string getTitel() const; //Titel getter
    std::string getJahr() const; //Veröffentlichungsjahr getter
    std::string getISBN() const; //ISBN getter
    std::string getRueckgabe() const; //Rückgabedatum getter
    int setKuenstler(); //Künstler setter
    int setTitel(); //Titel setter
    int setJahr(); //Veröffentlichungsjahr setter
    int setISBN(); //ISBN setter
    int setRueckgabe(); //Rückgabedatum setter
    int loeschen(); //löscht Medium inklusive in Ausleihe befindlicher Medien
};

#endif