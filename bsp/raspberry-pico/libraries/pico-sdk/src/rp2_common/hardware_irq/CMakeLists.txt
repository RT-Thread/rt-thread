pico_simple_hardware_target(irq)

# additional sources/libraries

target_sources(hardware_irq INTERFACE ${CMAKE_CURRENT_LIST_DIR}/irq_handler_chain.S)
target_link_libraries(hardware_irq INTERFACE pico_sync)