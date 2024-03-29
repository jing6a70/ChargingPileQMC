#ifndef THREAD_H
#define THREAD_H

#include <QThread>
#include <sys/ioctl.h>
#include <net/if.h>
#include <linux/can.h>


#ifndef PF_CAN
#define PF_CAN 29
#endif

#ifndef AF_CAN
#define AF_CAN PF_CAN
#endif

class ThreadCAN: public QThread
{
    Q_OBJECT
public:
    explicit ThreadCAN(int s,QObject *parent = 0);
    
signals:
    void msg(quint32 canid, char* dat, quint8 len);

public slots:
    void run();
    void stop();

private:
    int socket;
    bool running;
};

#endif // THREAD_H
