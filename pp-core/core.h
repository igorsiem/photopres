#ifndef ppcore_h_included
#define ppcore_h_included

#include <string>

/**
 * \brief All core declaration related to the PhotoPres application
 */
namespace PhotoPres {

/**
 * @brief Main interface to PhotoPres core functionality
 *
 * A single instance of this class is required to use the library. Multiple
 * instances are redundant, but OK.
 */
class Core
{

    public:

    /**
     * @brief Retrieve the version of the core library, as a std::string
     * @return The version string
     */
    static std::string version(void);

};  // end ppcore class

}   // end photopres namespace

#endif // ppcore_h_included
