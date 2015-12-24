#include "userform.h"
#include "ui_userform.h"

UserForm::UserForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::UserForm)
{
    ui->setupUi(this);

    model = new QSqlQueryModel(this);
    deparment = new QSqlQueryModel(this);

    setQuery();
    setFilter();

    ui->tableView->setModel(filterModel);
}

UserForm::~UserForm()
{
    delete ui;
}

void UserForm::setQuery()
{
    model->setQuery("SELECT username, firstName, lastName, name as name_department, manager \n"
                    "FROM user \n"
                    "NATURAL LEFT JOIN member_of_department\n"
                    "NATURAL LEFT JOIN department\n");
    model->setHeaderData(0, Qt::Horizontal, "Логин");
    model->setHeaderData(1, Qt::Horizontal, "Имя");
    model->setHeaderData(2, Qt::Horizontal, "Фамилия");
    model->setHeaderData(3, Qt::Horizontal, "Департамент");
    model->setHeaderData(4, Qt::Horizontal, "Менеджер");
    deparment->setQuery("SELECT name FROM department");
}

void UserForm::setFilter()
{
    filterModel = new MultipleFilterProxyModel(this);
    filterModel->setSourceModel(model);

    ui->filterDepartment->setModel(deparment);
    ui->filterDepartment->setCurrentIndex(-1);

    ui->filterDepartment->setContextMenuPolicy(Qt::ActionsContextMenu);
    QAction *clearValue = new QAction("Очистить", this);
    ui->filterDepartment->addAction(clearValue);
    connect(clearValue, &QAction::triggered, [this](){
        ui->filterDepartment->setCurrentIndex(-1);
    });

    connect(ui->filterUsername, &QLineEdit::textChanged, createFilter(0));
    connect(ui->filterFirstName, &QLineEdit::textChanged, createFilter(1));
    connect(ui->filterLastName, &QLineEdit::textChanged, createFilter(2));
    connect(ui->filterDepartment, &QComboBox::currentTextChanged, createFilter(3));
}

std::function<void (const QString &)> UserForm::createFilter(int column) const
{
    return [this, column](const QString &filter) {
        filterModel->setFilterWildcard(column, filter);
    };
}
