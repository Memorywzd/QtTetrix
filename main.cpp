#include "tetrixui.h"
#include <QtWidgets>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    TetrixUI window;
    window.show();
    return app.exec();
}
