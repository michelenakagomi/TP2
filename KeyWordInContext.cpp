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

#include <Windows.h> // include para suportar a saída do UTF-8 no Windows

// Classe do Quadro de avisos (Bulletin Board), gerencia a inscrição e a publicação dos eventos 
class EventManager {
public:
    
    /* Método para inscrever um handler para um tipo de evento
     Recebe:
     event_type -> string que identifica o tipo do evento
     handler -> uma função que será chamada quando o evento ocorrer
              O handler recebe um par, onde o primeiro elemento é o tipo do evento e
              o segundo é associado ao evento 
   */
    void subscribe(const std::string& event_type, std::function<void(const std::pair<std::string, std::any>&)> handler) {
        subscriptions[event_type].push_back(handler); // Adiciona o handler no map de subscriptions
    }

    /* Método para publicar um evento
       Recebe:   
       event -> um par contendo o tipo do evento e os dados do evento
    */
    void publish(const std::pair<std::string, std::any>& event) {
        auto it = subscriptions.find(event.first); // Procura se existem inscritos para o tipo de evento
        if (it != subscriptions.end()) {
            for (auto& handler : it->second) { // Itera sobre todos os handlers inscritos
                handler(event);                // Chama cada handler, passando o evento
            }
        }
    }

private:
    /* Mapa que armazena as inscrições
     A chave é o tipo do evento
     O valor é um vetor de funções que devem ser chamadas ao chamar o método publish
    */
    std::unordered_map<std::string, std::vector<std::function<void(const std::pair<std::string, std::any>&)>>> subscriptions;

    friend class EventManagerTests_Subscriptions_Test; //Classe para uso em testes unitários
};

// Classe Responsável por carregar os títulos, iniciar o processamento e armazenar os resultados.
class DataStorage {
public:
    // Construtor da classe com referência a classe EventManager
    DataStorage(EventManager& evt) : event_manager(evt) {
        event_manager.subscribe("load", [this](auto event) { load(event); });               // Inscreve o método load para ser chamado quando o evento "load" for publicado.
        event_manager.subscribe("start", [this](auto event) { separateWords(event); });     // Inscreve o método separateWords para ser chamado quando o evento "start" for publicado.
        event_manager.subscribe("store", [this](auto event) { storeKeywordTitle(event); }); // Inscreve o método storeKeywordTitle para ser chamado quando o evento "store" for publicado.
    }

private:
    //Classes para uso em testes unitários
    friend class DataStorageTests_Load_Test;
    friend class DataStorageTests_SeparateWords_Test;
    friend class DataStorageTests_StoreKeywordTitle_Test;
    friend class IntegrationTest_FullPipeline_Test;


    EventManager& event_manager; 
    std::vector<std::string> titulos; // Vetor para armazenar os titulos lidos do arquivo input.txt
    std::vector<std::string> keyword_titles; // Vetor para armazenar as palavras chaves já rotacionadas

    // Método chamado pelo evento "load"
    // Lê o arquivo input.txt -> extrai as linhas (titulos) -> armazena na lista de titulos
    void load(const std::pair<std::string, std::any>& event) {
        std::string path = std::any_cast<std::string>(event.second);
        std::ifstream file(path);
        std::string line;
        while (std::getline(file, line)) { // Lê linha por linha do arquivo
            titulos.push_back(line); // Adiciona as linhas lidas (titulos) no vetor de titulos -> ["The quick brown fox"]
        }
    }

    // Método chamado pelo evento "start"
    // Recebe a lista de titulos -> separa o titulo em palavras separadas
    void separateWords(const std::pair<std::string, std::any>&) {
        for (auto& titulo : titulos) {
            std::istringstream iss(titulo);
            std::vector<std::string> palavras; // Vetor para armazenar as palavras separadas de cada titulo
            std::string palavra;
            while (iss >> palavra) { // Extrai as palavras de cada titulo
                palavras.push_back(palavra); // Armazena no vetor de palavras separadas -> ["The", "quick", "brown", "fox"]
            }
            // Publica um evento para cada palavra separada
            event_manager.publish({"separatekeyword", palavras});
        }
        // Publica um evento para printar as palavras já ordenadas ("print final")
        event_manager.publish({"print", keyword_titles});
    }

    // Método chamado pelo evento "store"
    // Pega os titulos já ciclados -> coloca no vetor -> ordena em ordem alfabética
    void storeKeywordTitle(const std::pair<std::string, std::any>& event) {
        keyword_titles.push_back(std::any_cast<std::string>(event.second)); // Adiciona o titulo
        std::sort(keyword_titles.begin(), keyword_titles.end()); // Faz a ordenação alfabética
    }
};

// Classe responsável por pegar uma lista de palavras de um título e gerar pares para fazer a filtragem de stopwords
class KeyWordSeparator {
public:
    KeyWordSeparator(EventManager& evt) : event_manager(evt) {
        event_manager.subscribe("separatekeyword", [this](auto event) { createTuples(event); }); // Inscreve o método createTuples para ser chamado quando o evento "separatekeyword" for publicado
    }

private:
    EventManager& event_manager;

    // Método chamado pelo evento "separatekeyword"
    // Recebe o vetor de palavras -> para cada palavra no vetor -> gera um par de uma palavra e o vetor original de palavras do titulo
    void createTuples(const std::pair<std::string, std::any>& event) {
        auto palavras = std::any_cast<std::vector<std::string>>(event.second); // Extrai o vetor de palavras
        for (const auto& palavra : palavras) {
            event_manager.publish({"filter", std::make_pair(palavra, palavras)}); // publica um evento "filter" de cada par gerado -> ("The",["The", "quick", "brown", "fox"])
        }
    }
};

// Classe responsável por filtrar as stopwords
class StopWordFilter {
public:
    StopWordFilter(EventManager& evt) : event_manager(evt) {
        event_manager.subscribe("filter", [this](auto event) { filterStopWord(event); }); // Inscreve o método filterStopWord para ser chamado quando o evento "filter" for publicado
        stopwords = {"a","o","as","os","um","uma","é","de","do","da","dos","das",
                     "em","no","na","nos","nas","por","para","com","sem","sob","sobre",
                     "the","is","and","of","to","in","it","that","on","sat",}; // Lista de StopWords
    }

private:
    friend class IntegrationTest_FullPipeline_Test; // Classe para uso de testes unitários

    EventManager& event_manager;
    std::vector<std::string> stopwords; // Vetor para armazenar as stopwords
    std::vector<std::pair<std::string, std::string>> keywordNcontextList; // Vetor para armazenar a palavra e o titulo de onde ela vem
    
    // Método chamado pelo evento "filter" verifica se uma palavra é stopword
    void filterStopWord(const std::pair<std::string, std::any>& event) {
        auto[palavra, lista] = std::any_cast<std::pair<std::string, std::vector<std::string>>>(event.second); // Extrai a palavra chave e a lista de palavras do titulo
        std::string palavra_lower = palavra; // Cria uma cópia da palavra para converter para minúscula
        std::transform(palavra_lower.begin(), palavra_lower.end(), palavra_lower.begin(), ::tolower); // Converte a palavra para minúscula
        if (std::find(stopwords.begin(), stopwords.end(), palavra_lower) == stopwords.end()) { // Condição para verificar se é uma stopword
            std::ostringstream oss; // Cria um stream de string para reconstruir o titulo
            for (size_t i = 0; i < lista.size(); ++i) {
                if (i > 0) oss << ' '; // Adiciona um espaço entre as palavras
                oss << lista[i]; // Adiciona a palavra no stream
            }
            std::string result = oss.str(); // Obtém o titulo original como string
            keywordNcontextList.push_back(std::make_pair(palavra, result)); // Armazena o par no vetor -> (keyword, titulo original de onde ela vem)

            // Ordena a lista de pares pela keyword
            std::sort(keywordNcontextList.begin(), keywordNcontextList.end(),
            [](const auto& a, const auto& b) {
                return a.first < b.first;
            });
            event_manager.publish({"circle", std::make_pair(palavra, lista)}); // Publica o evento "circle" com a keyword e a lista original de palavras do titulo -> ("quick", ["The", "quick", "brown", "fox"])
        }
    }
};

// Classe responsável por realizar o deslocamento circular das palavras de um título
class CircleWords {
public:
    CircleWords(EventManager& evt) : event_manager(evt) {
        event_manager.subscribe("circle", [this](auto event) { circleWords(event); }); // Inscreve o método circleWords para ser chamado quando o evento "circle" for publicado
    }

private:
    EventManager& event_manager;

    // Método chamado pelo evento "circle" que gera a linha rotacionada
    void circleWords(const std::pair<std::string, std::any>& event) {
        auto[keyword, lista] = std::any_cast<std::pair<std::string, std::vector<std::string>>>(event.second); // Extrai a keyword e a lista de palavras
        auto it = std::find(lista.begin(), lista.end(), keyword); // Encontra a primeira ocorrência da keyword na lista de palavras
        if (it != lista.end()) { // Condição para verificar se a keyword foi encontrada na lista
            size_t index = std::distance(lista.begin(), it); // Pega o índice da keyword
            std::vector<std::string> rotated; // Vetor para armazenar a lista de palavras rotacionadas
            rotated.insert(rotated.end(), lista.begin() + index, lista.end()); // Insere os elementos da lista original a partir da keyword até o final
            rotated.insert(rotated.end(), lista.begin(), lista.begin() + index); // Insere os elementos da lista original do início até a keyword (mas não inclui a keyword)
            std::ostringstream oss; // Cria a stream de strings para construir a linha rotacionada
            for (size_t i = 0; i < rotated.size(); ++i) {
                oss << rotated[i]; // Adiciona a palavra na stream
                if (i < rotated.size() - 1)
                    oss << " "; // Adiciona um espaço
            }
            event_manager.publish({"store", oss.str()}); // Publica o evento "store" com a string já formatada -> quick brown fox The
        }
    }
};

// Classe da aplicação principal do KWIC responsável por dar início ao fluxo
class KeyWordInContextApplication {
public:
    KeyWordInContextApplication(EventManager& evt) : event_manager(evt) {
        event_manager.subscribe("run", [this](auto event) { run(event); }); // Inscreve o método run para ser chamado quando o evento "run" for publicado
        event_manager.subscribe("print", [this](auto event) { stop(event); }); // Inscreve o método stop para ser chamado quando o evento "print" for publicado
    }

private:
    friend class KeyWordInContextApplicationTests_RunAndPrintEvents_Test; // Classe para teste
    EventManager& event_manager;

    // Método chamado pelo evento "run" que inicia todo o processo do KWIC
    void run(const std::pair<std::string, std::any>& event) {
        std::string path = std::any_cast<std::string>(event.second); // Extrai o caminho do arquivo
        event_manager.publish({"load", path}); // Publica o evento "load" para carregar os dados do arquivo
        event_manager.publish({"start", {}}); // Publica o evento "start" para iniciar a separação de palavras e o resto do fluxo
    }

    // Método chamado pelo evento "print" que imprime os resultados finais
    void stop(const std::pair<std::string, std::any>& event) {
        for (const auto& s : std::any_cast<std::vector<std::string>>(event.second)) {
            std::cout << s << std::endl; // Imprime cada linha do KWIC
        }
    }
};


#ifndef UNIT_TEST
int main(int argc, char* argv[]) {
    SetConsoleOutputCP(CP_UTF8); // Configura o console do Windows para exibir os caracteres do UTF-8
    if (argc < 2) { // Verifica se o número de argumentos da linha de comando é menor que 2 (nome do programa + arquivo de entrada)
        std::cerr << "Usage: " << argv[0] << " <input_file>" << std::endl; // Exibe mensagem de uso correto
        return 1;
    }

    EventManager em; // Instância do EventManager
    
    // Instâncias de cada classe
    DataStorage ds(em);
    KeyWordSeparator ks(em);
    StopWordFilter sf(em);
    CircleWords cw(em);
    KeyWordInContextApplication app(em);

    
    // Publica o evento inicial "run" com o caminho do arquivo de entrada fornecido na linha de comando disparando todo o fluxo do KWIC
    em.publish({"run", std::string(argv[1])});

    return 0;
}
#endif
