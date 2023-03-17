#ifndef __COMPILER_LD_H
#define __COMPILER_LD_H

#define ATTR_STRINGIFY(x)               #x
#define ATTR_TOSTRING(x)                ATTR_STRINGIFY(x)
#define ATTR_UNI_SYMBOL                 __FILE__ ATTR_TOSTRING(__LINE__)
#define ATTR_CLOCK_SECTION              __attribute__((section(".sclock_rlt_code." ATTR_UNI_SYMBOL)))
#define ATTR_CLOCK_CONST_SECTION        __attribute__((section(".sclock_rlt_const." ATTR_UNI_SYMBOL)))
#define ATTR_TCM_SECTION                __attribute__((section(".tcm_code." ATTR_UNI_SYMBOL)))
#define ATTR_TCM_CONST_SECTION          __attribute__((section(".tcm_const." ATTR_UNI_SYMBOL)))
#define ATTR_DTCM_SECTION               __attribute__((section(".tcm_data")))
#define ATTR_HSRAM_SECTION              __attribute__((section(".hsram_code")))
#define ATTR_DMA_RAM_SECTION            __attribute__((section(".system_ram")))
#define ATTR_NOCACHE_RAM_SECTION        __attribute__((section(".nocache_ram")))
#define ATTR_NOCACHE_NOINIT_RAM_SECTION __attribute__((section(".nocache_noinit_ram")))
#define ATTR_HBN_RAM_SECTION            __attribute__((section(".hbn_ram_code")))
#define ATTR_HBN_RAM_CONST_SECTION      __attribute__((section(".hbn_ram_data")))
#define ATTR_FALLTHROUGH()              __attribute__((fallthrough))

#endif
