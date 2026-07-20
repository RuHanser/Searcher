#include <iostream>
#include "ConverterJson.h"
#include "InvertedIndex.h"
#include "SearchServer.h"

int main() {
    //Создаём объект для работы с JSON-файлами
    ConverterJson converter;

    //Считываем документы из config.json и выводим их содержимое
    std::cout << "=== Indexing documents ===\n";
    auto docs = converter.GetTextDocuments();
    for (size_t i = 0; i < docs.size(); ++i) {
        std::cout << "Doc " << i << ": " << docs[i] << '\n';
    }

    //Строим инвертированный индекс на основе загруженных документов
    InvertedIndex idx;
    idx.UpdateDocumentBase(docs);

    //Считываем запросы из requests.json и выводим их
    std::cout << "\n=== Requests ===\n";
    auto requests = converter.GetRequests();
    for (const auto& req : requests) {
        std::cout << req << '\n';
    }

    //Выполняем поиск по запросам
    SearchServer server(idx);
    auto results = server.search(requests);

    //Преобразуем RelativeIndex в вид для записи в JSON
    std::vector<std::vector<std::pair<int, float>>> converted_results;
    for (const auto& query_result : results) {
        std::vector<std::pair<int, float>> converted_query;
        for (const auto& rel : query_result) {
            converted_query.push_back({ static_cast<int>(rel.doc_id), rel.rank });
        }
        converted_results.push_back(converted_query);
    }

    //Записываем результаты в answers
    std::cout << "\n=== Writing answers.json ===\n";
    converter.putAnswers(converted_results);
    std::cout << "Done!\n";

    return 0;
}
