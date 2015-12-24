#include "taskform.h"
#include "changecompletiondialog.h"
#include "ui_taskform.h"
#include <QContextMenuEvent>
#include <QMenu>
#include <QDebug>


TaskForm::TaskForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TaskForm)
{
    ui->setupUi(this);

    model = new QSqlQueryModel(this);
    createQuery();

    filterModel = new QSortFilterProxyModel(this);
    filterModel->setSourceModel(model);

    addMapping();
    connect(ui->nameFilter, &QLineEdit::textChanged, filterModel,
            &QSortFilterProxyModel::setFilterWildcard);

    _change = new QAction("Изменить выделенное", this);
    connect(_change, &QAction::triggered, this, &TaskForm::changeSelected);

    ui->taskListView->setModel(filterModel);
}

TaskForm::~TaskForm()
{
    delete ui;
}

int TaskForm::userID() const
{
    return _userID;
}

void TaskForm::setUserID(int id)
{
    _userID = id;
    createQuery();
}

void TaskForm::update()
{
    createQuery();
}

void TaskForm::changeSelected()
{
    ChangeCompletionDialog dialog;
    dialog.setCompletion(ui->taskCompletion->value());
    if(dialog.exec() == QDialog::Accepted) {
        ui->taskCompletion->setValue(dialog.completion());
    }
}

void TaskForm::createQuery()
{
    QString query = "select task.name, task.date_start, task.date_end, task.completion, task.description, concat_ws(' ', user.firstName, user.lastName) as user\n"
                    "from task\n"
                    "natural join user;\n";
    if(_userID != -1) {
        query += QString("where task.userID = %1").arg(_userID);
    }
    model->setQuery(query);
}

void TaskForm::addMapping()
{
    mapper = new QDataWidgetMapper(this);

    mapper->setModel(filterModel);
    mapper->addMapping(ui->taskName, 0);
    mapper->addMapping(ui->taskDateStart, 1);
    mapper->addMapping(ui->taskDateEnd, 2);
    mapper->addMapping(ui->taskCompletion, 3, "value");

    mapper->addMapping(ui->taskDescription, 4);
    mapper->addMapping(ui->taskUser, 5);

    connect(ui->taskListView, &QListView::activated,
            mapper, &QDataWidgetMapper::setCurrentModelIndex);

    connect(ui->prevTask, &QPushButton::clicked,
            mapper, &QDataWidgetMapper::toPrevious);
    connect(ui->nextTask, &QPushButton::clicked,
            mapper, &QDataWidgetMapper::toNext);
}


void TaskForm::contextMenuEvent(QContextMenuEvent *event)
{
    if(mapper->currentIndex() != -1) {
        QMenu menu(this);
        menu.addAction(_change);
        menu.exec(event->globalPos());
        event->accept();
    }
}
