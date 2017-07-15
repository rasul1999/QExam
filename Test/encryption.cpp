#include <QString>
#include <QByteArray>
#include "encryption.h"

QString encryption::encrypt(QString qs){
    qs.replace("\n", " ");
    QByteArray ba = qs.toUtf8();
    for(auto i = 0; i != ba.length(); ++i){
        ba[i] = ba[i] + 3;
    }
    return QString::fromUtf8(ba.data());
}

QString encryption::decrypt(QString qs){
    QByteArray ba = qs.toUtf8();
    for(auto i = 0; i != ba.length(); ++i){
        ba[i] = ba[i] - 3;
    }
    return QString::fromUtf8(ba.data());
}
