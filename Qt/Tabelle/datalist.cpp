#include "datalist.h"
#include <QString>
#include <QFile>
#include <QMessageBox>
#include <QTextStream>
#include <QtGui>

const size_t COUNTBUCHPROPERTIES{6};
const size_t COUNTCDPROPERTIES{5};

datalist::datalist()
{
    QString line;
    std::vector<QString> properties;
    QString verzeichnis=QDir::currentPath();
    verzeichnis.append("/ausleihe.txt");
    QFile datei(verzeichnis);
    if(!datei.open(QIODevice::ReadOnly | QIODevice::Text))
    {
         QMessageBox::warning(0,"Warnung","Fehler beim Öffnen der Mediendatei");
    }

    QTextStream input(&datei);
    line = input.readLine();

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
                properties.push_back(line.mid((pos1+1),(pos2-pos1-1)));
            }
        }
        if(properties.size()==COUNTBUCHPROPERTIES)
        {
            Buch *member = new Buch(properties.at(1),properties.at(2),properties.at(3),properties.at(4),(properties.at(5)));
           // CD *member = new CD(properties.at(1),properties.at(2),properties.at(3),properties.at(4));
            data.push_back(member);
        }
        else if(properties.size()==COUNTCDPROPERTIES)
        {
            CD *member = new CD(properties.at(1),properties.at(2),properties.at(3),properties.at(4));
            data.push_back((member));
        }
        properties.clear();
    }
    datei.close();
    for(auto const& i: data)
    {
        ID.push_back(i->getISBN());
    }


    verzeichnis=QDir::currentPath();
    verzeichnis.append("/person.txt");

    QFile pdatei(verzeichnis);
    if(!pdatei.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QMessageBox::warning(0,"Warnung","Fehler beim Öffnen der Mediendatei");
    }

    QTextStream pinput(&pdatei);
        line = pinput.readLine();

        while(!pinput.atEnd())
        {
            int pos1{0};
            int pos2{0};
            int lastpos{0};
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
            pID.push_back(properties.at(0));
            properties.clear();
        }
    pdatei.close();
}

datalist::~datalist()
{
    data.clear();
    ID.clear();
}

void datalist::leeren()
{
    data.clear();
    ID.clear();
}
