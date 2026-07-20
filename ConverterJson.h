#pragma once

#include <vector>
#include <string>

class ConverterJson {
public:
    //Возвращаем содержимое файлов, указанных в config.json
    std::vector<std::string> GetTextDocuments();

    // Возвращаем максимальное количество ответов
    int GetResponsesLimit();

    // Возвращаем список запросов из requests.json
    std::vector<std::string> GetRequests();

    // Записываем результаты поиска в answers.json
    void putAnswers(const std::vector<std::vector<std::pair<int, float>>>& answers);
};

