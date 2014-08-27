/**
 * @file
 * Sequential API External module
 *
 */
 
/*
 * Copyright (c) 2001-2004 Swedish Institute of Computer Science.
 * All rights reserved. 
 * 
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
 * Author: Adam Dunkels <adam@sics.se>
 *
 */

/* This is the part of the API that is linked with
   the application */

#include "lwip/opt.h"

#if LWIP_NETCONN /* don't build if not configured for use in lwipopts.h */

#include "lwip/api.h"
#include "lwip/tcpip.h"
#include "lwip/memp.h"

#include "lwip/ip.h"
#include "lwip/raw.h"
#include "lwip/udp.h"
#include "lwip/tcp.h"

#include <string.h>

#define API_MSG_VAR_REF(name)             API_VAR_REF(name)
#define API_MSG_VAR_DECLARE(name)         API_VAR_DECLARE(struct api_msg, name)
#define API_MSG_VAR_ALLOC(name)           API_VAR_ALLOC(struct api_msg, MEMP_API_MSG, name)
#define API_MSG_VAR_ALLOC_DONTFAIL(name)  API_VAR_ALLOC_DONTFAIL(struct api_msg, MEMP_API_MSG, name)
#define API_MSG_VAR_FREE(name)            API_VAR_FREE(MEMP_API_MSG, name)

/**
 * Create a new netconn (of a specific type) that has a callback function.
 * The corresponding pcb is also created.
 *
 * @param t the type of 'connection' to create (@see enum netconn_type)
 * @param proto the IP protocol for RAW IP pcbs
 * @param callback a function to call on status changes (RX available, TX'ed)
 * @return a newly allocated struct netconn or
 *         NULL on memory error
 */
struct netconn*
netconn_new_with_proto_and_callback(enum netconn_type t, u8_t proto, netconn_callback callback)
{
  struct netconn *conn;
  API_MSG_VAR_DECLARE(msg);

  conn = netconn_alloc(t, callback);
  if (conn != NULL) {
    err_t err;
    API_MSG_VAR_ALLOC_DONTFAIL(msg);
    API_MSG_VAR_REF(msg).msg.msg.n.proto = proto;
    API_MSG_VAR_REF(msg).msg.conn = conn;
    TCPIP_APIMSG(&API_MSG_VAR_REF(msg), lwip_netconn_do_newconn, err);
    API_MSG_VAR_FREE(msg);
    if (err != ERR_OK) {
      LWIP_ASSERT("freeing conn without freeing pcb", conn->pcb.tcp == NULL);
      LWIP_ASSERT("conn has no op_completed", sys_sem_valid(&conn->op_completed));
      LWIP_ASSERT("conn has no recvmbox", sys_mbox_valid(&conn->recvmbox));
#if LWIP_TCP
      LWIP_ASSERT("conn->acceptmbox shouldn't exist", !sys_mbox_valid(&conn->acceptmbox));
#endif /* LWIP_TCP */
      sys_sem_free(&conn->op_completed);
      sys_mbox_free(&conn->recvmbox);
      memp_free(MEMP_NETCONN, conn);
      return NULL;
    }
  }
  return conn;
}

/**
 * Close a netconn 'connection' and free its resources.
 * UDP and RAW connection are completely closed, TCP pcbs might still be in a waitstate
 * after this returns.
 *
 * @param conn the netconn to delete
 * @return ERR_OK if the connection was deleted
 */
err_t
netconn_delete(struct netconn *conn)
{
  API_MSG_VAR_DECLARE(msg);

  /* No ASSERT here because possible to get a (conn == NULL) if we got an accept error */
  if (conn == NULL) {
    return ERR_OK;
  }

  API_MSG_VAR_ALLOC(msg);
  API_MSG_VAR_REF(msg).function = lwip_netconn_do_delconn;
  API_MSG_VAR_REF(msg).msg.conn = conn;
  tcpip_apimsg(&API_MSG_VAR_REF(msg));
  API_MSG_VAR_FREE(msg);

  netconn_free(conn);

  /* don't care for return value of lwip_netconn_do_delconn since it only calls void functions */

  return ERR_OK;
}

/**
 * Get the local or remote IP address and port of a netconn.
 * For RAW netconns, this returns the protocol instead of a port!
 *
 * @param conn the netconn to query
 * @param addr a pointer to which to save the IP address
 * @param port a pointer to which to save the port (or protocol for RAW)
 * @param local 1 to get the local IP address, 0 to get the remote one
 * @return ERR_CONN for invalid connections
 *         ERR_OK if the information was retrieved
 */
err_t
netconn_getaddr(struct netconn *conn, ip_addr_t *addr, u16_t *port, u8_t local)
{
  API_MSG_VAR_DECLARE(msg);
  err_t err;

  LWIP_ERROR("netconn_getaddr: invalid conn", (conn != NULL), return ERR_ARG;);
  LWIP_ERROR("netconn_getaddr: invalid addr", (addr != NULL), return ERR_ARG;);
  LWIP_ERROR("netconn_getaddr: invalid port", (port != NULL), return ERR_ARG;);

  API_MSG_VAR_ALLOC(msg);
  API_MSG_VAR_REF(msg).msg.conn = conn;
  API_MSG_VAR_REF(msg).msg.msg.ad.local = local;
#if LWIP_MPU_COMPATIBLE
  TCPIP_APIMSG(msg, lwip_netconn_do_getaddr, err);
  *addr = *ipX_2_ip(&(msg->msg.msg.ad.ipaddr));
  *port = msg->msg.msg.ad.port;
#else /* LWIP_MPU_COMPATIBLE */
  msg.msg.msg.ad.ipaddr = ip_2_ipX(addr);
  msg.msg.msg.ad.port = port;
  TCPIP_APIMSG(&msg, lwip_netconn_do_getaddr, err);
#endif /* LWIP_MPU_COMPATIBLE */
  API_MSG_VAR_FREE(msg);

  NETCONN_SET_SAFE_ERR(conn, err);
  return err;
}

/**
 * Bind a netconn to a specific local IP address and port.
 * Binding one netconn twice might not always be checked correctly!
 *
 * @param conn the netconn to bind
 * @param addr the local IP address to bind the netconn to (use IP_ADDR_ANY
 *             to bind to all addresses)
 * @param port the local port to bind the netconn to (not used for RAW)
 * @return ERR_OK if bound, any other err_t on failure
 */
err_t
netconn_bind(struct netconn *conn, ip_addr_t *addr, u16_t port)
{
  API_MSG_VAR_DECLARE(msg);
  err_t err;

  LWIP_ERROR("netconn_bind: invalid conn", (conn != NULL), return ERR_ARG;);

  API_MSG_VAR_ALLOC(msg);
#if LWIP_MPU_COMPATIBLE
  if (addr == NULL) {
    addr = IP_ADDR_ANY;
  }
#endif /* LWIP_MPU_COMPATIBLE */
  API_MSG_VAR_REF(msg).msg.conn = conn;
  API_MSG_VAR_REF(msg).msg.msg.bc.ipaddr = API_MSG_VAR_REF(addr);
  API_MSG_VAR_REF(msg).msg.msg.bc.port = port;
  TCPIP_APIMSG(&API_MSG_VAR_REF(msg), lwip_netconn_do_bind, err);
  API_MSG_VAR_FREE(msg);

  NETCONN_SET_SAFE_ERR(conn, err);
  return err;
}

/**
 * Connect a netconn to a specific remote IP address and port.
 *
 * @param conn the netconn to connect
 * @param addr the remote IP address to connect to
 * @param port the remote port to connect to (no used for RAW)
 * @return ERR_OK if connected, return value of tcp_/udp_/raw_connect otherwise
 */
err_t
netconn_connect(struct netconn *conn, ip_addr_t *addr, u16_t port)
{
  API_MSG_VAR_DECLARE(msg);
  err_t err;

  LWIP_ERROR("netconn_connect: invalid conn", (conn != NULL), return ERR_ARG;);

  API_MSG_VAR_ALLOC(msg);
#if LWIP_MPU_COMPATIBLE
  if (addr == NULL) {
    addr = IP_ADDR_ANY;
  }
#endif /* LWIP_MPU_COMPATIBLE */
  API_MSG_VAR_REF(msg).msg.conn = conn;
  API_MSG_VAR_REF(msg).msg.msg.bc.ipaddr = API_MSG_VAR_REF(addr);
  API_MSG_VAR_REF(msg).msg.msg.bc.port = port;
#if LWIP_TCP
#if (LWIP_UDP || LWIP_RAW)
  if (NETCONNTYPE_GROUP(conn->type) == NETCONN_TCP)
#endif /* (LWIP_UDP || LWIP_RAW) */
  {
    /* The TCP version waits for the connect to succeed,
       so always needs to use message passing. */
    API_MSG_VAR_REF(msg).function = lwip_netconn_do_connect;
    err = tcpip_apimsg(&API_MSG_VAR_REF(msg));
  }
#endif /* LWIP_TCP */
#if (LWIP_UDP || LWIP_RAW) && LWIP_TCP
  else
#endif /* (LWIP_UDP || LWIP_RAW) && LWIP_TCP */
#if (LWIP_UDP || LWIP_RAW)
  {
     /* UDP and RAW only set flags, so we can use core-locking. */
     TCPIP_APIMSG(&API_MSG_VAR_REF(msg), lwip_netconn_do_connect, err);
  }
#endif /* (LWIP_UDP || LWIP_RAW) */
  API_MSG_VAR_FREE(msg);

  NETCONN_SET_SAFE_ERR(conn, err);
  return err;
}

/**
 * Disconnect a netconn from its current peer (only valid for UDP netconns).
 *
 * @param conn the netconn to disconnect
 * @return TODO: return value is not set here...
 */
err_t
netconn_disconnect(struct netconn *conn)
{
  API_MSG_VAR_DECLARE(msg);
  err_t err;

  LWIP_ERROR("netconn_disconnect: invalid conn", (conn != NULL), return ERR_ARG;);

  API_MSG_VAR_ALLOC(msg);
  API_MSG_VAR_REF(msg).msg.conn = conn;
  TCPIP_APIMSG(&API_MSG_VAR_REF(msg), lwip_netconn_do_disconnect, err);
  API_MSG_VAR_FREE(msg);

  NETCONN_SET_SAFE_ERR(conn, err);
  return err;
}

/**
 * Set a TCP netconn into listen mode
 *
 * @param conn the tcp netconn to set to listen mode
 * @param backlog the listen backlog, only used if TCP_LISTEN_BACKLOG==1
 * @return ERR_OK if the netconn was set to listen (UDP and RAW netconns
 *         don't return any error (yet?))
 */
err_t
netconn_listen_with_backlog(struct netconn *conn, u8_t backlog)
{
#if LWIP_TCP
  API_MSG_VAR_DECLARE(msg);
  err_t err;

  /* This does no harm. If TCP_LISTEN_BACKLOG is off, backlog is unused. */
  LWIP_UNUSED_ARG(backlog);

  LWIP_ERROR("netconn_listen: invalid conn", (conn != NULL), return ERR_ARG;);

  API_MSG_VAR_ALLOC(msg);
  API_MSG_VAR_REF(msg).msg.conn = conn;
#if TCP_LISTEN_BACKLOG
  API_MSG_VAR_REF(msg).msg.msg.lb.backlog = backlog;
#endif /* TCP_LISTEN_BACKLOG */
  TCPIP_APIMSG(&API_MSG_VAR_REF(msg), lwip_netconn_do_listen, err);
  API_MSG_VAR_FREE(msg);

  NETCONN_SET_SAFE_ERR(conn, err);
  return err;
#else /* LWIP_TCP */
  LWIP_UNUSED_ARG(conn);
  LWIP_UNUSED_ARG(backlog);
  return ERR_ARG;
#endif /* LWIP_TCP */
}

/**
 * Accept a new connection on a TCP listening netconn.
 *
 * @param conn the TCP listen netconn
 * @param new_conn pointer where the new connection is stored
 * @return ERR_OK if a new connection has been received or an error
 *                code otherwise
 */
err_t
netconn_accept(struct netconn *conn, struct netconn **new_conn)
{
#if LWIP_TCP
  struct netconn *newconn;
  err_t err;
#if TCP_LISTEN_BACKLOG
  API_MSG_VAR_DECLARE(msg);
#endif /* TCP_LISTEN_BACKLOG */

  LWIP_ERROR("netconn_accept: invalid pointer",    (new_conn != NULL),                  return ERR_ARG;);
  *new_conn = NULL;
  LWIP_ERROR("netconn_accept: invalid conn",       (conn != NULL),                      return ERR_ARG;);
  LWIP_ERROR("netconn_accept: invalid acceptmbox", sys_mbox_valid(&conn->acceptmbox),   return ERR_ARG;);

  err = conn->last_err;
  if (ERR_IS_FATAL(err)) {
    /* don't recv on fatal errors: this might block the application task
       waiting on acceptmbox forever! */
    return err;
  }

#if LWIP_SO_RCVTIMEO
  if (sys_arch_mbox_fetch(&conn->acceptmbox, (void **)&newconn, conn->recv_timeout) == SYS_ARCH_TIMEOUT) {
    NETCONN_SET_SAFE_ERR(conn, ERR_TIMEOUT);
    return ERR_TIMEOUT;
  }
#else
  sys_arch_mbox_fetch(&conn->acceptmbox, (void **)&newconn, 0);
#endif /* LWIP_SO_RCVTIMEO*/
  /* Register event with callback */
  API_EVENT(conn, NETCONN_EVT_RCVMINUS, 0);

  if (newconn == NULL) {
    /* connection has been aborted */
    NETCONN_SET_SAFE_ERR(conn, ERR_ABRT);
    return ERR_ABRT;
  }
#if TCP_LISTEN_BACKLOG
  /* Let the stack know that we have accepted the connection. */
  API_MSG_VAR_ALLOC_DONTFAIL(msg);
  API_MSG_VAR_REF(msg).msg.conn = conn;
  /* don't care for the return value of lwip_netconn_do_recv */
  TCPIP_APIMSG_NOERR(&API_MSG_VAR_REF(msg), lwip_netconn_do_recv);
  API_MSG_VAR_FREE(msg);
#endif /* TCP_LISTEN_BACKLOG */

  *new_conn = newconn;
  /* don't set conn->last_err: it's only ERR_OK, anyway */
  return ERR_OK;
#else /* LWIP_TCP */
  LWIP_UNUSED_ARG(conn);
  LWIP_UNUSED_ARG(new_conn);
  return ERR_ARG;
#endif /* LWIP_TCP */
}

/**
 * Receive data: actual implementation that doesn't care whether pbuf or netbuf
 * is received
 *
 * @param conn the netconn from which to receive data
 * @param new_buf pointer where a new pbuf/netbuf is stored when received data
 * @return ERR_OK if data has been received, an error code otherwise (timeout,
 *                memory error or another error)
 */
static err_t
netconn_recv_data(struct netconn *conn, void **new_buf)
{
  void *buf = NULL;
  u16_t len;
  err_t err;
#if LWIP_TCP
  API_MSG_VAR_DECLARE(msg);
#endif /* LWIP_TCP */

  LWIP_ERROR("netconn_recv: invalid pointer", (new_buf != NULL), return ERR_ARG;);
  *new_buf = NULL;
  LWIP_ERROR("netconn_recv: invalid conn",    (conn != NULL),    return ERR_ARG;);
  LWIP_ERROR("netconn_accept: invalid recvmbox", sys_mbox_valid(&conn->recvmbox), return ERR_CONN;);

  err = conn->last_err;
  if (ERR_IS_FATAL(err)) {
    /* don't recv on fatal errors: this might block the application task
       waiting on recvmbox forever! */
    /* @todo: this does not allow us to fetch data that has been put into recvmbox
       before the fatal error occurred - is that a problem? */
    return err;
  }

#if LWIP_SO_RCVTIMEO
  if (sys_arch_mbox_fetch(&conn->recvmbox, &buf, conn->recv_timeout) == SYS_ARCH_TIMEOUT) {
    NETCONN_SET_SAFE_ERR(conn, ERR_TIMEOUT);
    return ERR_TIMEOUT;
  }
#else
  sys_arch_mbox_fetch(&conn->recvmbox, &buf, 0);
#endif /* LWIP_SO_RCVTIMEO*/

#if LWIP_TCP
#if (LWIP_UDP || LWIP_RAW)
  if (NETCONNTYPE_GROUP(conn->type) == NETCONN_TCP)
#endif /* (LWIP_UDP || LWIP_RAW) */
  {
    if (!netconn_get_noautorecved(conn) || (buf == NULL)) {
      /* Let the stack know that we have taken the data. */
      /* TODO: Speedup: Don't block and wait for the answer here
         (to prevent multiple thread-switches). */
      API_MSG_VAR_ALLOC_DONTFAIL(msg);
      API_MSG_VAR_REF(msg).msg.conn = conn;
      if (buf != NULL) {
        API_MSG_VAR_REF(msg).msg.msg.r.len = ((struct pbuf *)buf)->tot_len;
      } else {
        API_MSG_VAR_REF(msg).msg.msg.r.len = 1;
      }
      /* don't care for the return value of lwip_netconn_do_recv */
      TCPIP_APIMSG_NOERR(&API_MSG_VAR_REF(msg), lwip_netconn_do_recv);
      API_MSG_VAR_FREE(msg);
    }

    /* If we are closed, we indicate that we no longer wish to use the socket */
    if (buf == NULL) {
      API_EVENT(conn, NETCONN_EVT_RCVMINUS, 0);
      /* Avoid to lose any previous error code */
      NETCONN_SET_SAFE_ERR(conn, ERR_CLSD);
      return ERR_CLSD;
    }
    len = ((struct pbuf *)buf)->tot_len;
  }
#endif /* LWIP_TCP */
#if LWIP_TCP && (LWIP_UDP || LWIP_RAW)
  else
#endif /* LWIP_TCP && (LWIP_UDP || LWIP_RAW) */
#if (LWIP_UDP || LWIP_RAW)
  {
    LWIP_ASSERT("buf != NULL", buf != NULL);
    len = netbuf_len((struct netbuf *)buf);
  }
#endif /* (LWIP_UDP || LWIP_RAW) */

#if LWIP_SO_RCVBUF
  SYS_ARCH_DEC(conn->recv_avail, len);
#endif /* LWIP_SO_RCVBUF */
  /* Register event with callback */
  API_EVENT(conn, NETCONN_EVT_RCVMINUS, len);

  LWIP_DEBUGF(API_LIB_DEBUG, ("netconn_recv_data: received %p, len=%"U16_F"\n", buf, len));

  *new_buf = buf;
  /* don't set conn->last_err: it's only ERR_OK, anyway */
  return ERR_OK;
}

/**
 * Receive data (in form of a pbuf) from a TCP netconn
 *
 * @param conn the netconn from which to receive data
 * @param new_buf pointer where a new pbuf is stored when received data
 * @return ERR_OK if data has been received, an error code otherwise (timeout,
 *                memory error or another error)
 *         ERR_ARG if conn is not a TCP netconn
 */
err_t
netconn_recv_tcp_pbuf(struct netconn *conn, struct pbuf **new_buf)
{
  LWIP_ERROR("netconn_recv: invalid conn", (conn != NULL) &&
             NETCONNTYPE_GROUP(netconn_type(conn)) == NETCONN_TCP, return ERR_ARG;);

  return netconn_recv_data(conn, (void **)new_buf);
}

/**
 * Receive data (in form of a netbuf containing a packet buffer) from a netconn
 *
 * @param conn the netconn from which to receive data
 * @param new_buf pointer where a new netbuf is stored when received data
 * @return ERR_OK if data has been received, an error code otherwise (timeout,
 *                memory error or another error)
 */
err_t
netconn_recv(struct netconn *conn, struct netbuf **new_buf)
{
#if LWIP_TCP
  struct netbuf *buf = NULL;
  err_t err;
#endif /* LWIP_TCP */

  LWIP_ERROR("netconn_recv: invalid pointer", (new_buf != NULL), return ERR_ARG;);
  *new_buf = NULL;
  LWIP_ERROR("netconn_recv: invalid conn",    (conn != NULL),    return ERR_ARG;);
  LWIP_ERROR("netconn_accept: invalid recvmbox", sys_mbox_valid(&conn->recvmbox), return ERR_CONN;);

#if LWIP_TCP
#if (LWIP_UDP || LWIP_RAW)
  if (NETCONNTYPE_GROUP(conn->type) == NETCONN_TCP)
#endif /* (LWIP_UDP || LWIP_RAW) */
  {
    struct pbuf *p = NULL;
    /* This is not a listening netconn, since recvmbox is set */

    buf = (struct netbuf *)memp_malloc(MEMP_NETBUF);
    if (buf == NULL) {
      NETCONN_SET_SAFE_ERR(conn, ERR_MEM);
      return ERR_MEM;
    }

    err = netconn_recv_data(conn, (void **)&p);
    if (err != ERR_OK) {
      memp_free(MEMP_NETBUF, buf);
      return err;
    }
    LWIP_ASSERT("p != NULL", p != NULL);

    buf->p = p;
    buf->ptr = p;
    buf->port = 0;
    ipX_addr_set_any(LWIP_IPV6, &buf->addr);
    *new_buf = buf;
    /* don't set conn->last_err: it's only ERR_OK, anyway */
    return ERR_OK;
  }
#endif /* LWIP_TCP */
#if LWIP_TCP && (LWIP_UDP || LWIP_RAW)
  else
#endif /* LWIP_TCP && (LWIP_UDP || LWIP_RAW) */
  {
#if (LWIP_UDP || LWIP_RAW)
    return netconn_recv_data(conn, (void **)new_buf);
#endif /* (LWIP_UDP || LWIP_RAW) */
  }
}

/**
 * TCP: update the receive window: by calling this, the application
 * tells the stack that it has processed data and is able to accept
 * new data.
 * ATTENTION: use with care, this is mainly used for sockets!
 * Can only be used when calling netconn_set_noautorecved(conn, 1) before.
 *
 * @param conn the netconn for which to update the receive window
 * @param length amount of data processed (ATTENTION: this must be accurate!)
 */
void
netconn_recved(struct netconn *conn, u32_t length)
{
#if LWIP_TCP
  if ((conn != NULL) && (NETCONNTYPE_GROUP(conn->type) == NETCONN_TCP) &&
      (netconn_get_noautorecved(conn))) {
    API_MSG_VAR_DECLARE(msg);
    /* Let the stack know that we have taken the data. */
    /* TODO: Speedup: Don't block and wait for the answer here
       (to prevent multiple thread-switches). */
    API_MSG_VAR_ALLOC_DONTFAIL(msg);
    API_MSG_VAR_REF(msg).msg.conn = conn;
    API_MSG_VAR_REF(msg).msg.msg.r.len = length;
    /* don't care for the return value of lwip_netconn_do_recv */
    TCPIP_APIMSG_NOERR(&API_MSG_VAR_REF(msg), lwip_netconn_do_recv);
    API_MSG_VAR_FREE(msg);
  }
#else /* LWIP_TCP */
  LWIP_UNUSED_ARG(conn);
  LWIP_UNUSED_ARG(length);
#endif /* LWIP_TCP */
}

/**
 * Send data (in form of a netbuf) to a specific remote IP address and port.
 * Only to be used for UDP and RAW netconns (not TCP).
 *
 * @param conn the netconn over which to send data
 * @param buf a netbuf containing the data to send
 * @param addr the remote IP address to which to send the data
 * @param port the remote port to which to send the data
 * @return ERR_OK if data was sent, any other err_t on error
 */
err_t
netconn_sendto(struct netconn *conn, struct netbuf *buf, ip_addr_t *addr, u16_t port)
{
  if (buf != NULL) {
    ipX_addr_set_ipaddr(PCB_ISIPV6(conn->pcb.ip), &buf->addr, addr);
    buf->port = port;
    return netconn_send(conn, buf);
  }
  return ERR_VAL;
}

/**
 * Send data over a UDP or RAW netconn (that is already connected).
 *
 * @param conn the UDP or RAW netconn over which to send data
 * @param buf a netbuf containing the data to send
 * @return ERR_OK if data was sent, any other err_t on error
 */
err_t
netconn_send(struct netconn *conn, struct netbuf *buf)
{
  API_MSG_VAR_DECLARE(msg);
  err_t err;

  LWIP_ERROR("netconn_send: invalid conn",  (conn != NULL), return ERR_ARG;);

  LWIP_DEBUGF(API_LIB_DEBUG, ("netconn_send: sending %"U16_F" bytes\n", buf->p->tot_len));
  API_MSG_VAR_ALLOC(msg);
  API_MSG_VAR_REF(msg).msg.conn = conn;
  API_MSG_VAR_REF(msg).msg.msg.b = buf;
  TCPIP_APIMSG(&API_MSG_VAR_REF(msg), lwip_netconn_do_send, err);
  API_MSG_VAR_FREE(msg);

  NETCONN_SET_SAFE_ERR(conn, err);
  return err;
}

/**
 * Send data over a TCP netconn.
 *
 * @param conn the TCP netconn over which to send data
 * @param dataptr pointer to the application buffer that contains the data to send
 * @param size size of the application data to send
 * @param apiflags combination of following flags :
 * - NETCONN_COPY: data will be copied into memory belonging to the stack
 * - NETCONN_MORE: for TCP connection, PSH flag will be set on last segment sent
 * - NETCONN_DONTBLOCK: only write the data if all dat can be written at once
 * @param bytes_written pointer to a location that receives the number of written bytes
 * @return ERR_OK if data was sent, any other err_t on error
 */
err_t
netconn_write_partly(struct netconn *conn, const void *dataptr, size_t size,
                     u8_t apiflags, size_t *bytes_written)
{
  API_MSG_VAR_DECLARE(msg);
  err_t err;
  u8_t dontblock;

  LWIP_ERROR("netconn_write: invalid conn",  (conn != NULL), return ERR_ARG;);
  LWIP_ERROR("netconn_write: invalid conn->type",  (NETCONNTYPE_GROUP(conn->type)== NETCONN_TCP), return ERR_VAL;);
  if (size == 0) {
    return ERR_OK;
  }
  dontblock = netconn_is_nonblocking(conn) || (apiflags & NETCONN_DONTBLOCK);
  if (dontblock && !bytes_written) {
    /* This implies netconn_write() cannot be used for non-blocking send, since
       it has no way to return the number of bytes written. */
    return ERR_VAL;
  }

  API_MSG_VAR_ALLOC(msg);
  /* non-blocking write sends as much  */
  API_MSG_VAR_REF(msg).msg.conn = conn;
  API_MSG_VAR_REF(msg).msg.msg.w.dataptr = dataptr;
  API_MSG_VAR_REF(msg).msg.msg.w.apiflags = apiflags;
  API_MSG_VAR_REF(msg).msg.msg.w.len = size;
#if LWIP_SO_SNDTIMEO
  if (conn->send_timeout != 0) {
    /* get the time we started, which is later compared to
        sys_now() + conn->send_timeout */
    API_MSG_VAR_REF(msg).msg.msg.w.time_started = sys_now();
  } else {
    API_MSG_VAR_REF(msg).msg.msg.w.time_started = 0;
  }
#endif /* LWIP_SO_SNDTIMEO */

  /* For locking the core: this _can_ be delayed on low memory/low send buffer,
     but if it is, this is done inside api_msg.c:do_write(), so we can use the
     non-blocking version here. */
  TCPIP_APIMSG(&API_MSG_VAR_REF(msg), lwip_netconn_do_write, err);
  if ((err == ERR_OK) && (bytes_written != NULL)) {
    if (dontblock
#if LWIP_SO_SNDTIMEO
        || (conn->send_timeout != 0)
#endif /* LWIP_SO_SNDTIMEO */
       ) {
      /* nonblocking write: maybe the data has been sent partly */
      *bytes_written = API_MSG_VAR_REF(msg).msg.msg.w.len;
    } else {
      /* blocking call succeeded: all data has been sent if it */
      *bytes_written = size;
    }
  }
  API_MSG_VAR_FREE(msg);

  NETCONN_SET_SAFE_ERR(conn, err);
  return err;
}

/**
 * Close ot shutdown a TCP netconn (doesn't delete it).
 *
 * @param conn the TCP netconn to close or shutdown
 * @param how fully close or only shutdown one side?
 * @return ERR_OK if the netconn was closed, any other err_t on error
 */
static err_t
netconn_close_shutdown(struct netconn *conn, u8_t how)
{
  API_MSG_VAR_DECLARE(msg);
  err_t err;

  LWIP_ERROR("netconn_close: invalid conn",  (conn != NULL), return ERR_ARG;);

  API_MSG_VAR_ALLOC(msg);
  API_MSG_VAR_REF(msg).function = lwip_netconn_do_close;
  API_MSG_VAR_REF(msg).msg.conn = conn;
  /* shutting down both ends is the same as closing */
  API_MSG_VAR_REF(msg).msg.msg.sd.shut = how;
  /* because of the LWIP_TCPIP_CORE_LOCKING implementation of lwip_netconn_do_close,
     don't use TCPIP_APIMSG here */
  err = tcpip_apimsg(&API_MSG_VAR_REF(msg));
  API_MSG_VAR_FREE(msg);

  NETCONN_SET_SAFE_ERR(conn, err);
  return err;
}

/**
 * Close a TCP netconn (doesn't delete it).
 *
 * @param conn the TCP netconn to close
 * @return ERR_OK if the netconn was closed, any other err_t on error
 */
err_t
netconn_close(struct netconn *conn)
{
  /* shutting down both ends is the same as closing */
  return netconn_close_shutdown(conn, NETCONN_SHUT_RDWR);
}

/**
 * Shut down one or both sides of a TCP netconn (doesn't delete it).
 *
 * @param conn the TCP netconn to shut down
 * @return ERR_OK if the netconn was closed, any other err_t on error
 */
err_t
netconn_shutdown(struct netconn *conn, u8_t shut_rx, u8_t shut_tx)
{
  return netconn_close_shutdown(conn, (shut_rx ? NETCONN_SHUT_RD : 0) | (shut_tx ? NETCONN_SHUT_WR : 0));
}

#if LWIP_IGMP || (LWIP_IPV6 && LWIP_IPV6_MLD)
/**
 * Join multicast groups for UDP netconns.
 *
 * @param conn the UDP netconn for which to change multicast addresses
 * @param multiaddr IP address of the multicast group to join or leave
 * @param netif_addr the IP address of the network interface on which to send
 *                  the igmp message
 * @param join_or_leave flag whether to send a join- or leave-message
 * @return ERR_OK if the action was taken, any err_t on error
 */
err_t
netconn_join_leave_group(struct netconn *conn,
                         ip_addr_t *multiaddr,
                         ip_addr_t *netif_addr,
                         enum netconn_igmp join_or_leave)
{
  API_MSG_VAR_DECLARE(msg);
  err_t err;

  LWIP_ERROR("netconn_join_leave_group: invalid conn",  (conn != NULL), return ERR_ARG;);

  API_MSG_VAR_ALLOC(msg);
#if LWIP_MPU_COMPATIBLE
  if (multiaddr == NULL) {
    multiaddr = IP_ADDR_ANY;
  }
  if (netif_addr == NULL) {
    netif_addr = IP_ADDR_ANY;
  }
#endif /* LWIP_MPU_COMPATIBLE */
  API_MSG_VAR_REF(msg).msg.conn = conn;
  API_MSG_VAR_REF(msg).msg.msg.jl.multiaddr = API_MSG_VAR_REF(ip_2_ipX(multiaddr));
  API_MSG_VAR_REF(msg).msg.msg.jl.netif_addr = API_MSG_VAR_REF(ip_2_ipX(netif_addr));
  API_MSG_VAR_REF(msg).msg.msg.jl.join_or_leave = join_or_leave;
  TCPIP_APIMSG(&API_MSG_VAR_REF(msg), lwip_netconn_do_join_leave_group, err);
  API_MSG_VAR_FREE(msg);

  NETCONN_SET_SAFE_ERR(conn, err);
  return err;
}
#endif /* LWIP_IGMP || (LWIP_IPV6 && LWIP_IPV6_MLD) */

#if LWIP_DNS
/**
 * Execute a DNS query, only one IP address is returned
 *
 * @param name a string representation of the DNS host name to query
 * @param addr a preallocated ip_addr_t where to store the resolved IP address
 * @return ERR_OK: resolving succeeded
 *         ERR_MEM: memory error, try again later
 *         ERR_ARG: dns client not initialized or invalid hostname
 *         ERR_VAL: dns server response was invalid
 */
err_t
netconn_gethostbyname(const char *name, ip_addr_t *addr)
{
  API_VAR_DECLARE(struct dns_api_msg, msg);
#if !LWIP_MPU_COMPATIBLE
  sys_sem_t sem;
#endif /* LWIP_MPU_COMPATIBLE */
  err_t err;

  LWIP_ERROR("netconn_gethostbyname: invalid name", (name != NULL), return ERR_ARG;);
  LWIP_ERROR("netconn_gethostbyname: invalid addr", (addr != NULL), return ERR_ARG;);

  API_VAR_ALLOC(struct dns_api_msg, MEMP_DNS_API_MSG, msg);
#if LWIP_MPU_COMPATIBLE
  strncpy(API_VAR_REF(msg).name, name, DNS_MAX_NAME_LENGTH-1);
  API_VAR_REF(msg).name[DNS_MAX_NAME_LENGTH-1] = 0;
#else /* LWIP_MPU_COMPATIBLE */
  msg.err = &err;
  msg.sem = &sem;
  API_VAR_REF(msg).addr = API_VAR_REF(addr);
  API_VAR_REF(msg).name = name;
#endif /* LWIP_MPU_COMPATIBLE */
  err = sys_sem_new(API_EXPR_REF(API_VAR_REF(msg).sem), 0);
  if (err != ERR_OK) {
    API_VAR_FREE(MEMP_DNS_API_MSG, msg);
    return err;
  }

  tcpip_callback(lwip_netconn_do_gethostbyname, &API_VAR_REF(msg));
  sys_sem_wait(API_EXPR_REF(API_VAR_REF(msg).sem));
  sys_sem_free(API_EXPR_REF(API_VAR_REF(msg).sem));

#if LWIP_MPU_COMPATIBLE
  *addr = msg->addr;
  err = msg->err;
#endif /* LWIP_MPU_COMPATIBLE */

  API_VAR_FREE(MEMP_DNS_API_MSG, msg);
  return err;
}
#endif /* LWIP_DNS*/

#endif /* LWIP_NETCONN */
