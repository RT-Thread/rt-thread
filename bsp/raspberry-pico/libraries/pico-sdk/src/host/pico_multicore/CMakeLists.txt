if (NOT TARGET pico_multicore)
    add_library(pico_multicore INTERFACE)

    target_include_directories(pico_multicore INTERFACE ${CMAKE_CURRENT_LIST_DIR}/include)
endif()



