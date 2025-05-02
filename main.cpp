#include "mainwindow.h"
#include <QApplication>
#include <QLocale>
#include <QTranslator>
#include <QLibraryInfo>  // <-- Добавить эту строку

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    // Установка русской локали
    QLocale::setDefault(QLocale(QLocale::Russian, QLocale::Russia));

    // Загрузка стандартных переводов Qt
    QTranslator translator;
    if (translator.load("qt_ru", QLibraryInfo::path(QLibraryInfo::TranslationsPath))) {
        a.installTranslator(&translator);
    }

    MainWindow w;
    w.show();
    return a.exec();
}
