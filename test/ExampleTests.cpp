#include <gtest/gtest.h>
#include "../Example.cpp"
using namespace std;

TEST(ExampleTests, SplitWordsTest){
    std::ofstream ofs("inputtest.txt");
    ofs << "The quick brown fox\n";
    ofs << "A brown cat sat\n";
    ofs << "The cat is brown\n";
    ofs.close();

    board["keywords"].clear();
    text_board["lines"].clear();

    split_words();
    // 4. Validar text_board["lines"]
    std::vector<std::string> expected_lines = {
        "The quick brown fox",
        "A brown cat sat",
        "The cat is brown"
    };
    EXPECT_EQ(text_board["lines"], expected_lines);

    // 5. Validar board["keywords"]
    // Vamos checar algumas palavras-chave (a lista pode ser maior)
    // Note que as palavras aparecem junto da linha que as contém
    std::vector<std::pair<std::string, std::string>> expected_keywords = {
        {"The", "The quick brown fox"},
        {"quick", "The quick brown fox"},
        {"brown", "The quick brown fox"},
        {"fox", "The quick brown fox"},
        {"A", "A brown cat sat"},
        {"brown", "A brown cat sat"},
        {"cat", "A brown cat sat"},
        {"sat", "A brown cat sat"},
        {"The", "The cat is brown"},
        {"cat", "The cat is brown"},
        {"is", "The cat is brown"},
        {"brown", "The cat is brown"}
    };

    // Checar se todos os esperados estão dentro do resultado (order pode variar)
    for (const auto& expected : expected_keywords) {
        auto it = std::find(board["keywords"].begin(), board["keywords"].end(), expected);
        EXPECT_NE(it, board["keywords"].end()) << "Keyword not found: " << expected.first;
    }   
}