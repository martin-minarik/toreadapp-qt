
#ifndef GLOBALDATA_H
#define GLOBALDATA_H

#include <vector>
#include "toreadrecord.h"



class GlobalData
{
public:
    static std::vector<ToreadRecord>& getRecords() {
        static std::vector<ToreadRecord> records;
        return records;
    }
};

#endif // GLOBALDATA_H
