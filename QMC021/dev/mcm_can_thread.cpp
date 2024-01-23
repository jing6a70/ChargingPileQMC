#include "mcm_can_thread.h"


ThreadCAN::ThreadCAN(int s,QObject *parent) :
    QThread(parent)
{
    socket  = s;
    this->running = true;
}

void ThreadCAN::run()
{
    int nbytes;
    int len;
    struct can_frame frame;
    struct sockaddr_can addr;
    char buf[10];
    quint32 eid;
    while(this->running)
    {
        nbytes = recvfrom(socket,&frame,sizeof(struct can_frame),0,(struct sockaddr *)&addr,(socklen_t*)&len);
        if( nbytes > 0 )
        {
            memset(buf,0,10);
            memcpy(buf, frame.data, 8);
            eid = frame.can_id & CAN_EFF_MASK;
            emit msg(eid, &buf[0], frame.can_dlc);
        }
    }
}

void ThreadCAN::stop()
{
    this->running = false;
}
