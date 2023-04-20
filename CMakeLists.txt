
cmake_minimum_required(VERSION 3.23)
project(matsprak-2023)

add_executable(
    matsprak-2023
    src/main.cpp
    src/file.cpp
    src/tokenizer.cpp
)


target_compile_features(
    matsprak-2023
    PRIVATE
    cxx_std_20
    )

find_package(Threads)
target_link_libraries(
    matsprak-2023
    PRIVATE
    ${CMAKE_THREAD_LIBS_INIT}
    )


file(
    COPY
    demo
    DESTINATION
    .
)
