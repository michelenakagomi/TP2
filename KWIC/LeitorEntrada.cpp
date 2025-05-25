#include "LeitorEntrada.h"
#include "QuadroAvisos.h" // Incluído para usar os métodos de 'quadro'
#include <fstream>
#include <iostream>

// Implementação do método executar da classe LeitorEntrada
void LeitorEntrada::executar(const std::string& nomeArquivo, QuadroAvisos& quadro) {
    std::cout << "\n--- LeitorEntrada: INÍCIO DA EXECUÇÃO ---" << std::endl;

    // Abre o arquivo para leitura
    std::ifstream arquivo(nomeArquivo);
    std::string linha;

    // Verifica se o arquivo foi aberto corretamente
    if (arquivo.is_open()) {
        int contadorLinhas = 0;

        // Lê o arquivo linha por linha
        while (std::getline(arquivo, linha)) {
            // Verifica se a linha não está vazia
            if (!linha.empty()) {
                // Posta a linha (título) no QuadroAvisos
                quadro.postarTitulo(linha);
                contadorLinhas++;
            }
        }

        // Fecha o arquivo após a leitura
        arquivo.close();

        // Exibe a quantidade de títulos postados com sucesso
        std::cout << "[LeitorEntrada] Leitura do arquivo concluída. "
                  << contadorLinhas << " títulos postados no quadro." << std::endl;
    } else {
        // Caso não consiga abrir o arquivo, exibe mensagem de erro
        std::cerr << "[LeitorEntrada] ERRO: Não foi possível abrir o arquivo: "
                  << nomeArquivo << std::endl;
    }

    std::cout << "--- LeitorEntrada: FIM DA EXECUÇÃO ---" << std::endl;
}
