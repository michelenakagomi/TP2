#ifndef QUADROAVISOS_H
#define QUADROAVISOS_H

#include <string>
#include <vector>
#include <iostream> // Necessário para std::cout nas funções de exibição

// Estrutura que representa uma palavra-chave extraída de um título
struct KeywordInfo {
    std::string keyword;       // - keyword: a palavra-chave em si
    std::string originalTitle; // - originalTitle: o título completo de onde a palavra-chave foi retirada
};

// Classe que simula um "quadro de avisos", usado para comunicação entre componentes
class QuadroAvisos {
public:
    // Armazena todos os títulos brutos postados por algum componente
    std::vector<std::string> titulosBrutosPostados;

    // Armazena todas as palavras-chave extraídas dos títulos
    std::vector<KeywordInfo> palavrasChaveInfoPostadas;

    // Índice que indica até onde os títulos já foram processados por outros componentes
    size_t ultimoIndiceTituloProcessadoParaKeywords = 0;

    // Construtor
    QuadroAvisos() = default;

    // Método que adiciona um novo título ao vetor de títulos brutos
    void postarTitulo(const std::string& titulo);

    // Método que adiciona uma nova palavra-chave ao vetor de palavras-chave
    void postarPalavraChaveInfo(const KeywordInfo& info);

    // Getters que retornam as listas armazenadas
    const std::vector<std::string>& getTitulosBrutos() const {
        return titulosBrutosPostados;
    }

    const std::vector<KeywordInfo>& getPalavrasChaveInfo() const {
        return palavrasChaveInfoPostadas;
    }

    // Exibe todas as palavras-chave já postadas no quadro (para debug)
    void exibirEstadoPalavrasChave() const;

    // Exibe todos os títulos brutos já postados (para debug)
    void exibirEstadoTitulos() const;
};

#endif // QUADROAVISOS_H
