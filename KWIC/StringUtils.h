#ifndef STRINGUTILS_H
#define STRINGUTILS_H

#include <string>
#include <vector>
#include <algorithm> // Para std::transform
#include <cctype>    // Para std::tolower, std::ispunct

// Converte uma string para min�sculas
std::string paraMinusculas(std::string s);

// Remove pontua��o b�sica do in�cio e fim da palavra
std::string limparPontuacao(std::string palavra);

// Verifica se uma palavra � uma stop word
bool ehStopWord(const std::string& palavra, const std::vector<std::string>& stopWords);

#endif // STRINGUTILS_H
