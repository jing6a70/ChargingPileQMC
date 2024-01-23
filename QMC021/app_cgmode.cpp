#include "app_cgmode.h"
#include "ui_app_cgmode.h"


static const QString cgmode_qss = "\
                            \
                                background-color: rgb(90, 168, 245); \
                                color: rgb(255,0,0);               \
                                border-radius:10px;\
                            ";

App_CgMode::App_CgMode(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::App_CgMode)
{
    ui->setupUi(this);
    this->setStyleSheet(cgmode_qss);
}

App_CgMode::~App_CgMode()
{
    delete ui;
}

void App_CgMode::on_btn_cg_mode_back_clicked()
{
    emit this->rx_key(MC_MP::MCKEY_BACK);
}

void App_CgMode::on_btn_cg_mode_pw_clicked()
{
    emit this->rx_key(MC_MP::MCKEY_PW_MODE);
}
