#include "error.h"

namespace PhotoPres {

Error::Error(QString msg) :
    m_message(std::move(msg))
{

}   // end constructor

}   // end PhotoPress namespace
