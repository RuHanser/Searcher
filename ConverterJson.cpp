//Подключаем заголовочный файл класса
#include "ConverterJson.h"
//Подключаем библиотеку nlohmann/json для работы с JSON
#include <nlohmann/json.hpp>
#include <fstream>
#include <iostream>
#include <sstream>

//Сокращаем длинное название библиотеки
using json = nlohmann::json;

//Чтение содержимого файлов, указанных в файдах config
std::vector<std::string> ConverterJson::GetTextDocuments() {
    std::vector<std::string> texts;
    //Открываем
    std::ifstream file("config.json");
    if (!file.is_open()) {
        std::cerr << "config.json not found!\n";
        return texts;
    }
    //Получаем структуру данных
    json data;
    file >> data;

    for (const auto& path : data["files"]) {
        std::ifstream doc(path.get<std::string>());
        if (doc.is_open()) {
            std::stringstream buffer;
            buffer << doc.rdbuf();
            texts.push_back(buffer.str());
        }
        else {
            std::cerr << "File not found: " << path.get<std::string>() << '\n';
        }
    }
    return texts;
}

//Чтение максимального количества ответов из config
int ConverterJson::GetResponsesLimit() {
    std::ifstream file("config.json");
    if (!file.is_open()) return 5;

    json data;
    file >> data;
    return data["config"].value("max_responses", 5);
}

//Чтение запросов из requests
std::vector<std::string> ConverterJson::GetRequests() {
    std::vector<std::string> requests;
    std::ifstream file("requests.json");
    if (!file.is_open()) return requests;

    json data;
    file >> data;
    //Заполняем вектор запросами из массива
    for (const auto& req : data["requests"]) {
        requests.push_back(req.get<std::string>());
    }
    return requests;
}

//Запись результатов в answers
void ConverterJson::putAnswers(const std::vector<std::vector<std::pair<int, float>>>& answers) {
    json result;
    int i = 1;
    //Для каждого запроса, ответ
    for (const auto& answer : answers) {
        std::string key = "request" + std::string(3 - std::to_string(i).length(), '0') + std::to_string(i);
        if (answer.empty()) {
            //Если документов нет -false
            result["answers"][key]["result"] = false;
        }
        else {
            //Если документы найдены - true и список relevance
            result["answers"][key]["result"] = true;
            for (const auto& [docid, rank] : answer) {
                result["answers"][key]["relevance"].push_back({ {"docid", docid}, {"rank", rank} });
            }
        }
        i++;
    }

    //Записываем результат в файл с отступом 4 пробела
    std::ofstream file("answers.json");
    file << result.dump(4);
}