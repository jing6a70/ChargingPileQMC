#ifndef DEVMCM_H
#define DEVMCM_H

#include <QObject>
#include <sys/ioctl.h>
#include <net/if.h>
#include <linux/can.h>
#include "dev/mcm_can.h"
#include "mpdef.h"
#include "mcm_data.h"


typedef enum CAN_MCM_ADDR
{
    DevMCM_MC_Addr = 0x00,
    DevMCM_CM_AddrA,
    DevMCM_CM_AddrB
}MCM_ADDR;

#define DEVMCM_CUR_OFFSET                   4000

// MC-CM CAN ID
#define DevMCM_ID_MCM_Start(CMAddr)          get_extension_can_id(0x08,0x01,CMAddr,DevMCM_MC_Addr)
#define DevMCM_ID_MCM_Stop(CMAddr)           get_extension_can_id(0x08,0x02,CMAddr,DevMCM_MC_Addr)
#define DevMCM_ID_MCM_Time_Syn(CMAddr)       get_extension_can_id(0x08,0x03,CMAddr,DevMCM_MC_Addr)
#define DevMCM_ID_MCM_Vin_Ack(CMAddr)        get_extension_can_id(0x18,0x33,CMAddr,DevMCM_MC_Addr)
#define DevMCM_ID_MCM_Stop_Ack(CMAddr)       get_extension_can_id(0x18,0x12,CMAddr,DevMCM_MC_Addr)
#define DevMCM_ID_MCM_SET1(CMAddr)           get_extension_can_id(0x08,0x06,CMAddr,DevMCM_MC_Addr)
#define DevMCM_ID_MCM_Link_St(CMAddr)        get_extension_can_id(0x08,0x05,CMAddr,DevMCM_MC_Addr)
#define DevMCM_ID_MCM_SYM_CF1(CMAddr)        get_extension_can_id(0x18,0xb0,CMAddr,DevMCM_MC_Addr)
#define DevMCM_ID_MCM_SYM_CF2(CMAddr)        get_extension_can_id(0x18,0xb1,CMAddr,DevMCM_MC_Addr)
#define DevMCM_ID_MCM_SYM_CF3(CMAddr)        get_extension_can_id(0x18,0xb2,CMAddr,DevMCM_MC_Addr)




typedef struct
{
    quint32 id;  // 帧号
    quint8 d[8]; // 数据
    quint8 len;  // 数据长度, RANGE = 0-8, A+0
}can_msg_t;


class devmcm : public MCM_CAN
{
    Q_OBJECT
public:
    explicit devmcm(MCM_CAN *parent = 0);
    ~devmcm();

    void mcm_start(quint8 devch);
    void mcm_stop(quint8 devch);

public:
    quint16 get_vol();
    quint16 get_cur();
    quint16 get_em();

private:
    void dev_mcm_rx_state(quint8 ch, can_msg_t* dat);
    void dev_mcm_rx_charge_state(quint8 ch, can_msg_t* dat);

signals:

public slots:
    void msg(quint32 canid, char* dat, quint8 len);

private:
    MCM_Data *Rec;
    bool rx_start;
    bool mp_st;
    bool sdgun;
};

#endif // DEVMCM_H
