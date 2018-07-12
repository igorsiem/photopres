#include "metadata.h"

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
}   // end forEachNotEmpty function

void forEachNotEmpty(MetadataItemMap& map, MIValueUpdatingFn fn)
{
    for (auto& itr : map)
        if (itr.second.isEmpty() == false) fn(itr.first, itr.second);
}   // end forEachNotEmpty function

std::size_t sizeNotEmpty(const MetadataItemMap& map)
{
    return std::count_if(
                map.begin(),
                map.end(),
                [](MetadataItemMap::value_type pr)
    {
        return !pr.second.isEmpty();
    });
}   // end sizeNotEmpty function

extern std::shared_ptr<QString> findNotEmpty(
        const MetadataItemMap& map,
        const QString& name)
{
    auto itr = map.find(name);
    if (itr == map.end()) return nullptr;
    else if (itr->second.isEmpty()) return nullptr;

    return std::make_shared<QString>(itr->second);
}   // end findNotEmpty function

void erase(MetadataItemMap& map, const QString& name)
{
    auto itr = map.find(name);
    if (itr != map.end()) map.erase(itr);
}   // end erase function

}   // end PhotoPres namespace
