if (NOT TARGET pico_multicore)
    pico_add_library(pico_multicore)

    target_include_directories(pico_multicore_headers INTERFACE ${CMAKE_CURRENT_LIST_DIR}/include)

    pico_mirrored_target_link_libraries(pico_multicore INTERFACE pico_base)
endif()



