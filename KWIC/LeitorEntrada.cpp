#include "LeitorEntrada.h"
#include "QuadroAvisos.h" // Inclu�do para usar os m�todos de 'quadro'
#include <fstream>
#include <iostream>

// Implementa��o do m�todo executar da classe LeitorEntrada
void LeitorEntrada::executar(const std::string& nomeArquivo, QuadroAvisos& quadro) {
    std::cout << "\n--- LeitorEntrada: IN�CIO DA EXECU��O ---" << std::endl;

    // Abre o arquivo para leitura
    std::ifstream arquivo(nomeArquivo);
    std::string linha;

    // Verifica se o arquivo foi aberto corretamente
    if (arquivo.is_open()) {
        int contadorLinhas = 0;

        // L� o arquivo linha por linha
        while (std::getline(arquivo, linha)) {
            // Verifica se a linha n�o est� vazia
            if (!linha.empty()) {
                // Posta a linha (t�tulo) no QuadroAvisos
                quadro.postarTitulo(linha);
                contadorLinhas++;
            }
        }

        // Fecha o arquivo ap�s a leitura
        arquivo.close();

        // Exibe a quantidade de t�tulos postados com sucesso
        std::cout << "[LeitorEntrada] Leitura do arquivo conclu�da. "
                  << contadorLinhas << " t�tulos postados no quadro." << std::endl;
    } else {
        // Caso n�o consiga abrir o arquivo, exibe mensagem de erro
        std::cerr << "[LeitorEntrada] ERRO: N�o foi poss�vel abrir o arquivo: "
                  << nomeArquivo << std::endl;
    }

    std::cout << "--- LeitorEntrada: FIM DA EXECU��O ---" << std::endl;
}
