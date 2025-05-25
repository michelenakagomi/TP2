#include "QuadroAvisos.h"

// Implementação do método que adiciona um título bruto ao quadro de avisos
// Também imprime uma mensagem no console para indicar que o título foi postado
void QuadroAvisos::postarTitulo(const std::string& titulo) {
    titulosBrutosPostados.push_back(titulo); // Adiciona o título à lista
    std::cout << "[QuadroAvisos] Evento: Novo título postado no quadro: \"" << titulo << "\"" << std::endl;
}

// Implementação do método que adiciona uma palavra-chave ao quadro de avisos
// A palavra-chave é representada por uma estrutura KeywordInfo com a keyword e o título original
void QuadroAvisos::postarPalavraChaveInfo(const KeywordInfo& info) {
    palavrasChaveInfoPostadas.push_back(info); // Adiciona a lista de palavras-chave
}

// Método auxiliar que exibe no console o estado atual das palavras-chave armazenadas (para debug)
void QuadroAvisos::exibirEstadoPalavrasChave() const {
    std::cout << "\n[QuadroAvisos] Estado Atual - Palavras-Chave Geradas:" << std::endl;

    // Verifica se a lista está vazia
    if (palavrasChaveInfoPostadas.empty()) {
        std::cout << "Nenhuma palavra-chave gerada ainda." << std::endl;
        return;
    }

    // Itera sobre todas as palavras-chave e exibe cada uma com seu título de origem
    for (const auto& info : palavrasChaveInfoPostadas) {
        std::cout << "- Palavra-chave: \"" << info.keyword
                  << "\", Título Original: \"" << info.originalTitle << "\"" << std::endl;
    }
}

// Método auxiliar que exibe no console todos os títulos brutos que foram postados (para debug)
void QuadroAvisos::exibirEstadoTitulos() const {
    std::cout << "\n[QuadroAvisos] Estado Atual - Títulos Brutos:" << std::endl;

    // Verifica se há algum título postado
    if (titulosBrutosPostados.empty()) {
        std::cout << "Nenhum título bruto postado ainda." << std::endl;
        return;
    }

    // Exibe todos os títulos armazenados
    for (const auto& titulo : titulosBrutosPostados) {
        std::cout << "- " << titulo << std::endl;
    }
}
