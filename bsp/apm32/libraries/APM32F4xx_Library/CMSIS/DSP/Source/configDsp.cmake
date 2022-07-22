function(configDsp project root)

if (HOST)
      target_compile_definitions(${project} PUBLIC __GNUC_PYTHON__)
endif()

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
    # Used in arm_vec_math.h
    target_include_directories(${project} PUBLIC "${root}/CMSIS/DSP/ComputeLibrary/Include")
endif()

if (MVEFLOAT16)
    target_compile_definitions(${project} PRIVATE ARM_MATH_MVE_FLOAT16) 
endif()

if (HELIUM OR MVEF OR SUPPORT)
   target_include_directories(${project} PRIVATE "${root}/CMSIS/DSP/PrivateInclude")
endif()

if (DISABLEFLOAT16)
    target_compile_definitions(${project} PRIVATE DISABLEFLOAT16) 
endif()


endfunction()
