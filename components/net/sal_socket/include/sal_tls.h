/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-11-10     ChenYong     First version
 */
#ifndef __SAL_TLS_H__
#define __SAL_TLS_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <rtthread.h>

/* Protocol level for TLS.
 * Here, the same socket protocol level for TLS as in Linux was used.
 */
#define SOL_TLS             282

/* Socket options for TLS */

/* Socket option to select TLS credentials to use. */
#define TLS_CRET_LIST        1
/* Socket option to set select ciphersuites to use. */
#define TLS_CIPHERSUITE_LIST 2
/* Socket option to set peer verification level for TLS connection. */
#define TLS_PEER_VERIFY      3
/* Socket option to set role for DTLS connection. */
#define TLS_DTLS_ROLE        4

/* Protocol numbers for TLS protocols */
#define PROTOCOL_TLS         256
#define PROTOCOL_DTLS        257


struct sal_proto_tls_ops
{
    int (*init)(void);
    void* (*socket)(int socket);
    int (*connect)(void *sock);
    int (*send)(void *sock, const void *data, size_t size);
    int (*recv)(void *sock, void *mem, size_t len);
    int (*closesocket)(void *sock);

    int (*set_cret_list)(void *sock, const void *cert, size_t size);              /* Set TLS credentials */
    int (*set_ciphersurite)(void *sock, const void* ciphersurite, size_t size);   /* Set select ciphersuites */
    int (*set_peer_verify)(void *sock, const void* peer_verify, size_t size);     /* Set peer verification */
    int (*set_dtls_role)(void *sock, const void *dtls_role, size_t size);         /* Set role for DTLS */
};

struct sal_proto_tls
{
    char name[RT_NAME_MAX];                      /* TLS protocol name */
    const struct sal_proto_tls_ops *ops;         /* SAL TLS protocol options */
};

/* SAL TLS protocol register */
int sal_proto_tls_register(const struct sal_proto_tls *pt);

#ifdef __cplusplus
}
#endif

#endif /* __SAL_TLS_H__ */
