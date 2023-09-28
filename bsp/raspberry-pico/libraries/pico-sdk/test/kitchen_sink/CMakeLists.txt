add_library(kitchen_sink_libs INTERFACE)
target_link_libraries(kitchen_sink_libs INTERFACE
    hardware_adc
    hardware_clocks
    hardware_divider
    hardware_exception
    hardware_dma
    hardware_flash
    hardware_gpio
    hardware_i2c
    hardware_interp
    hardware_irq
    hardware_pio
    hardware_pll
    hardware_pwm
    hardware_resets
    hardware_rtc
    hardware_uart
    hardware_spi
    hardware_sync
    hardware_timer
    hardware_uart
    hardware_vreg
    hardware_watchdog
    hardware_xosc
    pico_bit_ops
    pico_bootrom
    pico_bootsel_via_double_reset
    pico_divider
    pico_double
    pico_fix_rp2040_usb_device_enumeration
    pico_flash
    pico_float
    pico_i2c_slave
    pico_int64_ops
    pico_malloc
    pico_mem_ops
    pico_multicore
    pico_platform
    pico_rand
    pico_stdlib
    pico_sync
    pico_time
    pico_unique_id
    pico_util
)

add_library(kitchen_sink_options INTERFACE)

target_compile_options(kitchen_sink_options INTERFACE
        -Werror
        -Wall
        -Wextra
        #        -pedantic

        -Wnull-dereference
        -Wuninitialized
        -Wunused
        -Wcast-align
        -Wall
        -Wcast-qual
        -Wfloat-equal
        -Wmissing-format-attribute
        #-Wconversion
        -Wsign-compare
        $<$<COMPILE_LANGUAGE:C>:-Wstrict-prototypes>

        -Wno-inline
        # todo not sure these are true, but investigate
        #-Wpacked

        # todo we have some of these in usb_device_tiny to try to make it more readable.. perhaps doxygen would help here instead
        -Wredundant-decls

        -Wno-shadow
        -Wno-missing-field-initializers
        -Wno-missing-braces
        -Wno-multichar

        # todo useful but fix later
        #-Wundef
        )

if (PICO_C_COMPILER_IS_CLANG)
    # todo fix up clang warnings
    target_compile_options(kitchen_sink_options INTERFACE
            -Wno-cast-qual
            -Wno-unused-function
            -Wno-format)
endif()

target_compile_definitions(kitchen_sink_libs INTERFACE
        PARAM_ASSERTIONS_ENABLE_ALL=1 # want to check all the assertions for compilation warnings
        PICO_AUDIO_DMA_IRQ=1
)

add_executable(kitchen_sink ${CMAKE_CURRENT_LIST_DIR}/kitchen_sink.c)
target_link_libraries(kitchen_sink kitchen_sink_libs kitchen_sink_options)
pico_set_program_name(kitchen_sink "Wombat tentacles")
pico_add_extra_outputs(kitchen_sink)

add_executable(kitchen_sink_extra_stdio ${CMAKE_CURRENT_LIST_DIR}/kitchen_sink.c)
if (COMMAND suppress_tinyusb_warnings)
    # Explicitly suppress warnings in TinyUSB files which have them (this has to be done
    # from the project that uses them per CMake "feature"). Note the function comes from
    # TinyUSB itself, so we have to guard against TinyUSB not being present with the above if
    suppress_tinyusb_warnings()
endif()
target_compile_definitions(kitchen_sink_extra_stdio PRIVATE
        TUD_OPT_RP2040_USB_DEVICE_ENUMERATION_FIX=1)
if (TARGET pico_lwip)
    set_source_files_properties(
            ${PICO_LWIP_PATH}/src/core/ipv4/ip4_frag.c
            PROPERTIES
            COMPILE_FLAGS "-Wno-null-dereference")

endif()
target_link_libraries(kitchen_sink_extra_stdio kitchen_sink_libs kitchen_sink_options)
pico_add_extra_outputs(kitchen_sink_extra_stdio)
pico_enable_stdio_usb(kitchen_sink_extra_stdio 1)
pico_enable_stdio_semihosting(kitchen_sink_extra_stdio 1)

add_executable(kitchen_sink_copy_to_ram ${CMAKE_CURRENT_LIST_DIR}/kitchen_sink.c)
pico_set_binary_type(kitchen_sink_copy_to_ram copy_to_ram)
target_link_libraries(kitchen_sink_copy_to_ram kitchen_sink_libs kitchen_sink_options)
pico_add_extra_outputs(kitchen_sink_copy_to_ram)

add_executable(kitchen_sink_no_flash ${CMAKE_CURRENT_LIST_DIR}/kitchen_sink.c)
pico_set_binary_type(kitchen_sink_no_flash no_flash)
target_link_libraries(kitchen_sink_no_flash kitchen_sink_libs kitchen_sink_options)
pico_add_extra_outputs(kitchen_sink_no_flash)

add_executable(kitchen_sink_blocked_ram ${CMAKE_CURRENT_LIST_DIR}/kitchen_sink.c)
pico_set_binary_type(kitchen_sink_blocked_ram blocked_ram)
target_link_libraries(kitchen_sink_blocked_ram kitchen_sink_libs kitchen_sink_options)
pico_add_extra_outputs(kitchen_sink_blocked_ram)

add_executable(kitchen_sink_cpp ${CMAKE_CURRENT_LIST_DIR}/kitchen_sink_cpp.cpp)
target_link_libraries(kitchen_sink_cpp kitchen_sink_libs kitchen_sink_options)
pico_set_program_name(kitchen_sink_cpp "Wombat tentacles CPP")
pico_add_extra_outputs(kitchen_sink_cpp)

if (TARGET pico_cyw43_arch)
    # for lwipopts.h
    add_executable(kitchen_sink_lwip_poll ${CMAKE_CURRENT_LIST_DIR}/kitchen_sink.c)
    target_link_libraries(kitchen_sink_lwip_poll kitchen_sink_libs kitchen_sink_options)
    pico_add_extra_outputs(kitchen_sink_lwip_poll)
    target_link_libraries(kitchen_sink_lwip_poll
            pico_cyw43_arch_lwip_poll)
    if (TARGET pico_btstack)
        target_link_libraries(kitchen_sink_lwip_poll
            pico_btstack_ble pico_btstack_classic pico_btstack_cyw43)
    endif()
    # for lwipopts.h
    target_include_directories(kitchen_sink_lwip_poll PRIVATE
            ${CMAKE_CURRENT_LIST_DIR})

    add_executable(kitchen_sink_lwip_background ${CMAKE_CURRENT_LIST_DIR}/kitchen_sink.c)
    target_link_libraries(kitchen_sink_lwip_background kitchen_sink_libs kitchen_sink_options)
    pico_add_extra_outputs(kitchen_sink_lwip_background)
    target_link_libraries(kitchen_sink_lwip_background
            pico_cyw43_arch_lwip_threadsafe_background)
    # for lwipopts.h
    target_include_directories(kitchen_sink_lwip_background PRIVATE
            ${CMAKE_CURRENT_LIST_DIR})

    if (TARGET pico_lwip_mbedtls)
        target_link_libraries(kitchen_sink_lwip_poll pico_lwip_mbedtls)
        target_link_libraries(kitchen_sink_lwip_background pico_lwip_mbedtls)
    endif()
    if (TARGET pico_mbedtls)
        target_link_libraries(kitchen_sink_lwip_poll pico_mbedtls)
        target_link_libraries(kitchen_sink_lwip_background pico_mbedtls)
        suppress_mbedtls_warnings()
    endif()
endif()

if (TARGET pico_btstack_base AND COMMAND suppress_btstack_warnings)
    suppress_btstack_warnings()
endif()
