#include <QString>
#include <QTextStream>

#include "mainwindow.h"

#define PPM_TOP_LEVEL_TRY try

// Macro for catching exceptions and signalling to the User - this should ONLY
// be used in the ApplicationWindow class
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

ApplicationWindow::ApplicationWindow(QObject *parent) :
    QObject(parent),
    m_settings("Igor Siemienowicz", "PhotoPres"),
    m_core(m_settings)
{
}   // end constructor

QString ApplicationWindow::version(void) const
{
    return QString::fromStdString(PhotoPres::Core::version());
}   // end version method

void ApplicationWindow::setCurrentImageIndex(int cii)
{
    PPM_TOP_LEVEL_TRY
    {
        m_core.setCurrentImageIndex(cii);

        // If we have a valid image index, then we can get a valid image file
        if (m_core.currentImageIndex() >= 0)
        {
            QString imageFileNameUrl = currentFolderUrl() + "/" +
                    m_core.currentImageFileNameList()[
                        m_core.currentImageIndex()];
            emit displayImage(imageFileNameUrl);
            qDebug() << "displayed " << imageFileNameUrl;
        }
    }
    PPM_TOP_LEVEL_CATCH("Loading and Displaying an Image")
}   // end setCurrentImageIndex method

void ApplicationWindow::signalError(QString action, QString message)
{
    // icon code is for critical error
    emit messageBox(action, message, 3);
}   // end signalError method
