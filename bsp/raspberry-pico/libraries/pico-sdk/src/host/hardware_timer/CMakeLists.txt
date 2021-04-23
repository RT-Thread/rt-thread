pico_simple_hardware_target(timer)

target_compile_definitions(hardware_timer INTERFACE
    PICO_HARDWARE_TIMER_RESOLUTION_US=1000 # to loosen tests a little
)

if (NOT DEFINED PICO_TIME_NO_ALARM_SUPPORT)
    # we don't have alarm pools in the basic host support, though pico_host_sdl adds it
    set(PICO_TIME_NO_ALARM_SUPPORT "1" CACHE INTERNAL "")
endif()

if (PICO_TIME_NO_ALARM_SUPPORT)
    target_compile_definitions(hardware_timer INTERFACE
            PICO_TIME_DEFAULT_ALARM_POOL_DISABLED=1
    )
endif()