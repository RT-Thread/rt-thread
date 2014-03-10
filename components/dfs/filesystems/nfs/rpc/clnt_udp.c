/* @(#)clnt_udp.c	2.2 88/08/01 4.0 RPCSRC */
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
static char sccsid[] = "@(#)clnt_udp.c 1.39 87/08/11 Copyr 1984 Sun Micro";
#endif

/*
 * clnt_udp.c, Implements a UDP/IP based, client side RPC.
 *
 * Copyright (C) 1984, Sun Microsystems, Inc.
 */

#include <stdio.h>
#include <rpc/rpc.h>
#include <rtthread.h>

/*
 * UDP bases client side rpc operations
 */
static enum clnt_stat clntudp_call(register CLIENT *cl,         /* client handle */
	unsigned long proc,          /* procedure number */
	xdrproc_t xargs,             /* xdr routine for args */
	char* argsp,                 /* pointer to args */
	xdrproc_t xresults,          /* xdr routine for results */
	char* resultsp,              /* pointer to results */
	struct timeval utimeout);

static void clntudp_abort(void);
static void clntudp_geterr(CLIENT *, struct rpc_err *);
static bool_t clntudp_freeres(CLIENT *, xdrproc_t, char*);
static bool_t clntudp_control(CLIENT *, int, char *);
static void clntudp_destroy(CLIENT *);

static struct clnt_ops udp_ops =
{
	clntudp_call,
	clntudp_abort,
	clntudp_geterr,
	clntudp_freeres,
	clntudp_destroy,
	clntudp_control
};

/*
 * Private data kept per client handle
 */
struct cu_data
{
	int cu_sock;
	bool_t cu_closeit;
	struct sockaddr_in cu_raddr;
	int cu_rlen;
	struct timeval cu_wait;
	struct timeval cu_total;
	struct rpc_err cu_error;
	XDR cu_outxdrs;
	unsigned int cu_xdrpos;
	unsigned int cu_sendsz;
	char *cu_outbuf;
	unsigned int cu_recvsz;
	char cu_inbuf[1];
};

/*
 * Create a UDP based client handle.
 * If *sockp<0, *sockp is set to a newly created UPD socket.
 * If raddr->sin_port is 0 a binder on the remote machine
 * is consulted for the correct port number.
 * NB: It is the clients responsibility to close *sockp.
 * NB: The rpch->cl_auth is initialized to null authentication.
 *     Caller may wish to set this something more useful.
 *
 * wait is the amount of time used between retransmitting a call if
 * no response has been heard;  retransmition occurs until the actual
 * rpc call times out.
 *
 * sendsz and recvsz are the maximum allowable packet sizes that can be
 * sent and received.
 */
CLIENT *clntudp_bufcreate(struct sockaddr_in *raddr, 
	unsigned long program, 
	unsigned long version,
	struct timeval wait, 
	int *sockp, 
	unsigned int sendsz,
	unsigned int recvsz)
{
	CLIENT *cl;
	register struct cu_data *cu = NULL;
	struct rpc_msg call_msg;
	static int xid_count = 0;

	cl = (CLIENT *) rt_malloc (sizeof(CLIENT));
	if (cl == NULL)
	{
		rt_kprintf("clntudp_create: out of memory\n");
		goto fooy;
	}
	sendsz = ((sendsz + 3) / 4) * 4;
	recvsz = ((recvsz + 3) / 4) * 4;
	cu = (struct cu_data *) rt_malloc (sizeof(*cu) + sendsz + recvsz);
	if (cu == NULL)
	{
		rt_kprintf("clntudp_create: out of memory\n");
		goto fooy;
	}
	cu->cu_outbuf = &cu->cu_inbuf[recvsz];

	if (raddr->sin_port == 0) {
		unsigned short port;
		extern unsigned short pmap_getport(struct sockaddr_in *address, 
			unsigned long program, 
			unsigned long version, 
			unsigned int protocol);

		if ((port =
			 pmap_getport(raddr, program, version, IPPROTO_UDP)) == 0) {
			goto fooy;
		}
		raddr->sin_port = htons(port);
	}

	cl->cl_ops = &udp_ops;
	cl->cl_private = (char*) cu;
	cu->cu_raddr = *raddr;
	cu->cu_rlen = sizeof(cu->cu_raddr);
	cu->cu_wait = wait;
	cu->cu_total.tv_sec = -1;
	cu->cu_total.tv_usec = -1;
	cu->cu_sendsz = sendsz;
	cu->cu_recvsz = recvsz;
	call_msg.rm_xid = ((unsigned long)rt_thread_self()) ^ ((unsigned long)rt_tick_get()) ^ (xid_count++);
	call_msg.rm_direction = CALL;
	call_msg.rm_call.cb_rpcvers = RPC_MSG_VERSION;
	call_msg.rm_call.cb_prog = program;
	call_msg.rm_call.cb_vers = version;
	xdrmem_create(&(cu->cu_outxdrs), cu->cu_outbuf, sendsz, XDR_ENCODE);
	if (!xdr_callhdr(&(cu->cu_outxdrs), &call_msg))
	{
		goto fooy;
	}
	cu->cu_xdrpos = XDR_GETPOS(&(cu->cu_outxdrs));
	if (*sockp < 0)
	{
		*sockp = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
		if (*sockp < 0)
		{
			rt_kprintf("create socket error\n");
			goto fooy;
		}
		cu->cu_closeit = TRUE;
	}
	else
	{
		cu->cu_closeit = FALSE;
	}
	cu->cu_sock = *sockp;
	cl->cl_auth = authnone_create();
	return (cl);

fooy:
	if (cu) rt_free(cu);
	if (cl) rt_free(cl);

	return ((CLIENT *) NULL);
}

CLIENT *clntudp_create(struct sockaddr_in *raddr, 
	unsigned long program, 
	unsigned long version, 
	struct timeval wait, 
	int *sockp)
{
	return (clntudp_bufcreate(raddr, program, version, wait, sockp,
							  UDPMSGSIZE, UDPMSGSIZE));
}

static enum clnt_stat clntudp_call(CLIENT *cl, unsigned long proc, 
	xdrproc_t xargs, char* argsp, 
	xdrproc_t xresults, char* resultsp, 
	struct timeval utimeout)
{
	register struct cu_data *cu = (struct cu_data *) cl->cl_private;
	register XDR *xdrs;
	register int outlen;
	register int inlen;
	socklen_t fromlen;

	struct sockaddr_in from;
	struct rpc_msg reply_msg;
	XDR reply_xdrs;
	bool_t ok;
	int nrefreshes = 2;			/* number of times to refresh cred */

call_again:
	xdrs = &(cu->cu_outxdrs);
	xdrs->x_op = XDR_ENCODE;
	XDR_SETPOS(xdrs, cu->cu_xdrpos);

	/*
	 * the transaction is the first thing in the out buffer
	 */
	(*(unsigned long *) (cu->cu_outbuf))++;

	if ((!XDR_PUTLONG(xdrs, (long *) &proc)) ||
			(!AUTH_MARSHALL(cl->cl_auth, xdrs)) || (!(*xargs) (xdrs, argsp)))
    {
        cu->cu_error.re_status = RPC_CANTENCODEARGS;
		return RPC_CANTENCODEARGS;
    }
	outlen = (int) XDR_GETPOS(xdrs);

send_again:
	if (sendto(cu->cu_sock, cu->cu_outbuf, outlen, 0,
			   (struct sockaddr *) &(cu->cu_raddr), cu->cu_rlen)
			!= outlen)
	{
		cu->cu_error.re_errno = errno;
        cu->cu_error.re_status = RPC_CANTSEND;
        
		return RPC_CANTSEND;
	}

	/*
	 * sub-optimal code appears here because we have
	 * some clock time to spare while the packets are in flight.
	 * (We assume that this is actually only executed once.)
	 */
	reply_msg.acpted_rply.ar_verf = _null_auth;
	reply_msg.acpted_rply.ar_results.where = resultsp;
	reply_msg.acpted_rply.ar_results.proc = xresults;

	/* do recv */
	do
	{
		fromlen = sizeof(struct sockaddr);

		inlen = recvfrom(cu->cu_sock, cu->cu_inbuf,
						 (int) cu->cu_recvsz, 0,
						 (struct sockaddr *) &from, &fromlen);
	}while (inlen < 0 && errno == EINTR);

	if (inlen < 4)
	{
		rt_kprintf("recv error, len %d\n", inlen);
		cu->cu_error.re_errno = errno;
		cu->cu_error.re_status = RPC_CANTRECV;
		
		return RPC_CANTRECV;
	}

	/* see if reply transaction id matches sent id */
	if (*((uint32_t *) (cu->cu_inbuf)) != *((uint32_t *) (cu->cu_outbuf)))
		goto send_again;

	/* we now assume we have the proper reply */

	/*
	 * now decode and validate the response
	 */
	xdrmem_create(&reply_xdrs, cu->cu_inbuf, (unsigned int) inlen, XDR_DECODE);
	ok = xdr_replymsg(&reply_xdrs, &reply_msg);
	/* XDR_DESTROY(&reply_xdrs);  save a few cycles on noop destroy */
	if (ok)
	{
		_seterr_reply(&reply_msg, &(cu->cu_error));
		if (cu->cu_error.re_status == RPC_SUCCESS)
		{
			if (!AUTH_VALIDATE(cl->cl_auth,
							   &reply_msg.acpted_rply.ar_verf))
			{
				cu->cu_error.re_status = RPC_AUTHERROR;
				cu->cu_error.re_why = AUTH_INVALIDRESP;
			}
			if (reply_msg.acpted_rply.ar_verf.oa_base != NULL)
			{
				extern bool_t xdr_opaque_auth(XDR *xdrs, struct opaque_auth *ap);
				
				xdrs->x_op = XDR_FREE;
				(void) xdr_opaque_auth(xdrs, &(reply_msg.acpted_rply.ar_verf));
			}
		} /* end successful completion */
		else
		{
			/* maybe our credentials need to be refreshed ... */
			if (nrefreshes > 0 && AUTH_REFRESH(cl->cl_auth))
			{
				nrefreshes--;
				goto call_again;
			}
		} /* end of unsuccessful completion */
	} /* end of valid reply message */
	else
	{
		cu->cu_error.re_status = RPC_CANTDECODERES;
	}

	return (enum clnt_stat)(cu->cu_error.re_status);
}

static void clntudp_geterr(CLIENT *cl, struct rpc_err *errp)
{
	register struct cu_data *cu = (struct cu_data *) cl->cl_private;

	*errp = cu->cu_error;
}

static bool_t clntudp_freeres(CLIENT *cl, xdrproc_t xdr_res, char* res_ptr)
{
	register struct cu_data *cu = (struct cu_data *) cl->cl_private;
	register XDR *xdrs = &(cu->cu_outxdrs);

	xdrs->x_op = XDR_FREE;
	return ((*xdr_res) (xdrs, res_ptr));
}

static void clntudp_abort()
{
}

static bool_t clntudp_control(CLIENT *cl, int request, char *info)
{
	register struct cu_data *cu = (struct cu_data *) cl->cl_private;

	switch (request)
	{
	case CLSET_TIMEOUT:
		{
		int mtimeout;

		cu->cu_total = *(struct timeval *) info;
		mtimeout = ((cu->cu_total.tv_sec * 1000) + ((cu->cu_total.tv_usec + 500)/1000));

		/* set socket option, note: lwip only support msecond timeout */
		setsockopt(cu->cu_sock, SOL_SOCKET, SO_RCVTIMEO, 
			&mtimeout, sizeof(mtimeout));
		}
		break;
	case CLGET_TIMEOUT:
		*(struct timeval *) info = cu->cu_total;
		break;
	case CLSET_RETRY_TIMEOUT:
		cu->cu_wait = *(struct timeval *) info;
		break;
	case CLGET_RETRY_TIMEOUT:
		*(struct timeval *) info = cu->cu_wait;
		break;
	case CLGET_SERVER_ADDR:
		*(struct sockaddr_in *) info = cu->cu_raddr;
		break;
	default:
		return (FALSE);
	}
	return (TRUE);
}

static void clntudp_destroy(CLIENT *cl)
{
	register struct cu_data *cu = (struct cu_data *) cl->cl_private;

	if (cu->cu_closeit)
	{
		lwip_close(cu->cu_sock);
	}

	XDR_DESTROY(&(cu->cu_outxdrs));
	rt_free(cu);
	rt_free(cl);
}
