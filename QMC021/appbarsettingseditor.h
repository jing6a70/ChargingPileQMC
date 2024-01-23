#ifndef APPBARSETTINGSEDITOR_H
#define APPBARSETTINGSEDITOR_H

#include <QWidget>
#include "mpdef.h"
#include "qtmaterialdrawer.h"
#include "ui_appbarsettingsform.h"

class QtMaterialAppBar;

class AppBarSettingsEditor : public QWidget
{
    Q_OBJECT

public:
    explicit AppBarSettingsEditor(QWidget *parent = 0);
    ~AppBarSettingsEditor();
signals:
    void rx_key(quint16 key_val);

protected slots:
    void setupForm();
    void updateWidget();
    void selectColor();

private slots:
    // slot : 界面按键触发
    void on_btn_GunA_clicked();
    void on_btn_GunB_clicked();
    void on_btn_setting_clicked();

private:
    Ui::AppBarSettingsForm *const ui;
    QtMaterialAppBar       *const m_appBar;
    QtMaterialDrawer       *const m_drawer;
};

#endif // APPBARSETTINGSEDITOR_H
