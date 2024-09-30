cmake_minimum_required (VERSION 3.14)

if(DEFINED ENV{VCPKG_ROOT} AND NOT DEFINED CMAKE_TOOLCHAIN_FILE)
  set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake")
endif()

project (ssi-fastconnect)

set(WERROR true CACHE BOOL "Enable warnings as errors.")
set(WALL true CACHE BOOL "Enable all warnings.")
set(BUILD_SHARED_LIBS ON CACHE BOOL "Build shared libraries")

if(NOT WIN32)
  set(EXTRA_FLAGS "-std=c++11 -fPIC -DNO_FASTCONNECTCLIENT_EXPORTS")
else()
  set(EXTRA_FLAGS "-DFASTCONNECTCLIENT_EXPORTS")
endif()
set(USE_CPPRESTSDK true)
  find_package(cpprestsdk REQUIRED)
  set(CPPREST_LIB "cpprestsdk::cpprest")


if(INJECT_HEADER_AFTER_STDAFX)
  string(APPEND EXTRA_FLAGS " -DINJECT_HEADER_AFTER_STDAFX=${INJECT_HEADER_AFTER_STDAFX}")
endif()
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${EXTRA_FLAGS}")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${CMAKE_LDFLAGS}")



include_directories (include)
include_directories (third_party_code/signalrclient/include)
include_directories (third_party_code/pugixml/src)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)

add_subdirectory(src/fastconnect)
add_subdirectory(third_party_code)

# if(BUILD_TESTING)
#   enable_testing()
#   add_subdirectory(test)
# endif()

add_subdirectory(samples/fastconnectsample)

install(DIRECTORY include/ DESTINATION include/)