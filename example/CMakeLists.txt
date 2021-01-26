add_executable(sc_function function/function.c)
target_include_directories(sc_function PRIVATE ${PROJECT_SOURCE_DIR}/src ${PROJECT_BINARY_DIR}/include)
target_link_libraries(sc_function PRIVATE sc MPI::MPI_C m)
