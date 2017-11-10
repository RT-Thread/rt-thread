#define CONFIG_HEARTBEAT_LED 1

/*
 * Select Platform
 */
#ifdef AE210P
#define CONFIG_PLAT_AE210P 1
#define IRQ_STACK_SIZE     5120 /* IRQ stack size */
#else
#error "No valid platform is defined!"
#endif

/*
 * Platform Option
 */
#define VECTOR_BASE 0x00000000

#define VECTOR_NUMINTRS 32
#define NO_EXTERNAL_INT_CTL 1
#define XIP_MODE 1

#ifdef CONFIG_OSC_SUPPORT
#define OSC_EILM_SIZE 0x10000	// 64KB
#undef XIP_MODE
#endif

#undef CONFIG_HW_PRIO_SUPPORT

/*
 * Cache Option
 */
#if (!defined(__NDS32_ISA_V3M__)  && defined(CONFIG_CACHE_SUPPORT))
#define CONFIG_CPU_ICACHE_ENABLE 1
#define CONFIG_CPU_DCACHE_ENABLE 1
//#define CONFIG_CPU_DCACHE_WRITETHROUGH 1
#endif

#undef CONFIG_CHECK_RANGE_ALIGNMENT
#undef CONFIG_CACHE_L2
#undef CONFIG_FULL_ASSOC

/*
 * Debugging Options
 */
#undef CONFIG_DEBUG
#undef CONFIG_WERROR

#include "ae210p.h"
