#ifndef TABELLE_H
#define TABELLE_H

#include <QDialog>
#include "ui_tabelle.h"
#include "datalist.h"



namespace Ui {
class tabelleWindow;
}

class tabelleWindow : public QDialog, public Ui::tabelleWindow
{
    Q_OBJECT

public:
     explicit tabelleWindow(QWidget *parent = 0);
    ~tabelleWindow();

private slots:
    void lade_media();
    void lade_person();
    void lade_ausleihe();
    void speichern();
    void aenderung(QTableWidgetItem *);
    void loeschen();
    void insert();
    void info(QTableWidgetItem *);
    void help();

private:
    Ui::tabelleWindow *ui;
    void neuladen(QString);
    bool verify(datalist*);
    bool emptycheck();
    bool valid();
};

#endif // TABELLE_H
