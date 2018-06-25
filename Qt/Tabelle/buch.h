//Paul Willam 44093 Bachelor 062

/*
Header File für abgeleitete Buch Klasse
*/

#ifndef BUCH_H
#define BUCH_H

#include <iostream>
#include <QString>
#include "medien.h"


class Buch:Medien 
{
    private:
        std::size_t Auflage;
    public:
        Buch(QString,QString,QString,QString,std::size_t);
        ~Buch();
        QString getInfo() const;
};

#endif
