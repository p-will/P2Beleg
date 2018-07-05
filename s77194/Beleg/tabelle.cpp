//Paul Willam 44093 Bachelor 062

/*
 * Implementationsfile der Qt-basierten Tabelle
 */

#include "tabelle.h"
#include <QtGui>
#include <QMessageBox>
#include <string>
#include <QInputDialog>
#include <QDateTime>
#include <vector>

QString currVerzeichnis;        //enthält momentanes Verzeichnis
const size_t ISBNPOS{3};        //Nummer der Spalte, in der ISBN gespeichert ist

tabelleWindow::tabelleWindow(QWidget *parent) :
    QDialog(parent)                      //zunächst Konstruktor von QDialog(parent)
{
    media = new datalist();              //Datenliste erzeugen; media bereits pointer
    setupUi(this);                       //Ui aufsetzen
    connect(saveButton,SIGNAL(clicked()),this,SLOT(speichern()));
    connect(load_person,SIGNAL(clicked()),this,SLOT(lade_person()));
    connect(load_media,SIGNAL(clicked()),this,SLOT(lade_media()));                                           //Verbinden der einzelnen Button mit den jeweiligen Slots in tabelle.
    connect(load_ausleihe,SIGNAL(clicked()),this,SLOT(lade_ausleihe()));
    connect(tabelleWidget,SIGNAL(itemChanged(QTableWidgetItem *)),this,SLOT(aenderung(QTableWidgetItem *))); //ausgelöst bei Itemänderung in Tabelle
    connect(insertButton,SIGNAL(clicked()),this,SLOT(insert()));
    connect(deleteButton,SIGNAL(clicked()),this,SLOT(loeschen()));
    connect(tabelleWidget,SIGNAL(itemClicked(QTableWidgetItem*)),this,SLOT(info(QTableWidgetItem *)));    //ausgelöst, wenn auf Tabellenitem geclicked wird
    connect(helpButton,SIGNAL(clicked()),this,SLOT(help()));
}

tabelleWindow::~tabelleWindow()
{
    delete ui;         //löschen des UI
}

void tabelleWindow::help()            //Funktion des Hilfe-Buttons der Informationen über die Nutzung des Programms ausgibt
{
    QString helpText{""};           //wird mit Inhalt der Textdatei befüllt
    QString verzeichnis = QDir::currentPath();
    verzeichnis.append("/hilfe.txt");          //absoluter Pfad zur Hilfedatei. muss im selben Ordner sein

    QFile hilfe(verzeichnis);

    if(!hilfe.open(QIODevice::ReadOnly | QIODevice::Text))           //überprüfen, ob öffnen fehlgeschlagen
    {
        QMessageBox::warning(this,"Warnung","Hilfe konnte nicht augerufen werden.");
        return;
    }

    QTextStream input_h(&hilfe);      //Inputstream mit Verweis auf die Hilfedatei
    QString line{""};                 //wird Zeilenweise befüllt

    while(!input_h.atEnd())         //Abbruch, wenn an Dateiende
    {
        line = input_h.readLine();
        helpText.append(line);              //Zeile lesen, an helpText anhängen und Zeilenumbruch hinzufügen
        helpText.append("\n");
    }

    hilfe.close();     //datei schließen

    QMessageBox::about(this,"Hilfe",helpText);   //HilfeText mithilfe der static Funktion QMessageBox::about ausgeben; da static Funktion -> keine QMessageBox Instanz notwendig

}

bool tabelleWindow::emptycheck()  //überprüft, ob leere Felder vorhanden sind
{
    for(int z=0;z<tabelleWidget->rowCount();z++)
    {
        if(currVerzeichnis.contains("ausleihe"))  //wenn ausleihe.txt geöffnet ist
        {
            if(tabelleWidget->item(z,tabelleWidget->columnCount()-1)==0 || tabelleWidget->item(z,tabelleWidget->columnCount()-1)->text().isEmpty())
            {
                QDateTime datum=QDateTime::currentDateTime();
                datum=datum.addDays(21);                                              //automatisches Befüllen der Datumsspalte mit Datum in 21 Tagen, wenn Datumsspalte leer ist
                tabelleWidget->setItem(z,tabelleWidget->columnCount()-1,new QTableWidgetItem(datum.toString("dd.MM.yyyy")));

            }
        }
        for(int i=0;i<tabelleWidget->columnCount();i++)
        {
            if((tabelleWidget->item(z,i)==0  || tabelleWidget->item(z,i)->text().isEmpty())&& currVerzeichnis.contains("media") && tabelleWidget->item(z,0)->text() == "CD" && i == 5)
            {
                tabelleWidget->setItem(z,i,new QTableWidgetItem("")); //wenn eingegebenes Medium in Medien-Datei eine CD ist, ist die Angabe einer Auflagennummer nicht notwendig
                                                                      //leeres Feld erlauben -> wenn das Item nicht vom user bearbeitet wurde ,ist es nicht initialisiert und Speicherung führt zu
                                                                      //Programmabsturz -> Initialisierung und befüllen mit leerem String
            }
            else if((i != 5) && (tabelleWidget->item(z,i)->text().isEmpty() || tabelleWidget->item(z,i)==0))
            {
                QMessageBox::warning(this,"Warnung","Keine leeren Zellinhalte erlaubt");  //sollte obiger Fall nicht zutreffen und es werden leere Items gefunden -> Fehlerausgabe über static Funktion
                                                                                          // QMessageBox::warning
                return false;   //False Rückgabe -> Auswertung in Speicher-Funktion
            }
        }
    }
    return true;  //keine leeren Felder vorhanden -> Auswertung in Speicher-Funktion
}

bool tabelleWindow::valid() //überprüft, ob Kundennummer > 3 Ziffern; ob ISBN > 9 Zeichen ; ob > Rückgabedatum existiert und sinnvoll ist
{
    for(int z=0;z<tabelleWidget->rowCount();z++)
    {
        if(currVerzeichnis.contains("person") && tabelleWidget->item(z,0)->text().length()<= 3) //einzige notwendige Überprüfung für Personendatei; Länger der KunNr
        {
            return true;
        }
        if(tabelleWidget->item(z,tabelleWidget->rowCount()-2)->text().length()>9)             //für Medien- und Ausleihe-Datei: ISBN > 9 Zeichen?
        {
            QMessageBox::warning(this,"Warnung","ISBN darf maximal 9 Zeichen enthalten!");
            return false;
        }
        QString datum = tabelleWidget->item(z,tabelleWidget->columnCount()-1)->text();       //Datum für Überprüfung erzeugen
        if(currVerzeichnis.contains("ausleihe") && (datum.at(2)!='.' || datum.at(5)!='.'))   //Datumsformat überprüfen: Format dd.mm.yyyy ?
        {
            QMessageBox::warning(this,"Warnung","Datum bitte im Format dd.mm.yyyy angeben.");
            return false;
        }
        if(currVerzeichnis.contains("ausleihe") && (!QDate::fromString(datum).isValid() || QDate::fromString(datum)< QDate::currentDate()))  //keine früheren Daten zulassen, da nicht sinnvoll
        {                                                                                                                                    //keine ungültigen Daten wie 30.02.2019 zulassen
            QMessageBox::warning(this,"Warnung","Ungültiges Datum.");
            return false;
        }
    }
    return true;
}

void tabelleWindow::lade_person()   //lädt Personendatei
{
    QString verzeichnis = QCoreApplication::applicationDirPath();
    verzeichnis.append("/person.txt");
    insertButton->setEnabled(true);                      //absoluten Pfad der Personendatei an neuladen(QString) übergeben und Button zum Einfügen neuer Zeilen aktivieren
    this->neuladen(verzeichnis);
}

void tabelleWindow::lade_media()   //lädt Mediendatei
{
    QString verzeichnis = QCoreApplication::applicationDirPath();
    verzeichnis.append(("/media.txt"));
    insertButton->setEnabled(true);                     //absoluten Pfad der Mediendatei an neuladen(QString) übergeben und Button zum Einfügen neuer Zeilen aktivieren
    this->neuladen(verzeichnis);
}

void tabelleWindow::lade_ausleihe()   //lädt Ausleihedatei
{
    QString verzeichnis = QCoreApplication::applicationDirPath();
    verzeichnis.append("/ausleihe.txt");
    insertButton->setEnabled(true);                      //absoluten Pfad der Ausleihedatei an neuladen(QString) übergeben und Button zum Einfügen neuer Zeilen aktivieren
    this->neuladen(verzeichnis);
}

void tabelleWindow::neuladen(QString verzeichnis)
{
    int s {-1};
    int row {0};
    int column {0};
    int pos1,pos2,lastpos;
    QString line;
    QString eintrag;

    QFile datei(verzeichnis);
    if(datei.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QApplication::setOverrideCursor(Qt::WaitCursor);
        tabelleWidget->clear();
        tabelleWidget->setRowCount(0);
        tabelleWidget->setColumnCount(0);

        QTextStream in(&datei);
        while(!in.atEnd())
        {
            line = in.readLine();
            tabelleWidget->insertRow(row);

            column =0;
            pos1 =0;
            lastpos =0;
            while(pos1!=-1)
            {
                pos1=line.indexOf("\"",lastpos);
                lastpos=pos1+1;
                pos2=line.indexOf("\"",lastpos);
                lastpos=pos2+1;
                if(pos1!=-1)
                {
                    if(s<column)
                    {
                        tabelleWidget->insertColumn(column);
                        s=column;
                    }
                    eintrag=line.mid((pos1+1),(pos2-pos1-1));
                    QTableWidgetItem *newItem = new QTableWidgetItem;
                    newItem->setText(eintrag);

                    if(row==0)
                    {
                        tabelleWidget->setHorizontalHeaderItem(column,newItem);
                    }
                    else
                    {
                        tabelleWidget->setItem(row-1,column,newItem);
                    }
                    tabelleWidget->horizontalHeader()->setSectionResizeMode(column,QHeaderView::ResizeToContents);
                    column++;
                }
            }
        row++;
        }
        tabelleWidget->removeRow(row-1);
    }


//    int s;
//    int row,column;
//    int zeilen {0},spalten {0};
//    int pos1,pos2,lastpos;
//    QString line;
//    QString eintrag[99][99];

//    currVerzeichnis = verzeichnis;
//    QFile datei(verzeichnis);
//    if(datei.open(QIODevice::ReadOnly | QIODevice::Text))
//    {
//       QApplication::setOverrideCursor(Qt::WaitCursor);

//       QTextStream in(&datei);
//       while(!in.atEnd())
//       {
//           line=in.readLine();
//           s=0;
//           pos1=0;
//           lastpos=0;
//           while(pos1!=-1)
//           {
//               pos1=line.indexOf("\"",lastpos);
//               lastpos=pos1+1;
//               pos2=line.indexOf("\"",lastpos);
//               lastpos=pos2+1;
//               if(pos1!=-1)
//               {
//                   eintrag[zeilen][s]=line.mid((pos1+1),(pos2-pos1-1));
//                   s++;
//               }
//           }

//       //maximale Spaltenanzahl ermitteln
//           if(s>spalten)
//           {spalten=s;}
//           zeilen++;
//       }


//    }
//    else
//    {
//        QMessageBox::warning(this,"Warnung" ,"Datei konnte nicht geöffnet werden: " + currVerzeichnis);
//        return;
//    }
//    datei.close();
//    tabelleWidget->clear();
//    tabelleWidget->setRowCount(zeilen-1);
//    tabelleWidget->setColumnCount(spalten);

//    for(row=0;row<zeilen;row++)
//    {
//        for(column=0;column<spalten;column++)
//        {
//            QTableWidgetItem *newItem = new QTableWidgetItem;
//            newItem->setText(eintrag[row][column]);
//            if(eintrag[row][column].isEmpty())
//            {
//                newItem->setFlags(newItem->flags() ^Qt::ItemIsEditable);
//            }
//            if(row==0)
//            {
//                tabelleWidget->setHorizontalHeaderItem(column,newItem);
//            }
//            else
//            {
//                tabelleWidget->setItem(row-1,column,newItem);
//            }
//        }
//    }
    media->leeren();
    media = new datalist();
    QApplication::restoreOverrideCursor();        //Datenliste leeren und neu befüllen; normalen Cursor wiederherstellen; Speicherbutton aktivieren
    saveButton->setEnabled(false);

}


bool tabelleWindow::verify(datalist* dlst)         //überprüft Datenkonsistenz in den jeweiligen Dateien
{
    if(currVerzeichnis.contains("ausleihe"))      //für Ausleihe
    {
        for(size_t z{0};z<tabelleWidget->rowCount();z++)
        {
            if(std::find(dlst->pID.begin(),dlst->pID.end(),tabelleWidget->item(z,0)->text())!=dlst->pID.end())   //überprüfen, ob Kundennummer bereits exisitiert
            {
                if(std::find(dlst->ID.begin(),dlst->ID.end(),tabelleWidget->item(z,ISBNPOS)->text())!=dlst->ID.end())  //übeprüfen, ob ISBN bereits existiert
                {
                    ;
                }
                else
                {
                    QMessageBox::warning(this,"Warnung","Datei konnte nicht verifiziert werden. Überprüfen sie auf unbekannte Kundennummern/ISBN");
                    return false;
                }
            }
            else
            {
                QMessageBox::warning(this,"Warnung","Datei konnte nicht verifiziert werden. Überprüfen sie auf unbekannte Kundennummern/ISBN");
                return false;
            }
        }
        return true;  //ISBN und Kundennummer sind bekannt -> Auswertung in Speicher-Funktion
    }
    else if(currVerzeichnis.contains("person"))   //für Personendatei
    {
        for(size_t z {dlst->pID.size()};z<tabelleWidget->rowCount();z++)
        {
            if(std::find(dlst->pID.begin(),dlst->pID.end(),tabelleWidget->item(z,0)->text())!=dlst->pID.end())    //überprüfen, ob Kundennummer bereits existiert
            {
                QMessageBox::warning(this,"Warnung","Datei konnte nicht verifiziert werden. Überprüfen sie auf doppelte Kundennummern.");
                return false;;
            }
            else
            {
                ;
            }
        }
    return true;   //keine doppelten Werte für die Kundennummern
    }
    else if(currVerzeichnis.contains("media")) //für Mediendatei
    {
        for(size_t z {dlst->ID.size()};z<tabelleWidget->rowCount();z++)
        {

            if(std::find(dlst->ID.begin(),dlst->ID.end(),tabelleWidget->item(z,4)->text())!=dlst->ID.end()) //überprüfen ob ISBN bereits existiert
            {
                QMessageBox::warning(this,"Warnung","Datei konnte nicht verifiziert werden. Überprüfen sie auf doppelte ISBN.");
                return false;
            }
            else
            {
                 ;
            }
        }
    return true; //keine doppelten ISBNs
    }
    else
    {
        QMessageBox::warning(this,"Warnung","Datei konnte nicht verifiziert werden.");
        return false;
    }
    return false;
}


void tabelleWindow::speichern() //speichert die momentane Tabellendaten in die jeweilige Datei
{
    if(!verify(media))     //Auswertung der Datenkonsistenz
    {
        return;
    }


    if (!emptycheck())   //Auswertung, ob leere Felder vorhanden sind
    {
        return;
    }

    if(!valid())      //Auswertung, ob sinnvolle Werte eingegeben wurden
    {
        return;
    }

    QString inhalt;
    int z,i;

    QFile datei(currVerzeichnis); //öffnet momentanes Verzeichnis
    if(datei.open(QFile::WriteOnly | QFile::Truncate))  //löscht gesamten Inhalt der Datei
    {
        QTextStream out(&datei);  //Outputstream

        QApplication::setOverrideCursor(Qt::WaitCursor); //Warte-Cursor
        for(i=0;i<tabelleWidget->columnCount();i++)
        {
            if(tabelleWidget->horizontalHeaderItem(i)!=0)   //wenn Kopfzeilen vorhanden sind, werden diese als erstes in die Datei geschrieben. müssen gesondert entnommen werden
            {
                inhalt = tabelleWidget->horizontalHeaderItem(i)->text();
                if(i==tabelleWidget->columnCount()-1)
                {
                    out << "\"" << inhalt << "\"";  //speichern zwischen " "
                }
                else
                {
                    out << "\"" << inhalt << "\"";
                }
            }
        }
    out << endl;  //Zeilenumbruch einfügen



    for(z=0;z<tabelleWidget->rowCount();z++)
    {
        for(i=0;i<tabelleWidget->columnCount();i++)
        {
            if(tabelleWidget->item(z,i)!=0)
            {
                inhalt=tabelleWidget->item(z,i)->text();                        //Inhalt der jeweiligen Zeilen entnehmen und in der Datei zwischen " " speichern
                if(i==tabelleWidget->columnCount()-1)
                {
                    out << "\"" << inhalt << "\"";
                }
                else
                {
                    out << "\"" << inhalt << "\"";
                }
            }
        }
    out << endl;  //Zeilenumbruch einfügen
    }

    QApplication::restoreOverrideCursor();        //Standard-Cursor wiederherstellen
    datei.close(); //datei schließen

    saveButton->setEnabled(false);          //Speicher-Button disablen; -> keine Speicherung ohne Änderung möglich
    }
    else
    {
        QMessageBox::warning(this,"Warnung","Datei konnte nicht zum speichern geöffnet werden. " +currVerzeichnis);
        return;
    }
    QMessageBox::warning(this,"Erfolg!","Datei erfoglreich gespeichert!");  //Nutzerhinweis
    this->neuladen(currVerzeichnis);   //Tabelle aktualisieren

}

void tabelleWindow::aenderung(QTableWidgetItem *)
{
    saveButton->setEnabled(true);   //bei Änderungen in der Tabelle das Speichern ermöglichen
}

void tabelleWindow::loeschen() //löscht eine Zeile
{
    int row=QInputDialog::getInt(this,"Zeilenangabe","Bitte geben sie die zu löschende Zeile an",1,1,tabelleWidget->rowCount());  //User-Eingabe der Zeilennummer, die gelöscht werden soll
    QString line; //enthält den Inhalt einer Zeile
    QFile tmp("tmp.txt"); //temporäre Datei erstellen
    if(!tmp.open(QFile::WriteOnly | QFile::Truncate))  //Datei öffnen und überprüfen, ob erfolgreich
        QMessageBox::warning(this,"Warning","Tmp File konnte nicht geöffnet werden.");
    QFile datei(currVerzeichnis);    //aktuelle Datei
    if(datei.open(QFile::ReadOnly | QFile::Text))   //Datei öffnen und überprüfen, ob erfolgreich
    {
        QTextStream edit(&datei);
        int i=0;
        while(!edit.atEnd())
        {
            line = edit.readLine();
            if(i!=row)
            {
                tmp.write(line.toUtf8());             //Datei auslesen und zeilenweise in tmp überführen
                tmp.write("\n");
            }
            else
            {
                ;                                     //gewünschte Zeile überspringen
            }
            i++;
        }
    }
    else
    {
        QMessageBox::warning(this,"Warning","Datei konnte nicht geöffnet werden: " +currVerzeichnis);
    }
    datei.close();
    tmp.close();
    datei.remove();   //datei entfernen und durch tmp Datei ersetzen
    tmp.rename(currVerzeichnis);

    this->neuladen(currVerzeichnis); //Tabelle aktualisieren, um neuen Inhalt zu zeigen
    saveButton->setEnabled(true);    //Speichern ermöglichen
}

void tabelleWindow::insert() //neue Zeile einfügen
{
    tabelleWidget->setRowCount(tabelleWidget->rowCount()+1);  //rowCount um 1 erhöhen
}

void tabelleWindow::info(QTableWidgetItem *qwi)  //gibt Medieninformationen zu dem jeweiligen Medium aus
{
    if(currVerzeichnis.contains("ausleihe"))     //nur in Ausleihe-Datei nötig
    {
        if(qwi->column()==ISBNPOS)              //nur, wenn auf ISBN geclicked wurde
        {
            std::vector<QString>::iterator it{media->ID.begin()};   //iterator über den ISBN Vector
            size_t index{0};         //index mit 0 initialisieren

            it=std::find(media->ID.begin(),media->ID.end(),qwi->text());      //ISBN des geclickten Items in der Medienliste suchen
            index = it-media->ID.begin();                                     //Nummer des Index des Items
            //index--;
            if(index < media->ID.size())                                     //Wenn der Index in der Liste vorhanden ist
            {
                auto start = media->data.begin();                           //iterator für die Liste mittels auto erzeugen
                std::advance(start,index);                                  //iterator bis zum Index fortschreiten lassen
                //QMessageBox::warning(this,"Warning",media->ID.at(index));
                QMessageBox::about(this,"Medieninformation",(*start)->getInfo());   //Informationen des momentanen Mediums über Memberfunktion getInfo ausgeben
            }
         }
    }

}
