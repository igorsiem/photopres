#include <QByteArray>
#include <QCoreApplication>
#include <QFile>
#include <QJsonDocument>

#include "metadata.h"
#include "error.h"

namespace PhotoPres {

const QString Metadata::m_metadataFileName = ".photopres.json";

Metadata::Metadata(QDir d) :
    m_json(),
    m_dir(std::move(d))
{
}   // end constructor

QString Metadata::caption(const QString& fileName) const
{
    return m_json["files"][fileName]["caption"].toString();

    // If we didn't find an existing entry, return an empty string.
    // return QString();

}   // end caption method

void Metadata::setCaption(const QString& fileName, QString t)
{

    // Get out the objects and values we want, then put them back.
    auto files = m_json["files"].toObject();
    auto fileOb = files[fileName].toObject();

    fileOb["caption"] = t;
    files[fileName] = fileOb;
    m_json["files"] = files;

}   // end setCaption method

void Metadata::eraseCaption(const QString& fileName)
{
    auto files = m_json["files"].toObject();
    auto fileOb = files[fileName].toObject();

    auto itr = fileOb.find("caption");
    if (itr != fileOb.end()) fileOb.erase(itr);

    files[fileName] = fileOb;
    m_json["files"] = files;
}   // end eraseCaption

void Metadata::load(void)
{

    // First, clear our existing data (if any)
    m_json = QJsonObject();

    // Only attempt this if the file exists. If it does not exist, there is no
    // error - just no data.
    if (m_dir.exists(m_metadataFileName))
    {
        auto fileName = m_dir.filePath(m_metadataFileName);

        QFile file(fileName);
        if (!file.open(QIODevice::ReadOnly))
            PP_RAISE_ERROR_AND_LOG(
                        QCoreApplication::translate(
                            "Metadata", "could not open file for reading - ") <<
                        m_dir.filePath(m_metadataFileName));

        QByteArray data = file.readAll();
        auto doc = QJsonDocument::fromJson(data);
        m_json = doc.object();
    }   // end if the file exists

}   // end load method

void Metadata::save(void) const
{
    // Attempt to open / create the file for writing
    auto fileName = m_dir.filePath(m_metadataFileName);
    QFile file(fileName);

    if (!file.open(QIODevice::WriteOnly))
        PP_RAISE_ERROR_AND_LOG(
                    QCoreApplication::translate(
                        "Metadata", "could not open file for writing - ") <<
                    m_dir.filePath(m_metadataFileName));

    QJsonDocument doc(m_json);
    file.write(doc.toJson());
}   // end save method

}   // end PhotoPres namespace
