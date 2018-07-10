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
    m_core(m_settings),
    m_imageLbl(nullptr)
{
    ui->setupUi(this);

    // Set up image / scrolling area manually
    ui->imageScrl->setBackgroundRole(QPalette::Dark);

    m_imageLbl = new  QLabel;
    m_imageLbl->setBackgroundRole(QPalette::Dark);
    m_imageLbl->setSizePolicy(
                QSizePolicy::Ignored,
                QSizePolicy::Ignored);
    // m_imageLbl->setScaledContents(true);

    ui->imageScrl->setWidget(m_imageLbl);

}   // end constructor

MainWindow::~MainWindow()
{
    delete ui;
}   // end destructor

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

        m_imageLbl->resize(ui->imageScrl->size());

        QString imageFileName =
                QDir(
                    m_core.currentFolderPath()).filePath(
                        m_core.currentImageFileNameList()[
                            m_core.currentImageIndex()]);

        QImageReader reader(imageFileName);
        reader.setAutoTransform(true);
        QPixmap pixmap = QPixmap::fromImage(reader.read());

        m_imageLbl->setPixmap(
                    pixmap.scaled(
                        m_imageLbl->width(),
                        m_imageLbl->height(),
                        Qt::KeepAspectRatio,
                        Qt::SmoothTransformation)
                   );

        m_imageLbl->adjustSize();

        qDebug() << "loaded image file " << imageFileName;

    }   // end if we have a valid current index

}   //  end setCurrentImageIndex method
