#ifndef QUADROAVISOS_H
#define QUADROAVISOS_H

#include <string>
#include <vector>
#include <iostream> // Necess�rio para std::cout nas fun��es de exibi��o

// Estrutura que representa uma palavra-chave extra�da de um t�tulo
struct KeywordInfo {
    std::string keyword;       // - keyword: a palavra-chave em si
    std::string originalTitle; // - originalTitle: o t�tulo completo de onde a palavra-chave foi retirada
};

// Classe que simula um "quadro de avisos", usado para comunica��o entre componentes
class QuadroAvisos {
public:
    // Armazena todos os t�tulos brutos postados por algum componente
    std::vector<std::string> titulosBrutosPostados;

    // Armazena todas as palavras-chave extra�das dos t�tulos
    std::vector<KeywordInfo> palavrasChaveInfoPostadas;

    // �ndice que indica at� onde os t�tulos j� foram processados por outros componentes
    size_t ultimoIndiceTituloProcessadoParaKeywords = 0;

    // Construtor
    QuadroAvisos() = default;

    // M�todo que adiciona um novo t�tulo ao vetor de t�tulos brutos
    void postarTitulo(const std::string& titulo);

    // M�todo que adiciona uma nova palavra-chave ao vetor de palavras-chave
    void postarPalavraChaveInfo(const KeywordInfo& info);

    // Getters que retornam as listas armazenadas
    const std::vector<std::string>& getTitulosBrutos() const {
        return titulosBrutosPostados;
    }

    const std::vector<KeywordInfo>& getPalavrasChaveInfo() const {
        return palavrasChaveInfoPostadas;
    }

    // Exibe todas as palavras-chave j� postadas no quadro (para debug)
    void exibirEstadoPalavrasChave() const;

    // Exibe todos os t�tulos brutos j� postados (para debug)
    void exibirEstadoTitulos() const;
};

#endif // QUADROAVISOS_H
