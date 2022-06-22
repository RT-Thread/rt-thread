PROJECT(pico_float_test)

add_executable(pico_float_test
        pico_float_test.c
        llvm/call_apsr.S
        )

add_executable(pico_double_test
        pico_double_test.c
        llvm/call_apsr.S
        )


target_compile_definitions(pico_float_test PRIVATE
        PICO_USE_CRT_PRINTF=1 # want full precision output
#        PICO_FLOAT_PROPAGATE_NANS=1
)

target_compile_definitions(pico_double_test PRIVATE
        PICO_USE_CRT_PRINTF=1 # want full precision output
                PICO_FLOAT_PROPAGATE_NANS=1
                PICO_DOUBLE_PROPAGATE_NANS=1
        )

# handy for testing we aren't pulling in extra stuff
#target_link_options(pico_float_test PRIVATE -nodefaultlibs)

target_include_directories(pico_float_test PRIVATE ${CMAKE_CURRENT_LIST_DIR}/llvm)
target_link_libraries(pico_float_test pico_float pico_stdlib)
pico_add_extra_outputs(pico_float_test)
#pico_set_float_implementation(pico_float_test compiler)
#pico_set_double_implementation(pico_float_test compiler)

target_include_directories(pico_double_test PRIVATE ${CMAKE_CURRENT_LIST_DIR}/llvm)
target_link_libraries(pico_double_test pico_double pico_stdlib)
pico_add_extra_outputs(pico_double_test)
#pico_set_float_implementation(pico_double_test compiler)
#pico_set_double_implementation(pico_double_test compiler)