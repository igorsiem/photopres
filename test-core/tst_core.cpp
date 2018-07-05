#include <QString>
#include <QTextStream>
#include <QtTest>
#include <core.h>

/**
 * @brief Tests for the functionality of the core library
 */
class core_tests : public QObject
{
    Q_OBJECT

    private slots:

    // --- Misc. Tests ---

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

    // --- Metadata Item ---

};  // end core_tests test class

void core_tests::test_version(void)
{
    QVERIFY(PhotoPres::Core::version() == "0.1");
}   // end version test

void core_tests::test_text_stream(void)
{
    QString buffer;
    QTextStream strm(&buffer);
    strm << "Hello, there - " << 1 << " - " << 2 << " - " << 3;
    strm.flush();

    QCOMPARE(buffer, "Hello, there - 1 - 2 - 3");
}   // end text stream test

void core_tests::test_error(void)
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

QTEST_APPLESS_MAIN(core_tests)

#include "tst_core.moc"
