#include "systemconfig.h"
#include "ui_systemconfig.h"
#include <QDebug>

#include "mpdef.h"

static const QString appsetting_qss = "\
                            \
                                background-color: rgb(90, 168, 245); \
                                color: rgb(255,0,0);               \
                                border-radius:10px;\
                            ";

systemconfig::systemconfig(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::systemconfig)
{
    ui->setupUi(this);

    this->setStyleSheet(appsetting_qss);
//进入参数界面先根据保存的参数去显示对应文本
//(后面建议把每个界面进去的数据加载单独写函数，然后调用。)
/******************
  系统参数界面加载数据
*****************/
    ui->gunnum->setCurrentIndex(this->Par.Gunnum);//充电枪
    ui->Pt_agreement->setCurrentIndex(this->Par.Pt_agreement);//平台协议
    ui->cg_mode->setCurrentIndex(this->Par.cg_mode);//充电模式
    ui->Auxiliarypower->setCurrentIndex(this->Par.Auxiliarypower);//辅助电源
    ui->Singlevehmode->setCurrentIndex(this->Par.Singlevehmode);//单车充电
    ui->Piletype->setCurrentIndex(this->Par.Piletype );//电桩类型

/******************
  监控参数界面加载数据
*****************/
   ui->Cgtype->setCurrentIndex(this->MPar.Cgtype );//充电机类型


   ui->InsulationDete->setCurrentIndex(this->MPar.InsulationDete);//绝缘检测
   ui->VehconnectDete->setCurrentIndex(this->MPar.VehconnectDete);//充电枪连接检测
   ui->GuntempDete->setCurrentIndex(this->MPar.GuntempDete);//充电枪温度检测
   ui->ElecLockFaultDete->setCurrentIndex(this->MPar.ElecLockFaultDete);//电子锁故障检测
   ui->InsulationModuleProtocol->setCurrentIndex(this->MPar.InsulationModuleProtocol);//绝缘模块通讯规约
   ui->ChargingModuleProtocol->setCurrentIndex(this->MPar.ChargingModuleProtocol);//充电模块通讯规约
   ui->ElecMeterProtocol->setCurrentIndex(this->MPar.ElecMeterProtocol  );//电表通讯规约




/******************
  桩基本数据界面加载数据
*****************/


/******************
  费率界面加载数据
*****************/


}

systemconfig::~systemconfig()
{
    delete ui;
}

/*********************************************************
 系统参数___界面数据设置
 ********************************************************/
//返回主界面
void systemconfig::on_set1_cancel_clicked()
{

    emit this->rx_key(MC_MP::MCKEY_BACK);
}



/*********************************************************
 监控参数___界面数据设置
 ********************************************************/

//返回主界面
void systemconfig::on_Monitored_cancel_clicked()
{

    emit this->rx_key(MC_MP::MCKEY_BACK);
}



/*********************************************************
 桩基本数据___界面数据设置
 ********************************************************/
//清除记录——预留
void systemconfig::on_clearrecords_clicked()
{

}

//返回主界面
void systemconfig::on_Piledata_cancel_clicked()
{
    emit this->rx_key(MC_MP::MCKEY_BACK);
}



/****************************************************
 各设置界面—— “确定” 按键集合
 ****************************************************/
/*
 系统参数——确定
 */
void systemconfig::on_Config_OK_clicked()
{

    this->Par.Gunnum         =  ui->gunnum->currentIndex();//充电枪数量
    this->Par.Pt_agreement   =  ui->Pt_agreement->currentIndex();//平台协议
    this->Par.cg_mode        =  ui->cg_mode->currentIndex();//充电模式
    this->Par.Auxiliarypower =  ui->Auxiliarypower->currentIndex();//辅助电源
    this->Par.Singlevehmode  =  ui->Singlevehmode->currentIndex();//单车充电
    this->Par.Piletype       =  ui->Piletype->currentIndex();//电桩类型

    emit this->tx_par(&this->Par);
}

/*
 监控参数——确定
*/
void systemconfig::on_Monitored_OK_clicked()
{
    this->MPar.Cgtype                                 =  ui->Cgtype->currentIndex();//充电机类型


    this->MPar.InsulationDete                         =  ui->InsulationDete->currentIndex();//绝缘检测
    this->MPar.VehconnectDete                         =  ui->VehconnectDete->currentIndex();//充电枪连接检测
    this->MPar.GuntempDete                            =  ui->GuntempDete->currentIndex();//充电枪温度检测
    this->MPar.ElecLockFaultDete                      =  ui->ElecLockFaultDete->currentIndex();//电子锁故障检测
    this->MPar.InsulationModuleProtocol               =  ui->InsulationModuleProtocol->currentIndex();//绝缘模块通讯规约
    this->MPar.ChargingModuleProtocol                 =  ui->ChargingModuleProtocol->currentIndex();//充电模块通讯规约
    this->MPar.ElecMeterProtocol                      =  ui->ElecMeterProtocol->currentIndex();//电表通讯规约


    emit this->tx_mpar(&this->MPar);
}



