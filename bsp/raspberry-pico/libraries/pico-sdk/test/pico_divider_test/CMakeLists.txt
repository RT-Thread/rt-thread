PROJECT(pico_divider_test)

if (PICO_ON_DEVICE)
    add_executable(pico_divider_test
            pico_divider_test.c
            )

    target_link_libraries(pico_divider_test pico_stdlib)

    pico_set_divider_implementation(pico_divider_test hardware_explicit) # want to compare against compiler impl

    pico_add_extra_outputs(pico_divider_test)

    target_compile_definitions(pico_divider_test PRIVATE
#            TURBO
    )
endif()