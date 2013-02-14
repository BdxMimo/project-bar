#include <QApplication>
#include "barwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    BARWindow b;
    b.show();
    
    return a.exec();
}
