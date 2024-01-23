#ifndef APP_CGMODE_H
#define APP_CGMODE_H

#include <QWidget>
#include "mpdef.h"

namespace Ui {
class App_CgMode;
}

class App_CgMode : public QWidget
{
    Q_OBJECT

public:
    explicit App_CgMode(QWidget *parent = 0);
    ~App_CgMode();

signals:
    void rx_key(quint16 key_val);

private slots:
    void on_btn_cg_mode_back_clicked();

    void on_btn_cg_mode_pw_clicked();

private:
    Ui::App_CgMode *ui;
};

#endif // APP_CGMODE_H
