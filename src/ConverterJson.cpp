//Ïîäêëþ÷àåì çàãîëîâî÷íûé ôàéë êëàññà
#include "ConverterJson.h"
//Ïîäêëþ÷àåì áèáëèîòåêó nlohmann/json äëÿ ðàáîòû ñ JSON
#include <nlohmann/json.hpp>
#include <fstream>
#include <iostream>
#include <sstream>

//Ñîêðàùàåì äëèííîå íàçâàíèå áèáëèîòåêè
using json = nlohmann::json;

//×òåíèå ñîäåðæèìîãî ôàéëîâ, óêàçàííûõ â ôàéäàõ config
std::vector<std::string> ConverterJson::GetTextDocuments() {
    std::vector<std::string> texts;
    //Îòêðûâàåì
    std::ifstream file("config.json");
    if (!file.is_open()) {
        std::cerr << "config.json not found!\n";
        return texts;
    }
    //Ïîëó÷àåì ñòðóêòóðó äàííûõ
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

//×òåíèå ìàêñèìàëüíîãî êîëè÷åñòâà îòâåòîâ èç config
int ConverterJson::GetResponsesLimit() {
    std::ifstream file("config.json");
    if (!file.is_open()) return 5;

    json data;
    file >> data;
    return data["config"].value("max_responses", 5);
}

//×òåíèå çàïðîñîâ èç requests
std::vector<std::string> ConverterJson::GetRequests() {
    std::vector<std::string> requests;
    std::ifstream file("requests.json");
    if (!file.is_open()) return requests;

    json data;
    file >> data;
    //Çàïîëíÿåì âåêòîð çàïðîñàìè èç ìàññèâà
    for (const auto& req : data["requests"]) {
        requests.push_back(req.get<std::string>());
    }
    return requests;
}

//Çàïèñü ðåçóëüòàòîâ â answers
void ConverterJson::putAnswers(const std::vector<std::vector<std::pair<int, float>>>& answers) {
    json result;
    int i = 1;
    //Äëÿ êàæäîãî çàïðîñà, îòâåò
    for (const auto& answer : answers) {
        std::string key = "request" + std::string(3 - std::to_string(i).length(), '0') + std::to_string(i);
        if (answer.empty()) {
            //Åñëè äîêóìåíòîâ íåò -false
            result["answers"][key]["result"] = false;
        }
        else {
            //Åñëè äîêóìåíòû íàéäåíû - true è ñïèñîê relevance
            result["answers"][key]["result"] = true;
            for (const auto& [docid, rank] : answer) {
                result["answers"][key]["relevance"].push_back({ {"docid", docid}, {"rank", rank} });
            }
        }
        i++;
    }

    //Çàïèñûâàåì ðåçóëüòàò â ôàéë ñ îòñòóïîì 4 ïðîáåëà
    std::ofstream file("answers.json");
    file << result.dump(4);
}
