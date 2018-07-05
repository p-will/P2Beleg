//Paul Willam 44093 Bachelor 062

/*
 * Header File der Qt-basierten Tabelle, auf der alle Hauptoperationen ausgeführt werden
 */


#ifndef TABELLE_H
#define TABELLE_H

#include <QDialog>           //übergeordnete Klasse, von der geerbt werden soll
#include "ui_tabelle.h"
#include "datalist.h"



namespace Ui {
class tabelleWindow;
}

class tabelleWindow : public QDialog, public Ui::tabelleWindow     //erbt von QDialog und der Ui::tabelleWindow
{
    Q_OBJECT

public:
     explicit tabelleWindow(QWidget *parent = 0);          //Konstruktor; ist QWidget untergeordnet; Standardwert = 0
    ~tabelleWindow();                //Destruktor
    datalist *media;                 //enthält Datenliste mit dem Medien und Personenbestand

private slots:                       //slots zum zuordnen zu den jeweiligen Buttons
    void lade_media();               //lädt den Mediendatenbestand in "media.txt"
    void lade_person();              //lädt Personendatenbestand in "person.txt"
    void lade_ausleihe();            //lädt Ausleihdatenbestand in "ausleihe.txt"
    void speichern();                //speichert die Änderungen am Datenbestand in der jeweiligen Datei. Keine Verzeichnisübergabe nötig, da globale Variable über das aktuelle Verzeichnis geführt wird
    void aenderung(QTableWidgetItem *); //wird ausgelöst, wenn ein Item in der Tabelle geändert wird
    void loeschen();                 //dient zum Löschen einer Zeile
    void insert();                   //fügt neue Zeile ein
    void info(QTableWidgetItem *);   //dient zur Informationsausgabe über einzelne Medien mittels media->getInfo() const
    void help();                     //Funktion des Hilfe-Buttons

private:
    Ui::tabelleWindow *ui;
    void neuladen(QString);          //lädt das angegebene Verzeichnis neu aus; wird in fast allen Funktion zur Aktualisierung genutzt
    bool verify(datalist*);          //überprüft Datenkonsistenz vor Speichern der Daten
    bool emptycheck();               //überprüft, ob leere Felder vorhanden sind vor dem Speichern der Daten
    bool valid();                    //überprüft ob Eingaben legitim sind; z.B. ob korrekte Daten für die Rückgabe übergeben wurden
};

#endif // TABELLE_H
