#ifndef __COMPILER_GCC_H
#define __COMPILER_GCC_H

#ifndef __ASM
#define __ASM __asm
#endif
#ifndef __INLINE
#define __INLINE inline
#endif
#ifndef __ALWAYS_INLINE
#define __ALWAYS_INLINE inline __attribute__((always_inline))
#endif
#ifndef __ALWAYS_STATIC_INLINE
#define __ALWAYS_STATIC_INLINE __attribute__((always_inline)) static inline
#endif
#ifndef __STATIC_INLINE
#define __STATIC_INLINE static inline
#endif
#ifndef __NO_RETURN
#define __NO_RETURN __attribute__((noreturn))
#endif
#ifndef __USED
#define __USED __attribute__((used))
#endif
#ifndef __UNUSED
#define __UNUSED __attribute__((unused))
#endif
#ifndef __WEAK
#define __WEAK __attribute__((weak))
#endif
#ifndef __PACKED
#define __PACKED __attribute__((packed, aligned(1)))
#endif
#ifndef __PACKED_STRUCT
#define __PACKED_STRUCT struct __attribute__((packed, aligned(1)))
#endif
#ifndef __PACKED_UNION
#define __PACKED_UNION union __attribute__((packed, aligned(1)))
#endif
#ifndef __IRQ
#define __IRQ __attribute__((interrupt))
#endif
#ifndef __IRQ_ALIGN64
#define __IRQ_ALIGN64 __attribute__((interrupt, aligned(64)))
#endif
#ifndef ALIGN4
#define ALIGN4 __attribute((aligned(4)))
#endif
#ifndef __PACK_START
#define __PACK_START
#endif
#ifndef __PACK_END
#define __PACK_END __attribute__((packed))
#endif
#ifndef likely
#define likely(x) __builtin_expect(!!(x), 1)
#endif
#ifndef unlikely
#define unlikely(x) __builtin_expect(!!(x), 0)
#endif
#ifndef __ALIGNED
#define __ALIGNED(x) __attribute__((aligned(x)))
#endif
#ifndef SECTION
#define SECTION(x) __attribute__((section(x)))
#endif

#endif