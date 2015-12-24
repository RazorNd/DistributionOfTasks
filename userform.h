#ifndef USERFORM_H
#define USERFORM_H

#include "multiplefilterproxymodel.h"
#include <QWidget>
#include <QSqlQueryModel>
#include <functional>

namespace Ui {
class UserForm;
}

class UserForm : public QWidget
{
    Q_OBJECT
    QSqlQueryModel *model;
    QSqlQueryModel *deparment;
    MultipleFilterProxyModel *filterModel;
public:
    explicit UserForm(QWidget *parent = 0);
    ~UserForm();


private:
    void setQuery();
    void setFilter();
    std::function<void (const QString&)> createFilter(int column) const;
    Ui::UserForm *ui;
};

#endif // USERFORM_H
