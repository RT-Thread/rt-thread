/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 */
/* @(#)rpc_prot.c   2.3 88/08/07 4.0 RPCSRC */
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
static char sccsid[] = "@(#)rpc_prot.c 1.36 87/08/11 Copyr 1984 Sun Micro";
#endif

/*
 * rpc_prot.c
 *
 * Copyright (C) 1984, Sun Microsystems, Inc.
 *
 * This set of routines implements the rpc message definition,
 * its serializer and some common rpc utility routines.
 * The routines are meant for various implementations of rpc -
 * they are NOT for the rpc client or rpc service implementations!
 * Because authentication stuff is easy and is part of rpc, the opaque
 * routines are also in this program.
 */

#include <rpc/rpc.h>

/* * * * * * * * * * * * * * XDR Authentication * * * * * * * * * * * */

/*
 * XDR an opaque authentication struct
 * (see auth.h)
 */
bool_t xdr_opaque_auth(XDR *xdrs, struct opaque_auth *ap)
{

    if (xdr_enum(xdrs, &(ap->oa_flavor)))
        return (xdr_bytes(xdrs, &ap->oa_base,
                          &ap->oa_length, MAX_AUTH_BYTES));
    return (FALSE);
}

/*
 * XDR a DES block
 */
bool_t xdr_des_block(XDR *xdrs, des_block *blkp)
{
    return (xdr_opaque(xdrs, (char*) blkp, sizeof(des_block)));
}

/* * * * * * * * * * * * * * XDR RPC MESSAGE * * * * * * * * * * * * * * * */

/*
 * XDR the MSG_ACCEPTED part of a reply message union
 */
static bool_t xdr_accepted_reply(XDR *xdrs, struct accepted_reply *ar)
{

    /* personalized union, rather than calling xdr_union */
    if (!xdr_opaque_auth(xdrs, &(ar->ar_verf)))
        return (FALSE);
    if (!xdr_enum(xdrs, (enum_t *) & (ar->ar_stat)))
        return (FALSE);
    switch (ar->ar_stat) {

    case SUCCESS:
        return ((*(ar->ar_results.proc)) (xdrs, ar->ar_results.where));

    case PROG_MISMATCH:
        if (!xdr_u_long(xdrs, &(ar->ar_vers.low)))
            return (FALSE);
        return (xdr_u_long(xdrs, &(ar->ar_vers.high)));
    }
    return (TRUE);              /* TRUE => open ended set of problems */
}

/*
 * XDR the MSG_DENIED part of a reply message union
 */
static bool_t xdr_rejected_reply(XDR *xdrs, struct rejected_reply *rr)
{

    /* personalized union, rather than calling xdr_union */
    if (!xdr_enum(xdrs, (enum_t *) & (rr->rj_stat)))
        return (FALSE);
    switch (rr->rj_stat) {

    case RPC_MISMATCH:
        if (!xdr_u_long(xdrs, &(rr->rj_vers.low)))
            return (FALSE);
        return (xdr_u_long(xdrs, &(rr->rj_vers.high)));

    case AUTH_ERROR:
        return (xdr_enum(xdrs, (enum_t *) & (rr->rj_why)));
    }
    return (FALSE);
}

static struct xdr_discrim reply_dscrm[3] = {
    {(int) MSG_ACCEPTED, (xdrproc_t)xdr_accepted_reply},
    {(int) MSG_DENIED, (xdrproc_t)xdr_rejected_reply},
    {__dontcare__, NULL_xdrproc_t}
};

/*
 * XDR a reply message
 */
bool_t xdr_replymsg(XDR *xdrs, struct rpc_msg *rmsg)
{
    if (xdr_u_long(xdrs, &(rmsg->rm_xid)) &&
        xdr_enum(xdrs, (enum_t *) & (rmsg->rm_direction)) &&
        (rmsg->rm_direction == REPLY))
        return (xdr_union(xdrs, (enum_t *) & (rmsg->rm_reply.rp_stat),
                          (char*) & (rmsg->rm_reply.ru), reply_dscrm,
                          NULL_xdrproc_t));
    return (FALSE);
}


/*
 * Serializes the "static part" of a call message header.
 * The fields include: rm_xid, rm_direction, rpcvers, prog, and vers.
 * The rm_xid is not really static, but the user can easily munge on the fly.
 */
bool_t xdr_callhdr(XDR *xdrs, struct rpc_msg *cmsg)
{

    cmsg->rm_direction = CALL;
    cmsg->rm_call.cb_rpcvers = RPC_MSG_VERSION;
    if (
        (xdrs->x_op == XDR_ENCODE) &&
        xdr_u_long(xdrs, &(cmsg->rm_xid)) &&
        xdr_enum(xdrs, (enum_t *) & (cmsg->rm_direction)) &&
        xdr_u_long(xdrs, &(cmsg->rm_call.cb_rpcvers)) &&
        xdr_u_long(xdrs, &(cmsg->rm_call.cb_prog)))
            return (xdr_u_long(xdrs, &(cmsg->rm_call.cb_vers)));
    return (FALSE);
}

/* ************************** Client utility routine ************* */

static void accepted(enum accept_stat acpt_stat, struct rpc_err *error)
{

    switch (acpt_stat) {

    case PROG_UNAVAIL:
        error->re_status = RPC_PROGUNAVAIL;
        return;

    case PROG_MISMATCH:
        error->re_status = RPC_PROGVERSMISMATCH;
        return;

    case PROC_UNAVAIL:
        error->re_status = RPC_PROCUNAVAIL;
        return;

    case GARBAGE_ARGS:
        error->re_status = RPC_CANTDECODEARGS;
        return;

    case SYSTEM_ERR:
        error->re_status = RPC_SYSTEMERROR;
        return;

    case SUCCESS:
        error->re_status = RPC_SUCCESS;
        return;
    }
    /* something's wrong, but we don't know what ... */
    error->re_status = RPC_FAILED;
    error->re_lb.s1 = (int32_t) MSG_ACCEPTED;
    error->re_lb.s2 = (int32_t) acpt_stat;
}

static void rejected(enum reject_stat rjct_stat, struct rpc_err *error)
{

    switch (rjct_stat) {

    case RPC_VERSMISMATCH:
        error->re_status = RPC_VERSMISMATCH;
        return;

    case AUTH_ERROR:
        error->re_status = RPC_AUTHERROR;
        return;
    }
    /* something's wrong, but we don't know what ... */
    error->re_status = RPC_FAILED;
    error->re_lb.s1 = (int32_t) MSG_DENIED;
    error->re_lb.s2 = (int32_t) rjct_stat;
}

/*
 * given a reply message, fills in the error
 */
void _seterr_reply(struct rpc_msg *msg, struct rpc_err *error)
{

    /* optimized for normal, SUCCESSful case */
    switch (msg->rm_reply.rp_stat) {

    case MSG_ACCEPTED:
        if (msg->acpted_rply.ar_stat == SUCCESS) {
            error->re_status = RPC_SUCCESS;
            return;
        };
        accepted((enum accept_stat)msg->acpted_rply.ar_stat, error);
        break;

    case MSG_DENIED:
        rejected((enum reject_stat)msg->rjcted_rply.rj_stat, error);
        break;

    default:
        error->re_status = RPC_FAILED;
        error->re_lb.s1 = (int32_t) (msg->rm_reply.rp_stat);
        break;
    }
    switch (error->re_status) {

    case RPC_VERSMISMATCH:
        error->re_vers.low = msg->rjcted_rply.rj_vers.low;
        error->re_vers.high = msg->rjcted_rply.rj_vers.high;
        break;

    case RPC_AUTHERROR:
        error->re_why = msg->rjcted_rply.rj_why;
        break;

    case RPC_PROGVERSMISMATCH:
        error->re_vers.low = msg->acpted_rply.ar_vers.low;
        error->re_vers.high = msg->acpted_rply.ar_vers.high;
        break;
    }
}
