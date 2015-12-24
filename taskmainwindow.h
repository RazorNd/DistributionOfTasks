#ifndef TASKMAINWINDOW_H
#define TASKMAINWINDOW_H

#include <QMainWindow>
#include <functional>

namespace Ui {
class TaskMainWindow;
}

class TaskMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit TaskMainWindow(QWidget *parent = 0);
    ~TaskMainWindow();

private:
    QAction *createAction(QString text, std::function<void ()> onTrigered);
    void createMenu();

    template <class DialogType>
    static std::function<void ()> dialogExecuteFunction();

    Ui::TaskMainWindow *ui;
};

#endif // TASKMAINWINDOW_H
