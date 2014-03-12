#include "DBm.h"
#include <iostream>
#include <sstream>
#include "sql.def"

using namespace std;

string DBm::getInsertHead() {
    string res = "insert into ";
    res += tableName;
    res += "(";
    res += COLUMN_ALLNAME_WITHOUT_ID;
//    res += "name,year,month,day,begin_h,begin_m,end_h,end_m,tags,nums,comment";
    res += ") ";
    return res;
}
string DBm::getNameCond(const string &name) {
    string res = "";
    res += COLUMN_NAME;
    res += " == \"";
    res += name;
    res += "\"";

    return res;
}
string DBm::getYMDCondString(int y, int m, int d) {
    stringstream out;
    out << " " << COLUMN_YEAR << " == " << y << " and "<< COLUMN_MONTH << " == " << m << " and " << COLUMN_DAY << " == " << d;
    return out.str();
}
string DBm::getDeleteHead() {
    string res = "delete from ";
    res += tableName;
    res += " where ";

    return res;
}
string DBm::getSelectTagsHead() {
    string res = "select ";
    res += COLUMN_TAGS;
    res += " from ";
    res += tableName;
    res += " where ";

    return res;
}
string DBm::getSelectHead() {
    string res = "select * from ";
    res += tableName;
    res += " where ";

    return res;
}
string DBm::getYMDBetweenCondString(int ya, int ma, int da, int yb, int mb, int db) {
    stringstream out;
    out << "(";
    out << "" << COLUMN_YEAR << " > " << ya << " or " << COLUMN_YEAR << " == " << ya  << " and ( " << COLUMN_MONTH << " > " << ma << " or " << COLUMN_MONTH << " == " << ma << " and " << COLUMN_DAY << " >= " << da << ")";  
    out << ")";
    out << " and ";
    out << "(";
    out << "" << COLUMN_YEAR << " < " << yb << " or " << COLUMN_YEAR << " == " << yb  << " and ( " << COLUMN_MONTH << " < " << mb << " or " << COLUMN_MONTH << " == " << mb << " and " << COLUMN_DAY << " <= " << db << ")";  
    out << ")";

    return out.str();
}
string DBm::getValueAsString(const Record &record) {
    string res =  "values(";
    res += record.getStringWithoutId();
    res += ") ";

    return res;
}
bool DBm::insertRecord(const Record &record) {
    string head  = getInsertHead();
    string value = getValueAsString(record);

    string sqlStr = head + value;

    char *zr;
    int rc = sqlite3_exec(db, sqlStr.c_str(), NULL, 0, &zr);
    if(rc) {
        cout << zr << endl;
        return false;
    }
    return true;
}

bool DBm::removeDayRecord(int y, int m, int d) {
    string head = getDeleteHead();
    string condYMD = getYMDCondString(y,m,d);

    string sqlStr = head + condYMD;

    char *zr;
    int rc = sqlite3_exec(db, sqlStr.c_str(), NULL, 0, &zr);
    if(rc) {
        cout << zr << endl;
        return false;
    }

    return true;
}
bool DBm::updateDayRecord(RecordPocket &records) {
    if(records.getInterval() != 1) return false;

    int year = records.getBeginYear();
    int mon = records.getBeginMonth();
    int day = records.getBeginDay();
    removeDayRecord(year, mon, day);

    for(int I = 0; I < records.recordSize(); I++) {
        if(records[I].isThisDay(year, mon, day))
            insertRecord(records[I]);
    }
    return true;
}

int DBm::getTagsCallBack(void *data, int nColumn, char **col_values, char **col_names) {
    string *str = (string *) data;

    if(nColumn != 1) return 0;
    if(strcmp(col_names[0], COLUMN_TAGS) != 0) return 0;
    *str = col_values[0];

    return 0;
}
int DBm::readRecordCallBack(void *data, int nColumn, char **col_values, char **col_names) {
    RecordPocket * records = (RecordPocket *)data;

    int I;
    Record newRecord;
    for(I = 0;I < nColumn;I++) {

#define BRANCH_STR(TYPE, CODE) \
        else if(0 == strcmp(TYPE, col_names[I])) { \
            newRecord.CODE(col_values[I]); \
        }
#define BRANCH_INT(TYPE, CODE) \
        else if(0 == strcmp(TYPE, col_names[I])) { \
            newRecord.CODE(atoi(col_values[I])); \
        }

        if(false) ;
        BRANCH_STR(COLUMN_NAME, setName)
        BRANCH_INT(COLUMN_YEAR, setYear)
        BRANCH_INT(COLUMN_MONTH, setMonth)
        BRANCH_INT(COLUMN_DAY, setDay)
        BRANCH_INT(COLUMN_BEGIN_H, setBeginH)
        BRANCH_INT(COLUMN_BEGIN_M, setBeginM)
        BRANCH_INT(COLUMN_END_H, setEndH)
        BRANCH_INT(COLUMN_END_M, setEndM)
        BRANCH_STR(COLUMN_TAGS, initTags)
        else if(0 == strcmp(COLUMN_NUMS, col_names[I])) {
            newRecord.setNums(atof(col_values[I]));
        }
        BRANCH_STR(COLUMN_COMMENT, setComment)
    }

    records->addRecord(newRecord);

    return 0;
}
bool DBm::getTagsStringByName(const string &name, string &tags) {
    string sqlStr = "";
    string selectHead = getSelectTagsHead();
    string nameCond  = getNameCond(name);
    sqlStr = selectHead + nameCond;

    char *zr;
    int rc = sqlite3_exec(db, sqlStr.c_str(), &getTagsCallBack, &tags, &zr);


    if(rc) {
        cout << "select bug" << endl;

        return false;
    }
    return true;
}
bool DBm::readInRecordPocket(RecordPocket &records) {
    records.clear();

    int beginYear = records.getBeginYear();
    int beginMon = records.getBeginMonth();
    int beginDay = records.getBeginDay();

    int endYear = records.getEndYear();
    int endMon = records.getEndMonth();
    int endDay = records.getEndDay();

    string sqlStr = "";
    string selectHead = getSelectHead();
    string YMDCond = getYMDBetweenCondString(beginYear, beginMon, beginDay, endYear, endMon, endDay);

    sqlStr = selectHead + YMDCond;
    char *zr;
    int rc = sqlite3_exec(db, sqlStr.c_str(), &readRecordCallBack, &records, &zr);

    if(rc) {
        cout << "select bug" << endl;

        return false;
    }
    return true;
}
DBm::DBm(string dbPath, string table) : dbPath(dbPath), tableName(table) {
    int rc = sqlite3_open(dbPath.c_str(), &db);

    opened = true;

    if(SQLITE_OK != rc) {
        // ERROF
        cout << "open sqlite3 fail" << endl;
        opened = false;
    }
}

DBm::~DBm() {
    sqlite3_close(db);
}
bool DBm::opening() {
    return opened;
}
