#include "QuadroAvisos.h"

// Implementa��o do m�todo que adiciona um t�tulo bruto ao quadro de avisos
// Tamb�m imprime uma mensagem no console para indicar que o t�tulo foi postado
void QuadroAvisos::postarTitulo(const std::string& titulo) {
    titulosBrutosPostados.push_back(titulo); // Adiciona o t�tulo � lista
    std::cout << "[QuadroAvisos] Evento: Novo t�tulo postado no quadro: \"" << titulo << "\"" << std::endl;
}

// Implementa��o do m�todo que adiciona uma palavra-chave ao quadro de avisos
// A palavra-chave � representada por uma estrutura KeywordInfo com a keyword e o t�tulo original
void QuadroAvisos::postarPalavraChaveInfo(const KeywordInfo& info) {
    palavrasChaveInfoPostadas.push_back(info); // Adiciona a lista de palavras-chave
}

// M�todo auxiliar que exibe no console o estado atual das palavras-chave armazenadas (para debug)
void QuadroAvisos::exibirEstadoPalavrasChave() const {
    std::cout << "\n[QuadroAvisos] Estado Atual - Palavras-Chave Geradas:" << std::endl;

    // Verifica se a lista est� vazia
    if (palavrasChaveInfoPostadas.empty()) {
        std::cout << "Nenhuma palavra-chave gerada ainda." << std::endl;
        return;
    }

    // Itera sobre todas as palavras-chave e exibe cada uma com seu t�tulo de origem
    for (const auto& info : palavrasChaveInfoPostadas) {
        std::cout << "- Palavra-chave: \"" << info.keyword
                  << "\", T�tulo Original: \"" << info.originalTitle << "\"" << std::endl;
    }
}

// M�todo auxiliar que exibe no console todos os t�tulos brutos que foram postados (para debug)
void QuadroAvisos::exibirEstadoTitulos() const {
    std::cout << "\n[QuadroAvisos] Estado Atual - T�tulos Brutos:" << std::endl;

    // Verifica se h� algum t�tulo postado
    if (titulosBrutosPostados.empty()) {
        std::cout << "Nenhum t�tulo bruto postado ainda." << std::endl;
        return;
    }

    // Exibe todos os t�tulos armazenados
    for (const auto& titulo : titulosBrutosPostados) {
        std::cout << "- " << titulo << std::endl;
    }
}
