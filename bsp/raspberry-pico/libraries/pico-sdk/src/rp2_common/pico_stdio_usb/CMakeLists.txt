if (TARGET tinyusb_device_unmarked)
    add_library(pico_stdio_usb INTERFACE)

    target_include_directories(pico_stdio_usb INTERFACE ${CMAKE_CURRENT_LIST_DIR}/include)

    target_sources(pico_stdio_usb INTERFACE
        ${CMAKE_CURRENT_LIST_DIR}/stdio_usb.c
        ${CMAKE_CURRENT_LIST_DIR}/stdio_usb_descriptors.c
    )

    target_link_libraries(pico_stdio_usb INTERFACE
        tinyusb_device_unmarked
        pico_stdio
        pico_time
    )

    target_compile_definitions(pico_stdio_usb INTERFACE
            PICO_STDIO_USB=1
    )
endif()