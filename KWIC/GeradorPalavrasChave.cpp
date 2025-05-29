#include "GeradorPalavrasChave.h"
#include "QuadroAvisos.h"   // Para KeywordInfo e m�todos do quadro
#include "StringUtils.h"    // Para paraMinusculas, limparPontuacao, ehStopWord
#include <sstream>          // Para std::stringstream
#include <iostream>         // Para std::cout

// Implementa��o do m�todo executar da classe GeradorPalavrasChave
void GeradorPalavrasChave::executar(QuadroAvisos& quadro, const std::vector<std::string>& stopWords) {
    std::cout << "\n--- GeradorPalavrasChave: IN�CIO DA EXECU��O ---" << std::endl;

    // Recupera os t�tulos brutos que foram postados no quadro
    const auto& titulosParaProcessar = quadro.getTitulosBrutos();

    // Contador de palavras-chave geradas nesta execu��o
    size_t totalKeywordsGeradasNestaChamada = 0;

    // Percorre os t�tulos ainda n�o processados
    for (size_t i = quadro.ultimoIndiceTituloProcessadoParaKeywords; i < titulosParaProcessar.size(); ++i) {
        const std::string& tituloOriginal = titulosParaProcessar[i];
        std::cout << "[GeradorPalavrasChave] Processando t�tulo: \"" << tituloOriginal << "\"" << std::endl;

        // Utiliza stringstream para separar o t�tulo em palavras
        std::stringstream ss(tituloOriginal);
        std::string palavra;

        // Processa cada palavra do t�tulo
        while (ss >> palavra) {
            // Remove pontua��es do in�cio e fim da palavra
            std::string palavraLimpa = limparPontuacao(palavra);

            // Se a palavra n�o for vazia e n�o for uma stopword
            if (!palavraLimpa.empty() && !ehStopWord(palavraLimpa, stopWords)) {
                // Cria um objeto KeywordInfo com a palavra min�scula e o t�tulo original
                KeywordInfo info = {paraMinusculas(palavraLimpa), tituloOriginal};

                // Posta a informa��o no quadro
                quadro.postarPalavraChaveInfo(info);
                totalKeywordsGeradasNestaChamada++;
            }
        }
    }

    // Atualiza o �ndice de processamento no quadro
    quadro.ultimoIndiceTituloProcessadoParaKeywords = titulosParaProcessar.size();

    // Mensagem com o resultado da execu��o
    if (totalKeywordsGeradasNestaChamada > 0) {
        std::cout << "[GeradorPalavrasChave] Gera��o de palavras-chave conclu�da. "
                  << totalKeywordsGeradasNestaChamada << " novas KeywordInfo postadas no quadro." << std::endl;
    } else {
        std::cout << "[GeradorPalavrasChave] Nenhum novo t�tulo para processar ou nenhuma palavra-chave v�lida encontrada nos novos t�tulos." << std::endl;
    }

    std::cout << "--- GeradorPalavrasChave: FIM DA EXECU��O ---" << std::endl;
}
