#include "mainwindow.h"
#include <QApplication>
#include <QFontDatabase>

#include <QLineEdit>

#include "Keyboard/NumberKeyboard.h"
#include "Keyboard/Keyboard.h"



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Q_INIT_RESOURCE(resources);

    MainWindow w;
    w.show();

    int index = QFontDatabase::addApplicationFont("/Fonts/msyh.ttf");

    if(index != -1)

    {
       QStringList fontList(QFontDatabase::applicationFontFamilies(index));
       if(fontList.count() > 0)
       {
           QFont font_zh(fontList.at(0));
           font_zh.setBold(false);
           a.setFont(font_zh);
       }
    }

    return a.exec();
}
