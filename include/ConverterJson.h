#pragma once

#include <vector>
#include <string>

class ConverterJson {
public:
    //Âîçâðàùàåì ñîäåðæèìîå ôàéëîâ, óêàçàííûõ â config.json
    std::vector<std::string> GetTextDocuments();

    // Âîçâðàùàåì ìàêñèìàëüíîå êîëè÷åñòâî îòâåòîâ
    int GetResponsesLimit();

    // Âîçâðàùàåì ñïèñîê çàïðîñîâ èç requests.json
    std::vector<std::string> GetRequests();

    // Çàïèñûâàåì ðåçóëüòàòû ïîèñêà â answers.json
    void putAnswers(const std::vector<std::vector<std::pair<int, float>>>& answers);
};

