#include "metadataitem.h"

namespace PhotoPres {

MetadataItem::MetadataItem(QString n, QString v) :
    m_name(std::move(n)),
    m_value(std::move(v))
{

}   // end constructor

}   // end PhotoPres namespace
