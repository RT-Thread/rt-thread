if (NOT PICO_TIME_NO_ALARM_SUPPORT)
    add_executable(pico_time_test pico_time_test.c)
    target_compile_definitions(pico_time_test PRIVATE
            PICO_TIME_DEFAULT_ALARM_POOL_MAX_TIMERS=250
    )
    target_link_libraries(pico_time_test PRIVATE pico_test)
    pico_add_extra_outputs(pico_time_test)
endif()