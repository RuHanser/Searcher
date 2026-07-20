//Ïîäêëþ÷àåì çàãîëîâî÷íûé ôàéë êëàññà InvertedIndex
#include "InvertedIndex.h"
#include <sstream>
#include <algorithm>

//Îáíîâëåíèå áàçû äîêóìåíòîâ è ïîñòðîåíèå èíâåðòèðîâàííîãî èíäåêñà
void InvertedIndex::UpdateDocumentBase(const std::vector<std::string>& input_docs) {
    //Ñîõðàíÿåì ïåðåäàííûå äîêóìåíòû â ïîëå êëàññà
    docs = input_docs;
    //×èñòèì ñòàðûé ñëîâàðü 
    freq_dictionary.clear();

    //Ïåðåáèðàåì âñå äîêóìåíòû ïî èõ èíäåêñó
    for (size_t doc_id = 0; doc_id < docs.size(); ++doc_id) {
        //Ñîçäà¸ì ïîòîê äëÿ ðàçáîðà òåêóùåãî äîêóìåíòà íà ñëîâà
        std::istringstream stream(docs[doc_id]);
        std::string word;
        //Âðåìåííûé ñëîâàðü äëÿ ïîäñ÷¸òà ñëîâ â òåêóùåì äîêóìåíòå
        std::map<std::string, size_t> local_count;

        //×èòàåì âñå ñëîâà èç äîêóìåíòà
        while (stream >> word) {
            //Óâåëè÷èâàåì ñ÷¸ò÷èê äëÿ êàæäîãî ñëîâà
            local_count[word]++;
        }

        //Äëÿ êàæäîãî óíèêàëüíîãî ñëîâà â äîêóìåíòå ùàïèøåì â ñëîâàðü 
        for (const auto& [word, count] : local_count) {
            freq_dictionary[word].push_back({ doc_id, count });
        }
    }
}

//Ïîëó÷åíèå ÷àñòîòû ñëîâà âî âñåõ äîêóìåíòàõ
std::vector<Entry> InvertedIndex::GetWordCount(const std::string& word) const {
    //Èùåì ñëîâî â ÷àñòîòíîì ñëîâàðå
    auto it = freq_dictionary.find(word);
    //Åñëè ñëîâî íàéäåíî -> âåêòîð çàïèñåé
    if (it != freq_dictionary.end()) {
        return it->second;
    }
    //Åñëè ñëîâî íå íàéäåíî -> ïóñòîé âåêòîð
    return {};
}
