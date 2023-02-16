cmake_minimum_required(VERSION 3.3)
project("CPP Return Codes")

enable_testing()

add_compile_options(-Wall -Wextra)

add_library(rc_shared SHARED return.cpp)
add_library(rc_static STATIC return.cpp)
add_library(rc_shared_only_int SHARED return.cpp)
add_library(rc_static_only_int STATIC return.cpp)

set_target_properties(rc_shared PROPERTIES OUTPUT_NAME rc)
set_target_properties(rc_static PROPERTIES OUTPUT_NAME rc)
set_target_properties(rc_shared_only_int PROPERTIES OUTPUT_NAME rc_only_int)
set_target_properties(rc_static_only_int PROPERTIES OUTPUT_NAME rc_only_int)

target_compile_options(rc_shared PUBLIC "--std=c++20")
target_compile_options(rc_static PUBLIC "--std=c++20")
target_compile_options(rc_shared_only_int PUBLIC "--std=c++20")
target_compile_options(rc_static_only_int PUBLIC "--std=c++20")
target_compile_definitions(rc_shared_only_int PUBLIC "-DRETURN_CODE_ONLY_INT")
target_compile_definitions(rc_static_only_int PUBLIC "-DRETURN_CODE_ONLY_INT")

add_executable(rc_test test_rc.cpp)
add_executable(rc_only_int_test test_rc_only_int.cpp)
target_link_libraries(rc_test rc_shared criterion)
target_link_libraries(rc_only_int_test rc_shared_only_int criterion)

add_test(NAME test_rc COMMAND rc_test)
add_test(NAME test_rc_only_int COMMAND rc_only_int_test)

