#include "GeradorPalavrasChave.h"
#include "QuadroAvisos.h"   // Para KeywordInfo e métodos do quadro
#include "StringUtils.h"    // Para paraMinusculas, limparPontuacao, ehStopWord
#include <sstream>          // Para std::stringstream
#include <iostream>         // Para std::cout

// Implementação do método executar da classe GeradorPalavrasChave
void GeradorPalavrasChave::executar(QuadroAvisos& quadro, const std::vector<std::string>& stopWords) {
    std::cout << "\n--- GeradorPalavrasChave: INÍCIO DA EXECUÇÃO ---" << std::endl;

    // Recupera os títulos brutos que foram postados no quadro
    const auto& titulosParaProcessar = quadro.getTitulosBrutos();

    // Contador de palavras-chave geradas nesta execução
    size_t totalKeywordsGeradasNestaChamada = 0;

    // Percorre os títulos ainda não processados
    for (size_t i = quadro.ultimoIndiceTituloProcessadoParaKeywords; i < titulosParaProcessar.size(); ++i) {
        const std::string& tituloOriginal = titulosParaProcessar[i];
        std::cout << "[GeradorPalavrasChave] Processando título: \"" << tituloOriginal << "\"" << std::endl;

        // Utiliza stringstream para separar o título em palavras
        std::stringstream ss(tituloOriginal);
        std::string palavra;

        // Processa cada palavra do título
        while (ss >> palavra) {
            // Remove pontuações do início e fim da palavra
            std::string palavraLimpa = limparPontuacao(palavra);

            // Se a palavra não for vazia e não for uma stopword
            if (!palavraLimpa.empty() && !ehStopWord(palavraLimpa, stopWords)) {
                // Cria um objeto KeywordInfo com a palavra minúscula e o título original
                KeywordInfo info = {paraMinusculas(palavraLimpa), tituloOriginal};

                // Posta a informação no quadro
                quadro.postarPalavraChaveInfo(info);
                totalKeywordsGeradasNestaChamada++;
            }
        }
    }

    // Atualiza o índice de processamento no quadro
    quadro.ultimoIndiceTituloProcessadoParaKeywords = titulosParaProcessar.size();

    // Mensagem com o resultado da execução
    if (totalKeywordsGeradasNestaChamada > 0) {
        std::cout << "[GeradorPalavrasChave] Geração de palavras-chave concluída. "
                  << totalKeywordsGeradasNestaChamada << " novas KeywordInfo postadas no quadro." << std::endl;
    } else {
        std::cout << "[GeradorPalavrasChave] Nenhum novo título para processar ou nenhuma palavra-chave válida encontrada nos novos títulos." << std::endl;
    }

    std::cout << "--- GeradorPalavrasChave: FIM DA EXECUÇÃO ---" << std::endl;
}
