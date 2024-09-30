set (API_SAMPLE_SOURCES
  fctrading_api_sample.cpp
)

set (STREAM_SAMPLE_SOURCES
  fctrading_stream_sample.cpp
)

include_directories(
    ../../include/fastconnect)

add_executable (fastconnect_fctrading_api_sample ${API_SAMPLE_SOURCES})
add_executable (fastconnect_fctrading_stream_sample ${STREAM_SAMPLE_SOURCES})

target_link_libraries(fastconnect_fctrading_api_sample ssi-fastconnect)
target_link_libraries(fastconnect_fctrading_stream_sample ssi-fastconnect)

set (FCDATA_API_SAMPLE_SOURCES
  fcdata_api_sample.cpp
)

set (FCDATA_STREAM_SAMPLE_SOURCES
  fcdata_stream_sample.cpp
)

include_directories(
    ../../include/fastconnect)

add_executable (fastconnect_fcdata_api_sample ${FCDATA_API_SAMPLE_SOURCES})
add_executable (fastconnect_fcdata_stream_sample ${FCDATA_STREAM_SAMPLE_SOURCES})

target_link_libraries(fastconnect_fcdata_api_sample ssi-fastconnect)
target_link_libraries(fastconnect_fcdata_stream_sample ssi-fastconnect)
