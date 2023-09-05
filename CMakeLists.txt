cmake_minimum_required(VERSION 3.23)
project(matsprak-2023)

enable_testing()

add_library(
    matsprak_lib
    STATIC
    src/tokenizer.cpp
    src/file.cpp
    src/parser.cpp
    src/token.cpp
    src/ast.cpp
)
target_compile_features(matsprak_lib PRIVATE cxx_std_20)

add_executable(matsprak-2023 src/main.cpp)
target_link_libraries(matsprak-2023 PRIVATE matsprak_lib)

find_package(Threads)
target_link_libraries(matsprak-2023 PRIVATE ${CMAKE_THREAD_LIBS_INIT})

file(COPY demo DESTINATION .)

add_subdirectory(lib)
add_subdirectory(test)
