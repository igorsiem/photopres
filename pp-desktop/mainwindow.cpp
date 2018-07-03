#include "mainwindow.h"
#include "ui_mainwindow.h"

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
