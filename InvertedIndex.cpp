//Подключаем заголовочный файл класса InvertedIndex
#include "InvertedIndex.h"
#include <sstream>
#include <algorithm>

//Обновление базы документов и построение инвертированного индекса
void InvertedIndex::UpdateDocumentBase(const std::vector<std::string>& input_docs) {
    //Сохраняем переданные документы в поле класса
    docs = input_docs;
    //Чистим старый словарь 
    freq_dictionary.clear();

    //Перебираем все документы по их индексу
    for (size_t doc_id = 0; doc_id < docs.size(); ++doc_id) {
        //Создаём поток для разбора текущего документа на слова
        std::istringstream stream(docs[doc_id]);
        std::string word;
        //Временный словарь для подсчёта слов в текущем документе
        std::map<std::string, size_t> local_count;

        //Читаем все слова из документа
        while (stream >> word) {
            //Увеличиваем счётчик для каждого слова
            local_count[word]++;
        }

        //Для каждого уникального слова в документе щапишем в словарь 
        for (const auto& [word, count] : local_count) {
            freq_dictionary[word].push_back({ doc_id, count });
        }
    }
}

//Получение частоты слова во всех документах
std::vector<Entry> InvertedIndex::GetWordCount(const std::string& word) const {
    //Ищем слово в частотном словаре
    auto it = freq_dictionary.find(word);
    //Если слово найдено -> вектор записей
    if (it != freq_dictionary.end()) {
        return it->second;
    }
    //Если слово не найдено -> пустой вектор
    return {};
}