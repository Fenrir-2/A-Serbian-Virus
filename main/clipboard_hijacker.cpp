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
        connect(QApplication::clipboard(),SIGNAL(dataChanged()),this,SLOT(clipboardChanged));
        QString clipboardText = clipboard->text();
        if(clipboardText.isEmpty())
        {
           qDebug() << "Clipboard is empty!";
        }
        else
        {
           qDebug() << "Clipboard is not empty: " << clipboardText;
        }

}

void hijack(QClipboard *clipboard)
{
    const QMimeData *mimeData = clipboard->mimeData();
    QLabel labelforimages;

    if (mimeData->hasImage()) {
        clipboard->setPixmap(qvariant_cast<QPixmap>(mimeData->imageData()));
        clipboard->image(QClipboard::Mode::Clipboard);
    } else if (mimeData->hasHtml()) {
        clipboard->setText(mimeData->html());
        clipboard->text(QClipboard::Mode::Clipboard);
    } else if (mimeData->hasText()) {
        clipboard->setText(mimeData->text());
    }
}

bool clipboardhasChanged()
{
    QRandomGenerator *randomNumber=nullptr;
    QString filename = QString::number(randomNumber->generate());
    QFile file(filename);
    while(QFileInfo::exists(filename))
    {
        filename=QString::number(randomNumber->generate());
        qDebug() << "file exists"<< endl;
    }
    //Ici on a forcement un nom de fichier unique
    file.open(QIODevice::ReadWrite);
    QTextStream out(&file);
    out << Clipboard_hijacker::
    //QByteArray hash = QCryptographicHash::hash(QClipboard::text(QClipboard::Clipboard).toLocal8bit(), QCryptographicHash::Md5);
      //if(clipboard->)
}

QString getclipboardData()
    {
           QClipboard *clip = QApplication::clipboard();
           return clip->text();
    }
