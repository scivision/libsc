cmake_minimum_required(VERSION 3.15)
project(libsc
  LANGUAGES C)

include(CTest)

include(cmake/compilers.cmake)

if(NOT TARGET MPI::MPI_C)
  find_package(MPI COMPONENTS C)
endif()
find_package(ZLIB)

# --- iniparser
add_library(iniparser iniparser/dictionary.c iniparser/iniparser.c)
target_include_directories(iniparser
  INTERFACE iniparser
  PRIVATE ${PROJECT_BINARY_DIR}/include)

# --- libb64
add_library(libb64 libb64/cencode.c libb64/cdecode.c libb64/b64dec.c libb64/b64enc.c)
target_include_directories(libb64 PUBLIC libb64)

# --- sc
add_library(sc)
target_include_directories(sc
  PUBLIC src src/sc_builtin ${PROJECT_BINARY_DIR}/include)
target_link_libraries(sc PRIVATE iniparser libb64)
if(MPI_FOUND)
  target_link_libraries(sc PRIVATE MPI::MPI_C m)
endif()

add_subdirectory(src)

if(BUILD_TESTING)
  add_subdirectory(example)
  add_subdirectory(test)
endif(BUILD_TESTING)
