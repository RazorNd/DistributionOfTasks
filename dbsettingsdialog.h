#ifndef DBSETTINGSDIALOG_H
#define DBSETTINGSDIALOG_H

#include <QDialog>

namespace Ui {
class DbSettingsDialog;
}

class DbSettingsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit DbSettingsDialog(QWidget *parent = 0);
    ~DbSettingsDialog();

    static bool connecting();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::DbSettingsDialog *ui;
};

#endif // DBSETTINGSDIALOG_H
