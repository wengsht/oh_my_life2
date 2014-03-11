#include "omlMainWindow.h"
#include <QWidget>
#include <QHBoxLayout>
#include <iostream>
#include <QMessageBox>
#include <QIODevice>
#include <QTextStream>
#include <QString>
#include <QPalette>
#include <QColor>
#include <fstream>
#include "RecordWidget.h"
#include "StatisWidget.h"
#include <QFile>
#include <QDataStream>
#include "QT.def"

using namespace std;

void OmlMainWindow::changeToFrontEnd() {
    frontEnd->show();
    recordWidget->hide();
    statisWidget->hide();
}
void OmlMainWindow::changeToRecord() {
    frontEnd->hide();
    recordWidget->show();
    statisWidget->hide();
}
void OmlMainWindow::changeToStatic() {
    frontEnd->hide();
    recordWidget->hide();
    statisWidget->show();
}
void OmlMainWindow::initFrontEnd() {
    frontEnd = new QWidget();
    frontEnd->setWindowOpacity(0.5);
    QVBoxLayout *layout2 = new QVBoxLayout();

    QPushButton *button1 = new QPushButton(QString("新的征程"));
    QPushButton *button2 = new QPushButton(QString("旧的回忆"));

    button1->setFixedSize(QSize(150, 50));
    button2->setFixedSize(QSize(150, 50));

    layout2->addWidget(button1);
    layout2->addWidget(button2);

    frontEnd->setLayout(layout2);
    frontEnd->setFixedWidth(CENTRAL_WIDTH);
    frontEnd->setFixedHeight(CENTRAL_HEIGHT);
//    frontEnd->setAutoFillBackground(true); 

    QObject::connect(button1, SIGNAL(clicked()), this, SLOT(changeToRecord()));
    QObject::connect(button2, SIGNAL(clicked()), this, SLOT(changeToStatic()));

    recordWidget->hide();
    statisWidget->hide();
}
void OmlMainWindow::initRecordWidget() {
    recordWidget = new RecordWidget(db);
}
void OmlMainWindow::initStatisWidget() {
    statisWidget = new StatisWidget(db);
}

OmlMainWindow::OmlMainWindow() {
    setAutoFillBackground(true);
    QPalette palette;
    setFixedWidth(WINDOW_WIDTH);
    setFixedHeight(WINDOW_HEIGHT);
    QPixmap pixmap = QPixmap(":/images/background.jpg").scaled(QSize(1200, 900));// Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    palette.setBrush(QPalette::Background,QBrush(pixmap));
    setPalette(palette);

    /*  
    QString dbPath;
    QFile profile("~/.oh-my-life");
    profile.open(QIODevice::ReadOnly);
    QTextStream in(&profile);
    in >> dbPath;
    profile.close();
    */

    string dbPath;
    ifstream in("./.oh-my-life");
    in >> dbPath;

    if(dbPath.length() == 0)
        dbPath = "~/life.db";
    
    db = new DBm(dbPath.c_str(), "life");

    QWidget *widget = new QWidget();
    setCentralWidget(widget);

    QHBoxLayout *layout1 = new QHBoxLayout();
    QVBoxLayout *layout2 = new QVBoxLayout();

    initRecordWidget();
    initStatisWidget();

    initFrontEnd();

    layout1->addWidget(frontEnd);
    layout1->addWidget(recordWidget);
    layout1->addWidget(statisWidget);
    layout2->addLayout(layout1);

    QPushButton *returnButton = new QPushButton("回主选单");

    QObject::connect(returnButton, SIGNAL(clicked()), this, SLOT(changeToFrontEnd()));

    returnButton->setFixedHeight(50);

    layout2->addWidget(returnButton);

    widget->setLayout(layout2);
}
OmlMainWindow::~OmlMainWindow() {
}
