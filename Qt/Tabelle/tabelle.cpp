#include "tabelle.h"
#include <QtGui>
#include <QMessageBox>
#include <QFileDialog>
#include <string>
#include <QInputDialog>
#include <QDateTime>

QString currVerzeichnis;
const size_t ISBNPOS{4};

tabelleWindow::tabelleWindow(QWidget *parent) :
    QDialog(parent)
{
    setupUi(this);
    connect(saveButton,SIGNAL(clicked()),this,SLOT(speichern()));
    connect(reloadButton,SIGNAL(clicked()),this,SLOT(laden()));
    connect(tabelleWidget,SIGNAL(itemChanged(QTableWidgetItem *)),this,SLOT(aenderung(QTableWidgetItem *)));
    connect(insertButton,SIGNAL(clicked()),this,SLOT(insert()));
    connect(deleteButton,SIGNAL(clicked()),this,SLOT(loeschen()));
    connect(tabelleWidget,SIGNAL(itemClicked(QTableWidgetItem*)),this,SLOT(info(QTableWidgetItem *qwi)));
}

tabelleWindow::~tabelleWindow()
{
    delete ui;
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
        QMessageBox::warning(this,"Warning","Cannot open file: ");
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
    QApplication::restoreOverrideCursor();
    saveButton->setEnabled(false);

}



void tabelleWindow::speichern()
{
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
        if(currVerzeichnis.contains("ausleihe"))
        {
            if(tabelleWidget->item(z,tabelleWidget->columnCount()-1)==0 || tabelleWidget->item(z,tabelleWidget->columnCount()-1)->text().isEmpty())
            {
                QDateTime datum=QDateTime::currentDateTime();
                datum=datum.addDays(21);
                tabelleWidget->setItem(z,tabelleWidget->columnCount()-1,new QTableWidgetItem(datum.toString("dd.MM.yyyy")));

            }
        }
        for(i=0;i<tabelleWidget->columnCount();i++)
        {
            if(tabelleWidget->item(z,i)!=0)
            {
                inhalt=tabelleWidget->item(z,i)->text();
                if(inhalt.isEmpty())
                {
                    QMessageBox::warning(this,"Warnung","Keine leeren Zelleninhalte erlaubt!" );
                    break;
                }
                else
                {
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
            else
            {
                    QMessageBox::warning(this,"Warnung","Keine leeren Zelleninhalte erlaubt!" );
                    break;

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

    }
}
