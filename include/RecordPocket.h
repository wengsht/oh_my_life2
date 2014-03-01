#ifndef __RECORD_POCKET_H__
#define __RECORD_POCKET_H__

#include "Record.h"
#include <vector>
#include <ctime>
using namespace std;

class RecordPocket {
    public:
        RecordPocket(int year, int mon, int day, int day_interval);

        int recordSize() const;
        Record &getRecord(int I);
        Record &getRecordById(int id);

        int getInterval() const;
        int getBeginYear() const;
        int getBeginMonth() const;
        int getBeginDay() const;

        int getEndYear() const;
        int getEndMonth() const;
        int getEndDay() const;

        void addRecord(const Record &record);
        void clear();

        Record& operator [](int I);

    private:
        vector<Record> records;

        struct tm begin_time, end_time;
        int day_interval;
};

#endif
