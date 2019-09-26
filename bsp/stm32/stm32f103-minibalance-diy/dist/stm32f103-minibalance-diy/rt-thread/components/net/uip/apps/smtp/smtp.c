/**
 * \addtogroup apps
 * @{
 */

/**
 * \defgroup smtp SMTP E-mail sender
 * @{
 *
 * The Simple Mail Transfer Protocol (SMTP) as defined by RFC821 is
 * the standard way of sending and transfering e-mail on the
 * Internet. This simple example implementation is intended as an
 * example of how to implement protocols in uIP, and is able to send
 * out e-mail but has not been extensively tested.
 */

/**
 * \file
 * SMTP example implementation
 * \author Adam Dunkels <adam@dunkels.com>
 */

/*
 * Copyright (c) 2004, Adam Dunkels.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the Institute nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE INSTITUTE AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE INSTITUTE OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 * This file is part of the uIP TCP/IP stack.
 *
 * Author: Adam Dunkels <adam@sics.se>
 *
 * $Id: smtp.c,v 1.4 2006/06/11 21:46:37 adam Exp $
 */
#include "smtp.h"

#include "smtp-strings.h"
#include "psock.h"
#include "uip.h"

#include <string.h>

static struct smtp_state s;

static char *localhostname;
static uip_ipaddr_t smtpserver;

#define ISO_nl 0x0a
#define ISO_cr 0x0d

#define ISO_period 0x2e

#define ISO_2  0x32
#define ISO_3  0x33
#define ISO_4  0x34
#define ISO_5  0x35


/*---------------------------------------------------------------------------*/
static
PT_THREAD(smtp_thread(void))
{
  PSOCK_BEGIN(&s.psock);

  PSOCK_READTO(&s.psock, ISO_nl);
   
  if(strncmp(s.inputbuffer, smtp_220, 3) != 0) {
    PSOCK_CLOSE(&s.psock);
    smtp_done(2);
    PSOCK_EXIT(&s.psock);
  }
  
  PSOCK_SEND_STR(&s.psock, (char *)smtp_helo);
  PSOCK_SEND_STR(&s.psock, localhostname);
  PSOCK_SEND_STR(&s.psock, (char *)smtp_crnl);

  PSOCK_READTO(&s.psock, ISO_nl);
  
  if(s.inputbuffer[0] != ISO_2) {
    PSOCK_CLOSE(&s.psock);
    smtp_done(3);
    PSOCK_EXIT(&s.psock);
  }

  PSOCK_SEND_STR(&s.psock, (char *)smtp_mail_from);
  PSOCK_SEND_STR(&s.psock, s.from);
  PSOCK_SEND_STR(&s.psock, (char *)smtp_crnl);

  PSOCK_READTO(&s.psock, ISO_nl);
  
  if(s.inputbuffer[0] != ISO_2) {
    PSOCK_CLOSE(&s.psock);
    smtp_done(4);
    PSOCK_EXIT(&s.psock);
  }

  PSOCK_SEND_STR(&s.psock, (char *)smtp_rcpt_to);
  PSOCK_SEND_STR(&s.psock, s.to);
  PSOCK_SEND_STR(&s.psock, (char *)smtp_crnl);

  PSOCK_READTO(&s.psock, ISO_nl);
  
  if(s.inputbuffer[0] != ISO_2) {
    PSOCK_CLOSE(&s.psock);
    smtp_done(5);
    PSOCK_EXIT(&s.psock);
  }
  
  if(s.cc != 0) {
    PSOCK_SEND_STR(&s.psock, (char *)smtp_rcpt_to);
    PSOCK_SEND_STR(&s.psock, s.cc);
    PSOCK_SEND_STR(&s.psock, (char *)smtp_crnl);

    PSOCK_READTO(&s.psock, ISO_nl);
  
    if(s.inputbuffer[0] != ISO_2) {
      PSOCK_CLOSE(&s.psock);
      smtp_done(6);
      PSOCK_EXIT(&s.psock);
    }
  }
  
  PSOCK_SEND_STR(&s.psock, (char *)smtp_data);
  
  PSOCK_READTO(&s.psock, ISO_nl);
  
  if(s.inputbuffer[0] != ISO_3) {
    PSOCK_CLOSE(&s.psock);
    smtp_done(7);
    PSOCK_EXIT(&s.psock);
  }

  PSOCK_SEND_STR(&s.psock, (char *)smtp_to);
  PSOCK_SEND_STR(&s.psock, s.to);
  PSOCK_SEND_STR(&s.psock, (char *)smtp_crnl);
  
  if(s.cc != 0) {
    PSOCK_SEND_STR(&s.psock, (char *)smtp_cc);
    PSOCK_SEND_STR(&s.psock, s.cc);
    PSOCK_SEND_STR(&s.psock, (char *)smtp_crnl);
  }
  
  PSOCK_SEND_STR(&s.psock, (char *)smtp_from);
  PSOCK_SEND_STR(&s.psock, s.from);
  PSOCK_SEND_STR(&s.psock, (char *)smtp_crnl);
  
  PSOCK_SEND_STR(&s.psock, (char *)smtp_subject);
  PSOCK_SEND_STR(&s.psock, s.subject);
  PSOCK_SEND_STR(&s.psock, (char *)smtp_crnl);

  PSOCK_SEND(&s.psock, s.msg, s.msglen);
  
  PSOCK_SEND_STR(&s.psock, (char *)smtp_crnlperiodcrnl);

  PSOCK_READTO(&s.psock, ISO_nl);
  if(s.inputbuffer[0] != ISO_2) {
    PSOCK_CLOSE(&s.psock);
    smtp_done(8);
    PSOCK_EXIT(&s.psock);
  }

  PSOCK_SEND_STR(&s.psock, (char *)smtp_quit);
  smtp_done(SMTP_ERR_OK);
  PSOCK_END(&s.psock);
}
/*---------------------------------------------------------------------------*/
void
smtp_appcall(void)
{
  if(uip_closed()) {
    s.connected = 0;
    return;
  }
  if(uip_aborted() || uip_timedout()) {
    s.connected = 0;
    smtp_done(1);
    return;
  }
  smtp_thread();
}
/*---------------------------------------------------------------------------*/
/**
 * Specificy an SMTP server and hostname.
 *
 * This function is used to configure the SMTP module with an SMTP
 * server and the hostname of the host.
 *
 * \param lhostname The hostname of the uIP host.
 *
 * \param server A pointer to a 4-byte array representing the IP
 * address of the SMTP server to be configured.
 */
void
smtp_configure(char *lhostname, void *server)
{
  localhostname = lhostname;
  uip_ipaddr_copy(smtpserver, server);
}
/*---------------------------------------------------------------------------*/
/**
 * Send an e-mail.
 *
 * \param to The e-mail address of the receiver of the e-mail.
 * \param cc The e-mail address of the CC: receivers of the e-mail.
 * \param from The e-mail address of the sender of the e-mail.
 * \param subject The subject of the e-mail.
 * \param msg The actual e-mail message.
 * \param msglen The length of the e-mail message.
 */
unsigned char
smtp_send(char *to, char *cc, char *from,
	  char *subject, char *msg, u16_t msglen)
{
  struct uip_conn *conn;

  conn = uip_connect(smtpserver, HTONS(25));
  if(conn == NULL) {
    return 0;
  }
  s.connected = 1;
  s.to = to;
  s.cc = cc;
  s.from = from;
  s.subject = subject;
  s.msg = msg;
  s.msglen = msglen;

  PSOCK_INIT(&s.psock, s.inputbuffer, sizeof(s.inputbuffer));
  
  return 1;
}
/*---------------------------------------------------------------------------*/
void
smtp_init(void)
{
  s.connected = 0;
}
/*---------------------------------------------------------------------------*/
/** @} */
/** @} */
