#include <QtDebug>
#include "core.h"

const char* ppcore_version = "0.1";

namespace PhotoPres {

std::string Core::version(void)
{
    qDebug() << "PhotoPres Core library version " << ppcore_version;
    return ppcore_version;
}   // end version method

}   // end photopres namespace
