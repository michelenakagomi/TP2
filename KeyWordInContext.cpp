// KWIC - Estilo Bulletin Board em C++
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <functional>
#include <algorithm>
#include <cctype>
#include <any>

#include <Windows.h>



class EventManager {
public:
    void subscribe(const std::string& event_type, std::function<void(const std::pair<std::string, std::any>&)> handler) {
        subscriptions[event_type].push_back(handler);
    }

    void publish(const std::pair<std::string, std::any>& event) {
        auto it = subscriptions.find(event.first);
        if (it != subscriptions.end()) {
            for (auto& handler : it->second) {
                handler(event);
            }
        }
    }

private:
    std::unordered_map<std::string, std::vector<std::function<void(const std::pair<std::string, std::any>&)>>> subscriptions;
};

class DataStorage {
public:
    DataStorage(EventManager& evt) : event_manager(evt) {
        event_manager.subscribe("load", [this](auto event) { load(event); });
        event_manager.subscribe("start", [this](auto event) { separateWords(event); });
        event_manager.subscribe("store", [this](auto event) { storeKeywordTitle(event); });
    }

private:
    EventManager& event_manager;
    std::vector<std::string> titulos;
    std::vector<std::string> keyword_titles;

    void load(const std::pair<std::string, std::any>& event) {
        std::string path = std::any_cast<std::string>(event.second);
        std::ifstream file(path);
        std::string line;
        while (std::getline(file, line)) {
            titulos.push_back(line);
        }
    }

    void separateWords(const std::pair<std::string, std::any>&) {
        for (auto& titulo : titulos) {
            std::istringstream iss(titulo);
            std::vector<std::string> palavras;
            std::string palavra;
            while (iss >> palavra) {
                palavras.push_back(palavra);
            }
            event_manager.publish({"separatekeyword", palavras});
        }
        event_manager.publish({"print", keyword_titles});
    }

    void storeKeywordTitle(const std::pair<std::string, std::any>& event) {
        keyword_titles.push_back(std::any_cast<std::string>(event.second));
        std::sort(keyword_titles.begin(), keyword_titles.end());
    }
};

class KeyWordSeparator {
public:
    KeyWordSeparator(EventManager& evt) : event_manager(evt) {
        event_manager.subscribe("separatekeyword", [this](auto event) { createTuples(event); });
    }

private:
    EventManager& event_manager;

    void createTuples(const std::pair<std::string, std::any>& event) {
        auto palavras = std::any_cast<std::vector<std::string>>(event.second);
        for (const auto& palavra : palavras) {
            event_manager.publish({"filter", std::make_pair(palavra, palavras)});
        }
    }
};

class StopWordFilter {
public:
    StopWordFilter(EventManager& evt) : event_manager(evt) {
        event_manager.subscribe("filter", [this](auto event) { filterStopWord(event); });
        stopwords = {"a","o","as","os","um","uma","é","de","do","da","dos","das",
                     "em","no","na","nos","nas","por","para","com","sem","sob","sobre",
                     "the","is","and","of","to","in","it","that","on","sat",};
    }

private:
    EventManager& event_manager;
    std::vector<std::string> stopwords;

    void filterStopWord(const std::pair<std::string, std::any>& event) {
        auto[palavra, lista] = std::any_cast<std::pair<std::string, std::vector<std::string>>>(event.second);
        std::string palavra_lower = palavra;
        std::transform(palavra_lower.begin(), palavra_lower.end(), palavra_lower.begin(), ::tolower);
        if (std::find(stopwords.begin(), stopwords.end(), palavra_lower) == stopwords.end()) {
            event_manager.publish({"circle", std::make_pair(palavra, lista)});
        }
    }
};

class CircleWords {
public:
    CircleWords(EventManager& evt) : event_manager(evt) {
        event_manager.subscribe("circle", [this](auto event) { circleWords(event); });
    }

private:
    EventManager& event_manager;

    void circleWords(const std::pair<std::string, std::any>& event) {
        auto[keyword, lista] = std::any_cast<std::pair<std::string, std::vector<std::string>>>(event.second);
        auto it = std::find(lista.begin(), lista.end(), keyword);
        if (it != lista.end()) {
            size_t index = std::distance(lista.begin(), it);
            std::vector<std::string> rotated;
            rotated.insert(rotated.end(), lista.begin() + index, lista.end());
            rotated.insert(rotated.end(), lista.begin(), lista.begin() + index);
            std::ostringstream oss;
            for (size_t i = 0; i < rotated.size(); ++i) {
                oss << rotated[i];
                if (i < rotated.size() - 1)
                    oss << " ";
            }
            event_manager.publish({"store", oss.str()});
        }
    }
};

class WordFrequencyApplication {
public:
    WordFrequencyApplication(EventManager& evt) : event_manager(evt) {
        event_manager.subscribe("run", [this](auto event) { run(event); });
        event_manager.subscribe("print", [this](auto event) { stop(event); });
    }

private:
    EventManager& event_manager;

    void run(const std::pair<std::string, std::any>& event) {
        std::string path = std::any_cast<std::string>(event.second);
        event_manager.publish({"load", path});
        event_manager.publish({"start", {}});
    }

    void stop(const std::pair<std::string, std::any>& event) {
        for (const auto& s : std::any_cast<std::vector<std::string>>(event.second)) {
            std::cout << s << std::endl;
        }
    }
};

int main(int argc, char* argv[]) {
    SetConsoleOutputCP(CP_UTF8);
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <input_file>" << std::endl;
        return 1;
    }

    EventManager em;
    DataStorage ds(em);
    KeyWordSeparator ks(em);
    StopWordFilter sf(em);
    CircleWords cw(em);
    WordFrequencyApplication app(em);

    em.publish({"run", std::string(argv[1])});

    return 0;
}
