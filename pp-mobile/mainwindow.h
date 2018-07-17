#include <QDir>
#include <QObject>
#include <QSettings>
#include <QString>
#include <QUrl>

#include <core.h>

#ifndef ppmobile_core_h_included
#define ppmobile_core_h_included

/**
 * @brief Core functionality for the main Application Window
 *
 * @todo Expand class documentation
 */
class ApplicationWindow : public QObject
{
    Q_OBJECT

    public:

    /**
     * @brief Constructor - sets up the core object
     *
     * @param parent The parent object
     */
    explicit ApplicationWindow(QObject *parent = nullptr);

    // -- Accessors and Properties --

    // Version string for the Core library
    Q_PROPERTY(QString version READ version CONSTANT)

    /**
     * @brief Retrieve the core library version
     *
     * @return The version string for the Core library
     */
    QString version(void) const;

    // The folder currently in use
    Q_PROPERTY(QString currentFolder READ currentFolder WRITE setCurrentFolder)

    /**
     * @brief Retrieve the path to the current folder (from core)
     *
     * Note: core retrieves this from persistent settings
     *
     * @return The current folder path
     */
    QString currentFolder(void) const
        { return m_core.currentFolderPath(); }

    /**
     * @brief Set the current folder path in core
     *
     * Note that core takes care of recording this in persistent settings.
     *
     * @param cf The current folder path to set
     */
    void setCurrentFolder(QString cf)
        { m_core.setCurrentFolderPath(std::move(cf)); }

    // The folder currently in use
    Q_PROPERTY(
            QString currentFolderUrl
            READ currentFolderUrl
            WRITE setCurrentFolderUrl)

    /**
     * @brief Retrieve the current operating folder in URL form
     *
     * @return The current folder as a URL
     */
    QString currentFolderUrl(void) const
        { return QString("file://") + currentFolder(); }

    /**
     * @brief Set the current folder as a URL
     *
     * @param cfurl The URL of the current folder
     */
    void setCurrentFolderUrl(QString cfurl)
        { setCurrentFolder(QUrl(cfurl).toLocalFile()); }

    // The index of the image currently being displayed
    Q_PROPERTY(
            int currentImageIndex
            READ currentImageIndex
            WRITE setCurrentImageIndex)

    /**
     * @brief Retrieve the index of the currently displayed image file
     *
     * @return The index, or -1 if no image file can be displayed
     */
    int currentImageIndex(void) const { return m_core.currentImageIndex(); }

    /**
     * @brief Set the currently displayed image index, causing the image to
     * be displayed
     *
     * @param cii The index in the current file name list to display
     */
    void setCurrentImageIndex(int cii);

    // The current file name, indicated by the current image index
    Q_PROPERTY(QString currentFileName READ currentFileName)

    /**
     * @brief Retrieve the name of the image file currently indicated by the
     * image index
     *
     * @return The image file name (without a path), or an empty string if there
     * is no current file
     */
    QString currentFileName(void) const { return m_core.currentFileName(); }

    // The full URL of the current image  file
    Q_PROPERTY(QString currentFileNameUrl READ currentFileNameUrl)

    /**
     * @brief Retrieve the full URL of the file indication by the current
     * image index
     *
     * @return The full URL of the current file, or an empty string if there
     * is no current file
     */
    QString currentFileNameUrl(void) const
    {
        auto fn = currentFileName();
        if (fn.isEmpty()) return QString();
        else return currentFolderUrl() + "/" + fn;
    }

    // The caption for the current image
    Q_PROPERTY(
            QString currentCaption
            READ currentCaption
            WRITE setCurrentCaption)

    /**
     * @brief Retrieve the caption for the current image file
     *
     * @return The current caption for the file, or an empty string if there is
     * no caption for the file
     */
    QString currentCaption(void) const
    {
        return m_core.captionFor(currentFileName());
    }   // end currentCaption

    /**
     * @brief Set the caption the current file name, saving it to metadata
     * straight away
     *
     * @param ct The caption text to set
     */
    void setCurrentCaption(QString ct)
    {
        m_core.setCaptionFor(currentFileName(), std::move(ct));
    }

    /**
     * @brief Signal an error to the user
     *
     * This is a utility method for signalling the User about an error, using a
     * message box
     *
     * @param action The action that was being attempted when the error occurred
     *
     * @param message The human-readable error message
     */
    Q_INVOKABLE void signalError(QString action, QString message);

    /**
     * @brief Display a message box in the main window
     *
     * This method simply emits the `messageBox` signal.
     *
     * @param mbHeading The heading string
     *
     * @param mbText The text string
     *
     * @param iconCode The code for the icon to use (same as the
     * QMessageBox::Icon enum values)
     */
    Q_INVOKABLE void showMessageBox(
            QString mbHeading,
            QString mbText,
            int iconCode)
    {
        emit messageBox(mbHeading, mbText, iconCode);
    }   // end showMessageBox method

    // -- Utilities --

    signals:

    /**
     * @brief Request that the UI display a modal message box
     *
     * @param mbHeading The heading string
     *
     * @param mbText The text string
     *
     * @param iconCode The code for the icon to use (same as the
     * QMessageBox::Icon enum values)
     */
    void messageBox(
            QString mbHeading,
            QString mbText,
            int iconCode = 0);

    /**
     * @brief Load and display a given image in the Main Window
     *
     * @param path Path of the image file
     */
    void displayImage(QString path);

    public slots:

    protected:

    // -- Attributes --

    /**
     * @brief Persistent settings object for recording configuration items that
     * must persist between invocations
     */
    QSettings m_settings;

    /**
     * @brief The underlying PhotoPres Core object
     */
    PhotoPres::Core m_core;

};  // end ApplicationWindow class

#endif // ppmobile_core_h_included
