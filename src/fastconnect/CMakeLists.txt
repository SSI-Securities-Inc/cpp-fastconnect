set (SOURCES
  fctrading_api_client.cpp
  fctrading_stream_client.cpp
  base64.cpp
  util.cpp
  fcdata_api_client.cpp
  fcdata_stream_client.cpp
  ../../third_party_code/pugixml/src/pugixml.cpp
)

add_library (ssi-fastconnect ${SOURCES})

if(CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
    if(WERROR)
        target_compile_options(ssi-fastconnect PRIVATE /WX)
    endif()
    if(WALL)
        target_compile_options(ssi-fastconnect PRIVATE /Wall)
    endif()
    target_compile_options(ssi-fastconnect PRIVATE
        /wd4820 # padding added after data member
        /wd4514 # unreferenced inline function removed
        /wd5045 # compiler will insert Spectre mitigation if /Qspectre switch is added
        /wd4464 # relative include paths
        /wd4711 # function 'x' selected for automatic inline expansion
        /wd4710 # function not inlined
        /experimental:external /external:anglebrackets /external:templates- /external:W0
        # /GR- # do not disable run-time type information, it can be needed by libraries we depend on, like boost
        /guard:cf # enable control-flow guard
        /EHa # enable C++ EH (w/ SEH exceptions)
    )
else()
    if(WERROR)
        target_compile_options(ssi-fastconnect PRIVATE -Werror)
    endif()
    if(WALL)
        target_compile_options(ssi-fastconnect PRIVATE -Wall)
    endif()

    target_compile_options(ssi-fastconnect PRIVATE -Wextra -Wpedantic -Wno-unknown-pragmas)
endif()

target_link_libraries(ssi-fastconnect PUBLIC microsoft-signalr)
if(NOT USE_CPPRESTSDK)
  target_link_libraries(ssi-fastconnect)
else()
  set_target_properties(ssi-fastconnect PROPERTIES COMPILE_FLAGS "-DUSE_CPPRESTSDK" )

  if(APPLE)
    target_link_libraries(ssi-fastconnect
      PUBLIC ${CPPREST_LIB}
      PRIVATE OpenSSL::SSL Boost::boost Boost::system Boost::chrono Boost::thread
    )
  elseif(NOT WIN32)
    target_link_libraries(ssi-fastconnect
      PUBLIC ${CPPREST_LIB} Boost::system
      PRIVATE OpenSSL::SSL
    )
  else()
    target_link_libraries(ssi-fastconnect
      PUBLIC ${CPPREST_LIB}
    )
  endif()
endif() # USE_CPPRESTSDK

include(GNUInstallDirs)

install(TARGETS ssi-fastconnect
  # Creates the ssi-fastconnect-targets.cmake file which allows find_package() to work
  EXPORT ssi-fastconnect-targets
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

# Create the ssi-fastconnect-config.cmake with resolved values for variables used to build
configure_file(ssi-fastconnect-config.in.cmake "${CMAKE_CURRENT_BINARY_DIR}/ssi-fastconnect-config.cmake" @ONLY)

install(
  FILES ${CMAKE_CURRENT_BINARY_DIR}/ssi-fastconnect-config.cmake
  DESTINATION ${CMAKE_INSTALL_LIBDIR}/share/ssi-fastconnect
)

install(EXPORT ssi-fastconnect-targets
  FILE ssi-fastconnect-targets.cmake
  NAMESPACE ssi-fastconnect::
  DESTINATION ${CMAKE_INSTALL_LIBDIR}/share/ssi-fastconnect
)