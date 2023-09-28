# This file may be included directly by a build to get common SDK macros and types

if (NOT TARGET pico_platform_headers)
    add_library(pico_platform_headers INTERFACE)

    target_compile_definitions(pico_platform_headers INTERFACE
            PICO_NO_HARDWARE=1
            PICO_ON_DEVICE=0
            PICO_BUILD=1
    )

    target_include_directories(pico_platform_headers INTERFACE ${CMAKE_CURRENT_LIST_DIR}/include)
endif()

if (NOT TARGET pico_platform)
    if (COMMAND pico_add_platform_library)
        pico_add_platform_library(pico_platform)
    else()
        add_library(pico_platform INTERFACE)
    endif()

    target_sources(pico_platform INTERFACE
        ${CMAKE_CURRENT_LIST_DIR}/platform_base.c
    )

    target_link_libraries(pico_platform INTERFACE pico_platform_headers pico_bit_ops ${PICO_PLATFORM_EXTRA_LIBRARIES})
endif()

function(pico_add_platform_library TARGET)
    target_link_libraries(pico_platform INTERFACE ${TARGET})
endfunction()
