cmake_minimum_required(VERSION 4.0.2)

set(This ExampleTests)

set(Sources
    ExampleTests.cpp
)

add_executable(${This} ${Sources})
target_link_libraries(${This} PUBLIC
    gtest_main
    TP2KWIC
)

add_test(
    NAME ${This}
    COMMAND ${This}
)