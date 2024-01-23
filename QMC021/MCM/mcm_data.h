#ifndef MCM_DATA_H
#define MCM_DATA_H
#include <QtGlobal>

#define  MCMDATA_EXPORT_MAXSIZE          39

typedef enum
{
    DevMCM_A = 0,
    DevMCM_B,
    DevMCM_MaxSize,
}DevMCM_e;


typedef enum
{
    e_Stop  = 0x10,
    e_Run   = 0x20,
    e_Fault = 0x30,
    e_Wait  = 0x40,
    e_Test  = 0x50,
    e_Pre   = 0x60,
}devmcm_run_state_t;

typedef enum
{
    e_code_8u_run_st,
    e_code_8u_run_ccvol,
    e_code_16u_run_vol,
    e_code_16u_run_cur,
    e_code_16u_run_em,
    e_code_16u_run_time,
    e_code_8u_bcs_soc,
    e_code_16u_bcs_cmptime,
    e_code_16u_bcs_svolmax,
    e_code_16u_bcs_svolmin,
    e_code_8u_bcs_maxtemp,
    e_code_8u_info_type,
    e_code_8u_start_second,
    e_code_8u_start_min,
    e_code_8u_start_hour,
    e_code_8u_start_day,
    e_code_8u_start_mouth,
    e_code_8u_start_year,
    e_code_8u_start_soc,
    e_code_8u_stop_second,
    e_code_8u_stop_min,
    e_code_8u_stop_hour,
    e_code_8u_stop_day,
    e_code_8u_stop_mouth,
    e_code_8u_stop_year,
    e_code_16u_ac_a_vol,
    e_code_16u_ac_b_vol,
    e_code_16u_ac_c_vol,
    e_code_16u_ac_a_cur,
    e_code_16u_ac_b_cur,
    e_code_16u_ac_c_cur,
    e_code_32u_meter_em,
    e_code_32u_meter_pow,
    e_code_8u_stop_reason,
    e_code_32u_cm_ver,
    e_code_32u_cm_dt1,
    e_code_32u_cm_dt2,
    e_code_16u_bmsVolReq,
    e_code_16u_bmsCurReq,
}mcm_data_code_t;

typedef enum
{
    e_code_b_device_connect,
    e_code_b_device_door,
    e_code_b_device_chargegun
}mcm_device_sta_code_t;

typedef enum
{
    e_BMS = 1,
    e_Manual
}devmcm_charge_mode_t;

typedef struct
{
    quint8          type;
    void           *p;
}mcmdata_t;


class BSM_Data
{
    struct
    {
        quint8  Soc;
        quint16 CmpTime;
        quint16 SvolMax;
        quint16 SvolMin;
        quint8  MaxTemp;
    }BCS;
    struct
    {
        quint8  bms_pv[3];
        quint16 chm_ver;
        quint8  type;
        quint16 cap;
        quint16 rvol;
        quint8  vin[17];
    }info;
    struct
    {
        quint16 sigMaxVol;
        quint16 bmsMaxCur;
        quint16 batAllPow;
        quint16 bmsMaxVol;
        quint16 batVol;
        quint8  allTempMax;
    }BCP;
    struct
    {
        quint16 bmsReqVol;
        quint16 bmsReqCur;
        quint8  MinTemp;
        quint8  svMaxPos;
        quint8  tempMaxPos;
        quint8  tempMinPos;
        quint8  cgMode;
    }BCL;
};

class MCM_Data
{
public:
    MCM_Data();
    const    quint8 * get_sdn_list_data(quint8 ch);
    const    quint8 * get_fault_code_string(quint8 ch);
    quint32  get_mcm_data(quint8 ch, mcm_data_code_t code);
    bool     get_mcm_device_sta(quint8 ch, mcm_device_sta_code_t code);
    quint8   get_sdn_code(quint8 ch);
    const    quint8 * get_sdn_info(quint8 sdnCode, quint8 bmsToutCode);

    struct
    {
        devmcm_run_state_t Run;
        union
        {
            quint8 Byte;
            struct
            {
                quint8 Connect            :1;
                quint8 Door               :1;
                quint8 Chargegun          :1;
                quint8                    :5;
            }Bits;
        }Device;
        quint8 cc_vol;
        quint8 fault_code;
        quint8 fault_bms_tout_code;
        quint8 gunTemp;
    }Sta;
    struct
    {
        quint16 Vol;
        quint16 Cur;
        quint16 Em;
        quint16 Time;
    }Run;
    struct
    {
        quint32 em;
        quint32 pow;
    }meter;
    struct
    {
            quint8  Cnt;
            quint8  second;
            quint8  minutes;
            quint8  hour;
            quint8  day;
            quint8  month;
            quint8  year;
            quint8  soc;
    }start_sta;
    struct
    {
            quint8  second;
            quint8  minutes;
            quint8  hour;
            quint8  day;
            quint8  month;
            quint8  year;
    }stop_sta;
    struct
    {
        quint16 a_vol;
        quint16 b_vol;
        quint16 c_vol;
        quint16 a_cur;
        quint16 b_cur;
        quint16 c_cur;
    }ac;
    BSM_Data BM;
    quint8  sdn_code;
    quint8  bms_tout_code;
    quint8  bmsCode;
    quint32  cm_ver;
    quint32  cm_debug_time1;
    quint32  cm_debug_time2;

    mcmdata_t mcmdata[DevMCM_MaxSize][MCMDATA_EXPORT_MAXSIZE];
};

#endif // MCM_DATA_H
