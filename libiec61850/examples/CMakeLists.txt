add_subdirectory(server_example_basic_io)
add_subdirectory(iec61850_client_example4)

if (NOT WIN32)
    add_subdirectory(mms_utility)
endif(NOT WIN32)

if(WIN32)
    if (EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/../third_party/winpcap/Lib/wpcap.lib")
        set(BUILD_SV_GOOSE_EXAMPLES ON)
        message("Found winpcap -> compile examples for GOOSE and SV")
    endif()
else()
    set(BUILD_SV_GOOSE_EXAMPLES ON)
endif()

if(WITH_MBEDTLS)
add_subdirectory(tls_client_example)
add_subdirectory(tls_server_example)
endif(WITH_MBEDTLS)


