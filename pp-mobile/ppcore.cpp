#include <QString>
#include <QTextStream>

#include "ppcore.h"

#define PPM_TOP_LEVEL_TRY try

// Macro for catching exceptions and signalling to the User - this should ONLY
// be used using the PpCore class
#define PPM_TOP_LEVEL_CATCH( action ) \
    catch (const PhotoPres::Error& err) \
    { \
        QString message; \
        QTextStream strm(&message); \
        strm << tr("Error: ") << err.message(); \
        strm.flush(); \
        signalError(action, message); \
    } \
    catch (const QException& err) \
    { \
        QString message; \
        QTextStream strm(&message); \
        strm << tr("Error: ") << err.what(); \
        strm.flush(); \
        signalError(action, message); \
    } \
    catch (const std::exception& err) \
    { \
        QString message; \
        QTextStream strm(&message); \
        strm << tr("Error: ") << err.what(); \
        strm.flush(); \
        signalError(action, message); \
    } \
    catch (...) \
    { \
        signalError( \
            action, \
            tr("An unexpected or unrecognised error condition was " \
                "encountered")); \
    }

PpCore::PpCore(QObject *parent) :
    QObject(parent),
    m_settings("Igor Siemienowicz", "PhotoPres"),
    m_core(m_settings)
{
}   // end constructor

QString PpCore::version(void) const
{
    return QString::fromStdString(PhotoPres::Core::version());
}   // end version method

// TODO Temporary demo code - delete
void PpCore::makeAnError(void)
{
    PPM_TOP_LEVEL_TRY
    {
        PP_RAISE_ERROR("This is Igor's error!");
    }
    PPM_TOP_LEVEL_CATCH("Test Error");
}

void PpCore::signalError(QString action, QString message)
{
    // icon code is for critical error
    emit messageBox(action, message, 3);
}   // end signalError method
