#ifndef CLIPBOARD_HIJACKER_H
#define CLIPBOARD_HIJACKER_H
#include <QClipboard>


class Clipboard_hijacker : public QObject
{
Q_OBJECT
public:
    Clipboard_hijacker();
    //void hijack(QClipboard *clipboard);
    bool clipboardhasChanged;
    QString getclipboardString();
    QImage getclipboardImage();
    const QMimeData *getMimeData();
    ~Clipboard_hijacker();
private slots:
    void clipboardChanged();
    //void setClipboard();
private:

};

#endif // CLIPBOARD_HIJACKER_H
