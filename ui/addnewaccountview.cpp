#include "addnewaccountview.h"
#include "ui_addnewaccountview.h"

AddNewAccountView::AddNewAccountView(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddNewAccountView)
{
    ui->setupUi(this);
    ui->Passwordtext->setEchoMode(QLineEdit::Password);
}

AddNewAccountView::~AddNewAccountView()
{
    delete ui;
}
