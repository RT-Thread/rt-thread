


#ifndef _COMPAT_ATTRIBUTE_H_
#define _COMPAT_ATTRIBUTE_H_

#define __DEPRECATED__(x) __attribute__((deprecated(x)))
#define __PACKED__ __attribute__ ((packed))

#define __PACKED_START__
#define __PACKED_END__ __PACKED__

#define __UNUSED__ __attribute__((unused))
#define __MAY_ALIAS__ __attribute__((may_alias))

#define __ALIGNED__(y) __attribute__((aligned(y)))
#define __SECTION__(y) __attribute__((section(#y)))

#define __FORCED_INLINE__ inline __attribute__((always_inline))
#define __NOINLINE__ __attribute__((noinline))

#define __WEAK__ __attribute__((weak))
#define __INTERRUPT__ __attribute__((interrupt))
#define __USED__ __attribute__((used))
#define __NAKED__ __attribute__((naked))

#define __VISIBILITY__ __attribute__((visibility("default")))
#endif  /* _COMPAT_ATTRIBUTE_H_ */
