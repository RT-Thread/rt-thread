/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 */

#include <rpc/types.h>
#include <rpc/xdr.h>
#include <rpc/auth.h>

#define MAX_MARSHEL_SIZE 64

struct nfs_credentia
{
    rt_uint32_t stamp;
    char *name;
    rt_uint32_t uid;
    rt_uint32_t gid;
    rt_uint32_t *auxi;
    rt_uint32_t auxi_count;
};

static void authnone_verf(AUTH *);
static bool_t authnone_validate(AUTH *, struct opaque_auth *);
static bool_t authnone_refresh(AUTH *);
static void authnone_destroy(AUTH *);
static bool_t authnone_marshal(AUTH *client, XDR *xdrs);

static struct nfs_credentia _credentia = {
    .stamp = 0,
    .name = "rt-thread",
    .uid = 0,
    .gid = 0,
    .auxi = NULL,
    .auxi_count = 0,
};

struct opaque_auth _null_auth;

static struct auth_ops ops =
{
    authnone_verf,
    authnone_marshal,
    authnone_validate,
    authnone_refresh,
    authnone_destroy
};

static struct authnone_private
{
    AUTH no_client;
    char marshalled_client[MAX_MARSHEL_SIZE];
    unsigned int mcnt;
} *authnone_private;

AUTH *authnone_create(void)
{
    register struct authnone_private *ap = authnone_private;
    XDR xdr_stream;
    register XDR *xdrs;
    extern bool_t xdr_opaque_auth(XDR * xdrs, struct opaque_auth * ap);
    struct opaque_auth auth;
    rt_uint32_t *auth_buf, *auth_base;
    int buf_len = 0, str_len = 0;

    if (_credentia.name)
    {
        str_len = strlen(_credentia.name);
    }
    if (str_len == 0)
    {
        _credentia.name = "unknown";
        str_len = strlen(_credentia.name);
    }
    buf_len = ((str_len) + (sizeof(rt_uint32_t)) - 1) & ~((sizeof(rt_uint32_t)) - 1);
    buf_len += sizeof(struct nfs_credentia);
    if (_credentia.auxi && _credentia.auxi_count)
    {
        buf_len += sizeof(rt_uint32_t) * _credentia.auxi_count;
    }
    auth_buf = auth_base = rt_malloc(buf_len);
    if (auth_buf == NULL)
    {
        return NULL;
    }
    memset(auth_buf, 0, buf_len);
    *auth_buf++ = htonl(rt_tick_get());
    *auth_buf++ = htonl(str_len);
    memcpy(auth_buf, _credentia.name, str_len);
    auth_buf += (str_len + sizeof(rt_uint32_t) - 1) >> 2;
    *auth_buf++ = htonl(_credentia.uid);
    *auth_buf++ = htonl(_credentia.gid);
    if (_credentia.auxi && _credentia.auxi_count)
    {
        rt_uint32_t tmp_cnt = 0;
        *auth_buf++ = htonl(_credentia.auxi_count);
        while (tmp_cnt < _credentia.auxi_count)
        {
            *auth_buf++ = htonl(_credentia.auxi[tmp_cnt]);
        }
    }
    else
    {
        *auth_buf++ = htonl(0);
    }

    if (ap == 0)
    {
        ap = (struct authnone_private *) rt_malloc(sizeof(*ap));
        if (ap == 0)
        {
            rt_free(auth_base);
            return NULL;
        }
        memset(ap, 0, sizeof(*ap));
        authnone_private = ap;
    }

    if (!ap->mcnt)
    {
        memset(&auth, 0, sizeof(auth));
        auth.oa_flavor = 1;
        auth.oa_base = (char *)auth_base;
        auth.oa_length = (auth_buf - auth_base) * sizeof(rt_uint32_t);
        ap->no_client.ah_cred = auth;
        ap->no_client.ah_verf = _null_auth;
        ap->no_client.ah_ops = &ops;
        xdrs = &xdr_stream;
        xdrmem_create(xdrs, ap->marshalled_client,
                      (unsigned int) MAX_MARSHEL_SIZE, XDR_ENCODE);
        (void) xdr_opaque_auth(xdrs, &ap->no_client.ah_cred);
        (void) xdr_opaque_auth(xdrs, &ap->no_client.ah_verf);
        ap->mcnt = XDR_GETPOS(xdrs);
        XDR_DESTROY(xdrs);
    }
    rt_free(auth_base);
    return (&ap->no_client);
}

/*ARGSUSED*/
static bool_t authnone_marshal(AUTH *client, XDR *xdrs)
{
    register struct authnone_private *ap = authnone_private;

    if (ap == 0)
        return (0);
    return ((*xdrs->x_ops->x_putbytes)(xdrs,
                                       ap->marshalled_client, ap->mcnt));
}

static void authnone_verf(AUTH *x)
{
}

static bool_t authnone_validate(AUTH *x, struct opaque_auth *x1)
{

    return (TRUE);
}

static bool_t authnone_refresh(AUTH *x)
{

    return (FALSE);
}

static void authnone_destroy(AUTH *x)
{
}
