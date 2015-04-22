cmake_minimum_required(VERSION 2.8)
project(dansunhan)

set(dansunhan_VERSION_MAJOR 1)
set(dansunhan_VERSION_MINOR 6)
set(dansunhan_VERSION_PATCH 0)
set(CPACK_PACKAGE_VERSION_MAJOR 1)
set(CPACK_PACKAGE_VERSION_MINOR 6)
set(CPACK_PACKAGE_VERSION_PATCH 0)
set(dansunhan_VERSION "${dansunhan_VERSION_MAJOR}.${dansunhan_VERSION_MINOR}.${dansunhan_VERSION_PATCH}-alpha")

set(CPACK_GENERATOR ZIP)
set(CPACK_PACKAGE_FILE_NAME "${CMAKE_PROJECT_NAME}-${dansunhan_VERSION}-cpp")
include(CPack)

enable_testing()

if(MSVC)
  set(LIBRARY_PREFIX "")
  set(LIBRARY_SUFFIX .lib)
else()
  set(LIBRARY_PREFIX lib)
  set(LIBRARY_SUFFIX .a)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
endif()

add_subdirectory(src/main/cpp)
add_subdirectory(src/test/cpp)

install(FILES README.md LICENSE CHANGES.md src/dist/logo.bmp DESTINATION .)
