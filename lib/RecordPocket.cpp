#include "RecordPocket.h"
#include "assert.h"
#include <iostream>
using namespace std;

RecordPocket::RecordPocket(int year, int mon, int day, int day_interval) : records() , day_interval(day_interval) {
    begin_time.tm_year = year - 1900;
    begin_time.tm_mon  = mon - 1;
    begin_time.tm_mday = day;

    begin_time.tm_hour = 0;
    begin_time.tm_min = 0;
    begin_time.tm_sec = 0;

    begin_time.tm_isdst = 0;

    time_t begin = mktime(&begin_time);
    begin += (day_interval -1) * 60 * 60 * 24 + 1;

    end_time = *localtime(&begin);
}
int RecordPocket::recordSize() const {
    return records.size();
}
Record &RecordPocket::getRecord(int I) {
    return records[I];
}
void RecordPocket::addRecord(const Record &record) {
    records.push_back(record);
}
void RecordPocket::clear() {
    records.clear();
}
int RecordPocket::getInterval() const {
    return day_interval;
}
int RecordPocket::getEndYear() const {
    return end_time.tm_year + 1900;
}
int RecordPocket::getEndMonth() const {
    return end_time.tm_mon + 1;
}
int RecordPocket::getEndDay() const {
    return end_time.tm_mday;
}

int RecordPocket::getBeginYear() const {
    return begin_time.tm_year + 1900;
}
int RecordPocket::getBeginMonth() const {
    return begin_time.tm_mon + 1;
}
int RecordPocket::getBeginDay() const {
    return begin_time.tm_mday;
}
Record &RecordPocket::getRecordById(int id) {
    for(int I = 0;I < recordSize();I++) {
        if(records[I].id == id) {
            return records[I];
        }
    }
    assert(recordSize() > 0);
}

Record& RecordPocket::operator [](int I) {
    return getRecord(I);
}
