
#if defined (__CC_ARM)
  #if   (defined (ARMCM0))
    #include "ARMCC\startup_armv6-m.s"
  #elif (defined (ARMCM0P) || defined (ARMCM0P_MPU))
    #include "ARMCC\startup_armv6-m.s"
  #elif (defined (ARMCM3))
    #include "ARMCC\startup_armv7-m.s"
  #elif (defined (ARMCM4) || defined (ARMCM4_FP))
    #include "ARMCC\startup_armv7-m.s"
  #elif (defined (ARMCM7) || defined (ARMCM7_SP) || defined (ARMCM7_DP))
    #include "ARMCC\startup_armv7-m.s"
  #elif (defined (ARMv8MBL))
    #include "ARMCC\startup_armv6-m.s"
  #elif (defined (ARMv8MML)    || defined (ARMv8MML_DSP)    || \
         defined (ARMv8MML_SP) || defined (ARMv8MML_DSP_SP) || \
         defined (ARMv8MML_DP) || defined (ARMv8MML_DSP_DP)   )
    #include "ARMCC\startup_armv7-m.s"
  #else
    #error "No appropriate startup file found!"
  #endif

#elif defined (__ARMCC_VERSION) && (__ARMCC_VERSION >= 6010050)
  #if   (defined (ARMCM0))
    #include "ARMCLANG\startup_armv6-m.S"
  #elif (defined (ARMCM0P) || defined (ARMCM0P_MPU))
    #include "ARMCLANG\startup_armv6-m.S"
  #elif (defined (ARMCM3))
    #include "ARMCLANG\startup_armv7-m.S"
  #elif (defined (ARMCM4) || defined (ARMCM4_FP))
    #include "ARMCLANG\startup_armv7-m.S"
  #elif (defined (ARMCM7) || defined (ARMCM7_SP) || defined (ARMCM7_DP))
    #include "ARMCLANG\startup_armv7-m.S"
  #elif (defined (ARMv8MBL))
    #include "ARMCLANG\startup_armv6-m.S"
  #elif (defined (ARMv8MML)    || defined (ARMv8MML_DSP)    || \
         defined (ARMv8MML_SP) || defined (ARMv8MML_DSP_SP) || \
         defined (ARMv8MML_DP) || defined (ARMv8MML_DSP_DP)   )
    #include "ARMCLANG\startup_armv7-m.S"
  #else
    #error "No appropriate startup file found!"
  #endif

#elif defined (__GNUC__)
  #if   (defined (ARMCM0))
    #include "GCC\startup_armv6-m.S"
  #elif (defined (ARMCM0P) || defined (ARMCM0P_MPU))
    #include "GCC\startup_armv6-m.S"
  #elif (defined (ARMCM3))
    #include "GCC\startup_armv7-m.S"
  #elif (defined (ARMCM4) || defined (ARMCM4_FP))
    #include "GCC\startup_armv7-m.S"
  #elif (defined (ARMCM7) || defined (ARMCM7_SP) || defined (ARMCM7_DP))
    #include "GCC\startup_armv7-m.S"
  #elif (defined (ARMv8MBL))
    #include "GCC\startup_armv6-m.S"
  #elif (defined (ARMv8MML)    || defined (ARMv8MML_DSP)    || \
         defined (ARMv8MML_SP) || defined (ARMv8MML_DSP_SP) || \
         defined (ARMv8MML_DP) || defined (ARMv8MML_DSP_DP)   )
    #include "GCC\startup_armv7-m.S"
  #else
    #error "No appropriate startup file found!"
  #endif

#else
  #error "Compiler not supported!"
#endif

