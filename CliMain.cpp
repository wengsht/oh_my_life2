#include "sqlite3.h"
#include "Record.h"
#include "RecordPocket.h"
#include "DBm.h"

#include "iostream" 
using namespace std;

int f(void *msg, int cn, char **column_string, char **column_title) {
    cout << column_string[0] << endl;
    return 0;
}
int main() {
    Record record(0, string("xx"), 2013,2,12,18,50,24,51 , string("yy&zz"), 1.0, "haha");

    pair<int, int> p = record.getInterval();
//    cout << p.first <<  " " << p.second << endl;

    DBm dbm("life.db", "life");
//    dbm.insertRecord(record);
//    dbm.insertRecord(record);
//    dbm.insertRecord(record);

    Record record2(0, string("yy"), 2013,2,12,18,50,24,51 , string("yy&zz"), 1.0, "haha");
    RecordPocket r(2013, 2, 12, 1);

    dbm.readInRecordPocket(r);
//    r.addRecord(record2);
    dbm.updateDayRecord(r);

    return 0;
}
