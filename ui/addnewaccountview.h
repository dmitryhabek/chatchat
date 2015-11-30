#ifndef ADDNEWACCOUNTVIEW_H
#define ADDNEWACCOUNTVIEW_H

#include <QDialog>

namespace Ui {
class AddNewAccountView;
}

class AddNewAccountView : public QDialog
{
    Q_OBJECT

public:
    explicit AddNewAccountView(QWidget *parent = 0);
    ~AddNewAccountView();

private:
    Ui::AddNewAccountView *ui;
};

#endif // ADDNEWACCOUNTVIEW_H
