#include <QDir>
#include <QJsonObject>
#include "utils.h"

#ifndef ppcore_metadataitem_h_included
#define ppcore_metadataitem_h_included

namespace PhotoPres {

/**
 * @brief A class for accessing the metadata about files in the given directory
 *
 * Metadata about image files in a directory is held in a JSON file in the
 * directory itself. This class maintains that file, allowing access to the
 * data via conventional setters and getters.
 *
 * In this iteration, the only metadata item that is available for a file is
 * the caption text.
 */
class Metadata
{

    // --- External Interface ---

    public:

    /**
     * @brief Construct the Metadata object for a given directory
     *
     * @param d The directory for which this object holds information
     */
    explicit Metadata(QDir d);

    /**
     * @brief Retrieve the caption for the given file in the directory
     *
     * If there is no entry for the file in the metadata, or no caption entry
     * in the metadata for the file, an empty string is returned. Note that this
     * method does *not* check to ensure that the file actually exists in the
     * directory.
     *
     * @param fileName The name of the file
     *
     * @return The caption for the file, or an empty string if there is no entry
     * for the file
     */
    QString caption(const QString& fileName) const;

    /**
     * @brief Set the caption for the given file
     *
     * Note that this method does not check that the file actually exists in the
     * directory.
     *
     * @param fileName The file name for which to set the caption
     *
     * @param t The caption text
     */
    void setCaption(const QString& fileName, QString t);

    /**
     * @brief Erase the caption for a given file
     *
     * No error is raised if there is no existing caption for the file, or if
     * the file itself does not exist.
     *
     * @param fileName The name of the file whose caption will be erased
     */
    void eraseCaption(const QString& fileName);

    /**
     * @brief Load the metadata JSON file from the directory
     *
     * Note that, if the file does not exist, no error is signalled. However,
     * if the file exists, but there is a problem opening it, then an exception
     * is thrown.
     *
     * @throw Error The file exists, but there was a problem opening it for
     * reading
     */
    void load(void);

    /**
     * @brief Save the Metadata to the JSON file in the directory
     *
     * @throw Error A problem occurred while creating or opening the file for
     * writing
     */
    void save(void) const;

    // --- Internal Declarations ---

    protected:

    /**
     * @brief The JSON structure used to hold the data, and serialise it to and
     * from the metadata file
     */
    QJsonObject m_json;

    /**
     * @brief The name of the file used to record metadata for a directory
     */
    static const QString m_metadataFileName;

    /**
     * @brief The directory for the metadata
     *
     * The metadata in this object covers the files in this directory.
     */
    QDir m_dir;

};  // end Metadata class

PP_DECLARE_POINTERS_FOR( Metadata )

}   // end PhotoPres namespace

#endif // ppcore_metadataitem_h_included

/**
 * @page pp_metadata PhotoPres Metadata
 *
 * @todo Write mid-level docs on Metadata
 */
