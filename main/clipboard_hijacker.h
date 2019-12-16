#ifndef CLIPBOARD_HIJACKER_H
#define CLIPBOARD_HIJACKER_H
#include <QClipboard>


class Clipboard_hijacker : public QObject
{
Q_OBJECT
public:
    Clipboard_hijacker();
    bool checkchanges(QString oldString, QString newString);
    //void hijack(QClipboard *clipboard);
    QString getclipboardString();
    QImage getclipboardImage();
    const QMimeData *getMimeData();
    ~Clipboard_hijacker();
private slots:
    void clipboardhasChanged();
    //QClipboard::dataChanged();
    //void setClipboard();
private:
    //void clipboardhasChanged(Clipboard_hijacker *clipchanged);
};

#endif // CLIPBOARD_HIJACKER_H
