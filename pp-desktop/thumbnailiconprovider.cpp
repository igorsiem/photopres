#include <QPixmap>

#include "thumbnailiconprovider.h"

QIcon ThumbnailIconProvider::icon(const QFileInfo &info) const
{

    QPixmap picture(QSize(64, 64));
    picture.load(info.filePath());
    return QIcon(picture);

}   // end icon method
