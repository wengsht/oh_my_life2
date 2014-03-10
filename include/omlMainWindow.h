#ifndef __OML_MAINWINDOW__
#define __OML_MAINWINDOW__

#include <QMainWindow>
#include <QPushButton>
#include <QHBoxLayout>
#include "DBm.h"
class OmlMainWindow : public QMainWindow {
    Q_OBJECT
public:
    OmlMainWindow();
    ~OmlMainWindow();
private:
    DBm *db;
    QWidget *recordWidget;
    QWidget *statisWidget;
    QWidget *frontEnd;

    void initFrontEnd();
    void initRecordWidget();
    void initStatisWidget();
private slots:
    void changeToRecord();
    void changeToStatic();
    void changeToFrontEnd();

};

#endif
