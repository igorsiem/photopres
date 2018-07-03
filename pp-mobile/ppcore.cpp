#include "ppcore.h"

PpCore::PpCore(QObject *parent) : QObject(parent)
{

}   // end constructor

QString PpCore::version(void) const
{
    return QString::fromStdString(PhotoPres::Core::version());
}   // end version
