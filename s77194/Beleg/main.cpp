//Paul Willam 44093 Bachelor 062

/*
 * Main Funktion des Belegs
 */

#include <QApplication>
#include "tabelle.h"
#include "medien.h"
#include "person.h"
#include "buch.h"
#include "cd.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);               //zunächst Applikation als Grundgerüst erstellen
    tabelleWindow *dialog = new tabelleWindow;  //neue tabelleWindow instanz erstellen
    dialog->show();                             //zeigt die Instanz an

    return app.exec();                         //ausführen der Applikation
}
