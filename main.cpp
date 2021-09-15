#include "tetrixui.h"
#include <QtWidgets>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    TetrixUI window;
    window.show();
    return app.exec();
}
