#ifndef __RECORD_WIDGET__
#define __RECORD_WIDGET__

#include <QWidget>
#include <QCalendarWidget>
#include <QDate>
#include "RecordPocket.h"
#include <QTableWidget>
#include "DBm.h"
#include <QPushButton>

class RecordWidget : public QWidget {
    Q_OBJECT
public:
    RecordWidget(DBm *db);
    ~RecordWidget();

private:
    DBm *db;
    RecordPocket *recordPocket;
    QCalendarWidget *calendar;
    QTableWidget *table;
    QDate today;
    void initTable();

private slots:
    pair<int, int> getLatestHM();
    void reload();
    void update();
    void relist();
    void relistRecord(int I);
    void removeRow();
    void tagsGenerate();
    void updateRecord(int row);
    void addRecord();
};

#endif
