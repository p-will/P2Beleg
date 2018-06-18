//Paul Willam 44093 Bachelor 062

/*
Headerfile der Personenklasse, die zur Verwaltung der Kunden genutzt wird
*/
#ifndef PERSON_H
#define PERSON_H

#include <string>



class Person 
{
    private:
    std::string KuNr;      //enthält Kundennummer
    std::string KuName;    //Nachname des Kunden
    std::string KuVorname; //Vorname des Kunden
    public:
    Person(std::string,std::string,std::string);  //Konstruktion ohne private Variablen Angabe wird nicht ermöglicht
    ~Person(); //Destruktor der Klasse. Wird aufgerufen, wenn loeschen ausgeführt wird
    int loeschen(); //löscht die Person inklusive der Einträge in Ausleihe
    std::string getNr() const; //Kundennummer getter
    std::string getName() const; //Kundenname getter
    std::string getVorname() const; //Kundenvorname getter
    int setNr(); // setter analog
    int setName();
    int setVorname();
    void show() const; //zeigt alle Informationen der Person an
};




#endif