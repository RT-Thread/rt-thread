pico_add_library(pico_fix_rp2040_usb_device_enumeration)

target_sources(pico_fix_rp2040_usb_device_enumeration INTERFACE
        ${CMAKE_CURRENT_LIST_DIR}/rp2040_usb_device_enumeration.c
        )

target_include_directories(pico_fix_rp2040_usb_device_enumeration_headers INTERFACE ${CMAKE_CURRENT_LIST_DIR}/include)

pico_mirrored_target_link_libraries(pico_fix_rp2040_usb_device_enumeration INTERFACE hardware_structs hardware_gpio pico_time)