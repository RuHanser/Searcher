#pragma once
#include <vector>
#include <string>
#include <map>
#include "Entry.h"

class InvertedIndex {
public:
    InvertedIndex() = default;

    //Îáíîâëÿåì áàçó äîêóìåíòîâ è ïîëó÷àåì èíâåðòèðîâàííûé èíäåêñ
    void UpdateDocumentBase(const std::vector<std::string>& input_docs);

    //Âîçâðàùàåì ÷àñòîòó ïîâòîðåíèÿ ñëîâà âî âñåõ äîêóìåíòàõ
    std::vector<Entry> GetWordCount(const std::string& word) const;

private:
    std::vector<std::string> docs;//Ñîäåðæèìîå äîêóìåíòîâ
    std::map<std::string, std::vector<Entry>> freq_dictionary;//×àñòîòíûé ñëîâàðü
};
