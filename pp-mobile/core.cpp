#include "core.h"

Core::Core(QObject *parent) : QObject(parent)
{

}   // end constructor

QString Core::version(void) const
{
    return QString::fromStdString(photopres::ppcore::version());
}
