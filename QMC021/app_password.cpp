#include "app_password.h"
#include "ui_app_password.h"
#include <QLineEdit>

#include "Keyboard/NumberKeyboard.h"
#include "Keyboard/Keyboard.h"

#include <QMouseEvent>
#include <QKeyEvent>

#include "mpdef.h"

static const QString passwd_qss = "\
                            \
                                background-color: rgb(90, 168, 245); \
                                color: rgb(255,0,0);               \
                                border-radius:10px;\
                            ";


static const QString qss = "                               \
                            QLineEdit {                    \
                                border-style: none;        \
                                padding: 3px;              \
                                border-radius: 5px;        \
                                border: 1px solid #dce5ec; \
                                font-size: 30px;           \
                            }                              \
                            ";


static const char* keymap_qss = "border:3px solid blue";
static const quint16 KEYMAP_DISPLAY_X = 0;
static const quint16 KEYMAP_DISPLAY_y = 220;
static const quint16 KEYMAP_DISPLAY_w = 500;
static const quint16 KEYMAP_DISPLAY_h = 350;


App_Password::App_Password(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::App_Password)
{
    ui->setupUi(this);
    this->setStyleSheet(passwd_qss);
    ui->lineEdit->installEventFilter(this);
    ui->lineEdit->setEchoMode(QLineEdit::Password);
}

App_Password::~App_Password()
{
    delete ui;
}

void App_Password::keymap_num_display(quint16 x, quint16 y, quint16 w, quint16 h)
{
    this->keymap_num = new QWidget(this->parentWidget());
    if(this->keymap_num != nullptr)
    {
        this->keymap_num -> move(x, y);
        this->keymap_num -> setFixedSize(w, h);
        this->keymap_num->setStyleSheet(QString::fromUtf8(keymap_qss));
        AeaQt::NumberKeyboard *keyboard = new AeaQt::NumberKeyboard;
        QVBoxLayout *vbox = new QVBoxLayout;
        vbox->addWidget(keyboard);

        this->keymap_num->setLayout(vbox);
        this->keymap_num->show();
    }
}

void App_Password::keymap_num_hide()
{
    if(ui->lineEdit->hasFocus())
        ui->lineEdit->clearFocus();

    if(this->keymap_num != nullptr)
    {
        delete this->keymap_num;
        this->keymap_num = nullptr;
    }
}

bool App_Password::eventFilter(QObject *obj, QEvent *event)
{
    if (obj == ui->lineEdit)
    {
        if (event->type()==QEvent::FocusIn)
        {
            this->keymap_num_display(0, 220, 500, 350);
        }
    }
    return QWidget::eventFilter(obj, event);
}

void App_Password::keyPressEvent(QKeyEvent * event)
{
    switch(event->key())
    {
        case Qt::Key_Return:
        case Qt::Key_Enter:
        {
            this->keymap_num_hide();
            break;
        }
        case Qt::Key_Escape:
        {
            ui->lineEdit->clear();
            this->keymap_num_hide();
            break;
        }
        default: break;
    }
}

void App_Password::on_btn_Cancel_clicked()
{
    if(this->keymap_num != nullptr)
    {
        this->keymap_num_hide();
    }
    emit this->rx_key(MC_MP::MCKEY_BACK);

}
