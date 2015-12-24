#ifndef CHANGECOMPLETIONDIALOG_H
#define CHANGECOMPLETIONDIALOG_H

#include <QDialog>

namespace Ui {
class ChangeCompletionDialog;
}

class ChangeCompletionDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ChangeCompletionDialog(QWidget *parent = 0);
    ~ChangeCompletionDialog();

    void setCompletion(int value);
    int completion() const;

private:
    Ui::ChangeCompletionDialog *ui;
};

#endif // CHANGECOMPLETIONDIALOG_H
