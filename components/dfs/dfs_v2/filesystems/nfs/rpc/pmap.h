/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 */
#ifndef __RPC_PMAP_PROT_H__
#define __RPC_PMAP_PROT_H__

#include <rpc/xdr.h>

/* The following procedures are supported by the protocol:
 *
 * PMAPPROC_NULL() returns ()
 *  takes nothing, returns nothing
 *
 * PMAPPROC_SET(struct pmap) returns (bool_t)
 *  TRUE is success, FALSE is failure.  Registers the tuple
 *  [prog, vers, prot, port].
 *
 * PMAPPROC_UNSET(struct pmap) returns (bool_t)
 *  TRUE is success, FALSE is failure.  Un-registers pair
 *  [prog, vers].  prot and port are ignored.
 *
 * PMAPPROC_GETPORT(struct pmap) returns (uint32_t).
 *  0 is failure.  Otherwise returns the port number where the pair
 *  [prog, vers] is registered.  It may lie!
 *
 * PMAPPROC_DUMP() RETURNS (struct pmaplist *)
 *
 * PMAPPROC_CALLIT(unsigned, unsigned, unsigned, string<>)
 *  RETURNS (port, string<>);
 * usage: encapsulatedresults = PMAPPROC_CALLIT(prog, vers, proc, encapsulatedargs);
 *  Calls the procedure on the local machine.  If it is not registered,
 *  this procedure is quite; ie it does not return error information!!!
 *  This procedure only is supported on rpc/udp and calls via
 *  rpc/udp.  This routine only passes null authentication parameters.
 *  This file has no interface to xdr routines for PMAPPROC_CALLIT.
 *
 * The service supports remote procedure calls on udp/ip or tcp/ip socket 111.
 */

#define PMAPPORT        ((uint16_t)111)
#define PMAPPROG        ((uint32_t)100000)
#define PMAPVERS        ((uint32_t)2)
#define PMAPVERS_PROTO      ((uint32_t)2)
#define PMAPVERS_ORIG       ((uint32_t)1)
#define PMAPPROC_NULL       ((uint32_t)0)
#define PMAPPROC_SET        ((uint32_t)1)
#define PMAPPROC_UNSET      ((uint32_t)2)
#define PMAPPROC_GETPORT    ((uint32_t)3)
#define PMAPPROC_DUMP       ((uint32_t)4)
#define PMAPPROC_CALLIT     ((uint32_t)5)

struct pmap {
    uint32_t pm_prog;
    uint32_t pm_vers;
    uint32_t pm_prot;
    uint32_t pm_port;
};

extern bool_t xdr_pmap (XDR *__xdrs, struct pmap *__regs);

#endif
