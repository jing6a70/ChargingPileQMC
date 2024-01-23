#ifndef QMC_SERIALPORT_H
#define QMC_SERIALPORT_H
#include <QObject>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>

class QMC_SerialPort: QObject
{
    Q_OBJECT
public:
    explicit QMC_SerialPort(QString dev_name,  QObject *parent = 0);
    size_t send(QByteArray data);
public slots:
    void recv();
private:
    QSerialPort *serial;
};
#endif // QMC_SERIALPORT_H
