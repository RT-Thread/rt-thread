function(interpol PROJECT)

if (CONFIGTABLE AND ARM_COS_F32)
    target_compile_definitions(${PROJECT} PUBLIC ARM_TABLE_SIN_F32)
endif()

if (CONFIGTABLE AND ARM_COS_Q31) 
    target_compile_definitions(${PROJECT} PUBLIC ARM_TABLE_SIN_Q31)
endif()

if (CONFIGTABLE AND ARM_COS_Q15) 
    target_compile_definitions(${PROJECT} PUBLIC ARM_TABLE_SIN_Q15)
endif()

if (CONFIGTABLE AND ARM_SIN_F32) 
    target_compile_definitions(${PROJECT} PUBLIC ARM_TABLE_SIN_F32)
endif()

if (CONFIGTABLE AND ARM_SIN_Q31) 
    target_compile_definitions(${PROJECT} PUBLIC ARM_TABLE_SIN_Q31)
endif()

if (CONFIGTABLE AND ARM_SIN_Q15) 
    target_compile_definitions(${PROJECT} PUBLIC ARM_TABLE_SIN_Q15)
endif()

if (CONFIGTABLE AND ARM_SIN_COS_F32)
    target_compile_definitions(${PROJECT} PUBLIC ARM_TABLE_SIN_F32)
endif()

if (CONFIGTABLE AND ARM_SIN_COS_Q31)
    target_compile_definitions(${PROJECT} PUBLIC ARM_TABLE_SIN_Q31)
endif()

if (CONFIGTABLE AND ARM_LMS_NORM_Q31)
    target_compile_definitions(${PROJECT} PUBLIC ARM_TABLE_RECIP_Q31)
endif()

if (CONFIGTABLE AND ARM_LMS_NORM_Q15)
    target_compile_definitions(${PROJECT} PUBLIC ARM_TABLE_RECIP_Q15)
endif()

if (CONFIGTABLE AND ARM_CMPLX_MAG_Q31 AND (MVEI OR HELIUM))
    target_compile_definitions(${PROJECT} PUBLIC ARM_TABLE_FAST_SQRT_Q31_MVE)
endif()

if (CONFIGTABLE AND ARM_CMPLX_MAG_Q15 AND (MVEI OR HELIUM))
    target_compile_definitions(${PROJECT} PUBLIC ARM_TABLE_FAST_SQRT_Q15_MVE)
endif()

endfunction()