#pragma once
#include <cstddef>

struct Entry {
    size_t doc_id;
    size_t count;

    //Оператор сравнения для тестов, которую подключу позже
    bool operator==(const Entry& other) const {
        return doc_id == other.doc_id && count == other.count;
    }
};
