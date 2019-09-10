/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 */
#include "pmap.h"
#include "clnt.h"
#include <rpc/rpc.h>

static struct timeval timeout = { 5, 0 };
static struct timeval tottimeout = { 60, 0 };


bool_t xdr_pmap(XDR *xdrs, struct pmap *regs)
{
	if (xdr_u_long(xdrs, &regs->pm_prog) &&
		xdr_u_long(xdrs, &regs->pm_vers) &&
		xdr_u_long(xdrs, &regs->pm_prot))
			return (xdr_u_long(xdrs, &regs->pm_port));
	return (FALSE);
}

/*
 * Find the mapped port for program,version.
 * Calls the pmap service remotely to do the lookup.
 * Returns 0 if no map exists.
 */
unsigned short pmap_getport(struct sockaddr_in *address, unsigned long program, unsigned long version, unsigned int protocol)
{
	unsigned short port = 0;
	int socket = -1;
	register CLIENT *client = RT_NULL;
	struct pmap parms;

	address->sin_port = htons((unsigned short)PMAPPORT);
	if (protocol == IPPROTO_UDP)
	  client = clntudp_bufcreate(address, PMAPPROG, PMAPVERS, timeout,
								  &socket, RPCSMALLMSGSIZE,
							   RPCSMALLMSGSIZE);

	if (client != (CLIENT *) NULL)
	{
		parms.pm_prog = program;
		parms.pm_vers = version;
		parms.pm_prot = protocol;
		parms.pm_port = 0;		/* not needed or used */
		if (CLNT_CALL(client, PMAPPROC_GETPORT, (xdrproc_t)xdr_pmap, (char*)&parms,
					  (xdrproc_t)xdr_u_short, (char*)&port, tottimeout) != RPC_SUCCESS)
		{
			rt_kprintf("pmap failure\n");
		}
		CLNT_DESTROY(client);
	}

	(void) lwip_close(socket);
	address->sin_port = 0;

	return (port);
}
