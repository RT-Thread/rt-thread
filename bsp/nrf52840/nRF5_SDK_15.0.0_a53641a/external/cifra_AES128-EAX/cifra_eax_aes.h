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

/**
 * The AES block cipher
 * ====================
 *
 * This is a small, simple implementation of AES.  Key expansion is done
 * first, filling in a :c:type:`cf_aes_context`.  Then encryption and
 * decryption can be performed as desired.
 *
 * Usually you don't want to use AES directly; you should use it via
 * a :doc:`block cipher mode <modes>`.
 */

#ifndef AES_H
#define AES_H

#include <stddef.h>
#include <stdint.h>

#include "prp.h"

/* .. c:macro:: AES_BLOCKSZ
 * AES has a 128-bit block size.  This quantity is in bytes.
 */
#define AES_BLOCKSZ 16

/* --- Size configuration --- */

/* .. c:macro:: AES128_ROUNDS
 * .. c:macro:: AES192_ROUNDS
 * .. c:macro:: AES256_ROUNDS
 *
 * Round counts for different key sizes.
 */
#define AES128_ROUNDS 10
#define AES192_ROUNDS 12
#define AES256_ROUNDS 14

/* .. c:macro:: CF_AES_MAXROUNDS
 *
 * You can reduce the maximum number of rounds this implementation
 * supports. This reduces the storage needed by :c:type:`cf_aes_context`.
 *
 * The default is :c:macro:`AES256_ROUNDS` and is good for all key
 * sizes.
 */
#ifndef CF_AES_MAXROUNDS
# define CF_AES_MAXROUNDS AES256_ROUNDS
#endif

/* .. c:macro:: CF_AES_ENCRYPT_ONLY
 *
 * Define this to 1 if you don't need to decrypt anything.
 * This saves space.  :c:func:`cf_aes_decrypt` calls `abort(3)`.
 */
#ifndef CF_AES_ENCRYPT_ONLY
# define CF_AES_ENCRYPT_ONLY 0
#endif

/* .. c:type:: cf_aes_context
 * This type represents an expanded AES key.  Create one
 * using :c:func:`cf_aes_init`, make use of one using
 * :c:func:`cf_aes_encrypt` or :c:func:`cf_aes_decrypt`.
 *
 * The contents of this structure are equivalent to the
 * original key material.  You should clean the
 * contents of this structure with :c:func:`cf_aes_finish`
 * when you're done.
 *
 * .. c:member:: cf_aes_context.rounds
 * 
 * Number of rounds to use, set by :c:func:`cf_aes_init`.
 *
 * This depends on the original key size, and will be
 * :c:macro:`AES128_ROUNDS`, :c:macro:`AES192_ROUNDS` or
 * :c:macro:`AES256_ROUNDS`.
 *
 * .. c:member:: cf_aes_context.ks
 * 
 * Expanded key material.  Filled in by :c:func:`cf_aes_init`.
 */
typedef struct
{
  uint32_t rounds;
  uint32_t ks[AES_BLOCKSZ / 4 * (CF_AES_MAXROUNDS + 1)];
} cf_aes_context;

/* .. c:function:: $DECL
 * This function does AES key expansion.  It destroys
 * existing contents of :c:data:`ctx`.
 *
 * :param ctx: expanded key context, filled in by this function.
 * :param key: pointer to key material, of :c:data:`nkey` bytes.
 * :param nkey: length of key material. Must be `16`, `24` or `32`.
 */
extern void cf_aes_init(cf_aes_context *ctx,
                        const uint8_t *key,
                        size_t nkey);

/* .. c:function:: $DECL
 * Encrypts the given block, from :c:data:`in` to :c:data:`out`.
 * These may alias.
 *
 * Fails at runtime if :c:data:`ctx` is invalid.
 *
 * :param ctx: expanded key context
 * :param in: input block (read)
 * :param out: output block (written)
 */
extern void cf_aes_encrypt(const cf_aes_context *ctx,
                           const uint8_t in[AES_BLOCKSZ],
                           uint8_t out[AES_BLOCKSZ]);

/* .. c:function:: $DECL
 * Decrypts the given block, from :c:data:`in` to :c:data:`out`.
 * These may alias.
 *
 * Fails at runtime if :c:data:`ctx` is invalid.
 *
 * :param ctx: expanded key context
 * :param in: input block (read)
 * :param out: output block (written)
 */
extern void cf_aes_decrypt(const cf_aes_context *ctx,
                           const uint8_t in[AES_BLOCKSZ],
                           uint8_t out[AES_BLOCKSZ]);

/* .. c:function:: $DECL
 * Erase scheduled key material.
 *
 * Call this when you're done to erase the round keys. */
extern void cf_aes_finish(cf_aes_context *ctx);

/* .. c:var:: const cf_prp cf_aes
 * Abstract interface to AES.  See :c:type:`cf_prp` for
 * more information. */
extern const cf_prp cf_aes;

#endif
