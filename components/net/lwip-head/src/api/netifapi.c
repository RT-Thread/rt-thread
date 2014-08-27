/**
 * @file
 * Network Interface Sequential API module
 *
 */

/*
 * Redistribution and use in source and binary forms, with or without modification, 
 * are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 * 3. The name of the author may not be used to endorse or promote products
 *    derived from this software without specific prior written permission. 
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR IMPLIED 
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF 
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT 
 * SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, 
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT 
 * OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS 
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN 
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING 
 * IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY 
 * OF SUCH DAMAGE.
 *
 * This file is part of the lwIP TCP/IP stack.
 * 
 */

#include "lwip/opt.h"

#if LWIP_NETIF_API /* don't build if not configured for use in lwipopts.h */

#include "lwip/netifapi.h"
#include "lwip/tcpip.h"
#include "lwip/memp.h"

#define NETIFAPI_VAR_REF(name)      API_VAR_REF(name)
#define NETIFAPI_VAR_DECLARE(name)  API_VAR_DECLARE(struct netifapi_msg, name)
#define NETIFAPI_VAR_ALLOC(name)    API_VAR_ALLOC(struct netifapi_msg, MEMP_NETIFAPI_MSG, name)
#define NETIFAPI_VAR_FREE(name)     API_VAR_FREE(MEMP_NETIFAPI_MSG, name)

/**
 * Call netif_add() inside the tcpip_thread context.
 */
static void
netifapi_do_netif_add(struct netifapi_msg_msg *msg)
{
  if (!netif_add( msg->netif,
                  API_EXPR_REF(msg->msg.add.ipaddr),
                  API_EXPR_REF(msg->msg.add.netmask),
                  API_EXPR_REF(msg->msg.add.gw),
                  msg->msg.add.state,
                  msg->msg.add.init,
                  msg->msg.add.input)) {
    msg->err = ERR_IF;
  } else {
    msg->err = ERR_OK;
  }
  TCPIP_NETIFAPI_ACK(msg);
}

/**
 * Call netif_set_addr() inside the tcpip_thread context.
 */
static void
netifapi_do_netif_set_addr(struct netifapi_msg_msg *msg)
{
  netif_set_addr( msg->netif,
                  API_EXPR_REF(msg->msg.add.ipaddr),
                  API_EXPR_REF(msg->msg.add.netmask),
                  API_EXPR_REF(msg->msg.add.gw));
  msg->err = ERR_OK;
  TCPIP_NETIFAPI_ACK(msg);
}

/**
 * Call the "errtfunc" (or the "voidfunc" if "errtfunc" is NULL) inside the
 * tcpip_thread context.
 */
static void
netifapi_do_netif_common(struct netifapi_msg_msg *msg)
{
  if (msg->msg.common.errtfunc != NULL) {
    msg->err = msg->msg.common.errtfunc(msg->netif);
  } else {
    msg->err = ERR_OK;
    msg->msg.common.voidfunc(msg->netif);
  }
  TCPIP_NETIFAPI_ACK(msg);
}

/**
 * Call netif_add() in a thread-safe way by running that function inside the
 * tcpip_thread context.
 *
 * @note for params @see netif_add()
 */
err_t
netifapi_netif_add(struct netif *netif,
                   ip_addr_t *ipaddr,
                   ip_addr_t *netmask,
                   ip_addr_t *gw,
                   void *state,
                   netif_init_fn init,
                   netif_input_fn input)
{
  err_t err;
  NETIFAPI_VAR_DECLARE(msg);
  NETIFAPI_VAR_ALLOC(msg);
#if LWIP_MPU_COMPATIBLE
  if (ipaddr == NULL) {
    ipaddr = IP_ADDR_ANY;
  }
  if (netmask == NULL) {
    netmask = IP_ADDR_ANY;
  }
  if (gw == NULL) {
    gw = IP_ADDR_ANY;
  }
#endif /* LWIP_MPU_COMPATIBLE */
  NETIFAPI_VAR_REF(msg).function = netifapi_do_netif_add;
  NETIFAPI_VAR_REF(msg).msg.netif = netif;
  NETIFAPI_VAR_REF(msg).msg.msg.add.ipaddr  = NETIFAPI_VAR_REF(ipaddr);
  NETIFAPI_VAR_REF(msg).msg.msg.add.netmask = NETIFAPI_VAR_REF(netmask);
  NETIFAPI_VAR_REF(msg).msg.msg.add.gw      = NETIFAPI_VAR_REF(gw);
  NETIFAPI_VAR_REF(msg).msg.msg.add.state   = state;
  NETIFAPI_VAR_REF(msg).msg.msg.add.init    = init;
  NETIFAPI_VAR_REF(msg).msg.msg.add.input   = input;
  TCPIP_NETIFAPI(&API_VAR_REF(msg));

  err = NETIFAPI_VAR_REF(msg).msg.err;
  NETIFAPI_VAR_FREE(msg);
  return err;
}

/**
 * Call netif_set_addr() in a thread-safe way by running that function inside the
 * tcpip_thread context.
 *
 * @note for params @see netif_set_addr()
 */
err_t
netifapi_netif_set_addr(struct netif *netif,
                        ip_addr_t *ipaddr,
                        ip_addr_t *netmask,
                        ip_addr_t *gw)
{
  err_t err;
  NETIFAPI_VAR_DECLARE(msg);
  NETIFAPI_VAR_ALLOC(msg);
#if LWIP_MPU_COMPATIBLE
  if (ipaddr == NULL) {
    ipaddr = IP_ADDR_ANY;
  }
  if (netmask == NULL) {
    netmask = IP_ADDR_ANY;
  }
  if (gw == NULL) {
    gw = IP_ADDR_ANY;
  }
#endif /* LWIP_MPU_COMPATIBLE */
  NETIFAPI_VAR_REF(msg).function = netifapi_do_netif_set_addr;
  NETIFAPI_VAR_REF(msg).msg.netif = netif;
  NETIFAPI_VAR_REF(msg).msg.msg.add.ipaddr  = NETIFAPI_VAR_REF(ipaddr);
  NETIFAPI_VAR_REF(msg).msg.msg.add.netmask = NETIFAPI_VAR_REF(netmask);
  NETIFAPI_VAR_REF(msg).msg.msg.add.gw      = NETIFAPI_VAR_REF(gw);
  TCPIP_NETIFAPI(&API_VAR_REF(msg));

  err = NETIFAPI_VAR_REF(msg).msg.err;
  NETIFAPI_VAR_FREE(msg);
  return err;
}

/**
 * call the "errtfunc" (or the "voidfunc" if "errtfunc" is NULL) in a thread-safe
 * way by running that function inside the tcpip_thread context.
 *
 * @note use only for functions where there is only "netif" parameter.
 */
err_t
netifapi_netif_common(struct netif *netif, netifapi_void_fn voidfunc,
                       netifapi_errt_fn errtfunc)
{
  err_t err;
  NETIFAPI_VAR_DECLARE(msg);
  NETIFAPI_VAR_ALLOC(msg);

  NETIFAPI_VAR_REF(msg).function = netifapi_do_netif_common;
  NETIFAPI_VAR_REF(msg).msg.netif = netif;
  NETIFAPI_VAR_REF(msg).msg.msg.common.voidfunc = voidfunc;
  NETIFAPI_VAR_REF(msg).msg.msg.common.errtfunc = errtfunc;
  TCPIP_NETIFAPI(&API_VAR_REF(msg));

  err = NETIFAPI_VAR_REF(msg).msg.err;
  NETIFAPI_VAR_FREE(msg);
  return err;
}

#endif /* LWIP_NETIF_API */
