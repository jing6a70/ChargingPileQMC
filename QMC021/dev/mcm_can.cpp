#include "mcm_can.h"
#include <QDebug>

MCM_CAN::MCM_CAN(QObject *parent) : QObject(parent)
{
    char string[100] = {0};
    this->thread_can = NULL;

    system("ifconfig can0 down");
    sprintf(string,"ip link set can0 up type can bitrate %d triple-sampling on", 250000);
    system(string);
    system("ifconfig can0 up");
    socket =  ::socket(PF_CAN,SOCK_RAW,CAN_RAW);

    struct ifreq ifr;
    strcpy((char *)(ifr.ifr_name), "can0");
    ioctl(socket, SIOCGIFINDEX, &ifr);

    addr.can_family  = AF_CAN;
    addr.can_ifindex = ifr.ifr_ifindex;
    bind(socket,(struct sockaddr*)&addr,sizeof(addr));

    this->thread_can = new ThreadCAN(socket);
    connect(this->thread_can, SIGNAL(msg(quint32 , char* , quint8)), this, SLOT(msg(quint32 , char* ,quint8)));

    this->thread_can->start();

}


quint32 MCM_CAN::get_extension_can_id(quint8 prdp, quint8 pf, quint8 ps, quint8 sa)
{
    return ((((prdp << 24) + (pf << 16) + (ps << 8) +(sa)) & CAN_EFF_MASK) | CAN_EFF_FLAG);
}


quint8 MCM_CAN::can_tx(struct can_frame *frame)
{
    return sendto(socket,frame,sizeof(struct can_frame),0,(struct sockaddr*)&addr, sizeof(addr));
}


void MCM_CAN::msg(quint32 canid, char* dat, quint8 len)
{
    QString str;
    str = QString(dat);
    qDebug() << "MCM_CAN rx: " << str << "CAN ID:" << QString().sprintf("%X", canid);
}




