#include "tabelle.h"
#include <QtGui>
#include <QMessageBox>
#include <QFileDialog>
#include <string>
#include <QInputDialog>
#include <QDateTime>
#include <vector>

QString currVerzeichnis;
const size_t ISBNPOS{3};
datalist *media = new datalist();

tabelleWindow::tabelleWindow(QWidget *parent) :
    QDialog(parent)
{
    setupUi(this);
    connect(saveButton,SIGNAL(clicked()),this,SLOT(speichern()));
    connect(reloadButton,SIGNAL(clicked()),this,SLOT(laden()));
    connect(tabelleWidget,SIGNAL(itemChanged(QTableWidgetItem *)),this,SLOT(aenderung(QTableWidgetItem *)));
    connect(insertButton,SIGNAL(clicked()),this,SLOT(insert()));
    connect(deleteButton,SIGNAL(clicked()),this,SLOT(loeschen()));
    connect(tabelleWidget,SIGNAL(itemClicked(QTableWidgetItem*)),this,SLOT(info(QTableWidgetItem *)));
}

tabelleWindow::~tabelleWindow()
{
    delete ui;
}

bool tabelleWindow::emptycheck()
{
    for(int z=0;z<tabelleWidget->rowCount();z++)
    {
        if(currVerzeichnis.contains("ausleihe"))
        {
            if(tabelleWidget->item(z,tabelleWidget->columnCount()-1)==0 || tabelleWidget->item(z,tabelleWidget->columnCount()-1)->text().isEmpty())
            {
                QDateTime datum=QDateTime::currentDateTime();
                datum=datum.addDays(21);
                tabelleWidget->setItem(z,tabelleWidget->columnCount()-1,new QTableWidgetItem(datum.toString("dd.MM.yyyy")));

            }
        }
        for(int i=0;i<tabelleWidget->columnCount();i++)
        {
            if((tabelleWidget->item(z,i)==0  || tabelleWidget->item(z,i)->text().isEmpty())&& currVerzeichnis.contains("media") && tabelleWidget->item(z,0)->text() == "CD" && i == 5)
            {
                tabelleWidget->setItem(z,i,new QTableWidgetItem(""));
            }
            else if((i != 5) && (tabelleWidget->item(z,i)->text().isEmpty() || tabelleWidget->item(z,i)==0))
            {
                QMessageBox::warning(this,"Warnung","Keine leeren Zellinhalte erlaubt");
                return false;
            }
        }
    }
    return true;
}

bool tabelleWindow::valid()
{
    for(int z=0;z<tabelleWidget->rowCount();z++)
    {
        if(tabelleWidget->item(z,tabelleWidget->rowCount()-2)->text().length()>9)
        {
            QMessageBox::warning(this,"Warnung","ISBN darf maximal 9 Zeichen enthalten!");
            return false;
        }
        QString datum = tabelleWidget->item(z,tabelleWidget->columnCount()-1)->text();
        if(currVerzeichnis.contains("ausleihe") && (datum.at(2)!='.' || datum.at(5)!='.'))
        {
            QMessageBox::warning(this,"Warnung","Datum bitte im Format dd.mm.yyyy angeben.");
            return false;
        }
        if(!QDate::fromString(datum).isValid() || QDate::fromString(datum)< QDate::currentDate())
        {
            QMessageBox::warning(this,"Warnung","Ungültiges Datum.");
            return false;
        }
    }
    return true;
}

void tabelleWindow::laden()
{
    QString verzeichnis=QFileDialog::getOpenFileName(this,"Öffne die Datei");
    insertButton->setEnabled(true);
    this->neuladen(verzeichnis);

}

void tabelleWindow::neuladen(QString verzeichnis)
{
    int s;
    int row,column;
    int zeilen {0},spalten {0};
    int pos1,pos2,lastpos;
    QString line;
    QString eintrag[99][99];

    currVerzeichnis = verzeichnis;
    QFile datei(verzeichnis);
    if(datei.open(QIODevice::ReadOnly | QIODevice::Text))
    {
       QApplication::setOverrideCursor(Qt::WaitCursor);

       QTextStream in(&datei);
       while(!in.atEnd())
       {
           line=in.readLine();
           s=0;
           pos1=0;
           lastpos=0;
           while(pos1!=-1)
           {
               pos1=line.indexOf("\"",lastpos);
               lastpos=pos1+1;
               pos2=line.indexOf("\"",lastpos);
               lastpos=pos2+1;
               if(pos1!=-1)
               {
                   eintrag[zeilen][s]=line.mid((pos1+1),(pos2-pos1-1));
                   s++;
               }
           }

       //maximale Spaltenanzahl ermitteln
           if(s>spalten)
           {spalten=s;}
           zeilen++;
       }


    }
    else
    {
        QMessageBox::warning(this,"Warnung" ,"Datei konnte nicht geöffnet werden: " + currVerzeichnis);
        return;
    }
    datei.close();
    tabelleWidget->clear();
    tabelleWidget->setRowCount(zeilen-1);
    tabelleWidget->setColumnCount(spalten);

    for(row=0;row<zeilen;row++)
    {
        for(column=0;column<spalten;column++)
        {
            QTableWidgetItem *newItem = new QTableWidgetItem;
            newItem->setText(eintrag[row][column]);
            if(eintrag[row][column].isEmpty())
            {
                newItem->setFlags(newItem->flags() ^Qt::ItemIsEditable);
            }
            if(row==0)
            {
                tabelleWidget->setHorizontalHeaderItem(column,newItem);
            }
            else
            {
                tabelleWidget->setItem(row-1,column,newItem);
            }
        }
    }
    media->leeren();
    media = new datalist();
    QApplication::restoreOverrideCursor();
    saveButton->setEnabled(false);

}


bool tabelleWindow::verify(datalist* dlst)
{
    if(currVerzeichnis.contains("ausleihe"))
    {
        for(size_t z{0};z<tabelleWidget->rowCount();z++)
        {
            if(std::find(dlst->pID.begin(),dlst->pID.end(),tabelleWidget->item(z,0)->text())!=dlst->pID.end())
            {
                if(std::find(dlst->ID.begin(),dlst->ID.end(),tabelleWidget->item(z,ISBNPOS)->text())!=dlst->ID.end())
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
        return true;
    }
    else if(currVerzeichnis.contains("person"))
    {
        for(size_t z {dlst->pID.size()};z<tabelleWidget->rowCount();z++)
        {
            if(std::find(dlst->pID.begin(),dlst->pID.end(),tabelleWidget->item(z,0)->text())!=dlst->pID.end())
            {
                QMessageBox::warning(this,"Warnung","Datei konnte nicht verifiziert werden. Überprüfen sie auf doppelte Kundennummern.");
                return false;;
            }
            else
            {
                ;
            }
        }
    return true;
    }
    else if(currVerzeichnis.contains("media"))
    {
        for(size_t z {dlst->ID.size()};z<tabelleWidget->rowCount();z++)
        {

            if(std::find(dlst->ID.begin(),dlst->ID.end(),tabelleWidget->item(z,4)->text())!=dlst->ID.end())
            {
                QMessageBox::warning(this,"Warnung","Datei konnte nicht verifiziert werden. Überprüfen sie auf doppelte ISBN.");
                return false;
            }
            else
            {
                 ;
            }
        }
    return true;
    }
    else
    {
        QMessageBox::warning(this,"Warnung","Datei konnte nicht verifiziert werden.");
        return false;
    }
    return false;
}


void tabelleWindow::speichern()
{
    if(!verify(media))
    {
        return;
    }


    if (!emptycheck())
    {
        return;
    }

    if(!valid())
    {
        return;
    }

    QString inhalt;
    int z,i;

    QFile datei(currVerzeichnis);
    if(datei.open(QFile::WriteOnly | QFile::Truncate))
    {
        QTextStream out(&datei);

        QApplication::setOverrideCursor(Qt::WaitCursor);
        for(i=0;i<tabelleWidget->columnCount();i++)
        {
            if(tabelleWidget->horizontalHeaderItem(i)!=0)
            {
                inhalt = tabelleWidget->horizontalHeaderItem(i)->text();
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
    out << endl;



    for(z=0;z<tabelleWidget->rowCount();z++)
    {
        for(i=0;i<tabelleWidget->columnCount();i++)
        {
            if(tabelleWidget->item(z,i)!=0)
            {
                inhalt=tabelleWidget->item(z,i)->text();
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
    out << endl;
    }

    QApplication::restoreOverrideCursor();
    datei.close();

    saveButton->setEnabled(false);
    }
    else
    {
        QMessageBox::warning(this,"Warnung","Datei konnte nicht zum speichern geöffnet werden. " +currVerzeichnis);
        return;
    }
    QMessageBox::warning(this,"Erfolg!","Datei erfoglreich gespeichert!");
    this->neuladen(currVerzeichnis);

}

void tabelleWindow::aenderung(QTableWidgetItem *)
{
    saveButton->setEnabled(true);
}

void tabelleWindow::loeschen()
{
    int row=QInputDialog::getInt(this,"Zeilenangabe","Bitte geben sie die zu löschende Zeile an",1,1,tabelleWidget->rowCount());
    QString line;
    QFile tmp("tmp.txt");
    if(!tmp.open(QFile::WriteOnly | QFile::Truncate))
        QMessageBox::warning(this,"Warning","Tmp File konnte nicht geöffnet werden.");
    QFile datei(currVerzeichnis);
    if(datei.open(QFile::ReadOnly | QFile::Text))
    {
        QTextStream edit(&datei);
        int i=0;
        while(!edit.atEnd())
        {
            line = edit.readLine();
            if(i!=row)
            {
                tmp.write(line.toUtf8());
                tmp.write("\n");
            }
            else
            {
                ;
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
    datei.remove();
    tmp.rename(currVerzeichnis);

    this->neuladen(currVerzeichnis);
    saveButton->setEnabled(true);
}

void tabelleWindow::insert()
{
    tabelleWidget->setRowCount(tabelleWidget->rowCount()+1);
}

void tabelleWindow::info(QTableWidgetItem *qwi)
{
    if(currVerzeichnis.contains("ausleihe"))
    {
        if(qwi->column()==ISBNPOS)
        {
            std::vector<QString>::iterator it{media->ID.begin()};
            size_t index{0};

            it=std::find(media->ID.begin(),media->ID.end(),qwi->text());
            index = it-media->ID.begin();
            //index--;
            if(index < media->ID.size())
            {
                auto start = media->data.begin();
                std::advance(start,index);
                //QMessageBox::warning(this,"Warning",media->ID.at(index));
                QMessageBox::about(this,"Medieninformation",(*start)->getInfo());
            }
         }
    }

}
