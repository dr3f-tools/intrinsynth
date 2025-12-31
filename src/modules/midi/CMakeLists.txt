project(midi LANGUAGES CXX)

add_library(midi SHARED
    device_list.cpp
)
target_include_directories(midi PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_link_libraries(midi PRIVATE
    libremidi::libremidi
    logger
)