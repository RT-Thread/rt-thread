add_library(pico_test INTERFACE)

target_include_directories(pico_test INTERFACE ${CMAKE_CURRENT_LIST_DIR}/include)
target_link_libraries(pico_test INTERFACE pico_stdlib)
