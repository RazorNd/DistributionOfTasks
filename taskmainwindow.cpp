#include "taskmainwindow.h"
#include "ui_taskmainwindow.h"
#include "taskform.h"
#include "userform.h"
#include "usereditdialog.h"
#include "departmentform.h"
#include "dbsettingsdialog.h"
#include "createtaskdialog.h"

TaskMainWindow::TaskMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::TaskMainWindow)
{
    ui->setupUi(this);

    createMenu();
    TaskForm *taskForm = new TaskForm(this);
    ui->tabWidget->addTab(taskForm, "Задания");
    UserForm *userForm = new UserForm(this);
    ui->tabWidget->addTab(userForm, "Пользователи");
    DepartmentForm *departmentForm = new DepartmentForm(this);
    ui->tabWidget->addTab(departmentForm, "Отделы");
}

TaskMainWindow::~TaskMainWindow()
{
    delete ui;
}

QAction *TaskMainWindow::createAction(QString text, std::function<void ()> onTrigered)
{
    QAction *action = new QAction(text, this);
    connect(action, &QAction::triggered, onTrigered);
    return action;
}

void TaskMainWindow::createMenu()
{
    QMenu *fileMenu = ui->menuBar->addMenu("Файл");
    fileMenu->addActions(QList<QAction *>()
                         << createAction("Настройки подключения к БД", dialogExecuteFunction<DbSettingsDialog>())
                         << createAction("Выйти", std::bind(&TaskMainWindow::close, this)));
    QMenu *createMenu = ui->menuBar->addMenu("Создать");
    createMenu->addActions(QList<QAction *>()
                           << createAction("Создать пользователя", dialogExecuteFunction<UserEditDialog>())
                           << createAction("Создать задание", dialogExecuteFunction<CreateTaskDialog>()));
}

template <class DialogType>
std::function<void ()> TaskMainWindow::dialogExecuteFunction()
{
    return []() {
        DialogType dialog;
        dialog.exec();
    };
}
