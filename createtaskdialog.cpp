#include "createtaskdialog.h"
#include "ui_createtaskdialog.h"
#include <QSqlQuery>
#include <QMessageBox>
#include <QSqlError>

int CreateTaskDialog::department() const
{
    return _department;
}

void CreateTaskDialog::setDepartment(int department)
{
    _department = department;
}

void CreateTaskDialog::saveTask()
{
    QSqlQuery query;
    query.prepare("INSERT INTO task (name, userID, date_start, date_end, description)\n"
                  "VALUE (:name, :userID, :dateStart, :dateEnd, :description)");
    query.bindValue(":name", ui->name->text());
    query.bindValue(":dateStart", ui->dateStart->date());
    query.bindValue(":dateEnd", ui->dateEnd->date());
    query.bindValue(":description", ui->description->toPlainText());
    query.bindValue(":userID", _users->index(ui->userID->currentIndex(), 0).data());
    if(query.exec()) {
        accept();
    } else {
        QMessageBox::warning(this, "Ошибка сохраниения задания", QString("При сохранении задания произошла ошибка: %1")
                             .arg(query.lastError().text()));
    }
}

void CreateTaskDialog::setQuery()
{
    if(department() != -1) {
        _users->setQuery(QString("SELECT userID, CONCAT_WS(' ', firstName, lastName) as name\n"
                         "FROM user\n"
                         "NATURAL JOIN member_of_department\n"
                         "WHERE departmentID = %1").arg(department()));
    } else {
        _users->setQuery(QString("SELECT userID, CONCAT_WS(' ', firstName, lastName) as name\n"
                                 "FROM user"));
    }
}

CreateTaskDialog::CreateTaskDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CreateTaskDialog)
{
    ui->setupUi(this);

    _users = new QSqlQueryModel(this);
    setQuery();

    connect(ui->buttonBox, &QDialogButtonBox::accepted, this, &CreateTaskDialog::saveTask);

    ui->userID->setModel(_users);
    ui->userID->setModelColumn(1);

    ui->dateStart->setDate(QDate::currentDate());
    ui->dateEnd->setDate(QDate::currentDate());
}

CreateTaskDialog::~CreateTaskDialog()
{
    delete ui;
}
