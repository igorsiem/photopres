#include <QFileIconProvider>
#include <QFileInfo>
#include <QIcon>

#ifndef ppdesktop_thumbnailiconprovider_h_included
#define ppdesktop_thumbnailiconprovider_h_included

/**
 * @brief A file icon provider class that produces thumbnails of images for
 * icons
 */
class ThumbnailIconProvider : public QFileIconProvider
{

    public:

    virtual QIcon icon(const QFileInfo &info) const override;

};  // end ThumbnailIconProvider class

#endif // ppdesktop_thumbnailiconprovider_h_included
