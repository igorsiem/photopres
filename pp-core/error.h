#include <QtDebug>
#include <QException>
#include <QString>
#include <QTextStream>

#ifndef ppcore_error_h_included
#define ppcore_error_h_included

namespace PhotoPres {

/**
 * @brief An exception signalling a PhotoPres-related error
 */
class Error : public QException
{
    public:

    /**
     * @brief Constructor for an Error exception
     *
     * @param msg A human-readable description of the error condition
     */
    explicit Error(QString msg);

    /**
     * @brief Throw self as an exception
     */
    virtual void raise(void) const override { throw *this; }

    /**
     * @brief Create a clone of self on the stack
     *
     * @return A copy of self, created using `new`
     */
    virtual QException* clone(void) const override { return new Error(*this); }

    /**
     * @brief Retrieve the human-readable error message as a c-string
     *
     * @return A pointer to the human readable error message string
     */
    virtual const char* what(void) const noexcept override
        { return m_message.toStdString().c_str(); }

    /**
     * @brief Reytrieve the error message
     *
     * @return The human-readable error message
     */
    virtual QString message(void) const { return m_message; }

    protected:

    /**
     * @brief Human-readable description of the error condition
     */
    QString m_message;

};  // end Error class

}   // end PhotoPress namespace

#define PP_RAISE_ERROR( msg ) do { \
    QString message; \
    QTextStream strm(&message); \
    strm << msg; \
    qCritical() << __FILE__ << ":" << __LINE__ << " - signalling error: " << \
        message; \
    ::PhotoPres::Error e(message); \
    e.raise(); } while (false)

#endif // ppcore_error_h_included
