//Paul Willam 44093 Bachelor 062

/*
Headerfile der abgeleiteten Klasse für CD Medien
*/

#ifndef CD_H
#define CD_H

#include <QString>
#include "medien.h"


class CD: public Medien
{
    private:

    public:
    CD(QString,QString,QString,QString);
    ~CD();
    QString getInfo() const;
};


#endif
