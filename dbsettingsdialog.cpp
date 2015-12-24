#include "dbsettingsdialog.h"
#include "ui_dbsettingsdialog.h"
#include <QSettings>
#include <QSqlDatabase>
#include <QSqlError>
#include <QMessageBox>


DbSettingsDialog::DbSettingsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DbSettingsDialog)
{
    ui->setupUi(this);
    QSettings settings;
    settings.beginGroup("db");

    ui->sqlServerType->addItems(QSqlDatabase::drivers());
    ui->sqlServerType->setCurrentText(settings.value("type").toString());
    ui->dbHost->setText(settings.value("host", "localhost").toString());
    ui->dbName->setText(settings.value("name", "DistributionOfTasks").toString());
    ui->dbUsername->setText(settings.value("username").toString());
    ui->dbPassword->setText(settings.value("password").toString());
}

DbSettingsDialog::~DbSettingsDialog()
{
    delete ui;
}

bool DbSettingsDialog::connecting()
{
    QSettings settings;
    settings.beginGroup("db");

    QSqlDatabase db = QSqlDatabase::addDatabase(settings.value("type").toString());
    db.setHostName(settings.value("host").toString());
    db.setDatabaseName(settings.value("name").toString());
    db.setUserName(settings.value("username").toString());
    db.setPassword(settings.value("password").toString());

    db.open();
    return db.isOpen();
}

void DbSettingsDialog::on_buttonBox_accepted()
{
    QSettings settings;
    settings.beginGroup("db");
    settings.setValue("type", ui->sqlServerType->currentText());
    settings.setValue("host", ui->dbHost->text());
    settings.setValue("name", ui->dbName->text());
    settings.setValue("username", ui->dbUsername->text());
    settings.setValue("password", ui->dbPassword->text());
    if(connecting()) {
        accept();
    } else {
        QMessageBox::warning(this, "Ошибка подключения к БД",
                             QString("При подключении к Базе Данных произошла ошибка: %1")
                             .arg(QSqlDatabase::database(QSqlDatabase::defaultConnection, false)
                                  .lastError().text()));
    }
}
