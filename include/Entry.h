#pragma once
#include <cstddef>

struct Entry {
    size_t doc_id;
    size_t count;

    //Îïåðàòîð ñðàâíåíèÿ äëÿ òåñòîâ, êîòîðóþ ïîäêëþ÷ó ïîçæå
    bool operator==(const Entry& other) const {
        return doc_id == other.doc_id && count == other.count;
    }
};
