#include <crypto.h>

crypto::crypto()
{
}
QString crypto::obfuscate(QString casualString, QByteArray key)
{
    QByteArray byteText = casualString.toUtf8();
    QByteArray finalString;
    for(int i=0; i<casualString.length();i++)
    {
        finalString[i]=byteText[i]^key[i%key.size()];
    }
    return QString::fromStdString(finalString.toStdString());
}
    const QByteArray crypto::getKey()
    {
        return this->key;
    }
