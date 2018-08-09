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

#include "prp.h"
#include "modes.h"
#include "bitops.h"
#include "blockwise.h"

#include <string.h>
#include "tassert.h"

/* CBC */
void cf_cbc_init(cf_cbc *ctx, const cf_prp *prp, void *prpctx, const uint8_t iv[CF_MAXBLOCK])
{
  ctx->prp = prp;
  ctx->prpctx = prpctx;
  memcpy(ctx->block, iv, prp->blocksz);
}

void cf_cbc_encrypt(cf_cbc *ctx, const uint8_t *input, uint8_t *output, size_t blocks)
{
  uint8_t buf[CF_MAXBLOCK];
  size_t nblk = ctx->prp->blocksz;

  while (blocks--)
  {
    xor_bb(buf, input, ctx->block, nblk);
    ctx->prp->encrypt(ctx->prpctx, buf, ctx->block);
    memcpy(output, ctx->block, nblk);
    input += nblk;
    output += nblk;
  }
}

void cf_cbc_decrypt(cf_cbc *ctx, const uint8_t *input, uint8_t *output, size_t blocks)
{
  uint8_t buf[CF_MAXBLOCK];
  size_t nblk = ctx->prp->blocksz;

  while (blocks--)
  {
    ctx->prp->decrypt(ctx->prpctx, input, buf);
    xor_bb(output, buf, ctx->block, nblk);
    memcpy(ctx->block, input, nblk);
    input += nblk;
    output += nblk;
  }
}

/* CTR */
void cf_ctr_init(cf_ctr *ctx, const cf_prp *prp, void *prpctx, const uint8_t nonce[CF_MAXBLOCK])
{
  memset(ctx, 0, sizeof *ctx);
  ctx->counter_offset = 0;
  ctx->counter_width = prp->blocksz;
  ctx->prp = prp;
  ctx->prpctx = prpctx;
  ctx->nkeymat = 0;
  memcpy(ctx->nonce, nonce, prp->blocksz);
}

void cf_ctr_custom_counter(cf_ctr *ctx, size_t offset, size_t width)
{
  assert(ctx->prp->blocksz <= offset + width);
  ctx->counter_offset = offset;
  ctx->counter_width = width;
}

static void ctr_next_block(void *vctx, uint8_t *out)
{
  cf_ctr *ctx = vctx;
  ctx->prp->encrypt(ctx->prpctx, ctx->nonce, out);
  incr_be(ctx->nonce + ctx->counter_offset, ctx->counter_width);
}

void cf_ctr_cipher(cf_ctr *ctx, const uint8_t *input, uint8_t *output, size_t bytes)
{
  cf_blockwise_xor(ctx->keymat, &ctx->nkeymat,
                   ctx->prp->blocksz,
                   input, output, bytes,
                   ctr_next_block,
                   ctx);
}

void cf_ctr_discard_block(cf_ctr *ctx)
{
  ctx->nkeymat = 0;
}
