
add_executable(matsprak_tests
    test_main.cpp
    parser_test.cpp
    tokenizer_test.cpp
    tokentreelookup_test.cpp
    ast_test.cpp
)
target_link_libraries(matsprak_tests gtest_main matsprak_lib)
target_include_directories(matsprak_tests PRIVATE ../src)
add_test(NAME matsprak_tests COMMAND matsprak_tests)



