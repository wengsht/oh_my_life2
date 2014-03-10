#include <iostream>
#include <QApplication>
#include <QPushButton>
#include "Record.h"
#include "RecordPocket.h"
#include "DBm.h"
#include "OmlMainWindow.h"
#include <QMessageBox>
#include <QTextCodec>

using namespace std;

int main(int argc, char **argv) {
    QApplication app(argc, argv);
    QTextCodec *codec = QTextCodec::codecForName("UTF-8");

    QTextCodec::setCodecForLocale(codec);
    QTextCodec::setCodecForCStrings(codec);
    QTextCodec::setCodecForTr(codec);

    OmlMainWindow wn;
    wn.show();

    return app.exec();
}
