cmake_minimum_required(VERSION 3.10)
project(TP2)

set(CMAKE_CXX_STANDARD 17)

enable_testing()
# Adiciona subdiretórios
add_subdirectory(external/googletest)
add_subdirectory(test)

# Adiciona a biblioteca com o código que você quer testar
add_library(kwic STATIC KeyWordInContext.cpp)

target_compile_definitions(test_keyword PRIVATE UNIT_TEST)
# Opcional: se você tiver um header separado
target_include_directories(kwic PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
