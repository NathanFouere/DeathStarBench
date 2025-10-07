add_executable(
    UniqueIdService
    UniqueIdService.cpp
)

target_include_directories(
    UniqueIdService PRIVATE
)

target_link_libraries(
    UniqueIdService
)

install(TARGETS UniqueIdService DESTINATION ./)