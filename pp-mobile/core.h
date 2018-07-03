#ifndef ppmobile_core_h_included
#define ppmobile_core_h_included

#include <QObject>
#include <ppcore.h>

/**
 * @brief Wrapper for the 'raw' C++ PhotoCore class
 */
class Core : public QObject
{
    Q_OBJECT

    public:

    /**
     * @brief Constructor - sets up the core object
     *
     * @param parent The parent object
     */
    explicit Core(QObject *parent = nullptr);

    // Version string for the Core library
    Q_PROPERTY(QString version READ version CONSTANT)

    /**
     * @brief Retrieve the core library version
     *
     * @return The version string for the Core library
     */
    QString version(void) const;

    signals:

    public slots:

};  // end Core class

#endif // ppmobile_core_h_included
