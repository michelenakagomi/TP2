#ifndef GERADORPALAVRASCHAVE_H
#define GERADORPALAVRASCHAVE_H

#include <string>
#include <vector>
#include "QuadroAvisos.h" // Necess�rio para acessar QuadroAvisos e KeywordInfo

// Classe respons�vel por gerar palavras-chave a partir dos t�tulos postados
class GeradorPalavrasChave {
public:
    // M�todo que executa a gera��o de palavras-chave.
    // Recebe uma refer�ncia ao QuadroAvisos (de onde l� os t�tulos)
    // e uma lista de stopwords que ser�o ignoradas na extra��o.
    void executar(QuadroAvisos& quadro, const std::vector<std::string>& stopWords);
};

#endif // GERADORPALAVRASCHAVE_H
