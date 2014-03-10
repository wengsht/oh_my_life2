#include "RecordWidget.h"
#include <QVBoxLayout>
#include <QPushButton>
#include <QWidget>
#include <QTableWidgeTItem>
#include <QMessageBox>
#include <string>
#include <iostream>
#include "QT.def"
using namespace std;

pair<int, int> RecordWidget::getLatestHM() {
#include "sql.def"
    int nC = table->rowCount();
    int h = 0, m = 0;
    for(int I = 0; I < nC - 1; I++) {
        int th = ((table->item(I, QT_ENDH_COLUMN))->text()).toInt();
        int tm = ((table->item(I, QT_ENDM_COLUMN))->text()).toInt();

        if(h < th || h == th && m < tm) {
            h = th;
            m = tm;
        }
    }
    return make_pair(h, m);
}
void RecordWidget::addRecord() {
    table->setRowCount(table->rowCount()+1);

    Record newRecord;

    pair<int, int> hm = getLatestHM();

    newRecord.setBeginTime(today.year(), today.month(), today.day(), hm.first, hm.second);
    newRecord.setEndTime(today.year(), today.month(), today.day(), hm.first, hm.second);

    recordPocket->addRecord(newRecord);

    relistRecord(table->rowCount() - 1);
}
void RecordWidget::tagsGenerate() {
    QPushButton *senderButton = qobject_cast<QPushButton *>(sender());

    if(senderButton == NULL) return ;

    QModelIndex index = table->indexAt(QPoint(senderButton->frameGeometry().x(),senderButton->frameGeometry().y()));

    int row = index.row();

#include "sql.def"
    string name = ((table->item(row, QT_NAME_COLUMN))->text()).toStdString();

    string tags = "";  

    db->getTagsStringByName(name, tags);

    table->setItem(row, QT_TAGS_COLUMN, new QTableWidgetItem(tags.c_str()));
}
void RecordWidget::removeRow() {
    int ret = QMessageBox::question(this, "删除记录", "确定删除本行?", QMessageBox::Yes | QMessageBox::No, QMessageBox::No);
    if(ret == QMessageBox::Yes) {
        QPushButton *senderButton = qobject_cast<QPushButton *>(sender());

        if(senderButton == NULL) return ;

        QModelIndex index = table->indexAt(QPoint(senderButton->frameGeometry().x(),senderButton->frameGeometry().y()));

        int row = index.row();
        table->removeRow(row);

        recordPocket->removeRecord(row);
    }
}
void RecordWidget::relistRecord(int I) {
#include "sql.def"
    QPushButton * removeButton = new QPushButton("删除");
    QPushButton * tagsButton = new QPushButton("推荐tags");
    table->setCellWidget(I, QT_COLUMNS, removeButton);
    table->setCellWidget(I, QT_COLUMNS+1, tagsButton);
    QObject::connect(removeButton, SIGNAL(clicked()), this, SLOT(removeRow()));
    QObject::connect(tagsButton, SIGNAL(clicked()), this, SLOT(tagsGenerate()));

#define TABLE_INIT_ITEM(J, text) \
    table->setItem(I, J, new QTableWidgetItem(text));
    TABLE_INIT_ITEM(0, (*recordPocket)[I].getName().c_str())
        TABLE_INIT_ITEM(1, QString::number((*recordPocket)[I].getBeginH()))
        TABLE_INIT_ITEM(2, QString::number((*recordPocket)[I].getBeginM()))
        TABLE_INIT_ITEM(3, QString::number((*recordPocket)[I].getEndH()))
        TABLE_INIT_ITEM(4, QString::number((*recordPocket)[I].getEndM()))
        TABLE_INIT_ITEM(5, (*recordPocket)[I].getTagsAsString().c_str())
        TABLE_INIT_ITEM(6, QString::number((*recordPocket)[I].getNums()))
        TABLE_INIT_ITEM(7, (*recordPocket)[I].getComment().c_str())
}
void RecordWidget::relist() {
    table->setRowCount(recordPocket->recordSize());
#include "sql.def"
    string strs[] = { QT_COLUMN_LIST };
    for(int I = 0; I < recordPocket->recordSize();I++) {
        relistRecord(I);
    }
}
void RecordWidget::reload() {
    int ret = QMessageBox::question(this, "确认加载", "未保存修改将丢失，确认继续加载?", QMessageBox::Yes | QMessageBox::No , QMessageBox::No);
    if(ret == QMessageBox::No) 
        return ;

    today = calendar->selectedDate();
    recordPocket->clear();
    recordPocket->resetDate(today.year(), today.month(), today.day(), 1);

    db->readInRecordPocket(*recordPocket);

    relist();
}
void RecordWidget::updateRecord(int row) {
#define TABLE_UPDATE_ITEM(J, code, toSomeThing) \
    (*recordPocket)[row].code(((table->item(row, J))->text()).toSomeThing());

    TABLE_UPDATE_ITEM(0, setName, toStdString);
    TABLE_UPDATE_ITEM(1, setBeginH, toInt);
    TABLE_UPDATE_ITEM(2, setBeginM, toInt);
    TABLE_UPDATE_ITEM(3, setEndH, toInt);
    TABLE_UPDATE_ITEM(4, setEndM, toInt);

    TABLE_UPDATE_ITEM(5, initTags, toStdString);
    TABLE_UPDATE_ITEM(6, setNums, toDouble);
    TABLE_UPDATE_ITEM(7, setComment, toStdString)
}
void RecordWidget::update() {
    int ret = QMessageBox::question(this, "保存与否", "需要保存已修改数据?", QMessageBox::Yes | QMessageBox::No , QMessageBox::No);

    if(ret == QMessageBox::No) 
        return ;

    int I;
    for(I = 0; I < recordPocket->recordSize(); I++) {
        updateRecord(I);
    }
    db->updateDayRecord(*recordPocket);
}
RecordWidget::RecordWidget(DBm *db) : db(db) {
    setFixedHeight(CENTRAL_HEIGHT);
    QVBoxLayout *layout1 = new QVBoxLayout();

    calendar = new QCalendarWidget();

    today = calendar->selectedDate();

    recordPocket = new RecordPocket(today.year(), today.month(), today.day(), 1);
    db->readInRecordPocket(*recordPocket);


    const int FixedLen = 300;
    const double HP = 0.618;
    calendar->setFixedWidth(FixedLen);
    calendar->setFixedHeight(FixedLen * HP);
    QHBoxLayout *layoutHead = new QHBoxLayout();

    layoutHead->addWidget(calendar);

    QPushButton *reloadButton = new QPushButton("加载");
    QPushButton *updateButton = new QPushButton("保存");
    QPushButton *addButton = new QPushButton("增添记录");

    QObject::connect(reloadButton, SIGNAL(clicked()), this, SLOT(reload()));
    QObject::connect(updateButton, SIGNAL(clicked()), this, SLOT(update()));
    QObject::connect(addButton, SIGNAL(clicked()), this, SLOT(addRecord()));

    reloadButton->setFixedWidth(HP * FixedLen );
    reloadButton->setFixedHeight(HP * FixedLen );

    updateButton->setFixedWidth(HP * FixedLen );
    updateButton->setFixedHeight(HP * FixedLen );

    addButton->setFixedWidth(HP * FixedLen );
    addButton->setFixedHeight(HP * FixedLen );

    QHBoxLayout *layoutButtons = new QHBoxLayout();
    layoutButtons->addWidget(reloadButton);
    layoutButtons->addWidget(updateButton);
    layoutButtons->addWidget(addButton);
    layoutHead->addLayout(layoutButtons);

    QHBoxLayout *layoutTail = new QHBoxLayout();

    initTable();

    layoutTail->addWidget(table);

    layout1->addLayout(layoutHead);
    layout1->addLayout(layoutTail);

    setLayout(layout1);
}
RecordWidget::~RecordWidget() {

}
void RecordWidget::initTable() {
    table = new QTableWidget();
    table->setRowCount(10);
    table->setFixedWidth(1050);
    table->setFixedHeight(400);

#include "sql.def"
    table->setColumnCount(QT_COLUMNS+2);

    QStringList *strList = new QStringList();
    QString strs[] = { QT_COLUMN_LIST };
    for(int I = 0; I < QT_COLUMNS; I++) {
        strList->push_back(strs[I]);
    }
    table->setHorizontalHeaderLabels(*strList);

    relist();
}
