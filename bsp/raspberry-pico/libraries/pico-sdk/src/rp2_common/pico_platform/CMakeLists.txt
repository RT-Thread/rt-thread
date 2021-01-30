if (NOT TARGET pico_platform_headers)
    add_library(pico_platform_headers INTERFACE)

    target_compile_definitions(pico_platform_headers INTERFACE
            PICO_NO_HARDWARE=0
            PICO_ON_DEVICE=1
            PICO_BUILD=1
    )

    target_include_directories(pico_platform_headers INTERFACE ${CMAKE_CURRENT_LIST_DIR}/include)

    target_link_libraries(pico_platform_headers INTERFACE hardware_regs)
endif()

if (NOT TARGET pico_platform)
    add_library(pico_platform INTERFACE)
    target_sources(pico_platform INTERFACE
            ${CMAKE_CURRENT_LIST_DIR}/platform.c)

    target_link_libraries(pico_platform INTERFACE pico_platform_headers)
endif()

function(pico_add_platform_library TARGET)
    target_link_libraries(pico_platform INTERFACE ${TARGET})
endfunction()