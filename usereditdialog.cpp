#include "usereditdialog.h"
#include "ui_usereditdialog.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>

int UserEditDialog::userID() const
{
    return _userID;
}

void UserEditDialog::setUserID(int userID)
{
    if(userID == -1 || !loadRecord(userID)) {
        _userID = -1;
        ui->changePassword->hide();
        ui->passwordWidget->show();
        ui->username->setReadOnly(false);
    } else {
        ui->changePassword->show();
        ui->passwordWidget->hide();
        ui->username->setReadOnly(true);
    }
}

void UserEditDialog::setIsNewRecord()
{
    setUserID(-1);
}

bool UserEditDialog::isNewRecord() const
{
    return userID() == -1;
}

bool UserEditDialog::saveRecord()
{
    return isNewRecord() ? insertRecord() : updateRecord();
}

bool UserEditDialog::insertRecord()
{
    QSqlQuery query;
    query.prepare("INSERT INTO user(username, firstName, lastName, password)\n"
                  "VALUE(:username, :firstName, :lastName, :password)");
    if(!checkPassword()) {
        QMessageBox::warning(this, "Не корректный пароль", "Вы ввели не корректный пароль. Убедитесь, "
                                                           "что вводите одинаковые пароли длинной больше 3 символов");
        return false;
    }
    query.bindValue(":username", ui->username->text());
    query.bindValue(":firstName", ui->firstName->text());
    query.bindValue(":lastName", ui->lastName->text());
    query.bindValue(":password", ui->password->text());
    return query.exec();
}

bool UserEditDialog::updateRecord()
{
    QSqlQuery query;
    if(ui->password->text().size()) {
        if(!checkPassword()) {
            return false;
        }
        query.prepare("UPDATE user SET username = :username, firstName = :firstName, lastName = :lastName, password = :password\n"
                      "WHERE userID = :userID");
        query.bindValue("password", ui->password->text());
    } else {
        query.prepare("UPDATE user SET username = :username, firstName = :firstName, lastName = :lastName\n"
                      "WHERE userID = :userID");
    }
    query.bindValue(":firstName", ui->firstName->text());
    query.bindValue(":lastName", ui->lastName->text());
    query.bindValue(":userID", userID());
    return query.exec();
}

bool UserEditDialog::loadRecord(int userID)
{
    QSqlQuery query;
    query.prepare("SELECT username, firstName, lastName\n"
                  "FROM user\n"
                  "WHERE userID = :userID");
    query.bindValue(":userID", userID);

    if(!query.exec() || query.size() != 1 || !query.next()) {
        return false;
    }

    ui->username->setText(query.value("username").toString());
    ui->firstName->setText(query.value("firstName").toString());
    ui->lastName->setText(query.value("lastName").toString());
    return true;
}

bool UserEditDialog::checkPassword()
{
    return ui->password->text() == ui->password_2->text()
            && ui->password->text().size() > 3;
}

void UserEditDialog::clearAllField()
{
    ui->username->clear();
    ui->firstName->clear();
    ui->lastName->clear();
    ui->password->clear();
    ui->password_2->clear();
}

UserEditDialog::UserEditDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::UserEditDialog)
{
    ui->setupUi(this);
    ui->changePassword->hide();
}

UserEditDialog::~UserEditDialog()
{
    delete ui;
}

void UserEditDialog::on_buttonBox_accepted()
{
    if(!saveRecord()) {
        QSqlError error = QSqlDatabase::database().lastError();
        QMessageBox::warning(this, "Пользователь не сохранен", QString("При сохранение пользователя возникла ошибка: %1")
                             .arg(error.text()));
        return;
    }
    accept();
}
