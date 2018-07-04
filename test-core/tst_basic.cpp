#include <QString>
#include <QTextStream>
#include <QtTest>
#include <core.h>

/**
 * @brief Tests for the basic functionality of the core library
 */
class basic : public QObject
{
    Q_OBJECT

private slots:

    /**
     * @brief Verify the functionality of the static version string retrieval
     */
    void test_version(void);

    /**
     * @brief Verify the functionality of the `QTextStream` class
     *
     * We want to use `QTextStream` for text streaming operations in a variety
     * of contexts. This test simply verifies that it operates as expected.
     */
    void test_text_stream(void);

    /**
     * @brief Verify that the error-raising macro works as expected
     */
    void test_error(void);

};  // end basic test class

void basic::test_version(void)
{
    QVERIFY(PhotoPres::Core::version() == "0.1");
}   // end version test

void basic::test_text_stream(void)
{
    QString buffer;
    QTextStream strm(&buffer);
    strm << "Hello, there - " << 1 << " - " << 2 << " - " << 3;
    strm.flush();

    QCOMPARE(buffer, "Hello, there - 1 - 2 - 3");
}   // end text stream test

void basic::test_error(void)
{
    try
    {
        PP_RAISE_ERROR("This is error #" << 1);
        QFAIL("exception was not thrown as expected");
    }
    catch (const PhotoPres::Error& err)
    {
        QCOMPARE(err.message(), "This is error #1");
    }
    catch (...)
    {
        QFAIL("a PhotoPres::Error exception was expected, but some other type "
             "of exception was thrown");
    }
}   // end error test

QTEST_APPLESS_MAIN(basic)

#include "tst_basic.moc"
