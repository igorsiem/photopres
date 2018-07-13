#include <fstream>
#include <iomanip>

#include <QCoreApplication>

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
    // We check to see if the JSON hierarchy components exist before loading
    // loading them, to prevent them being created 'on the fly'.
    if (m_json.find("files") != m_json.end())
        if (m_json["files"].find(fileName.toStdString()) !=
                m_json["files"].end())
            if (m_json["files"][fileName.toStdString()].find("caption") !=
                    m_json["files"][fileName.toStdString()].end())
                return QString::fromStdString(
                            m_json["files"][fileName.toStdString()]["caption"]);

    // If we didn't find an existing entry, return an empty string.
    return QString();
}   // end caption method

void Metadata::setCaption(const QString& fileName, QString t)
{
    m_json["files"][fileName.toStdString()]["caption"] = t.toStdString();
}   // end setCaption method

void Metadata::eraseCaption(const QString& fileName)
{
    if (m_json.find("files") != m_json.end())
    {
        auto itr = m_json["files"].find(fileName.toStdString());
        if (itr != m_json["files"].end())
            m_json["files"].erase(itr);
    }
}   // end eraseCaption

void Metadata::load(void)
{

    m_json.clear();

    // Only attempt this if the file exists. If it does not exist, there is no
    // error - just no data.
    if (m_dir.exists(m_metadataFileName))
    {
        auto fileName = m_dir.filePath(m_metadataFileName).toStdString();
        std::ifstream in(fileName);
        if (!in) PP_RAISE_ERROR_AND_LOG(
                    QCoreApplication::translate("Metadata", "could not open "
                                                "file for reading - ") <<
                    m_dir.filePath(m_metadataFileName));

        in >> m_json;
    }   // end if the file exists

}   // end load method

void Metadata::save(void) const
{
    // Attempt to open / create the file for writing
    auto fileName = m_dir.filePath(m_metadataFileName).toStdString();
    std::ofstream out(fileName);

    if (!out) PP_RAISE_ERROR_AND_LOG(
                QCoreApplication::translate("Metadata", "could not open "
                                            "file for writing - ") <<
                m_dir.filePath(m_metadataFileName));

    // Output the file with 4-space pretty-printing
    out << std::setw(4) << m_json;
}   // end save method

}   // end PhotoPres namespace
