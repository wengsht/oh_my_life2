#ifndef __STATIS_WIDGET__
#define __STATIS_WIDGET__

#include <QWidget>
#include "DBm.h"

class StatisWidget : public QWidget {
    Q_OBJECT
public:
    StatisWidget(DBm *db);
    ~StatisWidget();

private:
    DBm *db;

private slots:
};

#endif
