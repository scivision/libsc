include(CheckCSourceCompiles)


set(CMAKE_REQUIRED_INCLUDES ${PROJECT_SOURCE_DIR}/src/sc_builtin)
set(CMAKE_REQUIRED_LIBRARIES)

check_c_source_compiles("#include <obstack.h>
int main(void) {static struct obstack myobstack;
obstack_free (&myobstack,NULL);
return 0;}" HAS_OBSTACK)

set(tests allgather arrays darray_work dmatrix_pool dmatrix)
if(HAS_OBSTACK)
  list(APPEND tests builtin)
endif()
if(NOT MSVC AND NOT (WIN32 AND CMAKE_C_COMPILER_ID STREQUAL Clang))
  list(APPEND tests io_sink)
endif()

foreach(t ${tests})
  add_executable(test_${t} test_${t}.c)
  target_link_libraries(test_${t} PRIVATE sc)
  if(ZLIB_FOUND)
    target_link_libraries(test_${t} PRIVATE ZLIB::ZLIB)
  endif()
  if(MPI_FOUND)
    target_link_libraries(test_${t} PRIVATE MPI::MPI_C)
  endif()
  if(NOT WIN32)
    target_link_libraries(test_${t} PRIVATE m)
  endif()

  add_test(NAME sc:test:${t} COMMAND ${MPIEXEC_EXECUTABLE} ${MPIEXEC_NUMPROC_FLAG} ${MPIEXEC_MAX_NUMPROCS} $<TARGET_FILE:test_${t}>)
endforeach()
