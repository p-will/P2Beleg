#include "tabelle.h"
#include <QtGui>
#include <QMessageBox>
#include <QFileDialog>
#include <string>
#include <QInputDialog>

QString currVerzeichnis;

tabelleWindow::tabelleWindow(QWidget *parent) :
    QDialog(parent)
{
    setupUi(this);
    connect(saveButton,SIGNAL(clicked()),this,SLOT(speichern()));
    connect(reloadButton,SIGNAL(clicked()),this,SLOT(neuladen()));
    connect(tabelleWidget,SIGNAL(itemChanged(QTableWidgetItem *)),this,SLOT(aenderung(QTableWidgetItem *)));
    connect(insertButton,SIGNAL(clicked()),this,SLOT(insert()));
    connect(deleteButton,SIGNAL(clicked()),this,SLOT(loeschen()));
    connect(ausleihButton,SIGNAL(clicked()),this,SLOT(ausleihen()));
}

tabelleWindow::~tabelleWindow()
{
    delete ui;
}

void tabelleWindow::neuladen()
{
    int s;
    int row,column;
    int zeilen {0},spalten {0};
    int pos1,pos2,lastpos;
    QString line;
    QString eintrag[99][99];

   // QString verzeichnis="/home/paulsuse/Dokumente/P2Beleg/ausleihe.txt";
    QString verzeichnis=QFileDialog::getOpenFileName(this,"Öffne die Datei");
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
            newItem->setToolTip("Ja Moin Liebe Leute \n I Bims \n 1 ToolTip");
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
        for(i=0;i<tabelleWidget->columnCount();i++)
        {
            if(tabelleWidget->item(z,i)!=0)
            {
                inhalt=tabelleWidget->item(z,i)->text();

                if(!inhalt.isEmpty())
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
        }
    out << endl;
    }
    QApplication::restoreOverrideCursor();
    datei.close();

    saveButton->setEnabled(false);
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

    this->neuladen();
}

void tabelleWindow::insert()
{

}

void tabelleWindow::ausleihen()
{

}
