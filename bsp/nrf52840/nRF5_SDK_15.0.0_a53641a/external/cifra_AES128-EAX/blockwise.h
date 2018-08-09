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

#ifndef BLOCKWISE_H
#define BLOCKWISE_H

#include <stdint.h>
#include <stddef.h>

/* Processing function for cf_blockwise_accumulate. */
typedef void (*cf_blockwise_in_fn)(void *ctx, const uint8_t *data);

/* Processing function for cf_blockwise_xor. */
typedef void (*cf_blockwise_out_fn)(void *ctx, uint8_t *data);

/* This function manages the common abstraction of accumulating input in
 * a buffer, and processing it when a full block is available.
 *
 * partial is the buffer (maintained by the caller)
 * on entry, npartial is the currently valid count of used bytes on
 *   the front of partial.
 * on exit, npartial is updated to reflect the status of partial.
 * nblock is the blocksize to accumulate -- partial must be at least
 *   this long!
 * input is the new data to process, of length nbytes.
 * process is the processing function, passed ctx and a pointer
 *   to the data to process (always exactly nblock bytes long!)
 *   which may not neccessarily be the same as partial.
 */
void cf_blockwise_accumulate(uint8_t *partial, size_t *npartial,
                             size_t nblock,
                             const void *input, size_t nbytes,
                             cf_blockwise_in_fn process, 
                             void *ctx);

/* This function manages the common abstraction of accumulating input in
 * a buffer, and processing it when a full block is available.
 * This version supports calling a different processing function for
 * the last block.
 *
 * partial is the buffer (maintained by the caller)
 * on entry, npartial is the currently valid count of used bytes on
 *   the front of partial.
 * on exit, npartial is updated to reflect the status of partial.
 * nblock is the blocksize to accumulate -- partial must be at least
 *   this long!
 * input is the new data to process, of length nbytes.
 * process is the processing function, passed ctx and a pointer
 *   to the data to process (always exactly nblock bytes long!)
 *   which may not neccessarily be the same as partial.
 * process_final is called last (but may not be called at all if
 *   all input is buffered).
 */
void cf_blockwise_accumulate_final(uint8_t *partial, size_t *npartial,
                                   size_t nblock,
                                   const void *input, size_t nbytes,
                                   cf_blockwise_in_fn process, 
                                   cf_blockwise_in_fn process_final,
                                   void *ctx);

/* This function manages XORing an input stream with a keystream
 * to produce an output stream.  The keystream is produced in blocks
 * (ala a block cipher in counter mode).
 *
 * partial is the keystream buffer (maintained by the caller)
 * on entry, *npartial is the currently valid count of bytes in partial:
 *   unused bytes are at the *end*.  So *npartial = 4 means the last four
 *   bytes of partial are usable as keystream.
 * on exit, npartial is updated to reflect the new state of partial.
 * nblock is the blocksize to accumulate -- partial must be at least
 *   this long!
 * input is the new data to process, of length nbytes.
 * output is where to write input xored with the keystream -- also length
 *   nbytes.
 * process is the processing function, passed ctx and partial which it
 *   should fill with fresh key stream.
 */
void cf_blockwise_xor(uint8_t *partial, size_t *npartial,
                      size_t nblock,
                      const void *input, void *output, size_t nbytes,
                      cf_blockwise_out_fn newblock,
                      void *ctx);

/* This function processes a single byte a number of times. It's useful
 * for padding, and more efficient than calling cf_blockwise_accumulate
 * a bunch of times.
 *
 * partial is the buffer (maintained by the caller)
 * on entry, npartial is the currently valid count of used bytes on
 *   the front of partial.
 * on exit, npartial is updated to reflect the status of partial.
 * nblock is the blocksize to accumulate -- partial must be at least
 *   this long!
 * process is the processing function, passed ctx and a pointer
 *   to the data to process (always exactly nblock bytes long!)
 *   which may not neccessarily be the same as partial.
 * byte is the byte to process, nbytes times.
 */
void cf_blockwise_acc_byte(uint8_t *partial, size_t *npartial,
                           size_t nblock,
                           uint8_t byte, size_t nbytes,
                           cf_blockwise_in_fn process,
                           void *ctx);

/* This function attempts to process patterns of bytes common in
 * block cipher padding.
 *
 * This takes three bytes:
 * - a first byte, fbyte,
 * - a middle byte, mbyte,
 * - a last byte, lbyte.
 *
 * If nbytes is zero, nothing happens.
 * If nbytes is one, the byte fbyte ^ lbyte is processed.
 * If nbytes is two, the fbyte then lbyte are processed.
 * If nbytes is three or more, fbyte, then one or more mbytes, then fbyte
 *   is processed.
 *
 * partial is the buffer (maintained by the caller)
 * on entry, npartial is the currently valid count of used bytes on
 *   the front of partial.
 * on exit, npartial is updated to reflect the status of partial.
 * nblock is the blocksize to accumulate -- partial must be at least
 *   this long!
 * process is the processing function, passed ctx and a pointer
 *   to the data to process (always exactly nblock bytes long!)
 *   which may not neccessarily be the same as partial.
 */
void cf_blockwise_acc_pad(uint8_t *partial, size_t *npartial,
                          size_t nblock,
                          uint8_t fbyte, uint8_t mbyte, uint8_t lbyte,
                          size_t nbytes,
                          cf_blockwise_in_fn process,
                          void *ctx);

#endif
