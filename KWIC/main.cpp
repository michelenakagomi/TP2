#include <iostream>
#include <string>
#include <vector>

// Inclus�o dos headers dos m�dulos principais do programa
#include "QuadroAvisos.h"
#include "LeitorEntrada.h"
#include "GeradorPalavrasChave.h"

int main() {
    // Mensagem inicial indicando o in�cio do processo KWIC
    std::cout << "### IN�CIO DO PROCESSO KWIC (Estilo Bulletin Board) ###" << std::endl;

    // Cria��o do objeto principal que armazena t�tulos e palavras-chave
    QuadroAvisos quadro;

    // Nome do arquivo de entrada que cont�m os t�tulos a serem processados
    std::string nomeArquivoEntrada = "entrada.txt";

    // Lista de stop words que ser�o ignoradas na gera��o das palavras-chave
    std::vector<std::string> stopWords = {
        "a", "o", "as", "os", "um", "uma", "�", "de", "do", "da", "dos", "das",
        "em", "no", "na", "nos", "nas", "por", "para", "com", "sem", "sob", "sobre",
        "the", "is", "and", "of", "to", "in", "it", "that", "on"
    };

    // Instancia o leitor respons�vel por ler o arquivo de entrada e postar t�tulos no quadro
    LeitorEntrada leitor;

    // Instancia o gerador respons�vel por criar as palavras-chave a partir dos t�tulos
    GeradorPalavrasChave geradorKeywords;

    // Executa o componente leitor de entrada, lendo o arquivo e postando os t�tulos no quadro
    std::cout << "\n--- Disparando LeitorEntradaComponente ---" << std::endl;
    leitor.executar(nomeArquivoEntrada, quadro);

    // Exibe o estado atual do quadro, mostrando todos os t�tulos postados at� agora
    quadro.exibirEstadoTitulos();

    // Executa o componente gerador de palavras-chave, processando os t�tulos no quadro e criando as palavras-chave
    std::cout << "\n--- Disparando GeradorPalavrasChaveComponente ---" << std::endl;
    geradorKeywords.executar(quadro, stopWords);

    // Exibe o estado atual do quadro, mostrando as palavras-chave geradas a partir dos t�tulos
    quadro.exibirEstadoPalavrasChave();

    // Mensagem final indicando o fim do processo KWIC
    std::cout << "\n### FIM DO PROCESSO KWIC (Estilo Bulletin Board) ###" << std::endl;

    return 0;
}
