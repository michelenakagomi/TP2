#include <iostream>
#include <string>
#include <vector>

// Inclusão dos headers dos módulos principais do programa
#include "QuadroAvisos.h"
#include "LeitorEntrada.h"
#include "GeradorPalavrasChave.h"

int main() {
    // Mensagem inicial indicando o início do processo KWIC
    std::cout << "### INÍCIO DO PROCESSO KWIC (Estilo Bulletin Board) ###" << std::endl;

    // Criação do objeto principal que armazena títulos e palavras-chave
    QuadroAvisos quadro;

    // Nome do arquivo de entrada que contém os títulos a serem processados
    std::string nomeArquivoEntrada = "entrada.txt";

    // Lista de stop words que serão ignoradas na geração das palavras-chave
    std::vector<std::string> stopWords = {
        "a", "o", "as", "os", "um", "uma", "é", "de", "do", "da", "dos", "das",
        "em", "no", "na", "nos", "nas", "por", "para", "com", "sem", "sob", "sobre",
        "the", "is", "and", "of", "to", "in", "it", "that", "on"
    };

    // Instancia o leitor responsável por ler o arquivo de entrada e postar títulos no quadro
    LeitorEntrada leitor;

    // Instancia o gerador responsável por criar as palavras-chave a partir dos títulos
    GeradorPalavrasChave geradorKeywords;

    // Executa o componente leitor de entrada, lendo o arquivo e postando os títulos no quadro
    std::cout << "\n--- Disparando LeitorEntradaComponente ---" << std::endl;
    leitor.executar(nomeArquivoEntrada, quadro);

    // Exibe o estado atual do quadro, mostrando todos os títulos postados até agora
    quadro.exibirEstadoTitulos();

    // Executa o componente gerador de palavras-chave, processando os títulos no quadro e criando as palavras-chave
    std::cout << "\n--- Disparando GeradorPalavrasChaveComponente ---" << std::endl;
    geradorKeywords.executar(quadro, stopWords);

    // Exibe o estado atual do quadro, mostrando as palavras-chave geradas a partir dos títulos
    quadro.exibirEstadoPalavrasChave();

    // Mensagem final indicando o fim do processo KWIC
    std::cout << "\n### FIM DO PROCESSO KWIC (Estilo Bulletin Board) ###" << std::endl;

    return 0;
}
