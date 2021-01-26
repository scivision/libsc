include(CheckCSourceCompiles)

set(CMAKE_REQUIRED_INCLUDES ${PROJECT_SOURCE_DIR}/src/sc_builtin)
set(CMAKE_REQUIRED_LIBRARIES)

check_c_source_compiles("#include <obstack.h>
int main(void) {static struct obstack myobstack;
obstack_free (&myobstack,NULL);
return 0;}" HAS_OBSTACK)

set(tests allgather arrays darray_work dmatrix_pool dmatrix io_sink)
if(HAS_OBSTACK)
  list(APPEND tests builtin)
endif()

foreach(t ${tests})
  add_executable(test_${t} test_${t}.c)
  target_link_libraries(test_${t} PRIVATE sc MPI::MPI_C ZLIB::ZLIB m)

  add_test(NAME ${t} COMMAND $<TARGET_FILE:test_${t}>)
endforeach()
