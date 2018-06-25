//Paul Willam 44093 Bachelor 062

/*
Header File für abgeleitete Buch Klasse
*/

#ifndef BUCH_H
#define BUCH_H

#include <iostream>
#include <string>
#include "medien.h"


class Buch:Medien 
{
    private:
        std::size_t Auflage;
    public:
        Buch(std::string,std::string,std::string,std::string,std::size_t);
        ~Buch();
        void show() const;
        int ausleihen();
};

#endif