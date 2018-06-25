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
    void laden();
    void speichern();
    void aenderung(QTableWidgetItem *);
    void loeschen();
    void insert();

private:
    Ui::tabelleWindow *ui;
    void neuladen(QString);
};

#endif // TABELLE_H
