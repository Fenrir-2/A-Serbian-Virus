#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QFileDialog>
#include <QJsonObject>
#include <QJsonArray>
#include <QFile>
#include <QTableWidgetItem>
#include <QJsonDocument>
#include <QTcpSocket>
#include <QMessageBox>
#include <QTimer>
#include <QClipboard>
#include <vector>
#include <utility>

#include "addtargetwindow.h"
#include "helpwindow.h"
#include "textdisplaywindow.h"

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
    QJsonDocument* prepareJSON();
    void writeJSONToFile(QFile*);
    void displayError(QTcpSocket::SocketError);
    void resetStatusTimer(int);
    void resetStatus();
    void sendCmd(QString);
    void populateTable(std::vector<std::pair<QString, QString>>);

private slots:
    void on_actionHelp_triggered();
    void on_actionQuit_triggered();
    void on_clipboardButton_clicked();
    void on_connectButton_clicked();
    void on_sendCmdButton_clicked();
    void on_extractButton_clicked();
    void on_actionLoad_triggered();
    void on_actionSave_triggered();
    void on_actionSave_as_triggered();
    void on_tableWidget_cellClicked(int, int);
    void read();
    void on_screenshotButton_clicked();
    void machineDoubleClicked(int, int);
    void socketStateChanged(QAbstractSocket::SocketState);

    void on_actionAdd_new_target_triggered();

    void on_actionRemove_triggered();

private:
    Ui::MainWindow *ui;
    QLabel *statusLabel;
    QFile *loadedFile;
    QString selectedMachineIp;
    QString selectedMachineName;
    int selectedMachine;
    int connectedMachine;
    QTcpSocket *clientSocket;
    DATA_REQUESTER networkHandler;
};
#endif // MAINWINDOW_H
