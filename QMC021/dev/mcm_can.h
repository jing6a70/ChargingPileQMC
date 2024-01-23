#ifndef MCM_CAN_H
#define MCM_CAN_H

#include <QObject>
#include <sys/ioctl.h>
#include <net/if.h>
#include <linux/can.h>
#include "mcm_can_thread.h"

typedef enum _CAN_FRAME_TYPE
{
    MCM_CAN_STANDARD_FRAME = 0,
    MCM_CAN_EXTENSION_FRAME,
    MCM_CAN_REMOTE_FRAME,
}CAN_FT;


class MCM_CAN : public QObject
{
    Q_OBJECT
public:
    explicit MCM_CAN(QObject *parent = 0);
    quint8  can_tx(struct can_frame *frame);
    quint32 get_extension_can_id(quint8 prdp, quint8 pf, quint8 ps, quint8 sa);

signals:

public slots:
    virtual void msg(quint32 canid, char* dat, quint8 len) = 0;

public:
    int socket;
    struct sockaddr_can addr;
    ThreadCAN *thread_can;
};


#endif // MCM_CAN_H
