#include <QDir>
#include <QStandardPaths>
#include <QtDebug>

#include "core.h"

const char* ppcore_version = "0.1";

namespace PhotoPres {

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
    qDebug() << "setting current folder path to \"" << cf << "\"";
    m_settings.setValue("currentFolderPath", std::move(cf));

    // Invalidate the current file name list. It's a smart pointer, and will
    // be deleted automatically.
    m_currentImageFileNameList = nullptr;
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
                    | QDir::CaseSensitive);
        dir.setSorting(QDir::Name);

        // Should use make_unique here, but for some reason, the android C++
        // compiler doesn't seem to support it. :-(
        m_currentImageFileNameList =
                std::unique_ptr<QStringList>(
                    new QStringList(dir.entryList(QStringList({"*.jpg"}))));
    }   // end if we don't have a file name list

    return *m_currentImageFileNameList;

}   // end imageFileNameList method

}   // end photopres namespace
