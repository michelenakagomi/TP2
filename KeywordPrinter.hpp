#ifndef KEYWORD_PRINTER_HPP
#define KEYWORD_PRINTER_HPP

#include "EventManager.hpp"   // Inclui a defini��o do EventManager e Event
#include <iostream>           // Para sa�da no console (std::cout)

// Classe respons�vel por imprimir palavras-chave v�lidas e indicar o fim do processamento
class KeywordPrinter {
public:
    // Construtor que recebe uma refer�ncia ao EventManager para se inscrever nos eventos
    KeywordPrinter(EventManager& evtMgr) : eventManager(evtMgr) {
        // Assina o evento "valid_keyword" para imprimir a palavra-chave v�lida recebida
        eventManager.subscribe("valid_keyword", [this](const Event& e) { this->printKeyword(e); });

        // Assina o evento "eof" para indicar o fim do arquivo/processamento
        eventManager.subscribe("eof", [this](const Event&) { this->printEnd(); });
    }

private:
    EventManager& eventManager;  // Refer�ncia para o gerenciador de eventos para publicar/assinar

    // Fun��o chamada quando um evento "valid_keyword" � publicado
    // Imprime a palavra-chave v�lida no console
    void printKeyword(const Event& event) {
        std::cout << "Palavra-chave v�lida: " << event.data << std::endl;
    }

    // Fun��o chamada quando o evento "eof" � publicado
    // Indica que o processamento chegou ao fim
    void printEnd() {
        std::cout << "Fim do arquivo.\n";
    }
};

#endif
