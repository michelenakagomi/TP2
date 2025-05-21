#ifndef KEYWORD_PRINTER_HPP
#define KEYWORD_PRINTER_HPP

#include "EventManager.hpp"   // Inclui a definição do EventManager e Event
#include <iostream>           // Para saída no console (std::cout)

// Classe responsável por imprimir palavras-chave válidas e indicar o fim do processamento
class KeywordPrinter {
public:
    // Construtor que recebe uma referência ao EventManager para se inscrever nos eventos
    KeywordPrinter(EventManager& evtMgr) : eventManager(evtMgr) {
        // Assina o evento "valid_keyword" para imprimir a palavra-chave válida recebida
        eventManager.subscribe("valid_keyword", [this](const Event& e) { this->printKeyword(e); });

        // Assina o evento "eof" para indicar o fim do arquivo/processamento
        eventManager.subscribe("eof", [this](const Event&) { this->printEnd(); });
    }

private:
    EventManager& eventManager;  // Referência para o gerenciador de eventos para publicar/assinar

    // Função chamada quando um evento "valid_keyword" é publicado
    // Imprime a palavra-chave válida no console
    void printKeyword(const Event& event) {
        std::cout << "Palavra-chave válida: " << event.data << std::endl;
    }

    // Função chamada quando o evento "eof" é publicado
    // Indica que o processamento chegou ao fim
    void printEnd() {
        std::cout << "Fim do arquivo.\n";
    }
};

#endif
