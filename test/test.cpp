//Подключаем библиотеки 
#include <gtest/gtest.h>//Google Test для написания и запуска юнит-тестов
#include "InvertedIndex.h"//Подключаем заголовочный файл класса InvertedIndex для темтирования методов
#include "SearchServer.h"//Подключаем заголовочный файл класса SearchServer для темтирования методов

//Первый тест: проверяем корректность работы инвертированного индекса
TEST(InvertedIndexTest, BasicSearch) {
    //Создаём вектор с текстами документов (doc_id будет соответствовать индексу в векторе)
    std::vector<std::string> docs = {
        "london is the capital of great britain",   
        "london london hello world"               
    };
    //Создаём объект инвертированного индекса
    InvertedIndex idx;
    idx.UpdateDocumentBase(docs);
    auto result = idx.GetWordCount("london");//Запрашиваем частоту слвоа

    //Проверяем, что слово встречается в обоих документах
    ASSERT_EQ(result.size(), 2);

    //Проверяем данные для первого документа (doc_id = 0)
    EXPECT_EQ(result[0].doc_id, 0);
    EXPECT_EQ(result[0].count, 1);   

    //Проверяем данные для второго документа (doc_id = 1)
    EXPECT_EQ(result[1].doc_id, 1);
    EXPECT_EQ(result[1].count, 2);  
}

//Второй тест: проверяем корректность работы поискового сервера (такие же документы как в первом тесте)
TEST(SearchServerTest, SimpleQuery) {
    std::vector<std::string> docs = {
        "london is the capital of great britain",
        "london london hello world"
    };

    //Индексируем документы
    InvertedIndex idx;
    idx.UpdateDocumentBase(docs);

    //Создаём поисковый сервер, передавая ему ссылку на индекс
    SearchServer server(idx);
    std::vector<std::string> queries = { "london" };//Запрос со словом london
    auto results = server.search(queries);
    //Должен содержать 1 запрос
    ASSERT_EQ(results.size(), 1);
    //Должно быть найдено 2 документа
    ASSERT_EQ(results[0].size(), 2);

    //Первый документ в выдаче — самый релевантный (doc_id = 1, т.к. содержит 2 вхождения)
    EXPECT_EQ(results[0][0].doc_id, 1);
    EXPECT_FLOAT_EQ(results[0][0].rank, 1.0f);

    //Второй документ не такой релевантный (doc_id = 0, содержит 1 вхождение)
    EXPECT_EQ(results[0][1].doc_id, 0);
    EXPECT_FLOAT_EQ(results[0][1].rank, 0.5f);
}

//Точка входа для запуска тестов Google Test
int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}
