#include "StringUtils.h"

// Converte uma string para letras min�sculas
std::string paraMinusculas(std::string s) {
    // Transforma cada caractere da string usando std::tolower
    std::transform(s.begin(), s.end(), s.begin(),
                   [](unsigned char c){ return std::tolower(c); });
    return s; // Retorna a nova string em min�sculas
}

// Remove pontua��es no in�cio e no final de uma palavra
std::string limparPontuacao(std::string palavra) {
    // Remove pontua��es do final da palavra
    while (!palavra.empty() && std::ispunct(static_cast<unsigned char>(palavra.back()))) {
        palavra.pop_back(); // Remove o �ltimo caractere
    }
    // Remove pontua��es do in�cio da palavra
    while (!palavra.empty() && std::ispunct(static_cast<unsigned char>(palavra.front()))) {
        palavra.erase(0, 1); // Remove o primeiro caractere
    }
    return palavra; // Retorna a palavra limpa
}

// Verifica se uma palavra � uma stop word
bool ehStopWord(const std::string& palavra, const std::vector<std::string>& stopWords) {
    // Converte a palavra para min�sculas para compara��o
    std::string palavraMinusc = paraMinusculas(palavra);

    // Percorre a lista de stop words para verificar se h� correspond�ncia
    for (const std::string& stop : stopWords) {
        if (palavraMinusc == stop) {
            return true; // Encontrou, � uma stop word
        }
    }
    return false; // N�o encontrou, n�o � uma stop word
}
