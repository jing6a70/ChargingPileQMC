#ifndef SYSTEMCONFIG_H
#define SYSTEMCONFIG_H

#include <QWidget>

namespace Ui {
class systemconfig;
}

//系统参数
struct Parameter
 {
    quint8 Gunnum;         //充电枪数量
    quint8 Pt_agreement;   //充电平台协议
    quint8 cg_mode;        //充电模式

    quint8 Auxiliarypower;  //辅助电源
    quint8 Singlevehmode;  //单车充电模式
    quint8 Piletype;       //充电桩类型（主控板）
 };

//桩监控参数
struct MonitoredParameter
 {
    quint8   Cgtype;                     //充电机类型（监控板）

    quint16  Outvol ;                    //输出电压

    quint16  Outcur;                     //输出电流

    quint16  InsulationAlrmValue;        //绝缘告警值

    quint16  Maxbatterytemp;             //电池最高温度

    quint16  Maxsinbatteryvol;           //电池单体最高电压

    quint16  Maxguntemp;                 //充电枪最高温度

    quint8   InsulationDete;             //绝缘检测

    quint8   VehconnectDete;             //车辆连接检测

    quint8   GuntempDete;                //充电枪温度检测

    quint8   ElecLockFaultDete;          //电子锁故障检测

    quint8   InsulationModuleProtocol;   //绝缘模块通讯规约

    quint8   ChargingModuleProtocol;     //充电模块通讯规约

    quint8   ElecMeterProtocol;          //电表通讯规约

    quint16  FanDelay;                   //风扇延迟

 };

//桩基本数据
struct Piledate
 {
    quint8 Pilenum[16];           //充电桩编码
    quint8 Charger_password[6];   //充电员密码
    quint8 Admin_password[8];     //管理员密码
 };

class systemconfig : public QWidget
{
    Q_OBJECT


signals:
    void rx_key(quint16 key_val);
    void tx_par(struct Parameter*s);
    void tx_mpar(struct MonitoredParameter*s);

public:
    explicit systemconfig(QWidget *parent = 0);
    ~systemconfig();


private slots:


    void on_set1_cancel_clicked();

    void on_Config_OK_clicked();

    void on_clearrecords_clicked();




    void on_Monitored_OK_clicked();


    void on_Monitored_cancel_clicked();

    void on_Piledata_cancel_clicked();

public:
    struct Parameter Par; //系统参数

    struct MonitoredParameter MPar; //监控参数

    struct Piledate  P_data;//桩基本数据

private:

    //键盘
    void setkeymap_num_display(quint16 x, quint16 y, quint16 w, quint16 h);
    void setkeymap_num_hide();

private:
    Ui::systemconfig *ui;



};

#endif // SYSTEMCONFIG_H
