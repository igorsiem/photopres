#include <memory>
#include <map>
#include <QString>

#ifndef ppcore_metadataitem_h_included
#define ppcore_metadataitem_h_included

namespace PhotoPres {

/**
 * @brief A simple item of metadata with a string name and value
 */
class MetadataItem
{

    public:

    /**
     * @brief Constructor, setting the name and value
     *
     * @param n The Name of the Item
     *
     * @param v The arbitrary value of the item
     */
    explicit MetadataItem(QString n, QString v = "");

    /**
     * @brief Retrieve the name of the MetadataItem
     *
     * @return The name
     */
    const QString& name(void) const { return m_name; }

    /**
     * @brief Set the name  of the MetadataItem
     *
     * @param n The name to set
     */
    void setName(QString n) { m_name = std::move(n); }

    /**
     * @brief Retrieve the value of the MetadataItem
     *
     * @return The value
     */
    const QString& value(void) const { return m_name; }

    /**
     * @brief Set the value of the MetadataItem
     *
     * @param v The value to set
     */
    void setValue(QString v) { m_value = std::move(v); }

    protected:

    /**
     * @brief The name of the item
     */
    QString m_name;

    /**
     * @brief The value of the item
     */
    QString m_value;

};  // end MetadataItem class

/**
 * @brief A shared pointer to a MetadataItem
 */
using MetadataItemPtr = std::shared_ptr<MetadataItem>;

/**
 * @brief A shared pointer to a const MetadataItem
 */
using ConstMetadataItemPtr = std::shared_ptr<const MetadataItem>;

/**
 * @brief A map of strings (names) to MetadataItem (shared) pointers
 */
using MetadataItemMap = std::map<QString, MetadataItemPtr>;

}   // end PhotoPres namespace

#endif // ppcore_metadataitem_h_included
