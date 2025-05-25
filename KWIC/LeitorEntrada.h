#ifndef LEITORENTRADA_H
#define LEITORENTRADA_H
#include <string>

// Inclui a defini��o da classe QuadroAvisos, que ser� usada como refer�ncia
#include "QuadroAvisos.h"

// Declara��o da classe LeitorEntrada
class LeitorEntrada {
public:
    // M�todo p�blico que ser� chamado para executar a leitura de um arquivo de entrada.
    // Recebe:
    // - nomeArquivo: o caminho ou nome do arquivo a ser lido
    // - quadro: uma refer�ncia ao quadro de avisos onde os t�tulos ser�o postados
    void executar(const std::string& nomeArquivo, QuadroAvisos& quadro);
};

#endif // LEITORENTRADA_H
