#include <QObject>
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

    // Version string for the Core library
    Q_PROPERTY(QString version READ version CONSTANT)

    /**
     * @brief Retrieve the core library version
     *
     * @return The version string for the Core library
     */
    QString version(void) const;

    // TODO Temporary demo code - delete
    Q_INVOKABLE void makeAnError(void);

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

};  // end Core class

#endif // ppmobile_core_h_included
