#pragma once
#include <vector>
#include <string>
#include <map>
#include "Entry.h"

class InvertedIndex {
public:
    InvertedIndex() = default;

    //Обновляем базу документов и получаем инвертированный индекс
    void UpdateDocumentBase(const std::vector<std::string>& input_docs);

    //Возвращаем частоту повторения слова во всех документах
    std::vector<Entry> GetWordCount(const std::string& word) const;

private:
    std::vector<std::string> docs;//Содержимое документов
    std::map<std::string, std::vector<Entry>> freq_dictionary;//Частотный словарь
};
