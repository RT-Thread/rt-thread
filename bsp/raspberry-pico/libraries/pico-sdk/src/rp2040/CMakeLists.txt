# Targets specific to B0 silicon
pico_add_subdirectory(hardware_regs)
pico_add_subdirectory(hardware_structs)

pico_add_doxygen(${CMAKE_CURRENT_LIST_DIR})
pico_add_doxygen_exclude(${CMAKE_CURRENT_LIST_DIR}/hardware_regs) # very very big

pico_promote_common_scope_vars()