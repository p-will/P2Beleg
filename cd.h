//Paul Willam 44093 Bachelor 062

/*
Headerfile der abgeleiteten Klasse für CD Medien
*/

#ifndef CD_H
#define CD_H

#include <string>
#include "medien.h"
#include "path.h"


class CD:Medien
{
    private:

    public:
    CD(std::string,std::string,std::string,std::string);
    ~CD();
    void show() const;
    int ausleihen();
};


#endif