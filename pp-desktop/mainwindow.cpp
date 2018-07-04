#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "errorhandling.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QString versionString =
            tr("version: ")
            + QString::fromStdString(PhotoPres::Core::version());
    ui->version->setText(versionString);
}   // end constructor

MainWindow::~MainWindow()
{
    delete ui;
}   // end destructor

// TODO Temporary demo code - delete
void MainWindow::on_errorButton_clicked()
{
    PPD_TOP_LEVEL_TRY
    {
        PP_RAISE_ERROR("Test error");
        // throw std::runtime_error("test");
    }
    PPD_TOP_LEVEL_CATCH(tr("Test Test"))
}   // end on_errorButton_clicked method
