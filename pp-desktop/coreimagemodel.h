#ifndef ppdesktop_coreimagemodel_h_included
#define ppdesktop_coreimagemodel_h_included

#include <QAbstractItemModel>
#include <core.h>

/**
 * @brief A data model wrapper for the images list managed by the
 * `PhotoPres::Core` class
 *
 * This is a simple data model with a single list of data (no tree structure)
 * at the root. The internal managed data type is the string file name (within
 * the current directory).
 */
class CoreImageModel : public QAbstractItemModel
{

    Q_OBJECT

    public:

    /**
     * @brief Constructor, initialising all attributes
     *
     * @param core A reference to the core business logic object that this
     * model wraps
     *
     * @param parent The parent Qt object
     */
    explicit CoreImageModel(PhotoPres::Core& core, QObject* parent = nullptr);

    /**
     * @brief Return an index object for the given row and column
     *
     * @param row The row number; this is intended to correspond to the image
     * index in the Core object
     *
     * @param column the column number; the zero'th column is the file name
     *
     * @param parent The parent index (this is basically ignored, because all
     * items are at the root
     *
     * @return An index object (possibly invalid) for the row and column
     *
     * @todo Add support for caption as a second column
     */
    virtual QModelIndex index(
            int row,
            int column,
            const QModelIndex& parent) const override;

    /**
     * @brief Retrieve the parent of the given index
     *
     * @return Always `QModelIndex()`, because all items are at the root and
     * have no parent
     */
    virtual QModelIndex parent(const QModelIndex&) const override
        { return QModelIndex(); }

    /**
     * @brief Retrieve the number of rows in the model - which is the number
     * of images in the current folder
     *
     * @return The number of images in the current folder managed by `m_core`
     */
    virtual int rowCount(const QModelIndex&) const override
        { return m_core.currentImageFileNameList().size(); }

    /**
     * @brief Retrieve the column count
     *
     * @return The number of columns
     *
     * @todo The number columns is always 1 (the file name), but in the future,
     * we probably want to support a column for the caption, and perhaps the
     * image
     */
    virtual int columnCount(const QModelIndex&) const override
        { return 1; }

    /**
     * @brief Retrieve the data for the given index
     *
     * @param index The index for which data is to be retrieved
     *
     * @param role The role of the data
     *
     * @return The data for the given index as a QVariant
     *
     * @todo This iteration simply retrieve the file name for column 0 - future
     * iterations should retrieve the caption and possibly the image when
     * requested
     */
    virtual QVariant data(const QModelIndex& index, int role) const override;

    /**
     * @brief Retrieve the status flags for an item, ensuring that it is
     * read-only
     *
     * @param index The item index
     *
     * @return The flags for the item
     */
    virtual Qt::ItemFlags flags(const QModelIndex& index) const override
    {
        if (!index.isValid()) return 0;
        return QAbstractItemModel::flags(index);
    }

    public slots:

    /**
     * @brief Signal the model that the current folder has changed, and that the
     * list data must be refreshed
     *
     * @param folderPath The new folder path (unused)
     */
    void currentFolderChanged(const QString& folderPath);

    protected:

    /**
     * @brief A reference to the core business logic object
     */
    PhotoPres::Core& m_core;

};  // end CoreImageModel class

#endif // ppdesktop_coreimagemodel_h_included
