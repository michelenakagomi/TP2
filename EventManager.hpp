#ifndef EVENT_MANAGER_HPP
#define EVENT_MANAGER_HPP

#include <string>               // Para std::string
#include <unordered_map>        // Para armazenar assinantes em mapa hash
#include <functional>           // Para std::function, armazenar fun��es/callbacks
#include <vector>               // Para vetor de fun��es assinantes

// Estrutura que representa um evento com um tipo e dados associados
struct Event {
    std::string type;   // Tipo do evento (ex: "load", "start", "keyword")
    std::string data;   // Dados associados ao evento (ex: nome do arquivo, palavra-chave)
};

// Classe que gerencia eventos: permite assinar eventos e publicar eventos
class EventManager {
public:
    // M�todo para se inscrever em um evento espec�fico,
    // passando o tipo do evento e um manipulador (fun��o callback)
    void subscribe(const std::string& eventType, std::function<void(const Event&)> handler) {
        // Adiciona o handler na lista de assinantes para o tipo de evento dado
        subscribers[eventType].push_back(handler);
    }

    // M�todo para publicar um evento para todos os assinantes daquele tipo
    void publish(const Event& event) {
        // Busca os assinantes para o tipo do evento
        auto handlers = subscribers.find(event.type);
        if (handlers != subscribers.end()) {
            // Para cada handler registrado para esse evento, chama o callback passando o evento
            for (auto& handler : handlers->second) {
                handler(event);
            }
        }
        // Se n�o houver assinantes para o evento, simplesmente n�o faz nada
    }

private:
    // Mapa que associa cada tipo de evento a uma lista de fun��es (callbacks) que o tratam
    std::unordered_map<std::string, std::vector<std::function<void(const Event&)>>> subscribers;
};

#endif
