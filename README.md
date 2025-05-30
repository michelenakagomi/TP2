# TP2
 Trabalho da vídeo aula no estilo Bulletin Board em C++
 ^^

-----------------------------------------------------------------

📌 Tarefas obrigatórias:

(a) Implementar o algoritmo KWIC utilizando o estilo e linguagem de programação escolhidos.

(b) Implementar testes unitários e de integração para os principais componentes do KWIC.

(c) Elaborar uma vídeo aula sobre o estilo de programação escolhido, explicando:

- Como o estilo influenciou o design da solução;
- Restrições que motivam o estilo;
- Exemplo da implementação do KWIC no estilo;
- Detalhes relevantes sobre como o estilo impactou o projeto;
- Como o estilo é usado no design de sistemas ou historicamente.

------------------------------------------------------------------------

🔍 Especificação do Algoritmo KWIC (Keyword in Context)

🎯 Objetivo:
Receber uma lista de títulos ou frases e gerar uma lista alfabetizada de todas as palavras-chave nesses títulos, cada uma com seu contexto (a frase original com a palavra-chave no início).

📥 Entrada:
Um arquivo de texto contendo uma frase por linha.

📤 Saída:
Uma lista alfabetizada de palavras-chave, com cada palavra apresentada em seu contexto (frase original circularmente deslocada para que a palavra-chave esteja no início).

------------------------------------------------------------------------

🧠 Etapas do algoritmo:

1) Ler Entrada

Ler o arquivo de texto e armazenar os títulos em uma lista.

2) Gerar Lista de Palavras-chave

Para cada título:

- Dividir o título em palavras individuais.
- Ignorar palavras comuns (stop words) como: "a", "o", "as", "os", "um", "uma", "é", "de", etc.
- Armazenar cada palavra-chave junto com sua frase original.

3) Deslocamento Circular

Para cada palavra-chave, gerar uma versão circularmente deslocada da frase original com a palavra no início.

Exemplo:

- Título: "The quick brown fox"
- Palavra-chave: "brown"
- Deslocamento: "brown fox The quick"

4) Ordenar

Ordenar os deslocamentos alfabeticamente (baseados na palavra-chave deslocada).

5) Saída

Imprimir a lista ordenada no console ou em um novo arquivo de texto.


------------------------------------------------------------------------

📦 Arquivos para entrega:

Arquivo .txt ou .md contendo:
- Nome e matrícula dos membros do grupo;
- Estilo e linguagem de programação escolhidos;
- Link para o repositório no GitHub com o código do projeto;
- Link para o vídeo da videoaula;
- Instruções sobre como compilar e executar os testes do projeto.

------------------------------------------------------------------------

🔧 Como Executar este Programa:
- No terminal, dentro do diretório TP2, faça o seguinte:
- Compile o arquivo KeyWordInContext.cpp utilizando: g++ -std=c++17 -o KeyWordInContext KeyWordInContext.cpp
- Execute o executável KeyWordInContext.exe digitando no terminal: ./KeyWordInContext.exe input.txt
- Caso queira mudar o input, altere o arquivo input.txt neste diretório, inserindo Títulos em cada linha

🔧 Como Rodar os testes unitários deste Programa:
- No terminal, dentro do diretório TP2, digite os seguintes comandos:
- cmake -S . -B build
- cmake --build build
- ./build/test/test_keyword
- O programa CMake é necessário para compilar os testes, caso não o tenha no computador, utilize o executável diretamente
- Alternativamente, abra no vscode e instale a extensão CMake Tools no Visual Studio Code, e rode por meio do botão de testes imbutído
