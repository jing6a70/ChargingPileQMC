#ifndef MPDEF_H
#define MPDEF_H

#define _MC_VER "MCQ23_10"



typedef enum _MC_SYS_STAT{
    MP_STANDBY = 0,
    MP_RUNING,
    MP_WAIT,
}mp_st_e;


typedef enum _MC_GUN_NUM {
    MP_CM_SEL_A = 0,
    MP_CM_SEL_B,
    MP_CM_SEL_MAX,
}mp_gun_sel_e;

/*
 * ch: Gun number
 * Return Val:
 * - returns non-zero  on  success
 * - on error,  0 is returned
*/
#define mp_check_sel_max(ch) (ch < MP_CM_SEL_MAX)


// Convert
#define t_dc_8u_16u(h,l)            (((quint16)(h)<<8)+(l))
#define t_dc_16u_h_8u(w)            ((w)>>8)
#define t_dc_16u_l_8u(w)            ((quint8)(w))
#define t_dc_16u_8u(w,h,l)          h=t_dc_16u_h_8u(w);l=t_dc_16u_l_8u(w)
#define t_dc_8u_32u(h1,h0,l1,l0)    (((INT32U)(h1)<<24)+((INT32U)(h0)<<16)+((INT16U)(l1)<<8)+(l0))
#define t_dc_16u_32u(h,l)           (((INT32U)(h)<<16)+(l))
#define t_dc_32u_h_16u(l)           ((l)>>16)
#define t_dc_32u_l_16u(l)           ((INT16U)(l))
#define t_dc_32u_h1_8u(l)           ((l)>>24)
#define t_dc_32u_h0_8u(l)           (((l)&0x00ff0000)>>16)
#define t_dc_32u_l1_8u(l)           (((l)&0x0000ff00)>>8)
#define t_dc_32u_l0_8u(l)           ((l)&0x000000ff)
#define t_dc_32u_8u(l,h1,h0,l1,l0)  h1=t_dc_32u_h1_8u(l);h0=t_dc_32u_h0_8u(l);l1=t_dc_32u_l1_8u(l);l0=t_dc_32u_l0_8u(l)
#define t_dc_time1_16u(h,l)         t_dc_8u_16u(h,l)        // time1: hex
#define t_dc_time2_16u(h,l)         ((INT16U)(h)*60+(l))    // time2: h,小时/分钟 l,分钟/秒


// Mark
#define tM0                         0x01
#define tM1                         0x03
#define tM2                         0x07
#define tM3                         0x0f
#define tM4                         0x1f
#define tM5                         0x3f
#define tM6                         0x7f
#define tM7                         0xff
#define tB0                         0x01
#define tB1                         0x02
#define tB2                         0x04
#define tB3                         0x08
#define tB4                         0x10
#define tB5                         0x20
#define tB6                         0x40
#define tB7                         0x80
#define tB8                         0x0100
#define tB9                         0x0200
#define tB10                        0x0400
#define tB11                        0x0800
#define tB12                        0x1000
#define tB13                        0x2000
#define tB14                        0x4000
#define tB15                        0x8000
#define tB16                        0x00010000
#define tB17                        0x00020000
#define tB18                        0x00040000
#define tB19                        0x00080000
#define tB20                        0x00100000
#define tB21                        0x00200000
#define tB22                        0x00400000
#define tB23                        0x00800000
#define tB24                        0x01000000
#define tB25                        0x02000000
#define tB26                        0x04000000
#define tB27                        0x08000000
#define tB28                        0x10000000
#define tB29                        0x20000000
#define tB30                        0x40000000
#define tB31                        0x80000000

namespace MC_MP
{
    // 接收按键
    enum MC_KEY
    {
        MCKEY_GUN_A,
        MCKEY_GUN_B,
        MCKEY_BACK,
        MCKEY_IC_MODE,
        MCKEY_PW_MODE,
        MCKEY_VIN_MODE,
        MCKEY_QR_MODE,
        MCKEY_SETTING,
        MCKEY_ALARM,
        MCKEY_CHARING,
        MCKEY_CHARINGMORE
    };
    // 枪号
    enum MC_GUN
    {
        MC_CM_SEL_GUN_A,
        MC_CM_SEL_GUN_B,
        MC_CM_SEL_GUN_NULL
    };

    enum MC_PAGE
    {
        MP_STANDBY_FORM,
        MP_CGMODE_FORM,
        MP_PW_MODE_FORM,
        MP_SET_FORM,      //设置界面
        MP_IC_MODE_FORM,
        MP_QR_MODE_FORM,
        MP_VIN_MODE_FORM,
        MP_CG_FORM,
        MP_CG_MORE_FORM,
      //  MP_SET_FORM,        //设置界面
        MP_PAGE_MAX
    };
}

namespace MCQ_MI
{
    // 实页面 Number
    enum MC_FORM
    {
        MP_STANDBY_FORM = 0,
        MP_CGMODE_FORM,
        MP_PW_MODE_FORM,
        MP_SET_FORM,      //设置界面
        MP_IC_MODE_FORM,
        MP_QR_MODE_FORM,
        MP_VIN_MODE_FORM,
        MP_CG_FORM,
        MP_CG_MORE_FORM,

        MP_PAGE_MAX
    };
}

#endif // MPDEF_H
