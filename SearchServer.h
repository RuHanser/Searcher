//Защита от повторного включения заголовочного файла
#pragma once
#include <vector>
#include <string>
//Подключаем заголовочный файл инвертированного индекса
#include "InvertedIndex.h"

//Структура, хранящая информацию о релевантности документа
struct RelativeIndex {
    size_t doc_id;
    float rank;

    //Перегрузка оператора сравнения для тестов
    bool operator==(const RelativeIndex& other) const {
        return doc_id == other.doc_id && rank == other.rank;
    }
};

//Класс поискового сервера
class SearchServer {
public:
    //Конструктор
    SearchServer(const InvertedIndex& idx) : index(idx) {}

    std::vector<std::vector<RelativeIndex>> search(const std::vector<std::string>& queries_input);

private:
    const InvertedIndex& index;
};