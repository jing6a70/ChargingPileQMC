#include "mainwindow.h"
#include <qtmaterialraisedbutton.h>
#include <QLineEdit>
#include <QMap>

static const QString widget_qss = "\
                            QWidget {\
                                background-color: rgb(18, 130, 240); \
                                color: rgb(255,0,0);               \
                            }                                      \
                            ";

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    this->widget_map = new QMap<MCQ_MI::MC_FORM, QWidget*>;
    QWidget *widget = new QWidget;
    QHBoxLayout *layout = new QHBoxLayout;
    this->stack = new QStackedLayout;
    widget->setStyleSheet(widget_qss);

    this->widget_map->insert(MCQ_MI::MP_STANDBY_FORM, new AppBarSettingsEditor);
    this->widget_map->insert(MCQ_MI::MP_CGMODE_FORM,  new App_CgMode);
    this->widget_map->insert(MCQ_MI::MP_PW_MODE_FORM, new App_Password);
    this->widget_map->insert(MCQ_MI::MP_SET_FORM,     new systemconfig);

    widget->setLayout(layout);
    layout->addLayout(stack);
    setCentralWidget(widget);

    //widget->setWindowFlags(Qt::Window);
    //widget->showFullScreen();

    widget->update();
    for(QMap<MCQ_MI::MC_FORM, QWidget*>::iterator it = widget_map->begin(); it != widget_map->end(); it++)
    {
        stack->addWidget(it.value());
        QObject::connect(it.value(), SIGNAL(rx_key(quint16)), this, SLOT(rx_key(quint16)));
    }

    this->eh(MCQ_MI::MP_STANDBY_FORM);
}

void MainWindow::eh(qint16 page_index)
{
    this->page_index_cur = page_index;
    stack->setCurrentIndex(page_index);
}

void MainWindow::eh_back()
{
    bool eh_ok;
    eh_ok = false;
    quint8 PNext;
    switch(this->page_index_cur)
    {
        case MCQ_MI::MP_CGMODE_FORM:  { PNext = MCQ_MI::MP_STANDBY_FORM; eh_ok = true; break; }
        case MCQ_MI::MP_PW_MODE_FORM: { PNext = MCQ_MI::MP_CGMODE_FORM; eh_ok = true;  break; }
        case MCQ_MI::MP_SET_FORM:     { PNext = MCQ_MI::MP_STANDBY_FORM; eh_ok = true; break; }
        default: break;
    }

    if(eh_ok = true)
    {
        this->page_index_cur = PNext;
        this->stack->setCurrentIndex(this->page_index_cur);
    }
}

MainWindow::~MainWindow()
{

}

void MainWindow::mp_set_select_gun(quint8 gun_num)
{
    if(gun_num < MC_MP::MC_CM_SEL_GUN_NULL)
    {
        this->sel_gun = gun_num;
        this->eh(MC_MP::MP_CGMODE_FORM);
    }
}

void MainWindow::mp_set_pw_mode()
{
    this->eh(MC_MP::MP_PW_MODE_FORM);
}

void MainWindow::mp_setting()
{
    this->eh(MC_MP::MP_SET_FORM);
}

void MainWindow::rx_key(quint16 key_val)
{
    switch(key_val)
    {
        case MC_MP::MCKEY_GUN_A:   this->mp_set_select_gun(MC_MP::MC_CM_SEL_GUN_A); break;
        case MC_MP::MCKEY_GUN_B:   this->mp_set_select_gun(MC_MP::MC_CM_SEL_GUN_B); break;
        case MC_MP::MCKEY_SETTING: this->mp_setting(); break;
        case MC_MP::MCKEY_PW_MODE: this->mp_set_pw_mode(); break;

        // Back
        case MC_MP::MCKEY_BACK:  this->eh_back(); break;
        default: break;
    }
}


void MainWindow::paintEvent(QPaintEvent *e)
{
  QStyleOption opt;
  opt.init(this);
  QPainter p(this);
  style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
  QWidget::paintEvent(e);
}

