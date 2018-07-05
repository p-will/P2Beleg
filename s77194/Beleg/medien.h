//Paul Willam 44093 Bachelor 062

/*
Headerfile für die Übergeordnete Medienklasse
*/

#ifndef MEDIEN_H
#define MEDIEN_H

#include <QString>

class Medien 
{
    protected:
    QString Kuenstler; //enthält den Namen des Autors/Interpreten
    QString Titel; //enthält Namen des Buchs/Songs/Albums
    QString Jahr; //enthält Erscheinungs-/Veröffentlichungsjahr
    QString ISBN; //enthält einmalige ISBN des Mediums
//    QString Rueckgabe; //enthält fälliges Rückgabedatum
    public:
    Medien()
    {
        this->Kuenstler="";
        this->Titel="";                                                  //Einbindung der beiden Konstruktoren in der Headerdatei, da inline erwünscht aufgrund der Kürze
        this->Jahr="";
        this->ISBN="";
    } //Defaultkonstruktor
    Medien(QString K,QString T,QString J,QString ID)
    {
        this->Kuenstler=K;
        this->Titel=T;
        this->Jahr=J;
        this->ISBN=ID;
    }
     //Konstruktor; Rückgabedatum wird berechnet. Übergabe nicht nötig;
    ~Medien(); //Destruktor
    QString getKuenstler() const; //Künstler getter
    QString getTitel() const; //Titel getter
    QString getJahr() const; //Veröffentlichungsjahr getter
    QString getISBN() const
    {
        return this->ISBN;
    } //ISBN getter
   virtual QString getInfo() const;
//    QString getRueckgabe() const; //Rückgabedatum getter
    int setKuenstler(QString); //Künstler setter
    int setTitel(QString); //Titel setter
    int setJahr(QString); //Veröffentlichungsjahr setter
    int setISBN(QString); //ISBN setter
//    int setRueckgabe(QString); //Rückgabedatum setter
    //int loeschen(); //löscht Medium inklusive in Ausleihe befindlicher Medien
};

#endif
