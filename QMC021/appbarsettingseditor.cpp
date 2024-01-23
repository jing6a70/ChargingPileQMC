#include "appbarsettingseditor.h"
#include <QtWidgets/QVBoxLayout>
#include <QColorDialog>
#include <QPushButton>
#include <QLabel>

#include <qtmaterialappbar.h>
#include <qtmaterialiconbutton.h>
#include <lib/qtmaterialtheme.h>


static const QString appBar_qss = "\
                            \
                                background-color: rgb(90, 168, 245); \
                                color: rgb(255,0,0);               \
                                border-radius:10px;\
                            ";

static const QString appBar_button_qss = "\
                        \
                            background-color: rgb(90, 168, 245); \
                            color: rgb(255,0,0);                 \
                            border-radius:10px;                  \
                            min-height:50px;                     \
                        ";

static const QString widget_qss = "\
                            QWidget {\
                                background-color: rgb(18, 130, 240); \
                                color: rgb(255,0,0);               \
                            }                                      \
                            ";

AppBarSettingsEditor::AppBarSettingsEditor(QWidget *parent)
    : QWidget(parent),
      ui(new Ui::AppBarSettingsForm),
      m_appBar(new QtMaterialAppBar), m_drawer(new QtMaterialDrawer)
{

    ui->setupUi(this);


    QPushButton *ThemeSetting = new QPushButton("ThemeSetting");
    QPushButton *btn_Exit     = new QPushButton("Exit");
    QPushButton *btn_Setting  = new QPushButton("Setting");
    /*
        m_drawer setting
    */
    m_drawer->setParent(this);
    m_drawer->setClickOutsideToClose(true);
    m_drawer->setOverlayMode(true);

    QVBoxLayout *drawerLayout = new QVBoxLayout;
    m_drawer->setDrawerLayout(drawerLayout);

    QVector<QString> labels = {
        " About <MCQ>:",
        "\tsf_ver: MCQ021",
        "\thd_ver: FM6070WE",
        "\tsf_dver: 0.1.2",
        "\tctl_ver: CM017"
    };

    QVector<QString>::iterator it;
    for (it = labels.begin(); it != labels.end(); ++it)
    {
        QLabel *label = new QLabel(*it);
        label->setMinimumHeight(30);
        label->setFont(QFont("Roboto", 10, QFont::Medium));
        drawerLayout->addWidget(label);
    }

    drawerLayout->addStretch(3);
    m_drawer->setContentsMargins(10, 0, 0, 0);

    drawerLayout->addWidget(btn_Setting);
    drawerLayout->addWidget(ThemeSetting);
    drawerLayout->addWidget(btn_Exit);

    QLabel *label = new QLabel("Home");
    label->setAttribute(Qt::WA_TranslucentBackground);
    label->setForegroundRole(QPalette::Foreground);
    label->setContentsMargins(6, 0, 0, 0);

    QPalette palette = label->palette();
    palette.setColor(label->foregroundRole(), Qt::white);
    label->setPalette(palette);

    label->setFont(QFont("Roboto", 18, QFont::Normal));

    QtMaterialIconButton *button = new QtMaterialIconButton(QtMaterialTheme::icon("navigation", "menu"));
    button->setIconSize(QSize(60, 60));

    btn_Setting->setStyleSheet(appBar_button_qss);
    ThemeSetting->setStyleSheet(appBar_button_qss);
    btn_Exit->setStyleSheet(appBar_button_qss);

    m_appBar->appBarLayout()->addWidget(button);
    m_appBar->appBarLayout()->addWidget(label);
    m_appBar->appBarLayout()->addStretch(1);

    button->setColor(Qt::white);
    button->setFixedWidth(42);
    QVBoxLayout *vbox = new QVBoxLayout;
    this->setLayout(vbox);


    vbox->addWidget(m_appBar, 1);
    vbox->addWidget(ui->verticalLayoutWidget, 20);

    this->setStyleSheet(appBar_qss);
    m_drawer->setStyleSheet(widget_qss);
    m_appBar->setBackgroundColor(QColor("#1282f0"));
    connect(button,       SIGNAL(pressed()), m_drawer, SLOT(openDrawer()));
    connect(ThemeSetting, SIGNAL(pressed()), this, SLOT(selectColor()));
    connect(btn_Setting,  SIGNAL(pressed()), this, SLOT(on_btn_setting_clicked()));
    this->updateWidget();

}

AppBarSettingsEditor::~AppBarSettingsEditor()
{
    delete ui;
}

void AppBarSettingsEditor::setupForm()
{
    // ui->useThemeColorsCheckBox->setChecked(m_appBar->useThemeColors());
}

void AppBarSettingsEditor::updateWidget()
{
    // m_appBar->setUseThemeColors(ui->useThemeColorsCheckBox->isChecked());
}

void AppBarSettingsEditor::selectColor()
{
    QColorDialog dialog;
    if (dialog.exec())
    {
        QColor color = dialog.selectedColor();
        QString senderName = sender()->objectName();
        m_appBar->setBackgroundColor(color);
    }
    setupForm();
}


void AppBarSettingsEditor::on_btn_GunA_clicked()
{
    emit this->rx_key(0);
}

void AppBarSettingsEditor::on_btn_GunB_clicked()
{
    emit this->rx_key(1);
}

void AppBarSettingsEditor::on_btn_setting_clicked()
{
     emit this->rx_key(7);
}
