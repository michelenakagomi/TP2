#ifndef LEITORENTRADA_H
#define LEITORENTRADA_H
#include <string>

// Inclui a definição da classe QuadroAvisos, que será usada como referência
#include "QuadroAvisos.h"

// Declaração da classe LeitorEntrada
class LeitorEntrada {
public:
    // Método público que será chamado para executar a leitura de um arquivo de entrada.
    // Recebe:
    // - nomeArquivo: o caminho ou nome do arquivo a ser lido
    // - quadro: uma referência ao quadro de avisos onde os títulos serão postados
    void executar(const std::string& nomeArquivo, QuadroAvisos& quadro);
};

#endif // LEITORENTRADA_H
