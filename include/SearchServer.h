//Çàùèòà îò ïîâòîðíîãî âêëþ÷åíèÿ çàãîëîâî÷íîãî ôàéëà
#pragma once
#include <vector>
#include <string>
//Ïîäêëþ÷àåì çàãîëîâî÷íûé ôàéë èíâåðòèðîâàííîãî èíäåêñà
#include "InvertedIndex.h"

//Ñòðóêòóðà, õðàíÿùàÿ èíôîðìàöèþ î ðåëåâàíòíîñòè äîêóìåíòà
struct RelativeIndex {
    size_t doc_id;
    float rank;

    //Ïåðåãðóçêà îïåðàòîðà ñðàâíåíèÿ äëÿ òåñòîâ
    bool operator==(const RelativeIndex& other) const {
        return doc_id == other.doc_id && rank == other.rank;
    }
};

//Êëàññ ïîèñêîâîãî ñåðâåðà
class SearchServer {
public:
    //Êîíñòðóêòîð
    SearchServer(const InvertedIndex& idx) : index(idx) {}

    std::vector<std::vector<RelativeIndex>> search(const std::vector<std::string>& queries_input);

private:
    const InvertedIndex& index;
};
