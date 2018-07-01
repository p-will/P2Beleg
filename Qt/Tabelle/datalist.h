#ifndef DATALIST_H
#define DATALIST_H

#include <list>
#include <vector>
#include "medien.h"
#include "person.h"
#include "cd.h"
#include "buch.h"


class datalist
{
public:
    datalist();
    ~datalist();
    void leeren();
    std::list<Medien*> data;
    std::vector<QString> pID;
    //std::list<Person*> pdata;
    std::vector<QString> ID;
private:
};
#endif // DATALIST_H
