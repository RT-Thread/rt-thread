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

#include <string.h>
#include <stdlib.h>
#include "handy.h"
#include "cf_config.h"
#include "cifra_eax_aes.h"
#include "bitops.h"
#include "tassert.h"

static const uint8_t S[256] =
{
  0x63, 0x7c, 0x77, 0x7b, 0xf2, 0x6b, 0x6f, 0xc5, 0x30, 0x01, 0x67, 0x2b, 0xfe,
  0xd7, 0xab, 0x76, 0xca, 0x82, 0xc9, 0x7d, 0xfa, 0x59, 0x47, 0xf0, 0xad, 0xd4,
  0xa2, 0xaf, 0x9c, 0xa4, 0x72, 0xc0, 0xb7, 0xfd, 0x93, 0x26, 0x36, 0x3f, 0xf7,
  0xcc, 0x34, 0xa5, 0xe5, 0xf1, 0x71, 0xd8, 0x31, 0x15, 0x04, 0xc7, 0x23, 0xc3,
  0x18, 0x96, 0x05, 0x9a, 0x07, 0x12, 0x80, 0xe2, 0xeb, 0x27, 0xb2, 0x75, 0x09,
  0x83, 0x2c, 0x1a, 0x1b, 0x6e, 0x5a, 0xa0, 0x52, 0x3b, 0xd6, 0xb3, 0x29, 0xe3,
  0x2f, 0x84, 0x53, 0xd1, 0x00, 0xed, 0x20, 0xfc, 0xb1, 0x5b, 0x6a, 0xcb, 0xbe,
  0x39, 0x4a, 0x4c, 0x58, 0xcf, 0xd0, 0xef, 0xaa, 0xfb, 0x43, 0x4d, 0x33, 0x85,
  0x45, 0xf9, 0x02, 0x7f, 0x50, 0x3c, 0x9f, 0xa8, 0x51, 0xa3, 0x40, 0x8f, 0x92,
  0x9d, 0x38, 0xf5, 0xbc, 0xb6, 0xda, 0x21, 0x10, 0xff, 0xf3, 0xd2, 0xcd, 0x0c,
  0x13, 0xec, 0x5f, 0x97, 0x44, 0x17, 0xc4, 0xa7, 0x7e, 0x3d, 0x64, 0x5d, 0x19,
  0x73, 0x60, 0x81, 0x4f, 0xdc, 0x22, 0x2a, 0x90, 0x88, 0x46, 0xee, 0xb8, 0x14,
  0xde, 0x5e, 0x0b, 0xdb, 0xe0, 0x32, 0x3a, 0x0a, 0x49, 0x06, 0x24, 0x5c, 0xc2,
  0xd3, 0xac, 0x62, 0x91, 0x95, 0xe4, 0x79, 0xe7, 0xc8, 0x37, 0x6d, 0x8d, 0xd5,
  0x4e, 0xa9, 0x6c, 0x56, 0xf4, 0xea, 0x65, 0x7a, 0xae, 0x08, 0xba, 0x78, 0x25,
  0x2e, 0x1c, 0xa6, 0xb4, 0xc6, 0xe8, 0xdd, 0x74, 0x1f, 0x4b, 0xbd, 0x8b, 0x8a,
  0x70, 0x3e, 0xb5, 0x66, 0x48, 0x03, 0xf6, 0x0e, 0x61, 0x35, 0x57, 0xb9, 0x86,
  0xc1, 0x1d, 0x9e, 0xe1, 0xf8, 0x98, 0x11, 0x69, 0xd9, 0x8e, 0x94, 0x9b, 0x1e,
  0x87, 0xe9, 0xce, 0x55, 0x28, 0xdf, 0x8c, 0xa1, 0x89, 0x0d, 0xbf, 0xe6, 0x42,
  0x68, 0x41, 0x99, 0x2d, 0x0f, 0xb0, 0x54, 0xbb, 0x16
};

static const uint8_t Rcon[11] =
{
  0x8d, 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x1b, 0x36
};

#ifdef INLINE_FUNCS
static inline uint32_t word4(uint8_t b0, uint8_t b1, uint8_t b2, uint8_t b3)
{
  return b0 << 24 | b1 << 16 | b2 << 8 | b3;
}

static inline uint8_t byte(uint32_t w, unsigned x)
{
  /* nb. bytes are numbered 0 (leftmost, top)
   * to 3 (rightmost). */
  x = 3 - x;
  return (w >> (x * 8)) & 0xff;
}

static uint32_t round_constant(uint32_t i)
{
  return Rcon[i] << 24;
}

static uint32_t rot_word(uint32_t w)
{
  /* Takes
   * word [a0,a1,a2,a3]
   * returns
   * word [a1,a2,a3,a0]
   *
   */
  return rotl32(w, 8);
}
#endif

#define word4(a, b, c, d) (((uint32_t)(a) << 24) | ((uint32_t)(b) << 16) | ((uint32_t)(c) << 8) | (d))
#define byte(w, x) ((w >> ((3 - (x)) << 3)) & 0xff)
#define round_constant(i) ((uint32_t)(Rcon[i]) << 24)
#define rot_word(w) rotl32((w), 8)

static uint32_t sub_word(uint32_t w, const uint8_t *sbox)
{
  uint8_t a = byte(w, 0),
          b = byte(w, 1),
          c = byte(w, 2),
          d = byte(w, 3);
#if CF_CACHE_SIDE_CHANNEL_PROTECTION
  select_u8x4(&a, &b, &c, &d, sbox, 256);
#else
  a = sbox[a];
  b = sbox[b];
  c = sbox[c];
  d = sbox[d];
#endif
  return word4(a, b, c, d);
}

static void aes_schedule(cf_aes_context *ctx, const uint8_t *key, size_t nkey)
{
  size_t i,
         nb = AES_BLOCKSZ / 4,
         nk = nkey / 4,
         n = nb * (ctx->rounds + 1);
  uint32_t *w = ctx->ks;

  /* First words are just the key. */
  for (i = 0; i < nk; i++)
  {
    w[i] = read32_be(key + i * 4);
  }

  uint32_t i_div_nk = 1;
  uint32_t i_mod_nk = 0;

  for (; i < n; i++, i_mod_nk++)
  {
    uint32_t temp = w[i - 1];
    
    if (i_mod_nk == nk)
    {
      i_div_nk++;
      i_mod_nk = 0;
    }

    if (i_mod_nk == 0)
      temp = sub_word(rot_word(temp), S) ^ round_constant(i_div_nk);
    else if (nk > 6 && i_mod_nk == 4)
      temp = sub_word(temp, S);

    w[i] = w[i - nk] ^ temp;
  }
}

void cf_aes_init(cf_aes_context *ctx, const uint8_t *key, size_t nkey)
{
  memset(ctx, 0, sizeof *ctx);

  switch (nkey)
  {
#if CF_AES_MAXROUNDS >= AES128_ROUNDS
    case 16:
      ctx->rounds = AES128_ROUNDS;
      aes_schedule(ctx, key, nkey);
      break;
#endif

#if CF_AES_MAXROUNDS >= AES192_ROUNDS
    case 24:
      ctx->rounds = AES192_ROUNDS;
      aes_schedule(ctx, key, nkey);
      break;
#endif

#if CF_AES_MAXROUNDS >= AES256_ROUNDS
    case 32:
      ctx->rounds = AES256_ROUNDS;
      aes_schedule(ctx, key, nkey);
      break;
#endif

    default:
      abort();
  }
}

static void add_round_key(uint32_t state[4], const uint32_t rk[4])
{
  state[0] ^= rk[0];
  state[1] ^= rk[1];
  state[2] ^= rk[2];
  state[3] ^= rk[3];
}

static void sub_block(uint32_t state[4])
{
  state[0] = sub_word(state[0], S);
  state[1] = sub_word(state[1], S);
  state[2] = sub_word(state[2], S);
  state[3] = sub_word(state[3], S);
}

static void shift_rows(uint32_t state[4])
{
  uint32_t u, v, x, y;

  u = word4(byte(state[0], 0),
            byte(state[1], 1),
            byte(state[2], 2),
            byte(state[3], 3));

  v = word4(byte(state[1], 0),
            byte(state[2], 1),
            byte(state[3], 2),
            byte(state[0], 3));

  x = word4(byte(state[2], 0),
            byte(state[3], 1),
            byte(state[0], 2),
            byte(state[1], 3));

  y = word4(byte(state[3], 0),
            byte(state[0], 1),
            byte(state[1], 2),
            byte(state[2], 3));

  state[0] = u;
  state[1] = v;
  state[2] = x;
  state[3] = y;
}

static uint32_t gf_poly_mul2(uint32_t x)
{
  return
    ((x & 0x7f7f7f7f) << 1) ^
    (((x & 0x80808080) >> 7) * 0x1b);
}

static uint32_t mix_column(uint32_t x)
{
  uint32_t x2 = gf_poly_mul2(x);
  return x2 ^ rotr32(x ^ x2, 24) ^ rotr32(x, 16) ^ rotr32(x, 8);
}

static void mix_columns(uint32_t state[4])
{
  state[0] = mix_column(state[0]);
  state[1] = mix_column(state[1]);
  state[2] = mix_column(state[2]);
  state[3] = mix_column(state[3]);
}

void cf_aes_encrypt(const cf_aes_context *ctx,
                    const uint8_t in[AES_BLOCKSZ],
                    uint8_t out[AES_BLOCKSZ])
{
  assert(ctx->rounds == AES128_ROUNDS ||
         ctx->rounds == AES192_ROUNDS ||
         ctx->rounds == AES256_ROUNDS);

  uint32_t state[4] = {
    read32_be(in + 0),
    read32_be(in + 4),
    read32_be(in + 8),
    read32_be(in + 12)
  };

  const uint32_t *round_keys = ctx->ks;
  add_round_key(state, round_keys);
  round_keys += 4;

  for (uint32_t round = 1; round < ctx->rounds; round++)
  {
    sub_block(state);
    shift_rows(state);
    mix_columns(state);
    add_round_key(state, round_keys);
    round_keys += 4;
  }

  sub_block(state);
  shift_rows(state);
  add_round_key(state, round_keys);

  write32_be(state[0], out + 0);
  write32_be(state[1], out + 4);
  write32_be(state[2], out + 8);
  write32_be(state[3], out + 12);
}

#if CF_AES_ENCRYPT_ONLY == 0
static const uint8_t S_inv[256] =
{
  0x52, 0x09, 0x6a, 0xd5, 0x30, 0x36, 0xa5, 0x38, 0xbf, 0x40, 0xa3, 0x9e, 0x81,
  0xf3, 0xd7, 0xfb, 0x7c, 0xe3, 0x39, 0x82, 0x9b, 0x2f, 0xff, 0x87, 0x34, 0x8e,
  0x43, 0x44, 0xc4, 0xde, 0xe9, 0xcb, 0x54, 0x7b, 0x94, 0x32, 0xa6, 0xc2, 0x23,
  0x3d, 0xee, 0x4c, 0x95, 0x0b, 0x42, 0xfa, 0xc3, 0x4e, 0x08, 0x2e, 0xa1, 0x66,
  0x28, 0xd9, 0x24, 0xb2, 0x76, 0x5b, 0xa2, 0x49, 0x6d, 0x8b, 0xd1, 0x25, 0x72,
  0xf8, 0xf6, 0x64, 0x86, 0x68, 0x98, 0x16, 0xd4, 0xa4, 0x5c, 0xcc, 0x5d, 0x65,
  0xb6, 0x92, 0x6c, 0x70, 0x48, 0x50, 0xfd, 0xed, 0xb9, 0xda, 0x5e, 0x15, 0x46,
  0x57, 0xa7, 0x8d, 0x9d, 0x84, 0x90, 0xd8, 0xab, 0x00, 0x8c, 0xbc, 0xd3, 0x0a,
  0xf7, 0xe4, 0x58, 0x05, 0xb8, 0xb3, 0x45, 0x06, 0xd0, 0x2c, 0x1e, 0x8f, 0xca,
  0x3f, 0x0f, 0x02, 0xc1, 0xaf, 0xbd, 0x03, 0x01, 0x13, 0x8a, 0x6b, 0x3a, 0x91,
  0x11, 0x41, 0x4f, 0x67, 0xdc, 0xea, 0x97, 0xf2, 0xcf, 0xce, 0xf0, 0xb4, 0xe6,
  0x73, 0x96, 0xac, 0x74, 0x22, 0xe7, 0xad, 0x35, 0x85, 0xe2, 0xf9, 0x37, 0xe8,
  0x1c, 0x75, 0xdf, 0x6e, 0x47, 0xf1, 0x1a, 0x71, 0x1d, 0x29, 0xc5, 0x89, 0x6f,
  0xb7, 0x62, 0x0e, 0xaa, 0x18, 0xbe, 0x1b, 0xfc, 0x56, 0x3e, 0x4b, 0xc6, 0xd2,
  0x79, 0x20, 0x9a, 0xdb, 0xc0, 0xfe, 0x78, 0xcd, 0x5a, 0xf4, 0x1f, 0xdd, 0xa8,
  0x33, 0x88, 0x07, 0xc7, 0x31, 0xb1, 0x12, 0x10, 0x59, 0x27, 0x80, 0xec, 0x5f,
  0x60, 0x51, 0x7f, 0xa9, 0x19, 0xb5, 0x4a, 0x0d, 0x2d, 0xe5, 0x7a, 0x9f, 0x93,
  0xc9, 0x9c, 0xef, 0xa0, 0xe0, 0x3b, 0x4d, 0xae, 0x2a, 0xf5, 0xb0, 0xc8, 0xeb,
  0xbb, 0x3c, 0x83, 0x53, 0x99, 0x61, 0x17, 0x2b, 0x04, 0x7e, 0xba, 0x77, 0xd6,
  0x26, 0xe1, 0x69, 0x14, 0x63, 0x55, 0x21, 0x0c, 0x7d
};

static void inv_sub_block(uint32_t state[4])
{
  state[0] = sub_word(state[0], S_inv);
  state[1] = sub_word(state[1], S_inv);
  state[2] = sub_word(state[2], S_inv);
  state[3] = sub_word(state[3], S_inv);
}

static void inv_shift_rows(uint32_t state[4])
{
  uint32_t u, v, x, y;

  u = word4(byte(state[0], 0),
            byte(state[3], 1),
            byte(state[2], 2),
            byte(state[1], 3));

  v = word4(byte(state[1], 0),
            byte(state[0], 1),
            byte(state[3], 2),
            byte(state[2], 3));

  x = word4(byte(state[2], 0),
            byte(state[1], 1),
            byte(state[0], 2),
            byte(state[3], 3));

  y = word4(byte(state[3], 0),
            byte(state[2], 1),
            byte(state[1], 2),
            byte(state[0], 3));

  state[0] = u;
  state[1] = v;
  state[2] = x;
  state[3] = y;
}

static uint32_t inv_mix_column(uint32_t x)
{
  uint32_t x2 = gf_poly_mul2(x),
           x4 = gf_poly_mul2(x2),
           x9 = x ^ gf_poly_mul2(x4),
           x11 = x2 ^ x9,
           x13 = x4 ^ x9;

  return x ^ x2 ^ x13 ^ rotr32(x11, 24) ^ rotr32(x13, 16) ^ rotr32(x9, 8);
}

static void inv_mix_columns(uint32_t state[4])
{
  state[0] = inv_mix_column(state[0]);
  state[1] = inv_mix_column(state[1]);
  state[2] = inv_mix_column(state[2]);
  state[3] = inv_mix_column(state[3]);
}

void cf_aes_decrypt(const cf_aes_context *ctx,
                    const uint8_t in[AES_BLOCKSZ],
                    uint8_t out[AES_BLOCKSZ])
{
  assert(ctx->rounds == AES128_ROUNDS ||
         ctx->rounds == AES192_ROUNDS ||
         ctx->rounds == AES256_ROUNDS);

  uint32_t state[4] = {
    read32_be(in + 0),
    read32_be(in + 4),
    read32_be(in + 8),
    read32_be(in + 12)
  };

  const uint32_t *round_keys = &ctx->ks[ctx->rounds << 2];
  add_round_key(state, round_keys);
  round_keys -= 4;

  for (uint32_t round = ctx->rounds - 1; round != 0; round--)
  {
    inv_shift_rows(state);
    inv_sub_block(state);
    add_round_key(state, round_keys);
    inv_mix_columns(state);
    round_keys -= 4;
  }

  inv_shift_rows(state);
  inv_sub_block(state);
  add_round_key(state, round_keys);
  
  write32_be(state[0], out + 0);
  write32_be(state[1], out + 4);
  write32_be(state[2], out + 8);
  write32_be(state[3], out + 12);
}
#else
void cf_aes_decrypt(const cf_aes_context *ctx,
                    const uint8_t in[AES_BLOCKSZ],
                    uint8_t out[AES_BLOCKSZ])
{
  abort();
}
#endif

void cf_aes_finish(cf_aes_context *ctx)
{
  mem_clean(ctx, sizeof *ctx);
}

const cf_prp cf_aes = {
  .blocksz = AES_BLOCKSZ,
  .encrypt = (cf_prp_block) cf_aes_encrypt,
  .decrypt = (cf_prp_block) cf_aes_decrypt
};

