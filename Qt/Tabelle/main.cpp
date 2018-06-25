#include "tabelle.h"
#include <QApplication>
#include "medien.h"
#include "person.h"
#include "buch.h"
#include "cd.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    tabelleWindow *dialog = new tabelleWindow;
    dialog->show();

    return app.exec();
}
