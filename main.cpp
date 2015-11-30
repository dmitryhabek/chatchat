#include "ui/addnewaccountview.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    AddNewAccountView w;
    w.show();

    return a.exec();
}
