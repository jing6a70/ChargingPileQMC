#include "qmc_serialport.h"
#include "QDebug"

static const QString rs485_port1 = "dev/ttymxc2";

QMC_SerialPort::QMC_SerialPort(QString dev_name, QObject *parent) :
    QObject(parent)
{
    // 打开设备
    serial = new QSerialPort;
    //设置串口名
    serial->setPortName(dev_name);
    //打开串口
    if(serial->open(QIODevice::ReadWrite))
    {
        // 设置波特率
        serial->setBaudRate(115200);
        // 设定模式8n1
        serial->setDataBits(QSerialPort::Data8);
        serial->setParity(QSerialPort::NoParity);
        serial->setStopBits(QSerialPort::OneStop);
        // 关闭流量控制
        serial->setFlowControl(QSerialPort::NoFlowControl);
        QObject::connect(serial, SIGNAL(readyRead()), this, SLOT(recv()));
    }
    else
    {
        qDebug() << "rs485_port1 open Error";
    }
}


size_t QMC_SerialPort::send(const QByteArray data)
{
    if(!data.isEmpty())
    {
        this->serial->write(data);
    }

    return data.length();

}

//读取接收到的数据
void QMC_SerialPort::recv()
{
    QByteArray buf;
    buf = serial->readAll();
    if(!buf.isEmpty())
    {

    }
    buf.clear();
}
