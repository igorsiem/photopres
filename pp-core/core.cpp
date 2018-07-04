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

QString Core::currentFolder(void) const
{
    return m_settings.value(
                "currentFolder",
                QStandardPaths::writableLocation(
                    QStandardPaths::PicturesLocation)).toString();
}   // end getCurrentFolder method

void Core::setCurrentFolder(QString cf)
{
    qDebug() << "setting current folder to \"" << cf << "\"";
    m_settings.setValue("currentFolder", std::move(cf));
}   // end setCurrentFolder method

}   // end photopres namespace
