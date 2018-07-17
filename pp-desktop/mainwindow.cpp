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

void MainWindow::on_editCaptionAct_triggered(void)
{
    if (ui->editCaptionAct->isChecked()) beginCaptionEdit();
    else endCaptionEdit();
}   // end on_editCaptionAct_triggered

void MainWindow::on_previousImageAct_triggered()
{
    // If we're in caption-edit mode, save the changes.
    if (ui->editCaptionAct->isChecked())
    {
        endCaptionEdit();
        ui->editCaptionAct->setChecked(false);
    }

    setCurrentImageIndex(m_core.currentImageIndex()-1);
}   // end on_previousImageAct_triggered

void MainWindow::on_nextImageAct_triggered()
{
    // If we're in caption-edit mode, save the changes.
    if (ui->editCaptionAct->isChecked())
    {
        endCaptionEdit();
        ui->editCaptionAct->setChecked(false);
    }

    setCurrentImageIndex(m_core.currentImageIndex()+1);
}   // end on_nextImageAct_triggered

void MainWindow::setCurrentImageIndex(int cii)
{

    // If we were editing a caption, end the edit before we switch images.
    if (ui->editCaptionAct->isChecked())
    {
        endCaptionEdit();
        ui->editCaptionAct->setChecked(false);
    }

    // Set the index, no matter what it is, then check to see if we get a
    // valid file name for the index
    m_core.setCurrentImageIndex(cii);
    auto fileNameInDir = m_core.currentFileName();
    if (fileNameInDir.isEmpty())
    {
        // No image to display
        //
        // Disable the "edit caption" action
        ui->editCaptionAct->setEnabled(false);
    }
    else
    {

        // Get the full path
        auto imageFileName =
                QDir(m_core.currentFolderPath()).filePath(fileNameInDir);

        ui->textEdt->setText(m_core.captionFor(fileNameInDir));

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
            ui->textEdt->setMaximumWidth(QWIDGETSIZE_MAX);
        }
        else
        {
            newLayout = new QHBoxLayout;
            ui->textEdt->setMaximumWidth(this->size().width() / 3);
        }

        newLayout->addWidget(ui->imageScrl);
        newLayout->addWidget(ui->textEdt);

        // If there's no text to show, hide the label
        if (ui->textEdt->toPlainText().isEmpty())
            ui->textEdt->hide();
        else ui->textEdt->show();

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

        // Make sure the "edit caption" action is now enabled
        ui->editCaptionAct->setEnabled(true);

    }   // end if we have a valid current index (image to display)

    // Enable / disable our 'previous' / 'next' actions accordingly.
    if (m_core.currentImageIndex() > 0) ui->previousImageAct->setEnabled(true);
    else ui->previousImageAct->setEnabled(false);

    if (m_core.currentImageIndex() < m_core.currentImageFileNameList().size()-1)
        ui->nextImageAct->setEnabled(true);
    else ui->nextImageAct->setEnabled(false);


}   //  end setCurrentImageIndex method

void MainWindow::beginCaptionEdit(void)
{
    ui->textEdt->show();
    ui->textEdt->setReadOnly(false);

    qDebug() << "beginning edit caption";
}   // end beginCaptionEdit method

void MainWindow::endCaptionEdit(void)
{

    ui->textEdt->setReadOnly(true);

    auto cfn = m_core.currentFileName();

    if (ui->textEdt->toPlainText().isEmpty())
    {
        // No caption - make sure it is erased
        m_core.eraseCaptionFor(cfn);
        ui->textEdt->hide();

        qDebug() << "finished editing caption - empty caption";
    }
    else
    {
        // We have a caption - make sure it is recorded.
        m_core.setCaptionFor(cfn, ui->textEdt->toHtml());

        qDebug() << "finished editing caption - " << ui->textEdt->toPlainText();
    }

}   // end endCaptionEdit method
