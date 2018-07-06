#ifndef ppcore_core_h_included
#define ppcore_core_h_included

#include <string>

#include <QSettings>
#include <QString>

#include "error.h"
#include "metadataitem.h"

/**
 * \brief All core declaration related to the PhotoPres application
 */
namespace PhotoPres {

/**
 * @brief Main interface to PhotoPres core functionality
 *
 * A single instance of this class is required to use the library. Multiple
 * instances are redundant, but OK.
 */
class Core
{

    public:

    // Core(void) : m_settings("Igor Siemienowicz", "PhotoPres") {}
    explicit Core(QSettings& settings) : m_settings(settings) {}

    /**
     * @brief Retrieve the version of the core library, as a std::string
     * @return The version string
     */
    static std::string version(void);

    /**
     * @brief Retrieve the current working folder from persistent settings
     *
     * @return The path to the current working folder
     */
    QString currentFolder(void) const;

    /**
     * @brief Set the current working folder (recorded in persistent settings)
     *
     * @param cf The current folder path to set
     */
    void setCurrentFolder(QString cf);

    protected:

    /**
     * @brief Reference to externally-supplied persistent settings object
     */
    QSettings& m_settings;

};  // end ppcore class

}   // end photopres namespace

#endif // ppcore_core_h_included

/**
 * \page ppcore_library The PP Core Library
 *
 * \todo Expand mid-level docs for the Core library
 */
