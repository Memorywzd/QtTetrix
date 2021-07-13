#include "tetrixui.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    TetrixUI window;
    window.show();
    return app.exec();
}
