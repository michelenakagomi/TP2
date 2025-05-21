#ifndef STOP_WORD_FILTER_HPP
#define STOP_WORD_FILTER_HPP

#include "EventManager.hpp"           // Inclui definição de EventManager e Event
#include <unordered_set>              // Para armazenar stop words de forma eficiente
#include <string>
#include <iostream>

// Classe responsável por filtrar stopwords
class StopWordFilter {
public:
    // Construtor recebe uma referência para o EventManager para se inscrever nos eventos
    StopWordFilter(EventManager& evtMgr) : eventManager(evtMgr) {
        // Inscreve-se no evento "keyword" para filtrar cada palavra recebida
        eventManager.subscribe("keyword", [this](const Event& e) { this->filterStopWord(e); });

        // Inicializa a lista de stopwords
        initializeStopWords();
    }

private:
    EventManager& eventManager;                // Referência ao gerenciador de eventos
    std::unordered_set<std::string> stopWords; // Conjunto de palavras para filtrar rapidamente

    // Inicializa a lista de stopwords
    void initializeStopWords() {
        // Lista de stopwords
        const std::string sw[] = {
            "a", "an", "and", "are", "as", "at", "be", "but", "by",
            "for", "if", "in", "into", "is", "it", "no", "not", "of",
            "on", "or", "such", "that", "the", "their", "then", "there",
            "these", "they", "this", "to", "was", "will", "with"
        };
        // Insere todas as stopwords no conjunto para busca rápida
        for (const auto& w : sw) {
            stopWords.insert(w);
        }
        // Opcional: adiciona letras isoladas 'a' a 'z' como stopwords também
        for (char c = 'a'; c <= 'z'; ++c) {
            stopWords.insert(std::string(1, c));
        }
    }

    // Função que filtra stopwords
    // Recebe o evento do tipo "keyword" com dados no formato "palavra | linha"
    void filterStopWord(const Event& event) {
        // Encontra a posição do separador " | "
        auto pos = event.data.find(" | ");
        if (pos == std::string::npos) return; // Se formato errado, sai

        // Extrai a palavra antes do separador
        std::string word = event.data.substr(0, pos);

        // Se a palavra NÃO está no conjunto de stopwords, publica um evento "valid_keyword"
        if (stopWords.find(word) == stopWords.end()) {
            eventManager.publish({"valid_keyword", event.data});
        }
        // Caso contrário, descarta a palavra (não publica nada)
    }
};

#endif
