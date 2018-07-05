//Paul Willam 44093 Bachelor 062

/*
 * Implementationsfile der Datenliste
 */

#include "datalist.h"
#include <QString>
#include <QFile>
#include <QMessageBox>
#include <QTextStream>
#include <QtGui>

const size_t COUNTBUCHPROPERTIES{6};           //Anzahl der Variablen der Buch Klasse
const size_t COUNTCDPROPERTIES{5};             //Anzahl der Variablen der CD Klasse

datalist::datalist()
{
    QString line;                           //wird zeilenweise befüllt
    std::vector<QString> properties;        //QString vector, in den Zeilenweise die einzelnen Spalten gefüllt und dem später die gewünschten Spalten entnommen werden
    QString verzeichnis=QDir::currentPath();  //befüllt mit absolutem Pfad zu "ausleihe.txt" ; muss sich im selben Ordner befinden
    verzeichnis.append("/ausleihe.txt");
    QFile datei(verzeichnis);               //Initialisierung des QFiles mit dem gegebenen Pfad
    if(!datei.open(QIODevice::ReadOnly | QIODevice::Text))   //überprüfen, ob öffnen erfolgreich
    {
         QMessageBox::warning(0,"Warnung","Fehler beim Öffnen der Mediendatei");
    }

    QTextStream input(&datei);              //input textstream
    line = input.readLine();                //lesen der ersten Zeile

    while(!input.atEnd())                  //while schleife, solange die input-Datei noch nicht am Ende angelangt ist
    {
        int pos1{0};
        int pos2{0};                      //dienen dem Algorithmus für das Auslesen der einzelnen Spalten
        int lastpos{0};
        line = input.readLine();         //bereits nächste Zeile lesen -> überspringen der Kopfzeile in der Datei
        while(pos1!=-1)
        {
            pos1=line.indexOf("\"",lastpos);
            lastpos=pos1+1;                  //Algorithmus zum Spalten auslesen; stückweises vorrücken zwischen " " und herausschneiden der Spalte
            pos2=line.indexOf("\"",lastpos);
            lastpos=pos2+1;
            if(pos1!=-1)
            {
                properties.push_back(line.mid((pos1+1),(pos2-pos1-1)));
            }
        }
        if(properties.size()==COUNTBUCHPROPERTIES)            //wenn Anzahl der QStrings im Vector der Anzahl an Eigenschaften der Buchklasse entspricht wurde ein Buch eingelesen
        {
            Buch *member = new Buch(properties.at(1),properties.at(2),properties.at(3),properties.at(4),(properties.at(5)));   //properties.at(0) übersprungen, da dies nur die Medienart angibt
           // CD *member = new CD(properties.at(1),properties.at(2),properties.at(3),properties.at(4));
            data.push_back(member);                                            //pushen des neuen Members in die Medienliste
        }
        else if(properties.size()==COUNTCDPROPERTIES)      //wenn Anzahl der QStrings im Vector = Anzahl der Eigenschaften der CD Klasse entspricht wurde eine CD eingelesen
        {
            CD *member = new CD(properties.at(1),properties.at(2),properties.at(3),properties.at(4));
            data.push_back((member));               //s.o.
        }
        properties.clear();   //leeren von Properties, damit Daten der neuen Zeile eingefüllt werden können
    }
    datei.close();            //datei schließen
    for(auto const& i: data)  //über auto Datentyp automisch bestimmen lassen; durch einzelne Elemente von Data iterieren
    {
        ID.push_back(i->getISBN());   //ISBN des momentanen Mediums in den ISBN Vector pushen
    }


    verzeichnis=QDir::currentPath();
    verzeichnis.append("/person.txt");   //Verzeichnis neu belegen mit dem absoluten Pfad zu "person.txt"

    QFile pdatei(verzeichnis);
    if(!pdatei.open(QIODevice::ReadOnly | QIODevice::Text))        //überprüfen ob öffnen erfolgreich
    {
        QMessageBox::warning(0,"Warnung","Fehler beim Öffnen der Mediendatei");
    }

    QTextStream pinput(&pdatei);        //neuen Inputstream mit referenz auf Personendatei erzeugen
        line = pinput.readLine();       //Kopfzeile einlesen, um zu überspringen

        while(!pinput.atEnd())          //Abbruch, wenn Inputstream am Ende angelangt
        {
            int pos1{0};
            int pos2{0};
            int lastpos{0};             //s.o.
            line = pinput.readLine();
            while(pos1!=-1)
            {
                pos1=line.indexOf("\"",lastpos);
                lastpos=pos1+1;
                pos2=line.indexOf("\"",lastpos);
                lastpos=pos2+1;
                if(pos1!=-1)
                {
                    properties.push_back(line.mid((pos1+1),(pos2-pos1-1)));
                }
            }

            /*Person *Kunde = new Person(properties.at(0),properties.at(1),properties.at(2));
            pdata.push_back(Kunde);
            */
            pID.push_back(properties.at(0));           //nur Kundennummer benötigt, daher keine weitere Liste der einzelnen Personen nötig
            properties.clear();                        //properties löschen, um mit Daten der nächsten Zeile zu befüllen
        }
    pdatei.close();
}

datalist::~datalist()
{
    data.clear();
    ID.clear();
    pID.clear();
}
                                                    //leert zunächst die Datenlisten/Vectoren, damit sie ohne Probleme gelöscht werden können
void datalist::leeren()
{
    data.clear();
    ID.clear();
    pID.clear();
}
