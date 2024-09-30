

set (SOURCES
 callback_manager.cpp
 connection.cpp
 connection_impl.cpp
 default_websocket_client.cpp
 http_sender.cpp
 hub_connection.cpp
 hub_connection_impl.cpp
 hub_proxy.cpp
 internal_hub_proxy.cpp
 logger.cpp
 request_sender.cpp
 signalr_client_config.cpp
 stdafx.cpp
 trace_log_writer.cpp
 transport.cpp
 transport_factory.cpp
 url_builder.cpp
 web_request.cpp
 web_request_factory.cpp
 websocket_transport.cpp
)

add_library (microsoft-signalr ${SOURCES})
set_target_properties(microsoft-signalr PROPERTIES COMPILE_FLAGS "-DUSE_CPPRESTSDK" )

  if(APPLE)
    target_link_libraries(microsoft-signalr
      PUBLIC ${CPPREST_LIB}
      PRIVATE OpenSSL::SSL Boost::boost Boost::system Boost::chrono Boost::thread
    )
  elseif(NOT WIN32)
    target_link_libraries(microsoft-signalr
      PUBLIC ${CPPREST_LIB} Boost::system
      PRIVATE OpenSSL::SSL
    )
  else()
    target_link_libraries(microsoft-signalr
      PUBLIC ${CPPREST_LIB}
    )
  endif()

  include(GNUInstallDirs)

  install(TARGETS microsoft-signalr
    # Creates the microsoft-signalr-targets.cmake file which allows find_package() to work
    EXPORT microsoft-signalr-targets
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
  )
  
  # Create the microsoft-signalr-config.cmake with resolved values for variables used to build
  configure_file(microsoft-signalr-config.in.cmake "${CMAKE_CURRENT_BINARY_DIR}/microsoft-signalr-config.cmake" @ONLY)
  
  install(
    FILES ${CMAKE_CURRENT_BINARY_DIR}/microsoft-signalr-config.cmake
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/share/microsoft-signalr
  )
  
  install(EXPORT microsoft-signalr-targets
    FILE microsoft-signalr-targets.cmake
    NAMESPACE microsoft-signalr::
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/share/microsoft-signalr
  )