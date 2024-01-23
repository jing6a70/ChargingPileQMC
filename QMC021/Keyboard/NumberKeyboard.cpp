﻿
#include "NumberKeyboard.h"
#include "KeyButton.h"
#include <QVBoxLayout>


using namespace AeaQt;

typedef QList<KeyButton::Mode> Modes;
typedef QList<Modes> ModesList;

NumberKeyboard::NumberKeyboard(QWidget *parent) : AbstractKeyboard(parent)
{
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setSizeConstraint(QLayout::SetNoConstraint);
    layout->setSpacing(0);
    layout->setMargin(0);


    auto createLayout = [&](ModesList list){
        QHBoxLayout *h = new QHBoxLayout;
        h->setSizeConstraint(QLayout::SetNoConstraint);

        foreach (Modes iter, list) {
            KeyButton *button = createButton(iter);
            h->addWidget(button);
        }

        layout->addLayout(h);
    };

    const QList<Modes> modeListBar1 = {
            {{Qt::Key_1, "1"}},
            {{Qt::Key_2, "2"}},
            {{Qt::Key_3, "3"}},
            {{Qt::Key_Backspace, "", QString("退格")}},
    };

    const QList<Modes> modeListBar2 = {
            {{Qt::Key_4, "4"}},
            {{Qt::Key_5, "5"}},
            {{Qt::Key_6, "6"}},
            {{Qt::Key_Escape, "", QString("取消")}},
    };

    const QList<Modes> modeListBar3 = {
            {{Qt::Key_7, "7"}},
            {{Qt::Key_8, "8"}},
            {{Qt::Key_9, "9"}},
            {{Qt::Key_Minus, ","}},
    };

    const QList<Modes> modeListBar4 = {
            {{Qt::Key_unknown, "."}},
            {{Qt::Key_0, "0"}},
            {{Qt::Key_Space, " ", QString("|___|")}},
            {{Qt::Key_Enter, ":", QString("确认")}},
    };

    createLayout(modeListBar1);
    createLayout(modeListBar2);
    createLayout(modeListBar3);
    createLayout(modeListBar4);

    this->setLayout(layout);
}

KeyButton *NumberKeyboard::createButton(QList<KeyButton::Mode> modes)
{
    KeyButton *button = new KeyButton(modes, this);
    button->onReponse(this, SLOT(onButtonPressed(const int&, const QString&)));
    button->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    return button;
}

void NumberKeyboard::onButtonPressed(const int &code, const QString &text)
{
    onKeyPressed(code, text);
}
