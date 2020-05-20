#include "ttledit.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    TTLEdit w;
    w.show();
    return a.exec();
}
