#include <functional>
#include <map>
#include <memory>

#include <QString>

#ifndef ppcore_metadataitem_h_included
#define ppcore_metadataitem_h_included

namespace PhotoPres {

/**
 * @brief A simple name/value pair - metadata for a picture
 */
using MetadataItem = std::pair<QString, QString>;

/**
 * @brief A shared pointer to a metadata item
 */
using MetadataItemPtr = std::shared_ptr<MetadataItem>;

/**
 * @brief A shared pointer to a const metadata item
 */
using ConstMetadataItemPtr = std::shared_ptr<const MetadataItem>;

/**
 * @brief A simple name / value pair map for metadata items
 */
using MetadataItemMap = std::map<QString, QString>;

/**
 * @brief Determine whether a metadata item map has a named item with a
 * non-empty value
 *
 * @param map The map to check
 *
 * @param name The name to check
 *
 * @return `true` if `map` has an entry with key `name` that is a non-empty
 * string
 */
extern bool hasItemNotEmpty(const MetadataItemMap& map, const QString& name);

/**
 * @brief A callable object for processing const name / value pairs from a
 * metadata item
 */
using ConstMIProcessingFn = std::function<void(const QString&, const QString&)>;

/**
 * @brief Convenience function for iterating over the MI map, passing each name
 * and value to a given callable object
 *
 * Note that items with an empty value are skipped (as if they do not exist).
 *
 * @param map The MI map over which to iterate
 *
 * @param fn The callable object, lambda or function
 */
extern void forEachNotEmpty(const MetadataItemMap& map, ConstMIProcessingFn fn);

/**
 * @brief A callable object for an MI that may update the passed value
 */
using MIValueUpdatingFn = std::function<void(const QString&, QString&)>;

/**
 * @brief Iterate over the given MI map with a callable that may update values
 * (but not names)
 *
 * @param map The map object over which to iterate
 *
 * @param fn The callable function / lamda / object
 */
extern void forEachNotEmpty(MetadataItemMap& map, MIValueUpdatingFn fn);

/**
 * @brief Retrieve the size of the given MI map, *not counting empty items*
 *
 * The `MetadataItemMap::size` method will return the size of the map, with
 * empty items (which we usually ignore) included.
 *
 * Note that this method uses a straight `std::count_if` so it's not terribly
 * efficient.
 *
 * @param map The MI container to check
 *
 * @return The number of items in the collection with non-empty values
 */
extern std::size_t sizeNonEmpty(const MetadataItemMap& map);

}   // end PhotoPres namespace

#endif // ppcore_metadataitem_h_included

/**
 * @page pp_metadata PhotoPres Metadata
 *
 * Metadata for photosin PhotoPres is represented in simple string name / value
 * pairs. Aliases on standard map and pair templates are used with QString for
 * this.
 *
 * A number of free functions are provided for searching and iterating over
 * metadata item collections. These are a bit more convenient than the 'raw'
 * implementations from the STL that they wrap. They also treat MI elements
 * with empty values as 'non-existent', so that they are not returned in
 * searches, and are skipped over in iterations. Otherwise, these functions
 * perform pretty much as one might expect.
 *
 * @todo Expand mid-level docs on Metadata
 */
