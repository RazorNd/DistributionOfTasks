#ifndef DEPARTMENTFORM_H
#define DEPARTMENTFORM_H

#include <QWidget>
#include <QSqlTableModel>
#include <QSortFilterProxyModel>

namespace Ui {
class DepartmentForm;
}

class DepartmentForm : public QWidget
{
    Q_OBJECT

    QSqlTableModel *model;
    QSortFilterProxyModel *filterModel;
public:
    explicit DepartmentForm(QWidget *parent = 0);
    ~DepartmentForm();

private:
    Ui::DepartmentForm *ui;
};

#endif // DEPARTMENTFORM_H
