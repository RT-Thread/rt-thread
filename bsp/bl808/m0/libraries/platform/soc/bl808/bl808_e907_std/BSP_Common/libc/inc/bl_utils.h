#ifndef _UTIL_H_
#define _UTIL_H_

#ifdef __GNUC__

#define WARN_UNUSED_RET __attribute__ ((warn_unused_result))
#define WEAK __attribute__ ((weak))

#ifndef PACK_START
#define PACK_START
#endif
#ifndef PACK_END
#define PACK_END __attribute__((packed))
#endif
#define NORETURN __attribute__ ((noreturn))

/* alignment value should be a power of 2 */
#define ALIGN(num, align)  MASK(num, (typeof(num))align - 1)

#define ALIGN_2(num)               ALIGN(num, 2)
#define ALIGN_4(num)               ALIGN(num, 4)
#define ALIGN_8(num)               ALIGN(num, 8)
#define ALIGN_16(num)              ALIGN(num, 16)
#define ALIGN_32(num)              ALIGN(num, 32)

#else /* __GNUC__ */

#define WARN_UNUSED_RET
#define WEAK __weak

#define PACK_START __packed
#define PACK_END
#define NORETURN

#endif /* __GNUC__ */

#endif
