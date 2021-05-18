/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 */
/* @(#)rpc_msg.h    2.1 88/07/29 4.0 RPCSRC */
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
/*      @(#)rpc_msg.h 1.7 86/07/16 SMI      */

#ifndef _RPC_MSG_H
#define _RPC_MSG_H 1

#include <rpc/xdr.h>
#include <rpc/clnt.h>

/*
 * rpc_msg.h
 * rpc message definition
 *
 * Copyright (C) 1984, Sun Microsystems, Inc.
 */

#define RPC_MSG_VERSION     ((unsigned long) 2)
#define RPC_SERVICE_PORT    ((unsigned short) 2048)

/*
 * Bottom up definition of an rpc message.
 * NOTE: call and reply use the same overall struct but
 * different parts of unions within it.
 */

enum msg_type {
    CALL=0,
    REPLY=1
};

enum reply_stat {
    MSG_ACCEPTED=0,
    MSG_DENIED=1
};

enum accept_stat {
    SUCCESS=0,
    PROG_UNAVAIL=1,
    PROG_MISMATCH=2,
    PROC_UNAVAIL=3,
    GARBAGE_ARGS=4,
    SYSTEM_ERR=5
};

enum reject_stat {
    RPC_MISMATCH=0,
    AUTH_ERROR=1
};

/*
 * Reply part of an rpc exchange
 */

/*
 * Reply to an rpc request that was accepted by the server.
 * Note: there could be an error even though the request was
 * accepted.
 */
struct accepted_reply {
    struct opaque_auth  ar_verf;
    int                 ar_stat;
    union {
        struct {
            unsigned long   low;
            unsigned long   high;
        } AR_versions;
        struct {
            char*   where;
            xdrproc_t proc;
        } AR_results;
        /* and many other null cases */
    } ru;
#define ar_results  ru.AR_results
#define ar_vers     ru.AR_versions
};

/*
 * Reply to an rpc request that was rejected by the server.
 */
struct rejected_reply {
    int rj_stat;
    union {
        struct {
            unsigned long low;
            unsigned long high;
        } RJ_versions;
        int RJ_why;  /* why authentication did not work */
    } ru;
#define rj_vers ru.RJ_versions
#define rj_why  ru.RJ_why
};

/*
 * Body of a reply to an rpc request.
 */
struct reply_body {
    int rp_stat;
    union {
        struct accepted_reply RP_ar;
        struct rejected_reply RP_dr;
    } ru;
#define rp_acpt ru.RP_ar
#define rp_rjct ru.RP_dr
};

/*
 * Body of an rpc request call.
 */
struct call_body {
    unsigned long cb_rpcvers;   /* must be equal to two */
    unsigned long cb_prog;
    unsigned long cb_vers;
    unsigned long cb_proc;
    struct opaque_auth cb_cred;
    struct opaque_auth cb_verf; /* protocol specific - provided by client */
};

/*
 * The rpc message
 */
struct rpc_msg {
    unsigned long   rm_xid;
    int             rm_direction;
    union {
        struct call_body RM_cmb;
        struct reply_body RM_rmb;
    } ru;
#define rm_call     ru.RM_cmb
#define rm_reply    ru.RM_rmb
};
#define acpted_rply ru.RM_rmb.ru.RP_ar
#define rjcted_rply ru.RM_rmb.ru.RP_dr


/*
 * XDR routine to handle a rpc message.
 * xdr_callmsg(xdrs, cmsg)
 *  XDR *xdrs;
 *  struct rpc_msg *cmsg;
 */
extern bool_t   xdr_callmsg (XDR *__xdrs, struct rpc_msg *__cmsg);

/*
 * XDR routine to pre-serialize the static part of a rpc message.
 * xdr_callhdr(xdrs, cmsg)
 *  XDR *xdrs;
 *  struct rpc_msg *cmsg;
 */
extern bool_t   xdr_callhdr (XDR *__xdrs, struct rpc_msg *__cmsg);

/*
 * XDR routine to handle a rpc reply.
 * xdr_replymsg(xdrs, rmsg)
 *  XDR *xdrs;
 *  struct rpc_msg *rmsg;
 */
extern bool_t   xdr_replymsg (XDR *__xdrs, struct rpc_msg *__rmsg);

/*
 * Fills in the error part of a reply message.
 * _seterr_reply(msg, error)
 *  struct rpc_msg *msg;
 *  struct rpc_err *error;
 */
extern void _seterr_reply (struct rpc_msg *__msg, struct rpc_err *__error);

#endif /* rpc/rpc_msg.h */
