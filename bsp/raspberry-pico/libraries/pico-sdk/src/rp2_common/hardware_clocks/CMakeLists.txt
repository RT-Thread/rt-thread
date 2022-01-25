pico_simple_hardware_target(clocks)

target_link_libraries(hardware_clocks INTERFACE
        hardware_resets
        hardware_watchdog
        hardware_xosc
        hardware_pll
        # not currently used by clocks.c, but sensibly bundled here
        # as changing frequencies may require upping voltage
        hardware_vreg
)