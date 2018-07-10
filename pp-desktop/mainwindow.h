#ifndef ppdesktop_mainwindow_h_included
#define ppdesktop_mainwindow_h_included

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
     * @param parent Parent object (usually `nullptr`
     */
    explicit MainWindow(QWidget *parent = 0);

    /**
     * \brief Destructor - destroys all UI objects
     */
    ~MainWindow();

    private slots:

    // TODO Temporary demo code - delete
    void on_errorButton_clicked();

    void on_openBtn_clicked();

    private:

    int currentImageIndex(void) const { return m_core.currentImageIndex(); }

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

};  // end MainWindow class

#endif // ppdesktop_mainwindow_h_included
