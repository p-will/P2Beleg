#ifndef TABELLE_H
#define TABELLE_H

#include <QDialog>
#include "ui_tabelle.h"


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
    void neuladen();
    void speichern();
    void aenderung(QTableWidgetItem *);
    void loeschen();
    void insert();
    void ausleihen();

private:
    Ui::tabelleWindow *ui;
};

#endif // TABELLE_H
