#include <QFileDialog>
#include <QImageReader>
#include <QPixmap>

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

    // TODO remove demo code around version label
    /*
    QString versionString =
            tr("version: ")
            + QString::fromStdString(PhotoPres::Core::version());

    ui->version->setText(versionString);
    */

    // TODO improvements to image label set-up code
    ui->imageLbl->setBackgroundRole(QPalette::Dark);
    ui->imageLbl->setSizePolicy(
                QSizePolicy::Ignored,
                QSizePolicy::Ignored);
    ui->imageLbl->setScaledContents(true);

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
        if (!dir.isEmpty())
        {
            m_core.setCurrentFolderPath(dir);
            setCurrentImageIndex(0);
        }

    }
    PPD_TOP_LEVEL_CATCH("Open Folder")
}   // end on_openBtn_clicked method

void MainWindow::setCurrentImageIndex(int cii)
{

    m_core.setCurrentImageIndex(cii);

    // If we have a valid indedx, display the image
    if (m_core.currentImageIndex() >= 0)
    {

        ui->imageLbl->resize(ui->imageScrl->size());
        QString imageFileName =
                QDir(
                    m_core.currentFolderPath()).filePath(
                        m_core.currentImageFileNameList()[
                            m_core.currentImageIndex()]);

        QImageReader reader(imageFileName);
        QPixmap pixmap = QPixmap::fromImage(reader.read());

        ui->imageLbl->setPixmap(
                    pixmap.scaled(
                        ui->imageLbl->width(),
                        ui->imageLbl->height(),
                        Qt::KeepAspectRatio));
        ui->imageLbl->adjustSize();

        qDebug() << "loaded image file " << imageFileName;

    }   // end if we have a valid current index

}   //  end setCurrentImageIndex method
