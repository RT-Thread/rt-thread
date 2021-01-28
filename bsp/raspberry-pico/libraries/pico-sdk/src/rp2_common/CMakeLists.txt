option(PICO_NO_FLASH "Default binaries to not not use flash")
option(PICO_COPY_TO_RAM "Default binaries to Copy code to RAM when booting from flash")

set(CMAKE_EXECUTABLE_SUFFIX .elf)

pico_add_subdirectory(hardware_base)
pico_add_subdirectory(hardware_claim)
# HAL items which expose a public (inline) functions/macro API above the raw hardware
pico_add_subdirectory(hardware_adc)
pico_add_subdirectory(hardware_clocks)
pico_add_subdirectory(hardware_dma)
pico_add_subdirectory(hardware_divider)
pico_add_subdirectory(hardware_flash)
pico_add_subdirectory(hardware_gpio)
pico_add_subdirectory(hardware_i2c)
pico_add_subdirectory(hardware_interp)
pico_add_subdirectory(hardware_irq)
pico_add_subdirectory(hardware_pio)
pico_add_subdirectory(hardware_pll)
pico_add_subdirectory(hardware_pwm)
pico_add_subdirectory(hardware_resets)
pico_add_subdirectory(hardware_rtc)
pico_add_subdirectory(hardware_spi)
pico_add_subdirectory(hardware_sync)
pico_add_subdirectory(hardware_timer)
pico_add_subdirectory(hardware_uart)
pico_add_subdirectory(hardware_vreg)
pico_add_subdirectory(hardware_watchdog)
pico_add_subdirectory(hardware_xosc)

# Helper functions to connect to data/functions in the bootrom
pico_add_subdirectory(pico_bootrom)
pico_add_subdirectory(pico_platform)

if (NOT PICO_BARE_METAL)
    # NOTE THE ORDERING HERE IS IMPORTANT AS SOME TARGETS CHECK ON EXISTENCE OF OTHER TARGETS
    pico_add_subdirectory(boot_stage2)

    pico_add_subdirectory(pico_multicore)

    pico_add_subdirectory(pico_bit_ops)
    pico_add_subdirectory(pico_divider)
    pico_add_subdirectory(pico_double)
    pico_add_subdirectory(pico_int64_ops)
    pico_add_subdirectory(pico_float)
    pico_add_subdirectory(pico_mem_ops)
    pico_add_subdirectory(pico_malloc)
    pico_add_subdirectory(pico_printf)

    pico_add_subdirectory(pico_stdio)
    pico_add_subdirectory(pico_stdio_semihosting)
    pico_add_subdirectory(pico_stdio_uart)

    pico_add_subdirectory(tinyusb)
    pico_add_subdirectory(pico_stdio_usb)

    pico_add_subdirectory(pico_stdlib)

    pico_add_subdirectory(pico_cxx_options)
    pico_add_subdirectory(pico_standard_link)

    pico_add_subdirectory(pico_fix)

    pico_add_subdirectory(pico_runtime)

endif()

set(CMAKE_EXECUTABLE_SUFFIX "${CMAKE_EXECUTABLE_SUFFIX}" PARENT_SCOPE)

pico_add_doxygen(${CMAKE_CURRENT_LIST_DIR})
