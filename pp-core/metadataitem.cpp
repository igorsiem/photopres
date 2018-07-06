#include "metadataitem.h"

namespace PhotoPres {

bool hasItemNotEmpty(const MetadataItemMap& map, const QString& name)
{
    auto itr = map.find(name);
    if (itr == map.end()) return false;
    else return (!itr->second.isEmpty());
}   // end hasItem

void forEachNotEmpty(const MetadataItemMap &map, ConstMIProcessingFn fn)
{
    for (auto& itr : map)
        if (itr.second.isEmpty() == false) fn(itr.first, itr.second);
}   // end for_each

void forEachNotEmpty(MetadataItemMap& map, MIValueUpdatingFn fn)
{
    for (auto& itr : map)
        if (itr.second.isEmpty() == false) fn(itr.first, itr.second);
}

std::size_t sizeNonEmpty(const MetadataItemMap& map)
{
    return std::count_if(
                map.begin(),
                map.end(),
                [](MetadataItemMap::value_type pr)
    {
        return !pr.second.isEmpty();
    });
}

}   // end PhotoPres namespace
