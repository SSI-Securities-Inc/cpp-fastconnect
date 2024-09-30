cmake_minimum_required (VERSION 3.14)

if(DEFINED ENV{VCPKG_ROOT} AND NOT DEFINED CMAKE_TOOLCHAIN_FILE)
  set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake")
endif()

set(WERROR true CACHE BOOL "Enable warnings as errors.")
set(WALL true CACHE BOOL "Enable all warnings.")
set(BUILD_SHARED_LIBS ON CACHE BOOL "Build shared libraries")

if(NOT WIN32)
  set(EXTRA_FLAGS "-std=c++11 -fPIC -DNO_SIGNALRCLIENT_EXPORTS")
else()
  set(EXTRA_FLAGS "-DSIGNALRCLIENT_EXPORTS")
endif()


if(INJECT_HEADER_AFTER_STDAFX)
  string(APPEND EXTRA_FLAGS " -DINJECT_HEADER_AFTER_STDAFX=${INJECT_HEADER_AFTER_STDAFX}")
endif()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${EXTRA_FLAGS}")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${CMAKE_LDFLAGS}")

find_package(cpprestsdk REQUIRED)
set(CPPREST_LIB "cpprestsdk::cpprest")


include_directories (include)

if(NOT WIN32)
	if(APPLE)
	  file(GLOB OPENSSL_ROOT_DIR /usr/local/Cellar/openssl/*)
	  list(REVERSE OPENSSL_ROOT_DIR)
	endif()

	find_package(OpenSSL 1.0.0 REQUIRED)
	find_package(Boost REQUIRED COMPONENTS system thread chrono)
endif()

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)

add_subdirectory(src/signalrclient)


install(DIRECTORY include/ DESTINATION include/)