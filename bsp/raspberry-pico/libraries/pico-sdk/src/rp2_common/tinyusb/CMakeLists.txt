if (DEFINED ENV{PICO_TINYUSB_PATH} AND (NOT PICO_TINYUSB_PATH))
    set(PICO_TINYUSB_PATH $ENV{PICO_TINYUSB_PATH})
    message("Using PICO_TINYUSB_PATH from environment ('${PICO_TINYUSB_PATH}')")
endif ()

set(TINYUSB_TEST_PATH "src/portable/raspberrypi/rp2040")
if (NOT PICO_TINYUSB_PATH)
    set(PICO_TINYUSB_PATH ${PROJECT_SOURCE_DIR}/lib/tinyusb)
    if (NOT EXISTS ${PICO_TINYUSB_PATH}/${TINYUSB_TEST_PATH})
        message(WARNING "TinyUSB submodule has not been initialized; USB support will be unavailable
         hint: try 'git submodule update --init'.")
    endif()
elseif (NOT EXISTS ${PICO_TINYUSB_PATH}/${TINYUSB_TEST_PATH})
    message(WARNING "PICO_TINYUSB_PATH specified but content not present.")
endif()

if (EXISTS ${PICO_TINYUSB_PATH}/${TINYUSB_TEST_PATH})
    message("TinyUSB available at ${PICO_TINYUSB_PATH}/${TINYUSB_TEST_PATH}; adding USB support.")

    add_library(tinyusb_common INTERFACE)
    target_link_libraries(tinyusb_common INTERFACE
            hardware_structs
            hardware_irq
            hardware_resets
            pico_sync
    )

    target_sources(tinyusb_common INTERFACE
            ${PICO_TINYUSB_PATH}/src/tusb.c
            ${PICO_TINYUSB_PATH}/src/common/tusb_fifo.c
    )

    set(TINYUSB_DEBUG_LEVEL 0)
    if (CMAKE_BUILD_TYPE STREQUAL "Debug")
        message("Compiling TinyUSB with CFG_TUSB_DEBUG=1")
        set(TINYUSB_DEBUG_LEVEL 1)
    endif ()

    target_compile_definitions(tinyusb_common INTERFACE
            CFG_TUSB_MCU=OPT_MCU_RP2040
            CFG_TUSB_OS=OPT_OS_PICO #seems examples are hard coded to OPT_OS_NONE
            CFG_TUSB_DEBUG=${TINYUSB_DEBUG_LEVEL}
    )

    target_include_directories(tinyusb_common INTERFACE
            ${PICO_TINYUSB_PATH}/src
            ${PICO_TINYUSB_PATH}/src/common
            ${PICO_TINYUSB_PATH}/hw
    )

    add_library(tinyusb_device_unmarked INTERFACE)
    target_sources(tinyusb_device_unmarked INTERFACE
            ${PICO_TINYUSB_PATH}/src/portable/raspberrypi/rp2040/dcd_rp2040.c
            ${PICO_TINYUSB_PATH}/src/portable/raspberrypi/rp2040/rp2040_usb.c
            ${PICO_TINYUSB_PATH}/src/device/usbd.c
            ${PICO_TINYUSB_PATH}/src/device/usbd_control.c
            ${PICO_TINYUSB_PATH}/src/class/audio/audio_device.c
            ${PICO_TINYUSB_PATH}/src/class/cdc/cdc_device.c
            ${PICO_TINYUSB_PATH}/src/class/dfu/dfu_rt_device.c
            ${PICO_TINYUSB_PATH}/src/class/hid/hid_device.c
            ${PICO_TINYUSB_PATH}/src/class/midi/midi_device.c
            ${PICO_TINYUSB_PATH}/src/class/msc/msc_device.c
            ${PICO_TINYUSB_PATH}/src/class/net/net_device.c
            ${PICO_TINYUSB_PATH}/src/class/usbtmc/usbtmc_device.c
            ${PICO_TINYUSB_PATH}/src/class/vendor/vendor_device.c
    )

    target_compile_definitions(tinyusb_device_unmarked INTERFACE
            # off by default note TUD_OPT_RP2040_USB_DEVICE_ENUMERATION_FIX defaults from PICO_RP2040_USB_DEVICE_ENUMERATION_FIX
#            TUD_OPT_RP2040_USB_DEVICE_ENUMERATION_FIX=1
    )

    # unmarked version used by stdio USB
    target_link_libraries(tinyusb_device_unmarked INTERFACE tinyusb_common pico_fix_rp2040_usb_device_enumeration)

    add_library(tinyusb_device INTERFACE)
    target_link_libraries(tinyusb_device INTERFACE tinyusb_device_unmarked)
    target_compile_definitions(tinyusb_device INTERFACE
            RP2040_USB_DEVICE_MODE=1
            TINYUSB_DEVICE_LINKED=1
            )

    add_library(tinyusb_host INTERFACE)
    target_sources(tinyusb_host INTERFACE
            ${PICO_TINYUSB_PATH}/src/portable/raspberrypi/rp2040/hcd_rp2040.c
            ${PICO_TINYUSB_PATH}/src/portable/raspberrypi/rp2040/rp2040_usb.c
            ${PICO_TINYUSB_PATH}/src/host/usbh.c
            ${PICO_TINYUSB_PATH}/src/host/usbh_control.c
            ${PICO_TINYUSB_PATH}/src/host/hub.c
            ${PICO_TINYUSB_PATH}/src/class/cdc/cdc_host.c
            ${PICO_TINYUSB_PATH}/src/class/hid/hid_host.c
            ${PICO_TINYUSB_PATH}/src/class/msc/msc_host.c
            ${PICO_TINYUSB_PATH}/src/class/vendor/vendor_host.c
            )

    # Sometimes have to do host specific actions in mostly
    # common functions
    target_compile_definitions(tinyusb_host INTERFACE
            RP2040_USB_HOST_MODE=1
            TINYUSB_HOST_LINKED=1
            )

    target_link_libraries(tinyusb_host INTERFACE tinyusb_common)

    add_library(tinyusb_board INTERFACE)
    target_sources(tinyusb_board INTERFACE
            ${PICO_TINYUSB_PATH}/hw/bsp/raspberry_pi_pico/board_raspberry_pi_pico.c
    )

endif()

