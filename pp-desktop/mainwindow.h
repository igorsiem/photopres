#ifndef ppdesktop_mainwindow_h_included
#define ppdesktop_mainwindow_h_included

#include <QLabel>
#include <QMainWindow>
#include <QSettings>

#include <core.h>

/**
 * \brief User Interface elements
 */
namespace Ui {
class MainWindow;
}

/**
 * @brief Encapsulates the Main Window of the desktop application
 */
class MainWindow : public QMainWindow
{

    Q_OBJECT

    public:

    /**
     * @brief Constructor - sets up the UI
     *
     * @param parent Parent object (usually `nullptr`)
     */
    explicit MainWindow(QWidget *parent = 0);

    /**
     * \brief Destructor - destroys all UI objects
     */
    virtual ~MainWindow(void);

    /**
     * @brief Record window state and geometry in persistent settings when
     * closing
     *
     * @param event The Close Event object (passed to base-class
     */
    virtual void closeEvent(QCloseEvent* event) override;

    private slots:

    /**
     * @brief Open / set the image folder
     *
     * This method is called when the User clicks the "Open" button. It opens
     * a folder chooser dialog, and, if a folder with images is chosen, displays
     * the first image.
     */
    void on_openBtn_clicked();

    private:

    /**
     * @brief Retrieve the index of the currently displayed image (in the list
     * from the current folder)
     *
     * @return The index of the displayed image, or -1 if there are no images
     */
    int currentImageIndex(void) const { return m_core.currentImageIndex(); }

    /**
     * @brief Set the current image index, and display the image (if it exists)
     *
     * @param cii The image index to set
     */
    void setCurrentImageIndex(int cii);

    /**
     * @brief Internally-created UI elements
     */
    Ui::MainWindow *ui;

    /**
     * @brief Persistent settings object for recording configuration items that
     * must persist between invocations
     */
    QSettings m_settings;

    /**
     * @brief PhotoPres core library functionality
     */
    PhotoPres::Core m_core;

    /**
     * @brief The label used to display the image
     */
    QLabel* m_imageLbl;

};  // end MainWindow class

#endif // ppdesktop_mainwindow_h_included
