cmake_minimum_required(VERSION 3.13)

add_executable(convertedMicroServices UniqueIdHandler/UniqueIdHandler.cpp)

set_target_properties(convertedMicroServices PROPERTIES
    CXX_STANDARD 17
    OUTPUT_NAME convertedMicroServices
)

target_link_libraries(
    convertedMicroServices
)


if(CMAKE_SYSTEM_NAME MATCHES "Emscripten")
    set_target_properties(convertedMicroServices PROPERTIES LINK_FLAGS "-lembind")
endif()
