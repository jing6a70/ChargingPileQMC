#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QStackedLayout>
#include <QtWidgets/QListWidget>
#include <QPainter>

#include "appbarsettingseditor.h"
#include "app_cgmode.h"
#include "app_password.h"
#include "systemconfig.h"
#include <QMainWindow>
#include <QStack>

#include "mpdef.h"

#include "Keyboard/NumberKeyboard.h"
#include "Keyboard/Keyboard.h"


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void eh(qint16 page_index);
    void eh_back();

public slots:
    void rx_key(quint16 key_val);

protected:
    void paintEvent(QPaintEvent *);

private:
    void mp_set_select_gun(quint8 gun_num);
    void mp_set_pw_mode();
    void mp_setting();

private:
    QStackedLayout *stack;
    AppBarSettingsEditor *app_main;
    App_CgMode* cgmode;
    App_Password *pw_form;
    QWidget *keymap_num;
    QMap<MCQ_MI::MC_FORM, QWidget*> *widget_map;
private:
    QStack<MCQ_MI::MC_FORM> stack_page;
    quint8 page_index_cur;
    quint8 sel_gun;
};

#endif // MAINWINDOW_H
