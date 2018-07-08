#include <QString>
#include <QtTest>
#include <core.h>

namespace pp = PhotoPres;

/**
 * @brief Tests of Metadata functionality in the Core library
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

    // Create an MI map with two non-empty entries and an empty entry
    pp::MetadataItemMap miMap(
    {
        {"a", "1"},
        {"b", ""},      // note blank item
        {"d", "4"}
    });

    QVERIFY(miMap.size() == 3);
    QVERIFY(pp::sizeNotEmpty(miMap) == 2);

    // The 'hasItem' function will find an item with name "a", but not for
    // names "b" or "c".
    QVERIFY(pp::hasItemNotEmpty(miMap, "a") == true);
    QVERIFY(pp::hasItemNotEmpty(miMap, "b") == false);
    QVERIFY(pp::hasItemNotEmpty(miMap, "c") == false);
    QVERIFY(pp::hasItemNotEmpty(miMap, "d") == true);

    // Verify the 'for_each' function for metadata maps - lambda is only called
    // for the items with non-empty values.
    int counter = 0;
    pp::forEachNotEmpty(miMap, [&counter](const QString& , const QString& value)
    {
        counter++;
        QVERIFY2(value.isEmpty() == false, "for_each processed an item with an "
                 "empty value");
    });

    QVERIFY2(counter == 2, "for_each processed an incorrect number of items "
             "(expected 2)");

    // Verify 'for_each' with a value-updating function, to append a string to
    // one of the values.
    pp::forEachNotEmpty(miMap, [](const QString& name, QString& value)
    {
        if (name == "d") value += "x";
    });

    QVERIFY(miMap["d"] == "4x");

    // Find operations succeed for non-empty items - fail for empty /
    // non-existent items.
    QVERIFY(*pp::findNotEmpty(miMap, "a") == "1");
    QVERIFY(!pp::findNotEmpty(miMap, "b"));
    QVERIFY(!pp::findNotEmpty(miMap, "c"));
    QVERIFY(*pp::findNotEmpty(miMap, "d") == "4x");

    // Erase the "a" item
    pp::erase(miMap, "a");
    QVERIFY(!pp::findNotEmpty(miMap, "a"));

}   // end crud test

QTEST_APPLESS_MAIN(MetadataCoreTest)

#include "metadatacoretest.moc"
