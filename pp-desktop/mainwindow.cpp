#include <QFileDialog>

#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "errorhandling.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_settings("Igor Siemienowicz", "PhotoPres"),
    m_core(m_settings)
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

void MainWindow::on_openBtn_clicked()
{
    PPD_TOP_LEVEL_TRY
    {
        auto dir = QFileDialog::getExistingDirectory(
                    this,
                    tr("Image folder"),
                    m_core.currentFolderPath());
        if (!dir.isEmpty()) m_core.setCurrentFolderPath(dir);

///        // TODO remove demo code
///        QStringList imageFileNames = m_core.currentImageFileNameList();
///        for (auto name : imageFileNames)
///            qDebug() << "image file name: " << name;

        // TODO Set up the new view
    }
    PPD_TOP_LEVEL_CATCH("Open Folder")
}   // end on_openBtn_clicked method
