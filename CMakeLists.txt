project(fullproc)
cmake_minimum_required(VERSION 3.8.0)
add_executable(fullproc fullproc.cpp)

include(TestBigEndian)
include(CheckTypeSize)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_CXX_STANDARD 17) # appeared in CMake 3.8
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)
set(SHARE_DIR ${CMAKE_INSTALL_PREFIX}/share/fullproc)

option (FORCE_COLORED_OUTPUT "Always produce ANSI-colored output (GNU/Clang only)." FALSE)
if (${FORCE_COLORED_OUTPUT})
  if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    add_compile_options (-fdiagnostics-color=always)
  elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    add_compile_options (-fcolor-diagnostics)
  endif ()
endif ()

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")
find_package(GMPXX REQUIRED)
target_link_libraries(fullproc ${GMP_LIBRARY} ${GMPXX_LIBRARIES})

install(TARGETS fullproc DESTINATION bin)

test_big_endian(BIGENDIAN)
check_type_size("int" INT)
check_type_size("int *" INT_POINTER)

set(FULLPROC_MAJOR_VERSION 0)
set(FULLPROC_MINOR_VERSION 1)
set(FULLPROC_PATCH_VERSION 0)
set(FULLPROC_VERSION ${FULLPROC_MAJOR_VERSION}.${FULLPROC_MINOR_VERSION}.${FULLPROC_PATCH_VERSION})

set(CPACK_PACKAGE_VERSION_MAJOR ${FULLPROC_MAJOR_VERSION})
set(CPACK_PACKAGE_VERSION_MINOR ${FULLPROC_MINOR_VERSION})
set(CPACK_PACKAGE_VERSION_PATCH ${FULLPROC_PATCH_VERSION})
set(CPACK_SOURCE_IGNORE_FILES /\\\\.git;.*~)
include(CPack)

include(CTest)
