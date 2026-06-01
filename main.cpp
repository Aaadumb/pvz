#include "StartGameWidget.h"

#include <QtWidgets/QApplication>
#include <ctime>
#include <cstdlib>
int main(int argc, char *argv[])
{
    srand(time(0));
    QApplication app(argc, argv);
    StartGameWidget window;
    window.show();
    return app.exec();
}
