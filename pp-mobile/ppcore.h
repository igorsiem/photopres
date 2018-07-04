#include <QObject>
#include <QSettings>
#include <QString>
#include <core.h>

#ifndef ppmobile_core_h_included
#define ppmobile_core_h_included

/**
 * @brief Wrapper for the 'raw' C++ PhotoPres Core class
 *
 * This class also includes some utility methods to assist with interaction
 * between the UI and the business logic of the application.
 *
 * @todo Expand class documentation
 */
class PpCore : public QObject
{
    Q_OBJECT

    public:

    /**
     * @brief Constructor - sets up the core object
     *
     * @param parent The parent object
     */
    explicit PpCore(QObject *parent = nullptr);

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
        { return std::move(m_core.currentFolder()); }

    /**
     * @brief Set the current folder path in core
     *
     * Note that core takes care of recording this in persistent settings.
     *
     * @param cf The current folder path to set
     */
    void setCurrentFolder(QString cf)
        { m_core.setCurrentFolder(std::move(cf)); }

    // TODO Temporary demo code - delete
    Q_INVOKABLE void makeAnError(void);

    // -- Utilities --

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
    void signalError(QString action, QString message);

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
    void messageBox(QString mbHeading, QString mbText, int iconCode = 0);

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

};  // end Core class

#endif // ppmobile_core_h_included
