#ifndef DATALIST_H
#define DATALIST_H

#include <list>
#include "medien.h"

class datalist
{
public:
    datalist();
    ~datalist;
private:
    std::list<Medien> data;
};
#endif // DATALIST_H
