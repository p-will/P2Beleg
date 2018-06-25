#include "tabelle.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    tabelleWindow *dialog = new tabelleWindow;
    dialog->show();

    return app.exec();
}
