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

#ifndef MODES_H
#define MODES_H

#include <stddef.h>
#include <stdint.h>

#include "prp.h"

/**
 * Block cipher modes
 * ==================
 */

/**
 * CBC mode
 * --------
 * This implementation allows encryption or decryption of whole
 * blocks in CBC mode.  It does not offer a byte-wise incremental
 * interface, or do any padding.
 *
 * This mode provides no useful integrity and should not be used
 * directly.
 */

/* .. c:type:: cf_cbc
 * This structure binds together the things needed to encrypt/decrypt whole
 * blocks in CBC mode.
 *
 * .. c:member:: cf_cbc.prp
 * How to encrypt or decrypt blocks.  This could be, for example, :c:data:`cf_aes`.
 *
 * .. c:member:: cf_cbc.prpctx
 * Private data for prp functions.  For a `prp` of `cf_aes`, this would be a
 * pointer to a :c:type:`cf_aes_context` instance.
 *
 * .. c:member:: cf_cbc.block
 * The IV or last ciphertext block.
 */
typedef struct
{
  const cf_prp *prp;
  void *prpctx;
  uint8_t block[CF_MAXBLOCK];
} cf_cbc;

/* .. c:function:: $DECL
 * Initialise CBC encryption/decryption context using selected prp, prp context and IV. */
void cf_cbc_init(cf_cbc *ctx, const cf_prp *prp, void *prpctx, const uint8_t iv[CF_MAXBLOCK]);

/* .. c:function:: $DECL
 * Encrypt blocks in CBC mode.  input and output
 * must point to blocks * ctx->prp->blocksz bytes of storage (and may alias). */
void cf_cbc_encrypt(cf_cbc *ctx, const uint8_t *input, uint8_t *output, size_t blocks);

/* .. c:function:: $DECL
 * Decrypt blocks in CBC mode.  input and output
 * must point to blocks * ctx->prp->blocksz bytes of storage (and may alias). */
void cf_cbc_decrypt(cf_cbc *ctx, const uint8_t *input, uint8_t *output, size_t blocks);

/**
 * Counter mode
 * ------------
 * This implementation allows incremental encryption/decryption of
 * messages.  Encryption and decryption are the same operation.
 *
 * The counter is always big-endian, but has configurable location
 * and size within the nonce block.  The counter wraps, so you
 * should make sure the length of a message with a given nonce
 * doesn't cause nonce reuse.
 *
 * This mode provides no integrity and should not be used directly.
 */

/* .. c:type:: cf_ctr
 *
 * .. c:member:: cf_ctr.prp
 * How to encrypt or decrypt blocks.  This could be, for example, :c:data:`cf_aes`.
 *
 * .. c:member:: cf_ctr.prpctx
 * Private data for prp functions.  For a `prp` of `cf_aes`, this would be a
 * pointer to a :c:type:`cf_aes_context` instance.
 *
 * .. c:member:: cf_ctr.nonce
 * The next block to encrypt to get another block of key stream.
 *
 * .. c:member:: cf_ctr.keymat
 * The current block of key stream.
 *
 * .. c:member:: cf_ctr.nkeymat
 * The number of bytes at the end of :c:member:`keymat` that are so-far unused.
 * If this is zero, all the bytes are used up and/or of undefined value.
 *
 * .. c:member:: cf_ctr.counter_offset
 * The offset (in bytes) of the counter block within the nonce.
 *
 * .. c:member:: cf_ctr.counter_width
 * The width (in bytes) of the counter block in the nonce.
 */
typedef struct
{
  const cf_prp *prp;
  void *prpctx;
  uint8_t nonce[CF_MAXBLOCK];
  uint8_t keymat[CF_MAXBLOCK];
  size_t nkeymat;
  size_t counter_offset;
  size_t counter_width;
} cf_ctr;

/* .. c:function:: $DECL
 * Initialise CTR encryption/decryption context using selected prp and nonce.
 * (nb, this only increments the whole nonce as a big endian block) */
void cf_ctr_init(cf_ctr *ctx, const cf_prp *prp, void *prpctx, const uint8_t nonce[CF_MAXBLOCK]);

/* .. c:function:: $DECL
 * Set the location and width of the nonce counter.
 *
 * eg. offset = 12, width = 4 means the counter is mod 2^32 and placed
 * at the end of the nonce. */
void cf_ctr_custom_counter(cf_ctr *ctx, size_t offset, size_t width);

/* .. c:function:: $DECL
 * Encrypt or decrypt bytes in CTR mode.
 * input and output may alias and must point to specified number of bytes. */
void cf_ctr_cipher(cf_ctr *ctx, const uint8_t *input, uint8_t *output, size_t bytes);

/* .. c:function:: $DECL
 * Discards the rest of this block of key stream. */
void cf_ctr_discard_block(cf_ctr *ctx);

/**
 * CBC-MAC
 * -------
 * This is a incremental interface to computing a CBC-MAC tag over a message.
 *
 * It optionally pads the message with PKCS#5/PKCS#7 padding -- if you don't
 * do this, messages must be an exact number of blocks long.
 *
 * You shouldn't use this directly because it isn't secure for variable-length
 * messages.  Use CMAC instead.
 */

/* .. c:type:: cf_cbcmac_stream
 * Stream interface to CBC-MAC signing.
 *
 * .. c:member:: cf_cbcmac.prp
 * How to encrypt or decrypt blocks.  This could be, for example, :c:data:`cf_aes`.
 *
 * .. c:member:: cf_cbcmac.prpctx
 * Private data for prp functions.  For a `prp` of `cf_aes`, this would be a
 * pointer to a :c:type:`cf_aes_context` instance.
 *
 * .. c:member:: cf_cbcmac.cbc
 * CBC data.
 *
 * .. c:member:: cf_cbcmac.buffer
 * Buffer for data which can't be processed until we have a full block.
 *
 * .. c:member:: cf_cbcmac.used
 * How many bytes at the front of :c:member:`buffer` are valid.
 */
typedef struct
{
  const cf_prp *prp;
  void *prpctx;
  cf_cbc cbc;
  uint8_t buffer[CF_MAXBLOCK];
  size_t used;
} cf_cbcmac_stream;

/* .. c:function:: $DECL
 * Initialise CBC-MAC signing context using selected prp. */
void cf_cbcmac_stream_init(cf_cbcmac_stream *ctx, const cf_prp *prp, void *prpctx);

/* .. c:function:: $DECL
 * Reset the streaming signing context, to sign a new message. */
void cf_cbcmac_stream_reset(cf_cbcmac_stream *ctx);

/* .. c:function:: $DECL
 * Process ndata bytes at data. */
void cf_cbcmac_stream_update(cf_cbcmac_stream *ctx, const uint8_t *data, size_t ndata);

/* .. c:function:: $DECL
 * Finish the current block of data by adding zeroes.  Does nothing if there
 * are no bytes awaiting processing. */
void cf_cbcmac_stream_finish_block_zero(cf_cbcmac_stream *ctx);

/* .. c:function:: $DECL
 * Output the MAC to ctx->prp->blocksz bytes at out.
 * ctx->used must be zero: the inputed message must be an exact number of
 * blocks. */
void cf_cbcmac_stream_nopad_final(cf_cbcmac_stream *ctx, uint8_t out[CF_MAXBLOCK]);

/* .. c:function:: $DECL
 * Output the MAC to ctx->prp->blocksz bytes at out.
 *
 * The message is padded with PKCS#5 padding. */
void cf_cbcmac_stream_pad_final(cf_cbcmac_stream *ctx, uint8_t out[CF_MAXBLOCK]);

/**
 * CMAC
 * ----
 * This is both a one-shot and incremental interface to
 * computing a CMAC tag over a message.
 *
 * The one-shot interface separates out the per-key computation,
 * so if you need to compute lots of MACs with one key you don't
 * pay that cost more than once.
 *
 * CMAC is a good choice for a symmetric MAC.
 */

/* .. c:type:: cf_cmac
 * One-shot interface to CMAC signing.
 *
 * .. c:member:: cf_cmac.prp
 * How to encrypt or decrypt blocks.  This could be, for example, :c:data:`cf_aes`.
 *
 * .. c:member:: cf_cmac.prpctx
 * Private data for prp functions.  For a `prp` of `cf_aes`, this would be a
 * pointer to a :c:type:`cf_aes_context` instance.
 *
 * .. c:member:: cf_cmac.B
 * The XOR offset for the last message block if it is a complete block
 * (also known as K\ :sub:`1`).
 *
 * .. c:member:: cf_cmac.P
 * The XOR offset for the last message block if it is a partial block
 * (also known as K\ :sub:`2`).
 */
typedef struct
{
  const cf_prp *prp;
  void *prpctx;
  uint8_t B[CF_MAXBLOCK];
  uint8_t P[CF_MAXBLOCK];
} cf_cmac;

/* .. c:function:: $DECL
 * Initialise CMAC signing context using selected prp. */
void cf_cmac_init(cf_cmac *ctx, const cf_prp *prp, void *prpctx);

/* .. c:function:: $DECL
 * CMAC sign the given data.  The MAC is written to ctx->prp->blocksz
 * bytes at out.   This is a one-shot function. */
void cf_cmac_sign(cf_cmac *ctx, const uint8_t *data, size_t bytes,
                  uint8_t out[CF_MAXBLOCK]);

/* .. c:type:: cf_cmac_stream
 * Stream interface to CMAC signing.
 *
 * Input data in arbitrary chunks using :c:func:`cf_cmac_stream_update`.
 * The last bit of data must be signalled with the `isfinal` flag to
 * that function, and the data cannot be zero length unless the whole
 * message is empty.
 *
 * .. c:member:: cf_cmac_stream.cmac
 * CMAC one-shot data.
 *
 * .. c:member:: cf_cmac_stream.cbc
 * CBC block encryption data.
 *
 * .. c:member:: cf_cmac_stream.buffer
 * Buffer for data which can't be processed until we have a full block.
 *
 * .. c:member:: cf_cmac_stream.used
 * How many bytes at the front of :c:member:`buffer` are valid.
 *
 * .. c:member:: cf_cmac_stream.processed
 * How many bytes in total we've processed.  This is used to correctly
 * process empty messages.
 *
 * .. c:member:: cf_cmac_stream.finalised
 * A flag set when the final chunk of the message has been processed.
 * Only when this flag is set can you get the MAC out.
 */
typedef struct
{
  cf_cmac cmac;
  cf_cbc cbc;
  uint8_t buffer[CF_MAXBLOCK];
  size_t used;
  size_t processed;
  int finalised;
} cf_cmac_stream;

/* .. c:function:: $DECL
 * Initialise CMAC streaming signing context using selected prp. */
void cf_cmac_stream_init(cf_cmac_stream *ctx, const cf_prp *prp, void *prpctx);

/* .. c:function:: $DECL
 * Reset the streaming signing context, to sign a new message. */
void cf_cmac_stream_reset(cf_cmac_stream *ctx);

/* .. c:function:: $DECL
 * Process ndata bytes at data.  isfinal is non-zero if this is the last piece
 * of data. */
void cf_cmac_stream_update(cf_cmac_stream *ctx, const uint8_t *data, size_t ndata,
                           int isfinal);

/* .. c:function:: $DECL
 * Output the MAC to ctx->cmac->prp->blocksz bytes at out.
 * cf_cmac_stream_update with isfinal non-zero must have been called
 * since the last _init/_reset. */
void cf_cmac_stream_final(cf_cmac_stream *ctx, uint8_t out[CF_MAXBLOCK]);

/**
 * EAX
 * ---
 *
 * The EAX authenticated encryption mode.  This is a one-shot
 * interface.
 *
 * EAX is a pretty respectable and fast AEAD mode.
 */

/* .. c:function:: $DECL
 * EAX authenticated encryption.
 *
 * This function does not fail.
 *
 * :param prp/prpctx: describe the block cipher to use.
 * :param plain: message plaintext.
 * :param nplain: length of message.  May be zero.
 * :param header: additionally authenticated data (AAD).
 * :param nheader: length of AAD.  May be zero.
 * :param nonce: nonce.  This must not repeat for a given key.
 * :param nnonce: length of nonce.  The nonce can be any length.
 * :param cipher: ciphertext output.  `nplain` bytes are written here.
 * :param tag: authentication tag.  `ntag` bytes are written here.
 * :param ntag: authentication tag length.  This must be non-zero and no greater than `prp->blocksz`.
 */
void cf_eax_encrypt(const cf_prp *prp, void *prpctx,
                    const uint8_t *plain, size_t nplain,
                    const uint8_t *header, size_t nheader,
                    const uint8_t *nonce, size_t nnonce,
                    uint8_t *cipher,
                    uint8_t *tag, size_t ntag);

/* .. c:function:: $DECL
 * EAX authenticated decryption.
 *
 * :return: 0 on success, non-zero on error.  Nothing is written to plain on error.
 *
 * :param prp/prpctx: describe the block cipher to use.
 * :param cipher: message ciphertext.
 * :param ncipher: message length.
 * :param header: additionally authenticated data (AAD).
 * :param nheader: length of AAD.
 * :param nonce: nonce.
 * :param nnonce: length of nonce.
 * :param tag: authentication tag.  `ntag` bytes are read from here.
 * :param ntag: authentication tag length.
 * :param plain: plaintext output.  `ncipher` bytes are written here.
 */
int cf_eax_decrypt(const cf_prp *prp, void *prpctx,
                   const uint8_t *cipher, size_t ncipher,
                   const uint8_t *header, size_t nheader,
                   const uint8_t *nonce, size_t nnonce,
                   const uint8_t *tag, size_t ntag,
                   uint8_t *plain);

/**
 * GCM
 * ---
 * The GCM ('Galois counter mode') authenticated encryption mode.
 * This is a one-shot interface.
 *
 * GCM is a reasonably respectable AEAD mode.  It's somewhat more
 * complex than EAX, and side channel-free implementations can
 * be quite slow.
 */

/* .. c:function:: $DECL
 * GCM authenticated encryption.
 *
 * This function does not fail.
 *
 * :param prp/prpctx: describe the block cipher to use.
 * :param plain: message plaintext.
 * :param nplain: length of message.  May be zero.
 * :param header: additionally authenticated data (AAD).
 * :param nheader: length of AAD.  May be zero.
 * :param nonce: nonce.  This must not repeat for a given key.
 * :param nnonce: length of nonce.  The nonce can be any length, but 12 bytes is strongly recommended.
 * :param cipher: ciphertext output.  `nplain` bytes are written here.
 * :param tag: authentication tag.  `ntag` bytes are written here.
 * :param ntag: authentication tag length.  This must be non-zero and no greater than `prp->blocksz`.
 *
 *  This function does not fail.
 */
void cf_gcm_encrypt(const cf_prp *prp, void *prpctx,
                    const uint8_t *plain, size_t nplain,
                    const uint8_t *header, size_t nheader,
                    const uint8_t *nonce, size_t nnonce,
                    uint8_t *cipher,
                    uint8_t *tag, size_t ntag);

/* .. c:function:: $DECL
 * GCM authenticated decryption.
 *
 * :return: 0 on success, non-zero on error.  Nothing is written to plain on error.
 *
 * :param prp: describe the block cipher to use.
 * :param prpctx: describe the block cipher to use.
 * :param cipher: message ciphertext.
 * :param ncipher: message length.
 * :param header: additionally authenticated data (AAD).
 * :param nheader: length of AAD.
 * :param nonce: nonce.
 * :param nnonce: length of nonce.
 * :param tag: authentication tag.  `ntag` bytes are read from here.
 * :param ntag: authentication tag length.
 * :param plain: plaintext output.  `ncipher` bytes are written here.
 */
int cf_gcm_decrypt(const cf_prp *prp, void *prpctx,
                   const uint8_t *cipher, size_t ncipher,
                   const uint8_t *header, size_t nheader,
                   const uint8_t *nonce, size_t nnonce,
                   const uint8_t *tag, size_t ntag,
                   uint8_t *plain);

/**
 * CCM
 * ---
 *
 * The CCM ('Counter with CBC-MAC') authenticated encryption mode.
 * CCM is a widely used AEAD mode (in IPSec, WPA2, Bluetooth, etc.)
 *
 * It works (at a high level) by just gluing together CTR and CBC-MAC
 * modes (in MAC-then-encrypt mode) and then fixing the problems inherent
 * with CBC-MAC in over-complicated ways.
 *
 * This is a one-shot interface, which is good because the underlying
 * mechanism isn't actually online: you need to know the message length
 * before you start, or do everything in two passes.
 */

/* .. c:function:: $DECL
 * CCM authenticated encryption.
 *
 * This function does not fail.
 *
 * :param prp/prpctx: describe the block cipher to use.
 * :param plain: message plaintext.
 * :param nplain: length of message.  May be zero.  Must meet the constraints placed on it by `L`.
 * :param L: length of the message length encoding.  This must be in the interval `[2,8]` and gives a maximum message size of 2\ :sup:`8L` bytes.
 * :param header: additionally authenticated data (AAD).
 * :param nheader: length of AAD.  May be zero.
 * :param nonce: nonce.  This must not repeat for a given key.
 * :param nnonce: length of nonce.  Must be exactly `15 - L` bytes for a 128-bit block cipher.
 * :param cipher: ciphertext output.  `nplain` bytes are written here.
 * :param tag: authentication tag.  `ntag` bytes are written here.
 * :param ntag: authentication tag length.  This must be 4, 6, 8, 10, 12, 14 or 16.
 */
void cf_ccm_encrypt(const cf_prp *prp, void *prpctx,
                    const uint8_t *plain, size_t nplain, size_t L,
                    const uint8_t *header, size_t nheader,
                    const uint8_t *nonce, size_t nnonce,
                    uint8_t *cipher,
                    uint8_t *tag, size_t ntag);

/* .. c:function:: $DECL
 * CCM authenticated decryption.
 *
 * :return: 0 on success, non-zero on error.  Plain is cleared on error.
 *
 * :param prp: describe the block cipher to use.
 * :param prpctx: describe the block cipher to use.
 * :param cipher: message ciphertext.
 * :param ncipher: length of message.
 * :param L: length of the message length encoding.  See :c:func:`cf_ccm_encrypt`.
 * :param header: additionally authenticated data (AAD).
 * :param nheader: length of AAD.
 * :param nonce: nonce.
 * :param nnonce: length of nonce.
 * :param tag: authentication tag.  `ntag` bytes are read from here.
 * :param ntag: authentication tag length.  This must be 4, 6, 8, 10, 12, 14 or 16.
 * :param plain: plaintext output.  `ncipher` bytes are written here.
 */
int cf_ccm_decrypt(const cf_prp *prp, void *prpctx,
                   const uint8_t *cipher, size_t ncipher, size_t L,
                   const uint8_t *header, size_t nheader,
                   const uint8_t *nonce, size_t nnonce,
                   const uint8_t *tag, size_t ntag,
                   uint8_t *plain);

/**
 * OCB
 * ---
 *
 * OCB is an authenticated encryption mode by Phil Rogaway.
 *
 * This is version 3, as standardised in RFC7253.  It's defined
 * only for block ciphers with a 128-bit block size.
 *
 * This is a one-shot interface.
 */

/* .. c:function:: $DECL
 * OCB authenticated encryption.
 *
 * This function does not fail.
 *
 * :param prp/prpctx: describe the block cipher to use.
 * :param plain: message plaintext.
 * :param nplain: length of message.  May be zero.
 * :param header: additionally authenticated data (AAD).
 * :param nheader: length of AAD.  May be zero.
 * :param nonce: nonce.  This must not repeat for a given key.
 * :param nnonce: length of nonce.  Must be 15 or fewer bytes.
 * :param cipher: ciphertext output.  `nplain` bytes are written here.
 * :param tag: authentication tag.  `ntag` bytes are written here.
 * :param ntag: authentication tag length.  Must be 16 or fewer bytes.
 */
void cf_ocb_encrypt(const cf_prp *prp, void *prpctx,
                    const uint8_t *plain, size_t nplain,
                    const uint8_t *header, size_t nheader,
                    const uint8_t *nonce, size_t nnonce,
                    uint8_t *cipher,
                    uint8_t *tag, size_t ntag);

/* .. c:function:: $DECL
 * OCB authenticated decryption.
 *
 * :return: 0 on success, non-zero on error.  `plain` is cleared on error.
 *
 * :param prp: describe the block cipher to use.
 * :param prpctx: describe the block cipher to use.
 * :param cipher: message ciphertext.
 * :param ncipher: length of message.
 * :param header: additionally authenticated data (AAD).
 * :param nheader: length of AAD.
 * :param nonce: nonce.
 * :param nnonce: length of nonce.
 * :param tag: authentication tag.  `ntag` bytes are read from here.
 * :param ntag: authentication tag length.
 * :param plain: plaintext output.  `ncipher` bytes are written here.
 */
int cf_ocb_decrypt(const cf_prp *prp, void *prpctx,
                   const uint8_t *cipher, size_t ncipher,
                   const uint8_t *header, size_t nheader,
                   const uint8_t *nonce, size_t nnonce,
                   const uint8_t *tag, size_t ntag,
                   uint8_t *plain);
#endif
