#ifndef SERIALWRAPPER_H
#define SERIALWRAPPER_H

#include <QObject>
#include <QSerialPort>
#include "settingsdialog.h"

class SerialWrapper : public QObject
{
    Q_OBJECT
public:
    SerialWrapper();
    ~SerialWrapper();
public slots:
    void                open(const SettingsDialog::Settings& p);
    void                readData();
    void                handleError();
    void                close();
    void                write(const QByteArray& data);
    QString             errorString();
signals:
    void                error(const QString& message);
    void                printReadData(const QByteArray& data);
    void                connectionChange(const bool isOpen);
    void                endThread();
private:
    QSerialPort     *m_serial;
};

#endif // SERIALWRAPPER_H
