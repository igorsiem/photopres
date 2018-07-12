#include "metadata.h"

#ifndef ppcore_metadataserialiser_h_included
#define ppcore_metadataserialiser_h_included

namespace PhotoPres {

/**
 * @brief An abstract base class for classes the serialise / deserialise
 * metadata
 */
class MetadataSerialiser
{

    public:

    /**
     * @brief Write the given Metadata Container information to the
     * serialisation destination
     *
     * @param mc The Metadata Container
     *
     * @return A const reference to `mc`
     */
    virtual MetadataContainer& write(const MetadataContainer& mc) = 0;

    /**
     * @brief Read data into the given Metadata Container from the serialisation
     * source
     *
     * @param mc The Metadata Container into which the data should be placed;
     * implementations should clear this before reading
     *
     * @return A reference to `mc`
     */
    virtual MetadataContainer& read(MetadataContainer& mc) = 0;

};  // end MetadataSerialiser class

}   // end PhotoPres namespace

#endif // ppcore_metadataserialiser_h_included
