set(OPENOCD_PATH_WIN "C:/Softwares/xpack-openocd-0.12.0-1/bin")
set(OPENOCD_PATH_MACOS "/Users/kai/DevTools/xpack-openocd-0.12.0-4/bin")
if ("${CMAKE_HOST_SYSTEM_NAME}" MATCHES "Windows")
    set(OPENOCD_PATH ${OPENOCD_PATH_WIN})
elseif ("${CMAKE_HOST_SYSTEM_NAME}" MATCHES "Darwin")
    set(OPENOCD_PATH ${OPENOCD_PATH_MACOS})
else ()
    message(STATUS "Unknown OS: ${CMAKE_HOST_SYSTEM_NAME}")
endif ()

set(OPENOCD_CFG ${PROJECT_SOURCE_DIR}/stm32h730-ospi1.cfg)
add_custom_target(flash ALL
        COMMAND ${OPENOCD_PATH}/openocd
        -s ${OPENOCD_PATH}/../scripts
        -f ${OPENOCD_CFG}
        -c "tcl_port disabled" -c "gdb_port disabled"
        -c "program ${CMAKE_PROJECT_NAME}.elf"
        -c reset -c shutdown
        DEPENDS ${CMAKE_PROJECT_NAME}.elf
)