#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
//    Способ попроще но вызывает желтый warning
//    QTranslator translate;

//    translate.load("qt_" + QLocale::system().name(),
//                QLibraryInfo::path(QLibraryInfo::TranslationsPath));
//    a.installTranslator(&translate);
//    перевод на русский
    QTranslator qtTranslator;
        if (qtTranslator.load(QLocale::system(),
                    "qt", "_",
                    QLibraryInfo::path(QLibraryInfo::TranslationsPath)))
        {
            a.installTranslator(&qtTranslator);
        }

        QTranslator qtBaseTranslator;
        if (qtBaseTranslator.load("qtbase_" + QLocale::system().name(),
                    QLibraryInfo::path(QLibraryInfo::TranslationsPath)))
        {
            a.installTranslator(&qtBaseTranslator);
        }

    return a.exec();
}
