//Подключаем заголовочный файл класса SearchServer
#include "SearchServer.h"
#include <set>
#include <map>
#include <algorithm>
#include <sstream>

//Основной метод поиска
std::vector<std::vector<RelativeIndex>> SearchServer::search(const std::vector<std::string>& queries_input) {
    //Вектор результатов для каждого запроса
    std::vector<std::vector<RelativeIndex>> results;

    //Перебираем все запросы из входного вектора
    for (const auto& query : queries_input) {
        //Создаём поток для разбора строки запроса
        std::istringstream stream(query);
        std::string word;
        std::set<std::string> unique_words;

        while (stream >> word) {
            unique_words.insert(word);
        }

        //Преобразуем множество в вектор для дальнейшей обработки
        std::vector<std::string> words(unique_words.begin(), unique_words.end());

        //Если запрос пуст, добавляем пустой результат
        if (words.empty()) {
            results.push_back({});
            continue;
        }

        //Сортируем слова по возрастанию частоты встречаемости в индексе (от редктх до частых)
        std::sort(words.begin(), words.end(), [this](const std::string& a, const std::string& b) {
            return index.GetWordCount(a).size() < index.GetWordCount(b).size();
            });

        //Карта абсолютной релевантности документов
        std::map<size_t, float> abs_relevance;

        //Для каждого слова в запросе находим документы и количество вхождений
        for (const auto& word : words) {
            auto entries = index.GetWordCount(word);
            for (const auto& entry : entries) {
                abs_relevance[entry.doc_id] += static_cast<float>(entry.count);
            }
        }

        //Если документы не найдены, добавляем пустой результат
        if (abs_relevance.empty()) {
            results.push_back({});
            continue;
        }

        //Находим максимальную абсолютную релевантность среди всех документов
        float max_abs = 0.0f;
        for (const auto& [doc_id, count] : abs_relevance) {
            if (count > max_abs) max_abs = count;
        }

        //Вектор относительной релевантности для текущего запроса
        std::vector<RelativeIndex> rel;
        //Вычисляем относительную релевантность для каждого документа
        for (const auto& [doc_id, count] : abs_relevance) {
            rel.push_back({ doc_id, count / max_abs });
        }

        //Сортируем документы по убыванию релевантности
        std::sort(rel.begin(), rel.end(), [](const RelativeIndex& a, const RelativeIndex& b) {
            return a.rank > b.rank;
            });

        //Добавляем результат текущего запроса в общий список
        results.push_back(rel);
    }

    //Возвращаем все результаты
    return results;
}