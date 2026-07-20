//Ïîäêëþ÷àåì çàãîëîâî÷íûé ôàéë êëàññà SearchServer
#include "SearchServer.h"
#include <set>
#include <map>
#include <algorithm>
#include <sstream>

//Îñíîâíîé ìåòîä ïîèñêà
std::vector<std::vector<RelativeIndex>> SearchServer::search(const std::vector<std::string>& queries_input) {
    //Âåêòîð ðåçóëüòàòîâ äëÿ êàæäîãî çàïðîñà
    std::vector<std::vector<RelativeIndex>> results;

    //Ïåðåáèðàåì âñå çàïðîñû èç âõîäíîãî âåêòîðà
    for (const auto& query : queries_input) {
        //Ñîçäà¸ì ïîòîê äëÿ ðàçáîðà ñòðîêè çàïðîñà
        std::istringstream stream(query);
        std::string word;
        std::set<std::string> unique_words;

        while (stream >> word) {
            unique_words.insert(word);
        }

        //Ïðåîáðàçóåì ìíîæåñòâî â âåêòîð äëÿ äàëüíåéøåé îáðàáîòêè
        std::vector<std::string> words(unique_words.begin(), unique_words.end());

        //Åñëè çàïðîñ ïóñò, äîáàâëÿåì ïóñòîé ðåçóëüòàò
        if (words.empty()) {
            results.push_back({});
            continue;
        }

        //Ñîðòèðóåì ñëîâà ïî âîçðàñòàíèþ ÷àñòîòû âñòðå÷àåìîñòè â èíäåêñå (îò ðåäêòõ äî ÷àñòûõ)
        std::sort(words.begin(), words.end(), [this](const std::string& a, const std::string& b) {
            return index.GetWordCount(a).size() < index.GetWordCount(b).size();
            });

        //Êàðòà àáñîëþòíîé ðåëåâàíòíîñòè äîêóìåíòîâ
        std::map<size_t, float> abs_relevance;

        //Äëÿ êàæäîãî ñëîâà â çàïðîñå íàõîäèì äîêóìåíòû è êîëè÷åñòâî âõîæäåíèé
        for (const auto& word : words) {
            auto entries = index.GetWordCount(word);
            for (const auto& entry : entries) {
                abs_relevance[entry.doc_id] += static_cast<float>(entry.count);
            }
        }

        //Åñëè äîêóìåíòû íå íàéäåíû, äîáàâëÿåì ïóñòîé ðåçóëüòàò
        if (abs_relevance.empty()) {
            results.push_back({});
            continue;
        }

        //Íàõîäèì ìàêñèìàëüíóþ àáñîëþòíóþ ðåëåâàíòíîñòü ñðåäè âñåõ äîêóìåíòîâ
        float max_abs = 0.0f;
        for (const auto& [doc_id, count] : abs_relevance) {
            if (count > max_abs) max_abs = count;
        }

        //Âåêòîð îòíîñèòåëüíîé ðåëåâàíòíîñòè äëÿ òåêóùåãî çàïðîñà
        std::vector<RelativeIndex> rel;
        //Âû÷èñëÿåì îòíîñèòåëüíóþ ðåëåâàíòíîñòü äëÿ êàæäîãî äîêóìåíòà
        for (const auto& [doc_id, count] : abs_relevance) {
            rel.push_back({ doc_id, count / max_abs });
        }

        //Ñîðòèðóåì äîêóìåíòû ïî óáûâàíèþ ðåëåâàíòíîñòè
        std::sort(rel.begin(), rel.end(), [](const RelativeIndex& a, const RelativeIndex& b) {
            return a.rank > b.rank;
            });

        //Äîáàâëÿåì ðåçóëüòàò òåêóùåãî çàïðîñà â îáùèé ñïèñîê
        results.push_back(rel);
    }

    //Âîçâðàùàåì âñå ðåçóëüòàòû
    return results;
}
