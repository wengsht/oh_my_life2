#ifndef __DB_M_H__
#define __DB_M_H__

#include "sqlite3.h"
#include "Record.h"
#include "RecordPocket.h"
#include <string>
#include <vector>
using namespace std;

class DBm {
    public:
        DBm(string dbPath, string table);
        bool insertRecord(const Record &record);
        bool removeDayRecord(int y, int m, int d);
        bool updateDayRecord(RecordPocket &records);

        bool readInRecordPocket(RecordPocket &records);
        ~DBm();
    private:
        static int readRecordCallBack(void *data, int nColumn, char **col_values, char **col_names);
        string getInsertHead();
        string getYMDCondString(int y, int m, int d);
        string getDeleteHead();
        string getSelectHead();
        string getYMDBetweenCondString(int ya, int ma, int da, int yb, int mb, int db);
        string getValueAsString(const Record &record);
        string dbPath;
        string tableName;
        sqlite3 *db;

};
#endif
