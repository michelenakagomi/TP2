#ifndef EVENT_MANAGER_HPP
#define EVENT_MANAGER_HPP

#include <string>               // Para std::string
#include <unordered_map>        // Para armazenar assinantes em mapa hash
#include <functional>           // Para std::function, armazenar funções/callbacks
#include <vector>               // Para vetor de funções assinantes

// Estrutura que representa um evento com um tipo e dados associados
struct Event {
    std::string type;   // Tipo do evento (ex: "load", "start", "keyword")
    std::string data;   // Dados associados ao evento (ex: nome do arquivo, palavra-chave)
};

// Classe que gerencia eventos: permite assinar eventos e publicar eventos
class EventManager {
public:
    // Método para se inscrever em um evento específico,
    // passando o tipo do evento e um manipulador (função callback)
    void subscribe(const std::string& eventType, std::function<void(const Event&)> handler) {
        // Adiciona o handler na lista de assinantes para o tipo de evento dado
        subscribers[eventType].push_back(handler);
    }

    // Método para publicar um evento para todos os assinantes daquele tipo
    void publish(const Event& event) {
        // Busca os assinantes para o tipo do evento
        auto handlers = subscribers.find(event.type);
        if (handlers != subscribers.end()) {
            // Para cada handler registrado para esse evento, chama o callback passando o evento
            for (auto& handler : handlers->second) {
                handler(event);
            }
        }
        // Se não houver assinantes para o evento, simplesmente não faz nada
    }

private:
    // Mapa que associa cada tipo de evento a uma lista de funções (callbacks) que o tratam
    std::unordered_map<std::string, std::vector<std::function<void(const Event&)>>> subscribers;
};

#endif
