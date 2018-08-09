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

#include "cf_config.h"
#include "gf128.h"
#include "bitops.h"

#include <string.h>

void cf_gf128_tobytes_be(const cf_gf128 in, uint8_t out[16])
{
  write32_be(in[0], out + 0);
  write32_be(in[1], out + 4);
  write32_be(in[2], out + 8);
  write32_be(in[3], out + 12);
}

void cf_gf128_frombytes_be(const uint8_t in[16], cf_gf128 out)
{
  out[0] = read32_be(in + 0);
  out[1] = read32_be(in + 4);
  out[2] = read32_be(in + 8);
  out[3] = read32_be(in + 12);
}

/* out = 2 * in.  Arguments may alias. */
void cf_gf128_double(const cf_gf128 in, cf_gf128 out)
{
  uint8_t table[2] = { 0x00, 0x87 };
  uint32_t borrow = 0;
  uint32_t inword;

  inword = in[3];   out[3] = (inword << 1) | borrow;  borrow = inword >> 31;
  inword = in[2];   out[2] = (inword << 1) | borrow;  borrow = inword >> 31;
  inword = in[1];   out[1] = (inword << 1) | borrow;  borrow = inword >> 31;
  inword = in[0];   out[0] = (inword << 1) | borrow;  borrow = inword >> 31;
  
#if CF_CACHE_SIDE_CHANNEL_PROTECTION
  out[3] ^= select_u8(borrow, table, 2);
#else
  out[3] ^= table[borrow];
#endif
}

/* out = 2 * in.  Arguments may alias. */
void cf_gf128_double_le(const cf_gf128 in, cf_gf128 out)
{
  uint8_t table[2] = { 0x00, 0xe1 };
  uint32_t borrow = 0;
  uint32_t inword;

  inword = in[0];   out[0] = (inword >> 1) | (borrow << 31);  borrow = inword & 1;
  inword = in[1];   out[1] = (inword >> 1) | (borrow << 31);  borrow = inword & 1;
  inword = in[2];   out[2] = (inword >> 1) | (borrow << 31);  borrow = inword & 1;
  inword = in[3];   out[3] = (inword >> 1) | (borrow << 31);  borrow = inword & 1;

#if CF_CACHE_SIDE_CHANNEL_PROTECTION
  out[0] ^= select_u8(borrow, table, 2) << 24;
#else
  out[0] ^= table[borrow] << 24;
#endif
}

/* out = x + y.  Arguments may alias. */
void cf_gf128_add(const cf_gf128 x, const cf_gf128 y, cf_gf128 out)
{
  out[0] = x[0] ^ y[0];
  out[1] = x[1] ^ y[1];
  out[2] = x[2] ^ y[2];
  out[3] = x[3] ^ y[3];
}

/* out = xy.  Arguments may alias. */
void cf_gf128_mul(const cf_gf128 x, const cf_gf128 y, cf_gf128 out)
{
#if CF_TIME_SIDE_CHANNEL_PROTECTION
  cf_gf128 zero = { 0 };
#endif
 
  /* Z_0 = 0^128
   * V_0 = Y */ 
  cf_gf128 Z, V;
  memset(Z, 0, sizeof Z);
  memcpy(V, y, sizeof V);

  for (int i = 0; i < 128; i++)
  {
    uint32_t word = x[i >> 5];
    uint8_t bit = (word >> (31 - (i & 31))) & 1;

#if CF_TIME_SIDE_CHANNEL_PROTECTION
    select_xor128(Z, zero, V, bit);
#else
    if (bit)
      xor_words(Z, V, 4);
#endif

    cf_gf128_double_le(V, V);
  }

  memcpy(out, Z, sizeof Z);
}
