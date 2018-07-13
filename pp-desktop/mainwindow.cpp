#include <QFileDialog>
#include <QHBoxLayout>
#include <QImageReader>
#include <QLayout>
#include <QPixmap>
#include <QVBoxLayout>

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

    // Retrieve window geometry and state from persistent settings storage
    m_settings.beginGroup("MainWindow");
    restoreGeometry(m_settings.value("geometry").toByteArray());
    restoreState(m_settings.value("state").toByteArray());
    m_settings.endGroup();

    // Set some of the image / scrolling area stuff manually
    ui->imageScrl->setBackgroundRole(QPalette::Dark);
    ui->imageLbl->setBackgroundRole(QPalette::Dark);

}   // end constructor

MainWindow::~MainWindow(void)
{
    delete ui;
}   // end destructor

void MainWindow::closeEvent(QCloseEvent* event)
{
    m_settings.beginGroup("MainWindow");
    m_settings.setValue("geometry", saveGeometry());
    m_settings.setValue("windowState", saveState());
    m_settings.endGroup();

    QMainWindow::closeEvent(event);
}   // end closeEvent method

void MainWindow::on_openFolderAct_triggered()
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
}   // end on_openFolderAct_triggered method

void MainWindow::setCurrentImageIndex(int cii)
{

    m_core.setCurrentImageIndex(cii);

    // If we have a valid indedx, display the image
    if (m_core.currentImageIndex() >= 0)
    {

        // Get the file name and its full path
        auto fileNameInDir = m_core.currentImageFileNameList()[
                m_core.currentImageIndex()];
        auto imageFileName =
                QDir(m_core.currentFolderPath()).filePath(fileNameInDir);

        ui->textLbl->setText(m_core.captionFor(fileNameInDir));

        // Read the image from the file
        QImageReader reader(imageFileName);
        reader.setAutoTransform(true);
        QPixmap pixmap = QPixmap::fromImage(reader.read());

        // Create a new layout for the window, depending on whether the image
        // is wide or tall. Also, constrain the maximum width of the text label
        // when the text is placed on the right of the image.
        QLayout* newLayout = nullptr;
        if (pixmap.size().width() > pixmap.size().height())
        {
            newLayout = new QVBoxLayout;
            ui->textLbl->setMaximumWidth(QWIDGETSIZE_MAX);
        }
        else
        {
            newLayout = new QHBoxLayout;
            ui->textLbl->setMaximumWidth(this->size().width() / 3);
        }

        newLayout->addWidget(ui->imageScrl);
        newLayout->addWidget(ui->textLbl);

        delete ui->centralWidget->layout();
        ui->centralWidget->setLayout(newLayout);

        // We activate the layout at this point, so that the image is resized
        // correctly.
        newLayout->activate();

        // Put the image pixmap into the image label
        ui->imageLbl->resize(ui->imageScrl->size());

        ui->imageLbl->setPixmap(
                    pixmap.scaled(
                        ui->imageLbl->width(),
                        ui->imageLbl->height(),
                        Qt::KeepAspectRatio,
                        Qt::SmoothTransformation)
                   );

        // ui->imageLbl->adjustSize();

        qDebug() << "loaded image file " << imageFileName;

    }   // end if we have a valid current index

}   //  end setCurrentImageIndex method
