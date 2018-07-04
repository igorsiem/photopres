#include <QMessageBox>
#include <QString>
#include <QTextStream>
#include <core.h>

#ifndef ppdesktop_errorhandling_h_included
#define ppdesktop_errorhandling_h_included

/**
 * The 'try' portion of a top-level try / catch block
 *
 * In 'top level' interactions with the User, most error conditions need to be
 * caught and signalled. Together with the `PPD_TOP_LEVEL_CATCH` macro, this
 * construct performs most of the generic constructs required for this.
 */
#define PPD_TOP_LEVEL_TRY try

/**
 * The 'catch' portion of a top-level try / catch block
 *
 * This 'catch' portion of the block catches *all* exceptions, and displays
 * an appropriate message to the User.
 *
 * @param action A human-readable string describing the action that was being
 * attempted when the error condition occurred.
 */
#define PPD_TOP_LEVEL_CATCH( action ) \
    catch (const PhotoPres::Error& err) \
    { \
        QString message; \
        QTextStream strm(&message); \
        strm << tr("Error: ") << err.message(); \
        strm.flush(); \
        QMessageBox::critical(this, action, message); \
    } \
    catch (const QException& err) \
    { \
        QString message; \
        QTextStream strm(&message); \
        strm << tr("Error: ") << err.what(); \
        strm.flush(); \
        QMessageBox::critical(this, action, message); \
    } \
    catch (const std::exception& err) \
    { \
        QString message; \
        QTextStream strm(&message); \
        strm << tr("Error: ") << err.what(); \
        strm.flush(); \
        QMessageBox::critical(this, action, message); \
    } \
    catch (...) \
    { \
        QMessageBox::critical( \
            this, \
            action, \
            tr("An unexpected or unrecognised error condition was " \
                "encountered")); \
    }

#endif // ppdesktop_errorhandling_h_included
