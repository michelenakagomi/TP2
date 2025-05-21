#ifndef DATA_STORAGE_HPP
#define DATA_STORAGE_HPP

#include "EventManager.hpp"
#include <fstream>      // Para manipulação de arquivos
#include <sstream>      // Para manipulação de strings como fluxo (istringstream)
#include <string>       // Para usar std::string
#include <vector>       // Para armazenar linhas em std::vector
#include <cctype>       // Para funções de manipulação de caracteres (isalnum, tolower)
#include <algorithm>    // Para std::transform
#include <iostream>     // Para saída de erro no console

// Classe responsável por armazenar e processar o conteúdo do arquivo de entrada
class DataStorage {
public:
    // Construtor recebe uma referência ao gerenciador de eventos para se inscrever em eventos
    DataStorage(EventManager& evtMgr) : eventManager(evtMgr) {
        // Inscreve o método load para ser chamado quando o evento "load" for publicado
        eventManager.subscribe("load", [this](const Event& e) { this->load(e); });
        // Inscreve o método produceKeywords para ser chamado quando o evento "start" for publicado
        eventManager.subscribe("start", [this](const Event& e) { this->produceKeywords(e); });
    }

private:
    EventManager& eventManager;        // Referência ao gerenciador de eventos para publicar e receber eventos
    std::vector<std::string> lines;    // Armazena as linhas lidas do arquivo

    // Método que carrega o arquivo especificado no evento e armazena suas linhas em lowercase e sem pontuação
    void load(const Event& event) {
        std::ifstream file(event.data);   // Abre o arquivo cujo nome veio no campo 'data' do evento
        if (!file.is_open()) {            // Verifica se o arquivo foi aberto com sucesso
            std::cerr << "Erro ao abrir o arquivo: " << event.data << std::endl;
            return;
        }

        std::string line;
        while (std::getline(file, line)) {    // Lê o arquivo linha a linha
            // Converte cada caractere da linha:
            // Se for alfanumérico, transforma em minúsculo
            // Caso contrário, substitui por espaço
            std::transform(line.begin(), line.end(), line.begin(), [](char c) {
                return std::isalnum(static_cast<unsigned char>(c)) ?
                       std::tolower(static_cast<unsigned char>(c)) : ' ';
            });
            lines.push_back(line);          // Armazena a linha processada no vetor
        }
        file.close();                       // Fecha o arquivo após a leitura
    }

    // Método que extrai palavras-chave das linhas armazenadas e publica eventos "keyword"
    void produceKeywords(const Event&) {
        for (const auto& line : lines) {            // Para cada linha armazenada
            std::istringstream iss(line);           // Cria um fluxo para extrair as palavras
            std::string word;
            while (iss >> word) {                    // Para cada palavra na linha
                // Publica um evento "keyword" com a palavra + linha original separada por " | "
                // A linha é útil para mostrar o contexto da palavra
                eventManager.publish({"keyword", word + " | " + line});
            }
        }
        // Ao final, publica um evento "eof" indicando o fim da produção de keywords
        eventManager.publish({"eof", ""});
    }
};

#endif
