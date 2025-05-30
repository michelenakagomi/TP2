#include <gtest/gtest.h>
#include "../KeyWordInContext.cpp"  // ou KeyWordInContext.cpp se não houver header

TEST(EventManagerTests, Subscriptions) {
    EventManager em;
    DataStorage ds(em);
    KeyWordSeparator ks(em);
    StopWordFilter sf(em);
    CircleWords cw(em);
    KeyWordInContextApplication app(em);

    EXPECT_TRUE(em.subscriptions.find("load") != em.subscriptions.end());
    EXPECT_TRUE(em.subscriptions.find("start") != em.subscriptions.end());
    EXPECT_TRUE(em.subscriptions.find("store") != em.subscriptions.end());
    EXPECT_TRUE(em.subscriptions.find("separatekeyword") != em.subscriptions.end());
    EXPECT_TRUE(em.subscriptions.find("filter") != em.subscriptions.end());
    EXPECT_TRUE(em.subscriptions.find("circle") != em.subscriptions.end());
    EXPECT_TRUE(em.subscriptions.find("run") != em.subscriptions.end());
    EXPECT_TRUE(em.subscriptions.find("print") != em.subscriptions.end());

    EXPECT_EQ(em.subscriptions["print"].size(), 1);
}

TEST(EventManagerTests, Publish) {
    EventManager em;

    bool handler1_chamado = false;
    bool handler2_chamado = false;
    std::string dado_recebido1;
    std::string dado_recebido2;

    // Inscreve handler1 para o evento "test_event"
    em.subscribe("test_event", [&](const std::pair<std::string, std::any>& event) {
        handler1_chamado = true;
        std::string original = std::any_cast<std::string>(event.second);
        dado_recebido1 = original + "_handler1";
    });

    // Inscreve handler2 para o mesmo evento "test_event"
    em.subscribe("test_event", [&](const std::pair<std::string, std::any>& event) {
        handler2_chamado = true;
        std::string original = std::any_cast<std::string>(event.second);
        dado_recebido2 = original + "_handler2";
    });

    // Publica o evento
    em.publish({"test_event", std::string("hello world")});

    // Verifica se os dois handlers foram chamados
    EXPECT_TRUE(handler1_chamado);
    EXPECT_TRUE(handler2_chamado);

    // Verifica se os dados recebidos estão corretos
    EXPECT_EQ(dado_recebido1, "hello world_handler1");
    EXPECT_EQ(dado_recebido2, "hello world_handler2");
}

TEST(DataStorageTests, Load) {
    // Cria um arquivo temporário
    std::ofstream temp_file("temp_input.txt");
    temp_file << "Line one\n";
    temp_file << "Line two\n";
    temp_file << "Line three\n";
    temp_file.close();

    EventManager em;
    DataStorage ds(em);

    // Publica o evento "load"
    em.publish({"load", std::string("temp_input.txt")});

    // Verifica se os títulos foram carregados corretamente
    ASSERT_EQ(ds.titulos.size(), 3);
    EXPECT_EQ(ds.titulos[0], "Line one");
    EXPECT_EQ(ds.titulos[1], "Line two");
    EXPECT_EQ(ds.titulos[2], "Line three");

    // Limpa o arquivo temporário
    std::remove("temp_input.txt");
}

TEST(DataStorageTests, SeparateWords) {
    EventManager em;
    DataStorage ds(em);

    std::vector<std::vector<std::string>> dados_recebidos;
    std::vector<std::string> printed_data;

    bool capturados = false;
    std::vector<std::string> dados_capturados;

    // Captura os eventos de palavras separadas
    em.subscribe("separatekeyword", [&](const auto& event) {
        auto palavras = std::any_cast<std::vector<std::string>>(event.second);
        dados_recebidos.push_back(palavras);
    });

    // Escuta o evento "print"
    em.subscribe("print", [&](const auto& event) {
        capturados = true;
        dados_capturados = std::any_cast<std::vector<std::string>>(event.second);
    });

    // Carrega os dados diretamente (para evitar ter que ler o arquivo)
    ds.titulos = {
        "The quick brown fox",
        "Jumped over the lazy dog"
    };

    const std::vector<std::string> fake_titles = {
        "quick brown The", "brown The quick", "Jumped over the lazy dog"
    };

    // Publica o evento que ativa o método separateWords
    em.publish({"start", {}});

    ASSERT_EQ(dados_recebidos.size(), 2);

    EXPECT_EQ(dados_recebidos[0], (std::vector<std::string>{"The", "quick", "brown","fox"}));
    EXPECT_EQ(dados_recebidos[1], (std::vector<std::string>{"Jumped", "over", "the", "lazy", "dog"}));

    EXPECT_TRUE(printed_data.empty());

    em.publish({"print", fake_titles});
    ASSERT_TRUE(capturados);
    ASSERT_EQ(dados_capturados.size(), 3);
    EXPECT_EQ(dados_capturados[0], "quick brown The");
    EXPECT_EQ(dados_capturados[1], "brown The quick");
    EXPECT_EQ(dados_capturados[2], "Jumped over the lazy dog");

}

TEST(DataStorageTests, StoreKeywordTitle) {
    EventManager em;
    DataStorage ds(em);

    // Publicar três eventos "store" com títulos fora de ordem
    em.publish({"store", std::string("zebra is here")});
    em.publish({"store", std::string("apple comes first")});
    em.publish({"store", std::string("monkey in the middle")});

    // Verifica se os títulos foram armazenados e ordenados corretamente
    ASSERT_EQ(ds.keyword_titles.size(), 3);
    EXPECT_EQ(ds.keyword_titles[0], "apple comes first");
    EXPECT_EQ(ds.keyword_titles[1], "monkey in the middle");
    EXPECT_EQ(ds.keyword_titles[2], "zebra is here");
}

TEST(KeyWordSeparatorTests, CreateTuple){
    EventManager em;
    KeyWordSeparator ks(em);

    bool filtrado = false;

    std::vector<std::string> palavras = {
        "The", "quick", "brown", "fox"
    };

    std::vector<std::string> palavras_recebidas;
    std::vector<std::string> palavras_original;

    em.subscribe("filter", [&](const auto& event) {
        filtrado = true;
        auto dados = std::any_cast<std::pair<std::string, std::vector<std::string>>>(event.second);
        palavras_recebidas.push_back(dados.first);  //Pega os dados da primeira tupla
        palavras_original = dados.second;           //Pega o título original (separado em palavras)
    });


    em.publish({"separatekeyword", palavras});

    EXPECT_TRUE(filtrado);
    EXPECT_EQ(palavras_original, palavras);
    EXPECT_EQ(palavras_recebidas.size(), palavras.size());
    EXPECT_EQ(palavras_recebidas[0], "The");
    EXPECT_EQ(palavras_recebidas[1], "quick");
    EXPECT_EQ(palavras_recebidas[2], "brown");
    EXPECT_EQ(palavras_recebidas[3], "fox");
}

TEST(StopWordFilterTests, FilterStopWord){
    EventManager em;
    StopWordFilter sf(em);

    std::vector<std::pair<std::string, std::vector<std::string>>> eventos_recebidos;


    em.subscribe("circle", [&](const auto& event) {
        auto [palavra, lista] = std::any_cast<std::pair<std::string, std::vector<std::string>>>(event.second);
        eventos_recebidos.emplace_back(palavra, lista);
    });

    std::vector<std::pair<std::string, std::vector<std::string>>> entradas = {
        {"The", {"The", "quick", "fox"}},
        {"quick", {"The", "quick", "fox"}},
        {"and", {"Dogs", "and", "cats"}},
        {"cats", {"Dogs", "and", "cats"}},
        {"is", {"A","fox", "is", "fast"}},
        {"fox", {"A","fox", "is", "fast"}}
    };

    // Publica todos os pares como eventos "filter"
    for (const auto& entrada : entradas) {
        em.publish({"filter", entrada});
    }

    // "quick", "cats" e "fox" são as únicas não-stopwords
    std::vector<std::pair<std::string, std::vector<std::string>>> esperadas = {
        {"quick", {"The", "quick", "fox"}},
        {"cats", {"Dogs", "and", "cats"}},
        {"fox", {"A", "fox", "is", "fast"}}
    };

    ASSERT_EQ(eventos_recebidos.size(), esperadas.size());

    for (size_t i = 0; i < esperadas.size(); ++i) {
        EXPECT_EQ(eventos_recebidos[i].first, esperadas[i].first);
        EXPECT_EQ(eventos_recebidos[i].second, esperadas[i].second);
    }

}

TEST(CircleWordsTests, CircleWordsRotation) {
    EventManager em;
    CircleWords cw(em);

    std::vector<std::string> armazenadas;

    // Captura os resultados publicados como "store"
    em.subscribe("store", [&](const auto& event) {
        armazenadas.push_back(std::any_cast<std::string>(event.second));
    });

    // Palavras e palavra-chave: deve rotacionar para começar em "quick"
    std::vector<std::string> frase = {"The", "quick", "brown", "fox"};
    std::string keyword = "quick";

    // Publica o evento esperado
    em.publish({"circle", std::make_pair(keyword, frase)});

    // Esperado: ["quick", "brown", "fox", "The"]
    std::string esperado = "quick brown fox The";

    ASSERT_EQ(armazenadas.size(), 1);
    EXPECT_EQ(armazenadas[0], esperado);

    keyword = "brown";
    em.publish({"circle", std::make_pair(keyword, frase)});

    esperado = "brown fox The quick";

    ASSERT_EQ(armazenadas.size(), 2);
    EXPECT_EQ(armazenadas[1], esperado);

    keyword = "fox";
    em.publish({"circle", std::make_pair(keyword, frase)});

    esperado = "fox The quick brown";

    ASSERT_EQ(armazenadas.size(), 3);
    EXPECT_EQ(armazenadas[2], esperado);

}

TEST(KeyWordInContextApplicationTests, RunAndPrintEvents) {
    EventManager em;
    KeyWordInContextApplication app(em);

    bool load_called = false;
    bool start_called = false;
    std::string load_path;
    std::vector<std::string> printed_data;

    em.subscribe("load", [&](const auto& event) {
        load_called = true;
        load_path = std::any_cast<std::string>(event.second);
    });

    em.subscribe("start", [&](const auto& event) {
        start_called = true;
    });

    em.subscribe("print", [&](const auto& event) {
        printed_data = std::any_cast<std::vector<std::string>>(event.second);
    });

    std::string fake_path = "fake_input.txt";

    // Chama o método run com o "caminho" do arquivo
    app.run({"run", fake_path});

    EXPECT_TRUE(load_called);
    EXPECT_TRUE(start_called);
    EXPECT_EQ(load_path, fake_path);

    // Simular evento print manualmente para testar o stop (print)
    std::vector<std::string> dados = {"linha1", "linha2", "linha3"};
    em.publish({"print", dados});

    // Aqui o teste verifica se o vetor capturado é igual ao que foi publicado
    EXPECT_EQ(printed_data, dados);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}