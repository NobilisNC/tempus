cmake_minimum_required(VERSION 3.5 FATAL_ERROR)
project(tempus_tests VERSION 1.0.0 LANGUAGES CXX)

add_executable(
  main_tests
    main_tests.cc
)

target_link_libraries(
  main_tests

    PUBLIC
      deps::catch2
      tempus
)

add_test(NAME tests::main COMMAND main_tests)
