#include "calculator.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Calculator w;

    w.setWindowTitle("Calculator");
    w.resize(230, 300);
    w.show();

    return a.exec();
}
