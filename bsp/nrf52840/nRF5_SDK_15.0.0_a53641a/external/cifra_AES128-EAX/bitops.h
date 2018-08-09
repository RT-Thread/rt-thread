/*
 * cifra - embedded cryptography library
 * Written in 2014 by Joseph Birr-Pixton <jpixton@gmail.com>
 *
 * To the extent possible under law, the author(s) have dedicated all
 * copyright and related and neighboring rights to this software to the
 * public domain worldwide. This software is distributed without any
 * warranty.
 *
 * You should have received a copy of the CC0 Public Domain Dedication
 * along with this software. If not, see
 * <http://creativecommons.org/publicdomain/zero/1.0/>.
 */

#ifndef BITOPS_H
#define BITOPS_H

#include <stdint.h>
#include <stddef.h>

/* Assorted bitwise and common operations used in ciphers. */

/** Circularly rotate right x by n bits.
 *  0 > n > 32. */
static inline uint32_t rotr32(uint32_t x, unsigned n)
{
  return (x >> n) | (x << (32 - n));
}

/** Circularly rotate left x by n bits.
 *  0 > n > 32. */
static inline uint32_t rotl32(uint32_t x, unsigned n)
{
  return (x << n) | (x >> (32 - n));
}

/** Circularly rotate right x by n bits.
 *  0 > n > 64. */
static inline uint64_t rotr64(uint64_t x, unsigned n)
{
  return (x >> n) | (x << (64 - n));
}

/** Circularly rotate left x by n bits.
 *  0 > n > 64. */
static inline uint64_t rotl64(uint64_t x, unsigned n)
{
  return (x << n) | (x >> (64 - n));
}

/** Read 4 bytes from buf, as a 32-bit big endian quantity. */
static inline uint32_t read32_be(const uint8_t buf[4])
{
  return (buf[0] << 24) |
         (buf[1] << 16) |
         (buf[2] << 8) |
         (buf[3]);
}

/** Read 4 bytes from buf, as a 32-bit little endian quantity. */
static inline uint32_t read32_le(const uint8_t buf[4])
{
  return (buf[3] << 24) |
         (buf[2] << 16) |
         (buf[1] << 8) |
         (buf[0]);
}

/** Read 8 bytes from buf, as a 64-bit big endian quantity. */
static inline uint64_t read64_be(const uint8_t buf[8])
{
  uint32_t hi = read32_be(buf),
           lo = read32_be(buf + 4);
  return ((uint64_t)hi) << 32 |
         lo;
}

/** Read 8 bytes from buf, as a 64-bit little endian quantity. */
static inline uint64_t read64_le(const uint8_t buf[8])
{
  uint32_t hi = read32_le(buf + 4),
           lo = read32_le(buf);
  return ((uint64_t)hi) << 32 |
         lo;
}

/** Encode v as a 32-bit big endian quantity into buf. */
static inline void write32_be(uint32_t v, uint8_t buf[4])
{
  *buf++ = (v >> 24) & 0xff;
  *buf++ = (v >> 16) & 0xff;
  *buf++ = (v >> 8) & 0xff;
  *buf   = v & 0xff;
}

/** Encode v as a 32-bit little endian quantity into buf. */
static inline void write32_le(uint32_t v, uint8_t buf[4])
{
  *buf++ = v & 0xff;
  *buf++ = (v >> 8) & 0xff;
  *buf++ = (v >> 16) & 0xff;
  *buf   = (v >> 24) & 0xff;
}

/** Encode v as a 64-bit big endian quantity into buf. */
static inline void write64_be(uint64_t v, uint8_t buf[8])
{
  *buf++ = (v >> 56) & 0xff;
  *buf++ = (v >> 48) & 0xff;
  *buf++ = (v >> 40) & 0xff;
  *buf++ = (v >> 32) & 0xff;
  *buf++ = (v >> 24) & 0xff;
  *buf++ = (v >> 16) & 0xff;
  *buf++ = (v >> 8) & 0xff;
  *buf   = v & 0xff;
}

/** Encode v as a 64-bit little endian quantity into buf. */
static inline void write64_le(uint64_t v, uint8_t buf[8])
{
  *buf++ = v & 0xff;
  *buf++ = (v >> 8) & 0xff;
  *buf++ = (v >> 16) & 0xff;
  *buf++ = (v >> 24) & 0xff;
  *buf++ = (v >> 32) & 0xff;
  *buf++ = (v >> 40) & 0xff;
  *buf++ = (v >> 48) & 0xff;
  *buf   = (v >> 56) & 0xff;
}

/** out = in ^ b8.
 *  out and in may alias. */
static inline void xor_b8(uint8_t *out, const uint8_t *in, uint8_t b8, size_t len)
{
  for (size_t i = 0; i < len; i++)
    out[i] = in[i] ^ b8;
}

/** out = x ^ y.
 *  out, x and y may alias. */
static inline void xor_bb(uint8_t *out, const uint8_t *x, const uint8_t *y, size_t len)
{
  for (size_t i = 0; i < len; i++)
    out[i] = x[i] ^ y[i];
}

/* out ^= x
 * out and x may alias. */
static inline void xor_words(uint32_t *out, const uint32_t *x, size_t nwords)
{
  for (size_t i = 0; i < nwords; i++)
    out[i] ^= x[i];
}

/** Produce 0xffffffff if x == y, zero otherwise, without branching. */
static inline uint32_t mask_u32(uint32_t x, uint32_t y)
{
  uint32_t diff = x ^ y;
  uint32_t diff_is_zero = ~diff & (diff - 1);
  return - (diff_is_zero >> 31);
}

/** Product 0xff if x == y, zero otherwise, without branching. */
static inline uint8_t mask_u8(uint32_t x, uint32_t y)
{
  uint32_t diff = x ^ y;
  uint8_t diff_is_zero = ~diff & (diff - 1);
  return - (diff_is_zero >> 7);
}

/** Select the ith entry from the given table of n values, in a side channel-silent
 *  way. */
static inline uint32_t select_u32(uint32_t i, volatile const uint32_t *tab, uint32_t n)
{
  uint32_t r = 0;

  for (uint32_t ii = 0; ii < n; ii++)
  {
    uint32_t mask = mask_u32(i, ii);
    r = (r & ~mask) | (tab[ii] & mask);
  }

  return r;
}

/** Select the ith entry from the given table of n values, in a side channel-silent
 *  way. */
static inline uint8_t select_u8(uint32_t i, volatile const uint8_t *tab, uint32_t n)
{
  uint8_t r = 0;

  for (uint32_t ii = 0; ii < n; ii++)
  {
    uint8_t mask = mask_u8(i, ii);
    r = (r & ~mask) | (tab[ii] & mask);
  }

  return r;
}

/** Select the ath, bth, cth and dth entries from the given table of n values,
 *  placing the results into a, b, c and d. */
static inline void select_u8x4(uint8_t *a, uint8_t *b, uint8_t *c, uint8_t *d,
                               volatile const uint8_t *tab, uint32_t n)
{
  uint8_t ra = 0,
          rb = 0,
          rc = 0,
          rd = 0;
  uint8_t mask;

  for (uint32_t i = 0; i < n; i++)
  {
    uint8_t item = tab[i];

    mask = mask_u8(*a, i); ra = (ra & ~mask) | (item & mask);
    mask = mask_u8(*b, i); rb = (rb & ~mask) | (item & mask);
    mask = mask_u8(*c, i); rc = (rc & ~mask) | (item & mask);
    mask = mask_u8(*d, i); rd = (rd & ~mask) | (item & mask);
  }

  *a = ra;
  *b = rb;
  *c = rc;
  *d = rd;
}

/** out ^= if0 or if1, depending on the value of bit. */
static inline void select_xor128(uint32_t out[4],
                                 const uint32_t if0[4],
                                 const uint32_t if1[4],
                                 uint8_t bit)
{
  uint32_t mask1 = mask_u32(bit, 1);
  uint32_t mask0 = ~mask1;

  out[0] ^= (if0[0] & mask0) | (if1[0] & mask1);
  out[1] ^= (if0[1] & mask0) | (if1[1] & mask1);
  out[2] ^= (if0[2] & mask0) | (if1[2] & mask1);
  out[3] ^= (if0[3] & mask0) | (if1[3] & mask1);
}

/** Increments the integer stored at v (of non-zero length len)
 *  with the least significant byte first. */
static inline void incr_le(uint8_t *v, size_t len)
{
  size_t i = 0;
  while (1)
  {
    if (++v[i] != 0)
      return;
    i++;
    if (i == len)
      return;
  }
}

/** Increments the integer stored at v (of non-zero length len)
 *  with the most significant byte last. */
static inline void incr_be(uint8_t *v, size_t len)
{
  len--;
  while (1)
  {
    if (++v[len] != 0)
      return;
    if (len == 0)
      return;
    len--;
  }
}

/** Copies len bytes from in to out, with in shifted left by offset bits
 *  to the right. */
static inline void copy_bytes_unaligned(uint8_t *out, const uint8_t *in, size_t len, uint8_t offset)
{
  uint8_t byte_off = offset / 8;
  uint8_t bit_off = offset & 7;
  uint8_t rmask = (1 << bit_off) - 1;
  uint8_t lmask = ~rmask;

  for (size_t i = 0; i < len; i++)
  {
    out[i] = (in[i + byte_off] << bit_off) & lmask;
    out[i] |= (in[i + byte_off + 1] >> (8 - bit_off)) & rmask;
  }
}


#endif
