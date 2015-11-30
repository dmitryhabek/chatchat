#include "rootwindow.h"
#include "ui_rootwindow.h"

RootWindow::RootWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::RootWindow)
{
    ui->setupUi(this);
}

RootWindow::~RootWindow()
{
    delete ui;
}
