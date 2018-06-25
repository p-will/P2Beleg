//Paul Willam 44093 Bachelor 062

/*
Headerfile der Personenklasse, die zur Verwaltung der Kunden genutzt wird
*/
#ifndef PERSON_H
#define PERSON_H

#include <QString>



class Person 
{
    private:
    QString KuNr;      //enthält Kundennummer
    QString KuName;    //Nachname des Kunden
    QString KuVorname; //Vorname des Kunden
    public:
    Person(QString,QString,QString);  //Konstruktion ohne private Variablen Angabe wird nicht ermöglicht
    ~Person(); //Destruktor der Klasse. Wird aufgerufen, wenn loeschen ausgeführt wird
  //  int loeschen(); //löscht die Person inklusive der Einträge in Ausleihe
    QString getNr() const; //Kundennummer getter
    QString getName() const; //Kundenname getter
    QString getVorname() const; //Kundenvorname getter
    int setNr(QString); // setter analog
    int setName(QString);
    int setVorname(QString);
   // void show() const; //zeigt alle Informationen der Person an
};




#endif
