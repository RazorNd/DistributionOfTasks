#include "departmentform.h"
#include "ui_departmentform.h"

DepartmentForm::DepartmentForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DepartmentForm)
{
    ui->setupUi(this);

    model = new QSqlTableModel(this);
    model->setTable("department");
    model->select();

    filterModel = new QSortFilterProxyModel(this);
    filterModel->setSourceModel(model);
    filterModel->setFilterKeyColumn(1);

    connect(ui->lineEdit, &QLineEdit::textChanged,
            filterModel, &QSortFilterProxyModel::setFilterWildcard);

    ui->tableView->setModel(filterModel);
}

DepartmentForm::~DepartmentForm()
{
    delete ui;
}
