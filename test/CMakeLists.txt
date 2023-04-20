function(add_test_executable test_name)
    set(test_src "${test_name}_test.cpp")
    add_executable(${test_name}_test ${test_src})
    target_link_libraries(${test_name}_test gtest_main matsprak_lib)
    target_include_directories(${test_name}_test PRIVATE ../src)
    add_test(NAME ${test_name} COMMAND ${test_name}_test)
endfunction()


add_test_executable(tokenizer)
