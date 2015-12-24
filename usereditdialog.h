#ifndef USEREDITDIALOG_H
#define USEREDITDIALOG_H

#include <QDialog>

namespace Ui {
class UserEditDialog;
}

class UserEditDialog : public QDialog
{
    Q_OBJECT    
    int _userID = -1;
public:
    explicit UserEditDialog(QWidget *parent = 0);
    ~UserEditDialog();



    int userID() const;
    void setUserID(int userID);
    void setIsNewRecord();
    bool isNewRecord() const;

    bool saveRecord();

protected:
    bool insertRecord();
    bool updateRecord();
    bool loadRecord(int userID);
    bool checkPassword();
    void clearAllField();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::UserEditDialog *ui;
};

#endif // USEREDITDIALOG_H
