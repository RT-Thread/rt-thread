pico_simple_hardware_target(pio)

# additional libraries
pico_mirrored_target_link_libraries(hardware_pio INTERFACE
        hardware_gpio
        hardware_claim
        )