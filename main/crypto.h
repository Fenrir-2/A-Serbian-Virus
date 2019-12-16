#ifndef CRYPTO_H
#define CRYPTO_H
#include <QString>


class crypto
{
public:
    crypto();
    QString obfuscate(QString casualString,QByteArray key);
    const QByteArray getKey();
private:
    const QByteArray key="This is just for the PoC, XOR is not a true encryption method";
};

#endif // CRYPTO_H
