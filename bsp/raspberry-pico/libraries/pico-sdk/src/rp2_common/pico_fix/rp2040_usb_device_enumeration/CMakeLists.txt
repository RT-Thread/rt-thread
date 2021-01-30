add_library(pico_fix_rp2040_usb_device_enumeration INTERFACE)

target_sources(pico_fix_rp2040_usb_device_enumeration INTERFACE
        ${CMAKE_CURRENT_LIST_DIR}/rp2040_usb_device_enumeration.c
        )

target_include_directories(pico_fix_rp2040_usb_device_enumeration INTERFACE ${CMAKE_CURRENT_LIST_DIR}/include)

target_link_libraries(pico_fix_rp2040_usb_device_enumeration INTERFACE hardware_structs pico_time)