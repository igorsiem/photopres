#include <QtTest>
#include <ppcore.h>

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
    void test_version();

};  // end basic test class

void basic::test_version()
{
    auto v = photopres::ppcore::version();
    QVERIFY(v == "0.1");

}   // end

QTEST_APPLESS_MAIN(basic)

#include "tst_basic.moc"
