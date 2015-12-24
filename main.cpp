#include "taskmainwindow.h"
#include "dbsettingsdialog.h"
#include <QApplication>
#include <QSettings>

#include "createtaskdialog.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QApplication::setOrganizationName("RazorNd_ltd");
    QApplication::setOrganizationDomain("razornd.soft.ru");
    QApplication::setApplicationName("DistributionOfTask");

    if(!DbSettingsDialog::connecting()) {
        DbSettingsDialog settingsDialog;
        if(settingsDialog.exec() != QDialog::Accepted) {
            return 10;
        }
    }

    TaskMainWindow w;
    w.show();

    return a.exec();
}
