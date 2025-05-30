enable_testing()

# Adiciona o executável de testes
add_executable(test_keyword test_keyword.cpp)

# Liga o executável com a biblioteca de código + GoogleTest
target_link_libraries(test_keyword
    kwic
    gtest
    gtest_main
)

# Adiciona os testes ao CTest
add_test(NAME KWICTest COMMAND test_keyword ${CMAKE_SOURCE_DIR}/input.txt)