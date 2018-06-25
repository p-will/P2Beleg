#include "datalist.h"
#include <QString>
#include <QFile>
#include <QMessageBox>
#include <QTextStream>

datalist::datalist()
{
    QString line;
    QString verzeichnis="/home/paulsuse/Dokumente/P2Beleg/Qt/Tabelle/ausleihe.txt";

    QFile datei(verzeichnis);
    if(!datei.open(QIODevice::ReadOnly | QIODevice:Text))
    {
         QMessageBox::warning(0,"Warnung","Fehler beim Öffnen der Mediendatei");
    }

    QTextStream input(&datei);

    while(!input.atEnd())
    {
        int pos1{0};
        int pos2{0};
        int lastpos{0};
        line = input.readLine();
        while(pos1!=-1)
        {
            pos1=line.indexOf("\"",lastpos);
            lastpos=pos1+1;
            pos2=line.indexOf("\"",lastpos);
            lastpos=pos2+1;
            if(pos1!=-1)
            {

            }
        }

    }
}
