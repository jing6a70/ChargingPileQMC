/*
 * jingpeng 2024 01 08
 * CAN
 * MC & CM
*/

#include "devmcm.h"
#include <iostream>
#include <QDebug>



devmcm::devmcm(MCM_CAN *parent) : MCM_CAN(parent)
{
    this->Rec = new MCM_Data();
}

devmcm::~devmcm()
{

}


void devmcm::msg(quint32 canid, char* dat, quint8 len)
{
    quint8 CAN_PF, CAN_PS, CAN_SA;
    QString str;
    can_msg_t msg;
    str = QString(dat);
    qDebug() << "devmcm:" << str << "   " << QString().sprintf("Eid = %X", canid);
    // Get Can PF
    CAN_PF = (quint8)((canid & 0x00FF0000) >> 16);
    qDebug() << "devmcm:"<< "PF =" << QString().sprintf("Eid = %X", CAN_PF);
    // Get Can PS
    CAN_PS = (quint8)((canid & 0x0000FF00) >> 8);
    qDebug() << "devmcm:"<< "PS =" << QString().sprintf("Eid = %X", CAN_PS);
    // Get Can SA
    CAN_SA = (quint8)(canid & 0x000000FF);
    qDebug() << "devmcm:"<< "SA =" << QString().sprintf("Eid = %X", CAN_SA);

    switch(CAN_SA)
    {
        case 0: msg.id = 2; break;
        case 1: msg.id = 4; break;
        default: break;
    }
    memcpy(msg.d, dat, len);
    msg.len = len;

    switch(CAN_PF)
    {
        case 0x10: this->dev_mcm_rx_state(CAN_SA, &msg); break;
        case 0x11: this->dev_mcm_rx_charge_state(CAN_SA, &msg); break;
        default: break;
    }
}



/**************************************************************************
   协议层: TX
**************************************************************************/

void devmcm::mcm_start(quint8 devch)
{

    struct can_frame msg;
    memset(&msg, 0, sizeof(struct can_frame));

    switch(devch)
    {
        case 0: msg.can_id = DevMCM_ID_MCM_Start(DevMCM_CM_AddrA); break;
        case 1: msg.can_id = DevMCM_ID_MCM_Start(DevMCM_CM_AddrB); break;
        default:    return;
    }

    msg.data[0] = 0x55;
    msg.data[1] = 0xff;
    msg.data[2] = 0xff;
    msg.data[3] = 0xff;
    msg.data[4] = 0xff;
    msg.data[5] = 0xee;
    msg.data[6] = 0xff;
    msg.data[7] = 0xff;
    msg.can_dlc  = 8;

    this->can_tx(&msg);
}


void devmcm::mcm_stop(quint8 devch)
{
    struct can_frame msg;
    memset(&msg, 0, sizeof(struct can_frame));

    switch(devch)
    {
        case 0: msg.can_id = DevMCM_ID_MCM_Stop(DevMCM_CM_AddrA); break;
        case 1: msg.can_id = DevMCM_ID_MCM_Stop(DevMCM_CM_AddrB); break;
        default:    return;
    }

    msg.data[0] = 0x55;
    msg.data[1] = 0xff;
    msg.data[2] = 0xff;
    msg.data[3] = 0xff;
    msg.data[4] = 0xff;
    msg.data[5] = 0xff;
    msg.data[6] = 0xff;
    msg.data[7] = 0xff;
    msg.can_dlc = 8;

    this->can_tx(&msg);
}



/**************************************************************************
   协议层: RX
**************************************************************************/
void devmcm::dev_mcm_rx_state(quint8 ch, can_msg_t* msg)
{

    if(mp_check_sel_max(ch))
    {
        this->Rec->Sta.Run         = (devmcm_run_state_t)msg->d[0];
        this->Rec->Sta.Device.Byte = msg->d[1];
        this->Rec->Sta.cc_vol      = msg->d[3];
        this->Rec->Sta.fault_code  = msg->d[4];
        this->Rec->Sta.gunTemp     = msg->d[6];
    }
}


void devmcm::dev_mcm_rx_charge_state(quint8 ch, can_msg_t* msg)
{


    if(mp_check_sel_max(ch))
    {
        this->Rec->Run.Vol  = t_dc_8u_16u(msg->d[1],msg->d[0]) ;
        this->Rec->Run.Cur  = DEVMCM_CUR_OFFSET - t_dc_8u_16u(msg->d[3],msg->d[2]);

        this->Rec->Run.Em   = t_dc_8u_16u(msg->d[5], msg->d[4]);
        this->Rec->Run.Time = t_dc_8u_16u(msg->d[7], msg->d[6]);

        qDebug() << "当前电压:" << this->Rec->Run.Vol;
        qDebug() << "当前电流:" << this->Rec->Run.Cur;
        qDebug() << "当前电量:" << this->Rec->Run.Em;
    }
}

quint16 devmcm::get_vol() { return this->Rec->Run.Vol; }

quint16 devmcm::get_cur() { return this->Rec->Run.Cur; }

quint16 devmcm::get_em()  { return this->Rec->Run.Em;}
