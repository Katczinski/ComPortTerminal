#include "serialwrapper.h"

SerialWrapper::SerialWrapper() :
    m_serial(new QSerialPort)
{
    connect(m_serial, &QSerialPort::errorOccurred, this, &SerialWrapper::handleError);
    connect(m_serial, &QSerialPort::readyRead, this, &SerialWrapper::readData);
}

SerialWrapper::~SerialWrapper()
{
    m_serial->close();
    emit endThread();
}

void SerialWrapper::close()
{
    m_serial->close();
    emit endThread();
}

void SerialWrapper::write(const QByteArray &data)
{
    m_serial->write(data);
}

void SerialWrapper::open(const SettingsDialog::Settings& p)
{
    m_serial->setPortName(p.name);
    m_serial->setBaudRate(p.baudRate);
    m_serial->setDataBits(p.dataBits);
    m_serial->setParity(p.parity);
    m_serial->setStopBits(p.stopBits);
    m_serial->setFlowControl(p.flowControl);
    bool isOpen = m_serial->open(QIODevice::ReadWrite);
    emit connectionChange(isOpen);
}

void SerialWrapper::readData()
{
    const QByteArray data = m_serial->readAll();
    emit printReadData(data);
}

void SerialWrapper::handleError()
{
    QString errorMessage = m_serial->errorString();
    if (errorMessage != "No error")
        emit printReadData(errorMessage.toLocal8Bit());
    // Close Port
//    close();
}

QString SerialWrapper::errorString()
{
    return m_serial->errorString();
}
