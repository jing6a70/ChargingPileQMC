#ifndef APP_PASSWORD_H
#define APP_PASSWORD_H

#include <QWidget>
#include <QLineEdit>

namespace Ui {
    class App_Password;
}


class App_Password : public QWidget
{
    Q_OBJECT

public:
    explicit App_Password(QWidget *parent = 0);
    ~App_Password();

signals:
    void rx_key(quint16 key_val);

public slots:
    bool eventFilter(QObject *,QEvent *) override;
    void keyPressEvent(QKeyEvent * event);

private slots:
    void on_btn_Cancel_clicked();

private:
    void keymap_num_display(quint16 x, quint16 y, quint16 w, quint16 h);
    void keymap_num_hide();
private:
    Ui::App_Password *ui;
    QWidget *keymap_num = nullptr;
    QLineEdit* lineEdit;
};

#endif // APP_PASSWORD_H
