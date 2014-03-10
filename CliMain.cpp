#include "sqlite3.h"
#include "Record.h"
#include "RecordPocket.h"
#include "DBm.h"

#include "iostream" 
using namespace std;

#define CODING

#ifdef CODING
int f(void *msg, int cn, char **column_string, char **column_title) {
    cout << column_string[0] << endl;
    return 0;
}
int main() {
    Record record(0, string("xx"), 2013,2,12,18,50,24,51 , string("yy&zz"), 1.0, "haha");

    pair<int, int> p = record.getInterval();
    cout << p.first <<  " " << p.second << endl;

    DBm dbm("life.db", "life");
//    dbm.insertRecord(record);
//    dbm.insertRecord(record);
//    dbm.insertRecord(record);

    Record record2(0, string("yy"), 2014,3,4,18,50,24,51 , string("yy&zz"), 1.2, "haha");
    RecordPocket r(2014, 3, 4, 1);

    string a = "yy"; 
    string b = "xx";
    dbm.getTagsStringByName("yy", b) ;
    cout << b << endl;
    dbm.readInRecordPocket(r);
    r.addRecord(record2);
    dbm.updateDayRecord(r);

    return 0;
}
#else
int main() {
    cout << "Client in command line is for debug... use qmake to build it!" << endl;

    return 0;
}
#endif
