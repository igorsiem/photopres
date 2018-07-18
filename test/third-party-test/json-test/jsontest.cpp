// #include <sstream>
// #include <iomanip>

#include <QString>
#include <QtTest>

#include <nlohmann/json.hpp>

/**
 * @brief Simple tests for third-party JSON library
 */
class JsonTest : public QObject
{
    Q_OBJECT

    private Q_SLOTS:

    /**
     * @brief Verify basic Create, Retrieve, Update and Delete functionality
     */
    void crud();
};  // end JsonTest class


void JsonTest::crud()
{

    using json = nlohmann::json;

    try
    {
        // Assemble a simple JSON object
        json j;

        j["pi"] = 3.141;
        j["happy"] = true;
        j["name"] = "Igor";
        j["nothing"] = nullptr;
        j["answer"]["everything"] = 42;
        j["list"] = {1, 0, 2};
        j["object"] = { { "currency", "USD"}, { "value", 42.99 }};

        // Check some of its elements
        QVERIFY(j["pi"] == 3.141);
        QVERIFY(j["happy"] == true);
        QVERIFY(j["answer"]["everything"] == 42);

        // Check the 'find' method.
        QVERIFY(j.find("pi") != j.end());
        QVERIFY(j.find("xyz") == j.end());

        // Erase an element
        QVERIFY(j["answer"].size() == 1);
        j["answer"].erase("everything");
        QVERIFY(j["answer"].size() == 0);
        QVERIFY(j["answer"].find("everything") == j["answer"].end());

        // std::stringstream strm;
        // strm << std::setw(4) << j;
        // qDebug() << strm.str().c_str();

    }
    catch (...)
    {
        QFAIL("an exception was thrown when no exception was expected");
    }

}   // end crud test method

QTEST_APPLESS_MAIN(JsonTest)

#include "jsontest.moc"
