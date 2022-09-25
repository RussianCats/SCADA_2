include_directories(
   .
)

set(example_SRCS
   simple_server.cpp
)

IF(WIN32)
set_source_files_properties(${example_SRCS}
                                       PROPERTIES LANGUAGE CXX)
ENDIF(WIN32)

add_executable(send_server
  ${example_SRCS}
)

target_link_libraries(send_server
    lib60870
)
