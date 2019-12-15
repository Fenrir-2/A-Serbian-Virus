#include "mainwindow.h"
#include <QtGui>
#include <QLabel>
#include <QDebug>
#include <QApplication>
#include "clipboard_hijacker.h"
#include "screen_saver.h"
#include "unistd.h"
#include <QtTest/QTest>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    Clipboard_hijacker *clippy = new Clipboard_hijacker();
    QMimeData myMimeData;
    screenshot *scshot = new screenshot();
    while(true)
    {
        //QTest::qWait(1000);
        //usleep(10000);
        //qDebug() << "sleeping";
}

    //w.show();
    return a.exec();
}
