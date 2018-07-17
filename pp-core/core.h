#ifndef ppcore_core_h_included
#define ppcore_core_h_included

#include <string>

#include <QSettings>
#include <QString>
#include <QStringList>

#include "error.h"
#include "metadata.h"

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

    /**
     * @brief Construct a Core library object
     *
     * @param settings Persistent settings object for the application
     */
    explicit Core(QSettings& settings) :
        m_settings(settings),
        m_currentImageFileNameList(nullptr),
        m_metadata(nullptr),
        m_currentImageIndex(0)
    {}

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
    QString currentFolderPath(void) const;

    /**
     * @brief Set the current working folder (recorded in persistent settings)
     *
     * @param cf The current folder path to set
     */
    void setCurrentFolderPath(QString cf);

    /**
     * @brief Retrieve the list of image file names in the current directory
     *
     * The first time this method is called, it retrieve the image file names
     * from the directory, and stores them in an internal list that is retained
     * after it is returned. Subsequent calls just return the same list object.
     * When the directory changes, the list is deleted and 'refreshed' with a
     * new set of names.
     *
     * @return A reference to the list of file names.
     */
    const QStringList& currentImageFileNameList(void) const;

    /**
     * @brief Retrieve the current image index
     *
     * This index is 'trimmed' to the range
     * `[0,m_currentImageFileNameList.size()-1]`. If there are no elements
     * in `m_currentImageFileNameList`, then -1 is returned.
     *
     * @return The index of the image currently being displayed
     */
    int currentImageIndex(void) const;

    /**
     * @brief Retrieve the current image index
     *
     * This index is 'trimmed' to the range
     * `[0,m_currentImageFileNameList.size()-1]`. If there are no elements
     * in `m_currentImageFileNameList`, then -1 is returned.
     *
     * @param cii The index of the image currently being displayed
     */
    void setCurrentImageIndex(int cii);

    /**
     * @brief Retrieve the file name (without path) of the image currently
     * being displayed
     *
     * @return The file name, or an empty string if no file name is currently
     * being displayed
     */
    QString currentFileName(void) const;

    /**
     * @brief Retrieve the caption for the given file from metadata
     *
     * @param fileName The name of the file
     *
     * @return The caption for the file, or an empty string if there is no
     * caption for the file
     */
    QString captionFor(const QString& fileName) const;

    /**
     * @brief Set the caption for the given file in metadata
     *
     * Note that the metadata is saved to the JSON file in this method.
     *
     * @param fileName The name of the file for the caption
     *
     * @param ct The caption
     */
    void setCaptionFor(const QString& fileName, QString ct);

    /**
     * @brief Erase the caption for the given file
     *
     * Note that the metadata is saved after erasing.
     *
     * @param fileName The name of the file whose caption is being erased
     */
    void eraseCaptionFor(const QString& fileName);

    protected:

    /**
     * @brief Access the metadata object for this file, creating and loading it
     * 'on the fly' if necessary
     *
     * @return A reference to the metadata object for this file
     */
    Metadata& metadata(void);

    /**
     * @brief Access the metadata object for this file, creating and loading it
     * 'on the fly' if necessary
     *
     * @return A const reference to the metadata object for this file
     */
    const Metadata& metadata(void) const;

    /**
     * @brief Reference to externally-supplied persistent settings object
     */
    QSettings& m_settings;

    /**
     * @brief This list of file names of image files in the current directory
     *
     * This object is instantiated the first time `currentImageFileNameList` is
     * called. Subsequent calls just return this object. When
     * `setCurrentFolderPath` is called, this list is deleted, and the next
     * call to `currentImageFileNameList` recreates it.
     */
    mutable std::unique_ptr<QStringList> m_currentImageFileNameList;

    /**
     * @brief The metadata for the current directory
     *
     * This object is instantiated similarly to `m_currentImageFileNameList`.
     * The first time is is required (in calls to access metadata) it is
     * instantiated and loaded for the current directory.
     */
    mutable MetadataUpr m_metadata;

    /**
     * @brief The index -- in `m_currentImageFileNameList` -- of the image being
     * displayed
     *
     * This index is 'trimmed' to the range
     * `[0,m_currentImageFileNameList.size()-1]`. If there are no elements
     * in `m_currentImageFileNameList`, then it is set to -1.
     */
    int m_currentImageIndex;

};  // end ppcore class

}   // end photopres namespace

#endif // ppcore_core_h_included

/**
 * \page ppcore_library The PP Core Library
 *
 * \todo Expand mid-level docs for the Core library
 */
