#ifndef STRINGUTILS_H
#define STRINGUTILS_H

#include <string>
#include <vector>
#include <algorithm> // Para std::transform
#include <cctype>    // Para std::tolower, std::ispunct

// Converte uma string para minúsculas
std::string paraMinusculas(std::string s);

// Remove pontuação básica do início e fim da palavra
std::string limparPontuacao(std::string palavra);

// Verifica se uma palavra é uma stop word
bool ehStopWord(const std::string& palavra, const std::vector<std::string>& stopWords);

#endif // STRINGUTILS_H
