#include <QString>
#include <QtTest>
#include <core.h>

namespace pp = PhotoPres;

/**
 * @brief Tests of Metadata functionality in the Core library
 *
 * @todo Test for Metadata file writing and reading
 */
class MetadataCoreTest : public QObject
{
    Q_OBJECT

    private Q_SLOTS:

    /**
     * @brief Create / Retrieve / Update / Delete tests
     */
    void crud(void);

};  // end MetadataCoreTest class

void MetadataCoreTest::crud(void)
{
    namespace pp = PhotoPres;

    pp::Metadata md(QDir("."));

    // Test no entry
    QCOMPARE(md.caption("abc"), "");

    // Create a new entry
    md.setCaption("abc", "Hello, there");

    // Retrieve existing entry
    QCOMPARE(md.caption("abc"), "Hello, there");

    // Check another non-existent entry.
    QCOMPARE(md.caption("xyz"), "");

    // Update an existing entry and check it.
    md.setCaption("abc", "Goodbye");
    QCOMPARE(md.caption("abc"), "Goodbye");

    // Erase a caption
    md.eraseCaption(("abc"));
    QCOMPARE(md.caption("abc"), "");
}   // end crud test

QTEST_APPLESS_MAIN(MetadataCoreTest)

#include "metadatacoretest.moc"
