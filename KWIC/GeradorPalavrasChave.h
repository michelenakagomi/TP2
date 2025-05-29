#ifndef GERADORPALAVRASCHAVE_H
#define GERADORPALAVRASCHAVE_H

#include <string>
#include <vector>
#include "QuadroAvisos.h" // Necessário para acessar QuadroAvisos e KeywordInfo

// Classe responsável por gerar palavras-chave a partir dos títulos postados
class GeradorPalavrasChave {
public:
    // Método que executa a geração de palavras-chave.
    // Recebe uma referência ao QuadroAvisos (de onde lê os títulos)
    // e uma lista de stopwords que serão ignoradas na extração.
    void executar(QuadroAvisos& quadro, const std::vector<std::string>& stopWords);
};

#endif // GERADORPALAVRASCHAVE_H
