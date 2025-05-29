#include "StringUtils.h"

// Converte uma string para letras minúsculas
std::string paraMinusculas(std::string s) {
    // Transforma cada caractere da string usando std::tolower
    std::transform(s.begin(), s.end(), s.begin(),
                   [](unsigned char c){ return std::tolower(c); });
    return s; // Retorna a nova string em minúsculas
}

// Remove pontuações no início e no final de uma palavra
std::string limparPontuacao(std::string palavra) {
    // Remove pontuações do final da palavra
    while (!palavra.empty() && std::ispunct(static_cast<unsigned char>(palavra.back()))) {
        palavra.pop_back(); // Remove o último caractere
    }
    // Remove pontuações do início da palavra
    while (!palavra.empty() && std::ispunct(static_cast<unsigned char>(palavra.front()))) {
        palavra.erase(0, 1); // Remove o primeiro caractere
    }
    return palavra; // Retorna a palavra limpa
}

// Verifica se uma palavra é uma stop word
bool ehStopWord(const std::string& palavra, const std::vector<std::string>& stopWords) {
    // Converte a palavra para minúsculas para comparação
    std::string palavraMinusc = paraMinusculas(palavra);

    // Percorre a lista de stop words para verificar se há correspondência
    for (const std::string& stop : stopWords) {
        if (palavraMinusc == stop) {
            return true; // Encontrou, é uma stop word
        }
    }
    return false; // Não encontrou, não é uma stop word
}
