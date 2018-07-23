#include <QFileDialog>
#include <QHBoxLayout>
#include <QImageReader>
#include <QItemSelectionModel>
#include <QLayout>
#include <QList>
#include <QModelIndex>
#include <QPixmap>
#include <QVBoxLayout>

#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "errorhandling.h"
#include "thumbnailiconprovider.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_settings("Igor Siemienowicz", "PhotoPres"),
    m_core(m_settings),
    m_imageLbl(nullptr),
    m_filesModel(new QFileSystemModel)
{
    ui->setupUi(this);

    // Manual creation of image label and various bits of configuration
    m_imageLbl = new ClickableLabel();
    m_imageLbl->setText("<image>");
    m_imageLbl->setBackgroundRole(QPalette::Dark);

    // Set up the file system model for the images list view
    m_filesModel->setParent(this);  // <-- delete when parent is deleted
    m_filesModel->setFilter(QDir::NoDotAndDotDot
                            | QDir::Files);
    m_filesModel->setNameFilters(QStringList({"*.jpg"}));
    m_filesModel->setNameFilterDisables(false);
    m_filesModel->setIconProvider(new ThumbnailIconProvider());
    ui->filesLvw->setModel(m_filesModel);

    // TODO get split geometry from persistent settings, and use these widths
    // for defaults.
    ui->centralSpl->setSizes(
        QList<int>({ 200, 600 }));

    // Connect the click of the image label to a lambda that invokes the
    // previous or next action, depending on whether we clicked in the left or
    // the right.
    connect(m_imageLbl, &ClickableLabel::clicked, [this](int x, int) {
        if (x < (m_imageLbl->width() / 2)) on_previousImageAct_triggered();
        else on_nextImageAct_triggered();
    });

    ui->imageScrl->setWidget(m_imageLbl);
    ui->imageScrl->setBackgroundRole(QPalette::Dark);

    // m_imageLbl->setBackgroundRole(QPalette::Dark);

    // Retrieve window geometry and state from persistent settings storage
    m_settings.beginGroup("MainWindow");
    restoreGeometry(m_settings.value("geometry").toByteArray());
    restoreState(m_settings.value("state").toByteArray());
    m_settings.endGroup();

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

void MainWindow::showEvent(QShowEvent* event)
{
    QMainWindow::showEvent(event);

    // Set the image to zero, and notify the file list view and model of
    // the current directory.
    setCurrentImageIndex(0);
    ui->filesLvw->setRootIndex(
                m_filesModel->setRootPath(m_core.currentFolderPath()));
}   // end showEvent method

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

            // Set the root of the file model and view to the new dir
            ui->filesLvw->setRootIndex(m_filesModel->setRootPath(dir));

            qDebug() << "set file model root to " << dir;
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

void MainWindow::on_filesLvw_clicked(const QModelIndex &index)
{
    // If we're in caption-edit mode, save the changes.
    if (ui->editCaptionAct->isChecked())
    {
        endCaptionEdit();
        ui->editCaptionAct->setChecked(false);
    }

    setCurrentImageIndex(index.row());
}   // end on_filesLvw_clicked method

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

        delete ui->contentWdg->layout();
        ui->contentWdg->setLayout(newLayout);

        // We activate the layout at this point, so that the image is resized
        // correctly.
        newLayout->activate();

        // Put the image pixmap into the image label
        m_imageLbl->resize(ui->imageScrl->size());

        m_imageLbl->setPixmap(
                    pixmap.scaled(
                        m_imageLbl->width(),
                        m_imageLbl->height(),
                        Qt::KeepAspectRatio,
                        Qt::SmoothTransformation)
                   );

        // m_imageLbl->adjustSize();

        // Make sure the "edit caption" action is now enabled
        ui->editCaptionAct->setEnabled(true);

        // Make sure the list view knows about the image selection change. The
        // 'row' in the list is the image index.
        QModelIndex imageIndex = m_filesModel->index(
                    QDir(m_core.currentFolderPath()).filePath(
                        m_core.currentFileName()));
        ui->filesLvw->setCurrentIndex(imageIndex);

        qDebug() << "loaded image file " << imageFileName << " (item " << cii <<
                    ") in image sequence";


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
