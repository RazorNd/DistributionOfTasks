#include "changecompletiondialog.h"
#include "ui_changecompletiondialog.h"

ChangeCompletionDialog::ChangeCompletionDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ChangeCompletionDialog)
{
    ui->setupUi(this);
}

ChangeCompletionDialog::~ChangeCompletionDialog()
{
    delete ui;
}

void ChangeCompletionDialog::setCompletion(int value)
{
    ui->horizontalSlider->setValue(value);
}

int ChangeCompletionDialog::completion() const
{
    return ui->horizontalSlider->value();
}
