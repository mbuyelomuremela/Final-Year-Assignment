#include <QApplication>

#include "listener.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Listener listener;
    listener.show();

    return a.exec();
}
