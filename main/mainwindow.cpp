#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <clipboard_hijacker.h>
#include <QtGui>
#include <QLabel>
#include <QDebug>
#include <QApplication>
#include "clipboard_hijacker.h"
#include "screen_saver.h"
#include "unistd.h"
#include <QtTest/QTest>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    Clipboard_hijacker *clippy = new Clipboard_hijacker();
    QMimeData myMimeData;
    Screenshot *scshot = new Screenshot();

    /*while(true)
    {
        //QTest::qWait(1000);
        //usleep(10000);
        //qDebug() << "sleeping";
}
*/

}

MainWindow::~MainWindow()
{
    delete ui;
}

