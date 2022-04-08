function(configDsp project root)

if (CONFIGTABLE)
    # Public because initialization for FFT may be defined in client code 
    # and needs access to the table.
    target_compile_definitions(${project} PUBLIC ARM_DSP_CONFIG_TABLES)
endif()

if (LOOPUNROLL)
  target_compile_definitions(${project} PRIVATE ARM_MATH_LOOPUNROLL)
endif()

if (ROUNDING)
  target_compile_definitions(${project} PRIVATE ARM_MATH_ROUNDING)
endif()

if (MATRIXCHECK)
  target_compile_definitions(${project} PRIVATE ARM_MATH_MATRIX_CHECK)
endif()

if (AUTOVECTORIZE)
    target_compile_definitions(${project} PRIVATE ARM_MATH_AUTOVECTORIZE) 
endif()

if (NEON OR NEONEXPERIMENTAL)
    target_include_directories(${project} PRIVATE "${root}/CMSIS/DSP/ComputeLibrary/Include")
endif()

if (FLOAT16)
    target_compile_definitions(${project} PRIVATE ARM_MATH_FLOAT16) 
endif()

if (HELIUM OR MVEF OR SUPPORT)
   target_include_directories(${project} PRIVATE "${root}/CMSIS/DSP/PrivateInclude")
endif()

endfunction()
