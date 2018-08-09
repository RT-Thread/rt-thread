#ifndef HANDY_H
#define HANDY_H

#include <stddef.h>
#include <stdint.h>
#include <string.h>

/*
 * Handy CPP defines and C inline functions.
 */

/* Evaluates to the number of items in array-type variable arr. */
#define ARRAYCOUNT(arr) (sizeof arr / sizeof arr[0])

/* Normal MIN/MAX macros.  Evaluate argument expressions only once. */
#ifndef MIN
  #define MIN(x, y) \
    ({ typeof (x) __x = (x); \
       typeof (y) __y = (y); \
       __x < __y ? __x : __y; })
#endif
#ifndef MAX
  #define MAX(x, y) \
    ({ typeof (x) __x = (x); \
       typeof (y) __y = (y); \
       __x > __y ? __x : __y; })
#endif

/* Swap two values.  Uses GCC type inference magic. */
#ifndef SWAP
  #define SWAP(x, y) \
    do { \
      typeof (x) __tmp = (x); \
      (x) = (y); \
      (y) = __tmp; \
    } while (0)
#endif

/** Stringify its argument. */
#define STRINGIFY(x) STRINGIFY_(x)
#define STRINGIFY_(x) #x

/* Error handling macros.
 *
 * These expect a zero = success, non-zero = error convention.
 */

/** Error: return. 
 *  
 *  If the expression fails, return the error from this function. */
#define ER(expr) do { typeof (expr) err_ = (expr); if (err_) return err_; } while (0)

/** Error: goto.
 *
 *  If the expression fails, goto x_err.  Assumes defn of label
 *  x_err and 'error_type err'. */
#define EG(expr) do { err = (expr); if (err) goto x_err; } while (0)

/** Like memset(ptr, 0, len), but not allowed to be removed by
 *  compilers. */
static inline void mem_clean(volatile void *v, size_t len)
{
  if (len)
  {
    memset((void *) v, 0, len);
    (void) *((volatile uint8_t *) v);
  }
}

/** Returns 1 if len bytes at va equal len bytes at vb, 0 if they do not.
 *  Does not leak length of common prefix through timing. */
static inline unsigned mem_eq(const void *va, const void *vb, size_t len)
{
  const volatile uint8_t *a = va;
  const volatile uint8_t *b = vb;
  uint8_t tmp;
  uint8_t diff = 0;

  while (len--)
  {
    tmp = *b++;
    diff |= *a++ ^ tmp;
  }

  return !diff;
}

#endif
