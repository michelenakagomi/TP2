#include "EventManager.hpp"
#include "DataStorage.hpp"
#include "StopWordFilter.hpp"
#include "KeywordPrinter.hpp"

int main(int argc, char* argv[]) {
    // Verifica se o nome do arquivo de entrada foi passado como argumento
    if (argc < 2) {
        std::cerr << "Use: " << argv[0] << " <arquivo_de_entrada>\n";
        return 1; // Encerra com erro se n�o passou argumento
    }

    // Cria o gerenciador de eventos, que vai controlar a comunica��o entre m�dulos
    EventManager eventManager;

    // Cria os m�dulos e passa a refer�ncia do EventManager para que eles possam
    // se inscrever e publicar eventos
    DataStorage dataStorage(eventManager);      // L� o arquivo e armazena linhas
    StopWordFilter stopWordFilter(eventManager); // Filtra stopwords das palavras
    KeywordPrinter printer(eventManager);       // Imprime as palavras v�lidas na tela

    // Publica o evento "load" com o nome do arquivo, disparando a leitura do arquivo
    eventManager.publish({"load", argv[1]});

    // Publica o evento "start", que faz o DataStorage produzir as palavras-chave
    eventManager.publish({"start", ""});

    return 0; // Programa finaliza com sucesso
}
