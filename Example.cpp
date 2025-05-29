#include "Example.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <set>
#include <map>
#include <algorithm>
#include <cctype>

using namespace std;

// Bulletin Board
map<string, vector<pair<string, string>>> board;
map<string, vector<string>> text_board;

// Lista de stopwords
set<string> stopwords = {
    "a", "o", "as", "os", "um", "uma", "é", "de", "da", "do",
    "e", "em", "para", "por", "com", "no", "na", "se", "que",
    "the", "is", "sat"};

string to_lower(const string &s)
{
    string result;
    for (char c : s)
        result += tolower(c);
    return result;
}

// 1. Lê arquivo e separa palavras
void split_words()
{
    ifstream file("input.txt");
    string line;
    while (getline(file, line))
    {
        text_board["lines"].push_back(line);
        istringstream iss(line);
        string word;
        while (iss >> word)
        {
            string clean;
            for (char c : word)
                if (isalnum(c))
                    clean += c;
            if (!clean.empty())
                board["keywords"].emplace_back(clean, line);
        }
    }
}

// 2. Filtra keywords
void stopword_filtering()
{
    vector<pair<string, string>> filtered;
    for (const auto &[word, line] : board["keywords"])
    {
        if (stopwords.find(to_lower(word)) == stopwords.end())
            filtered.emplace_back(word, line);
    }
    // Remover duplicatas (ex: duas vezes 'brown' na mesma linha)
    set<pair<string, string>> unique(filtered.begin(), filtered.end());
    board["filtered_keywords"] = vector<pair<string, string>>(unique.begin(), unique.end());
}

// ✅ 3. Shift circular correto baseado na posição da keyword
void circular_shift_basic()
{
    vector<pair<string, string>> shifts;

    for (const auto &[keyword, line] : board["filtered_keywords"])
    {
        istringstream iss(line);
        vector<string> words;
        string word;
        while (iss >> word)
            words.push_back(word);

        for (size_t i = 0; i < words.size(); ++i)
        {
            // Limpar palavra atual
            string clean;
            for (char c : words[i])
                if (isalnum(c))
                    clean += c;

            if (to_lower(clean) == to_lower(keyword))
            {
                // Shift: coloca a palavra-chave no início
                vector<string> shifted;
                for (size_t j = i; j < words.size(); ++j)
                    shifted.push_back(words[j]);
                for (size_t j = 0; j < i; ++j)
                    shifted.push_back(words[j]);

                // Monta string final
                ostringstream oss;
                for (const string &w : shifted)
                    oss << w << " ";
                string shifted_line = oss.str();
                shifted_line.pop_back(); // remove o último espaço

                shifts.emplace_back(to_lower(keyword), shifted_line);
                break; // só a primeira ocorrência da keyword na frase
            }
        }
    }

    board["shifted_lines"] = shifts;
}

// 4. Ordena os shifts alfabeticamente
void ordering_correctness()
{
    sort(board["shifted_lines"].begin(), board["shifted_lines"].end(),
         [](const pair<string, string> &a, const pair<string, string> &b)
         {
             return a.second < b.second;
         });
}

// 5. Exibe a saída final
void integration_input_to_output()
{
    for (const auto &[keyword, shifted_line] : board["shifted_lines"])
    {
        cout << shifted_line << endl;
    }
}

// main
int main()
{
    split_words();
    stopword_filtering();
    circular_shift_basic();
    ordering_correctness();
    integration_input_to_output();
    return 0;
}