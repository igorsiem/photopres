#include <QDir>
#include <QIcon>
#include <QPixmap>

#include "coreimagemodel.h"

CoreImageModel::CoreImageModel(PhotoPres::Core& core, QObject* parent) :
    QAbstractItemModel(parent),
    m_core(core)
{
}   // end constructor

QModelIndex CoreImageModel::index(
        int row,
        int column,
        const QModelIndex& parent) const
{
    if (!hasIndex(row, column, parent)) return QModelIndex();

    // We only support column zero (the file name) at this stage
    //
    // TODO support a caption column
    if (column != 0) return QModelIndex();

    // Make sure the row is in range.
    if ((row >= 0) && (row < m_core.currentImageFileNameList().size()))
        return createIndex(row, column);
    else return QModelIndex();
}   // end index method

QVariant CoreImageModel::data(const QModelIndex& index, int role) const
{

    // If the index is not valid, then return invalid.
    if (!index.isValid()) return QVariant();

    // If the role is "decoration", then return an icon of the picture.
    if (role == Qt::DecorationRole)
    {
        QPixmap picture(QSize(64, 64));
        auto imageFilePath =
                QDir(m_core.currentFolderPath()).filePath(
                    m_core.currentImageFileNameList()[index.row()]);
        picture.load(imageFilePath);
        return QIcon(picture);
    }

    if (role != Qt::DisplayRole) return QVariant();
    if (index.column() != 0) return QVariant();

    return m_core.currentImageFileNameList()[index.row()];

}   // end data method

void CoreImageModel::currentFolderChanged(const QString&)
{
    beginResetModel();
    endResetModel();
}   // end currentFolderChanged
