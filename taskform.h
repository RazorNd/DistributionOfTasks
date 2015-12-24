#ifndef TASKFORM_H
#define TASKFORM_H

#include <QSortFilterProxyModel>
#include <QDataWidgetMapper>
#include <QSqlQueryModel>
#include <QWidget>
#include <QAction>

namespace Ui {
class TaskForm;
}

class TaskForm : public QWidget
{
    Q_OBJECT    
    QSqlQueryModel *model;
    QSortFilterProxyModel *filterModel;
    int _userID = -1;
    QAction *_change;
    QDataWidgetMapper *mapper;
public:
    explicit TaskForm(QWidget *parent = 0);
    ~TaskForm();


    int userID() const;

public slots:
    void setUserID(int id);
    void update();

protected slots:
    void changeSelected();

private:
    void createQuery();
    void addMapping();

    Ui::TaskForm *ui;

    // QWidget interface
protected:
    virtual void contextMenuEvent(QContextMenuEvent *) override;
};

#endif // TASKFORM_H
