#include <QDir>
#include <QStandardPaths>
#include <QtDebug>

#include "core.h"

const char* ppcore_version = "0.1";

namespace PhotoPres {

Core::Core(QSettings& settings) :
    m_settings(settings),
    m_currentImageFileNameList(nullptr),
    m_metadata(nullptr),
    m_currentImageIndex(0),
    signalFolderPathChanged(nullptr),
    signalImageIndexChanged(nullptr)
{}

std::string Core::version(void)
{
    qDebug() << "PhotoPres Core library version " << ppcore_version;
    return ppcore_version;
}   // end version method

QString Core::currentFolderPath(void) const
{
    return m_settings.value(
                "currentFolderPath",
                QStandardPaths::writableLocation(
                    QStandardPaths::PicturesLocation)).toString();
}   // end getCurrentFolder method

void Core::setCurrentFolderPath(QString cf)
{
    // qDebug() << "setting current folder path to \"" << cf << "\"";
    m_settings.setValue("currentFolderPath", std::move(cf));

    // Invalidate the current file name list. It's a smart pointer, and will
    // be deleted automatically.
    m_currentImageFileNameList = nullptr;
    m_metadata = nullptr;

    if (signalFolderPathChanged) signalFolderPathChanged(cf);
}   // end setCurrentFolder method

const QStringList& Core::currentImageFileNameList(void) const
{

    // If we have a copy cached, then return that - otherwise query the path
    // using a QDir object, get the string list from that.
    if (!m_currentImageFileNameList)
    {
        QDir dir(currentFolderPath());
        dir.setFilter(
                    QDir::Files
                    | QDir::NoDotAndDotDot
                    | QDir::Readable
                    | QDir::CaseSensitive
                    );
        dir.setSorting(QDir::Name);

        // Should use make_unique here, but for some reason, the android C++
        // compiler doesn't seem to support it. :-(
        m_currentImageFileNameList =
                std::unique_ptr<QStringList>(
                    std::move(new QStringList(
                        dir.entryList(
                            QStringList({"*.jpg"})
                                      ))));
    }   // end if we don't have a file name list

    return *m_currentImageFileNameList;

}   // end imageFileNameList method

int Core::currentImageIndex(void) const
{

    // Make sure file name list is populated, if necessary
    if (!m_currentImageFileNameList) currentImageFileNameList();

    // Trim as appropriate
    if (m_currentImageFileNameList->size() == 0) return -1;
    else
    {
        if (m_currentImageIndex < 0) return 0;
        else if (m_currentImageIndex > (m_currentImageFileNameList->size()-1))
            return m_currentImageFileNameList->size()-1;
        else return m_currentImageIndex;
    }

}   // end currentImageIndex method

void Core::setCurrentImageIndex(int cii)
{
    // Make sure file name list is populated, if necessary
    if (!m_currentImageFileNameList) currentImageFileNameList();

    // Trim as appropriate
    if (m_currentImageFileNameList->size() == 0) m_currentImageIndex = -1;
    else if (cii < 0) m_currentImageIndex = 0;
    else if (cii > m_currentImageFileNameList->size()-1)
        m_currentImageIndex = m_currentImageFileNameList->size()-1;
    else m_currentImageIndex = cii;

    if (signalImageIndexChanged) signalImageIndexChanged(m_currentImageIndex);
}   // end setCurrentImageIndex

QString Core::currentFileName(void) const
{
    auto cii = currentImageIndex();
    if (cii >= 0) return currentImageFileNameList()[cii];
    else return QString();
}   // end currentFileName

QString Core::captionFor(const QString& fileName) const
{
    return metadata().caption(fileName);
}   // end captionFor method

void Core::setCaptionFor(const QString& fileName, QString ct)
{
    metadata().setCaption(fileName, std::move(ct));
    metadata().save();
}   // end setCaptionFor method

void Core::eraseCaptionFor(const QString& fileName)
{
    metadata().eraseCaption(fileName);
    metadata().save();
}   // end eraseCaptionFor method

Metadata& Core::metadata(void)
{
    if (!m_metadata)
    {
        m_metadata = MetadataUpr(new Metadata(QDir(currentFolderPath())));
        m_metadata->load();
    }

    return *m_metadata;
}   // end metadata method

const Metadata& Core::metadata(void) const
{
    if (!m_metadata)
    {
        m_metadata = MetadataUpr(new Metadata(QDir(currentFolderPath())));
        m_metadata->load();
    }

    return *m_metadata;
}   // end metadata method

}   // end photopres namespace
