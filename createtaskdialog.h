#ifndef CREATETASKDIALOG_H
#define CREATETASKDIALOG_H

#include <QDialog>
#include <QSqlQueryModel>

namespace Ui {
class CreateTaskDialog;
}

class CreateTaskDialog : public QDialog
{
    Q_OBJECT
    int _department = -1;
    QSqlQueryModel *_users;
public:
    explicit CreateTaskDialog(QWidget *parent = 0);
    ~CreateTaskDialog();

    int department() const;
    void setDepartment(int department);

public slots:
    void saveTask();

private:
    void setQuery();

    Ui::CreateTaskDialog *ui;
};

#endif // CREATETASKDIALOG_H
