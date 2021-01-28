pico_add_subdirectory(boot_picoboot)
pico_add_subdirectory(boot_uf2)
pico_add_subdirectory(pico_base)

# PICO_CMAKE_CONFIG: PICO_BARE_METAL, Flag to exclude anything except base headers from the build, type=bool, default=0, group=build
if (NOT PICO_BARE_METAL)
    pico_add_subdirectory(pico_bit_ops)
    pico_add_subdirectory(pico_binary_info)
    pico_add_subdirectory(pico_divider)
    pico_add_subdirectory(pico_sync)
    pico_add_subdirectory(pico_time)
    pico_add_subdirectory(pico_util)
    pico_add_subdirectory(pico_stdlib)
endif()

pico_add_doxygen(${CMAKE_CURRENT_LIST_DIR})