/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 */
/* @(#)xdr_mem.c    2.1 88/07/29 4.0 RPCSRC */
/*
 * Sun RPC is a product of Sun Microsystems, Inc. and is provided for
 * unrestricted use provided that this legend is included on all tape
 * media and as a part of the software program in whole or part.  Users
 * may copy or modify Sun RPC without charge, but are not authorized
 * to license or distribute it to anyone else except as part of a product or
 * program developed by the user.
 *
 * SUN RPC IS PROVIDED AS IS WITH NO WARRANTIES OF ANY KIND INCLUDING THE
 * WARRANTIES OF DESIGN, MERCHANTIBILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE, OR ARISING FROM A COURSE OF DEALING, USAGE OR TRADE PRACTICE.
 *
 * Sun RPC is provided with no support and without any obligation on the
 * part of Sun Microsystems, Inc. to assist in its use, correction,
 * modification or enhancement.
 *
 * SUN MICROSYSTEMS, INC. SHALL HAVE NO LIABILITY WITH RESPECT TO THE
 * INFRINGEMENT OF COPYRIGHTS, TRADE SECRETS OR ANY PATENTS BY SUN RPC
 * OR ANY PART THEREOF.
 *
 * In no event will Sun Microsystems, Inc. be liable for any lost revenue
 * or profits or other special, indirect and consequential damages, even if
 * Sun has been advised of the possibility of such damages.
 *
 * Sun Microsystems, Inc.
 * 2550 Garcia Avenue
 * Mountain View, California  94043
 */
#if !defined(lint) && defined(SCCSIDS)
static char sccsid[] = "@(#)xdr_mem.c 1.19 87/08/11 Copyr 1984 Sun Micro";
#endif

/*
 * xdr_mem.h, XDR implementation using memory buffers.
 *
 * Copyright (C) 1984, Sun Microsystems, Inc.
 *
 * If you have some data to be interpreted as external data representation
 * or to be converted to external data representation in a memory buffer,
 * then this is the package for you.
 *
 */

#include <rpc/types.h>
#include <rpc/xdr.h>
#include <string.h>
#include <limits.h>
#include <byteswap.h>

static bool_t xdrmem_getlong (XDR *, int64_t *);
static bool_t xdrmem_putlong (XDR *, const int64_t *);
static bool_t xdrmem_getint32 (XDR *, int32_t *);
static bool_t xdrmem_putint32 (XDR *, const int32_t *);
static bool_t xdrmem_getbytes (XDR *, char *, unsigned int);
static bool_t xdrmem_putbytes (XDR *, const char *, unsigned int);
static unsigned int xdrmem_getpos (const XDR *);
static bool_t xdrmem_setpos (XDR *, unsigned int);
static int32_t *xdrmem_inline (XDR *, unsigned int);
static void xdrmem_destroy (XDR *);

static struct xdr_ops xdrmem_ops = {
    xdrmem_getlong,
    xdrmem_putlong,
    xdrmem_getbytes,
    xdrmem_putbytes,
    xdrmem_getpos,
    xdrmem_setpos,
    xdrmem_inline,
    xdrmem_destroy,
    xdrmem_getint32,
    xdrmem_putint32
};


/*
 * The procedure xdrmem_create initializes a stream descriptor for a
 * memory buffer.
 */
void
xdrmem_create (XDR *xdrs, const char* addr, unsigned int size, enum xdr_op op)
{
    xdrs->x_op = op;
    xdrs->x_ops = &xdrmem_ops;
    xdrs->x_private = xdrs->x_base = (char*)addr;
    xdrs->x_handy = size;
}

static void
xdrmem_destroy (XDR *xdrs)
{
}

static bool_t
xdrmem_getlong (XDR *xdrs, int64_t *lp)
{
  if (xdrs->x_handy < 8) return FALSE;
  xdrs->x_handy -= 8;

  *lp = bswap_64(*((uint64_t *) (xdrs->x_private)));
  xdrs->x_private += 8;
  return TRUE;
}

static bool_t
xdrmem_putlong (XDR *xdrs, const int64_t *lp)
{
  if (xdrs->x_handy < 8) return FALSE;
  xdrs->x_handy -= 8;

  *(uint64_t *)xdrs->x_private = bswap_64(*lp);
  xdrs->x_private += 8;
  return (TRUE);
}

static bool_t
xdrmem_getint32 (XDR *xdrs, int32_t *lp)
{
  if (xdrs->x_handy < 4) return FALSE;
  xdrs->x_handy -= 4;

  *lp = bswap_32(*((uint32_t *) (xdrs->x_private)));
  xdrs->x_private += 4;
  return TRUE;
}

static bool_t
xdrmem_putint32 (XDR *xdrs, const int32_t *lp)
{
  if (xdrs->x_handy < 4) return FALSE;
  xdrs->x_handy -= 4;

  *(uint32_t *)xdrs->x_private = bswap_32(*lp);
  xdrs->x_private += 4;
  return (TRUE);
}

static bool_t
xdrmem_getbytes (XDR *xdrs, char *addr, unsigned int len)
{
  if (xdrs->x_handy < len) return FALSE;
  xdrs->x_handy -= len;
  memmove(addr, xdrs->x_private, len);
  xdrs->x_private += len;
  return TRUE;
}

static bool_t
xdrmem_putbytes (XDR *xdrs, const char *addr, unsigned int len)
{
  if (xdrs->x_handy < len) return FALSE;
  xdrs->x_handy -= len;
  memmove(xdrs->x_private, addr, len);
  xdrs->x_private += len;
  return (TRUE);
}

static unsigned int xdrmem_getpos (const XDR *xdrs)
{
    return ((uint64_t) xdrs->x_private - (uint64_t) xdrs->x_base);
}

static bool_t xdrmem_setpos(XDR *xdrs, unsigned int pos)
{
  register char* newaddr = xdrs->x_base + pos;
  register char* lastaddr = xdrs->x_private + xdrs->x_handy;

  if ((uint64_t) newaddr > (uint64_t) lastaddr
      || (UINT_MAX < LONG_MAX
          && (uint64_t) UINT_MAX < (uint64_t) lastaddr - (uint64_t) newaddr))
      return (FALSE);
  xdrs->x_private = newaddr;
  xdrs->x_handy = (uint64_t) lastaddr - (uint64_t) newaddr;
  return (TRUE);
}

static int32_t *
xdrmem_inline (XDR *xdrs, unsigned int len)
{
    int32_t *buf = 0;

    if (xdrs->x_handy >= len) {
        xdrs->x_handy -= len;
        buf = (int32_t *) xdrs->x_private;
        xdrs->x_private += len;
    }
    return (buf);
}

