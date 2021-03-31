/***************************************************************************//**
 * @file    httpd.c
 * @brief   Simple http server demo application
 *  COPYRIGHT (C) 2012, RT-Thread Development Team
 * @author  onelife
 * @version 1.0
 *******************************************************************************
 * @section License
 * The license and distribution terms for this file may be found in the file
 * LICENSE in this distribution or at http://www.rt-thread.org/license/LICENSE
 *******************************************************************************
 * @section Change Logs
 * Date         Author      Notes
 * 2011-07-04   onelife     Derive from Energy Micro demo application
 ******************************************************************************/

/**************************************************************************//**
 * @file
 * @brief This file is dervied from the ``httpd.c'' skeleton.
 * @author Energy Micro AS
 * @@version 0.0.4
 ******************************************************************************
 * @section License
 * <b>(C) Copyright 2009 Energy Micro AS, http://www.energymicro.com</b>
 ******************************************************************************
 *
 * This source code is the property of Energy Micro AS. The source and compiled
 * code may only be used on Energy Micro "EFM32" microcontrollers.
 *
 * This copyright notice may not be removed from the source code nor changed.
 *
 * DISCLAIMER OF WARRANTY/LIMITATION OF REMEDIES: Energy Micro AS has no
 * obligation to support this Software. Energy Micro AS is providing the
 * Software "AS IS", with no express or implied warranties of any kind,
 * including, but not limited to, any implied warranties of merchantability
 * or fitness for any particular purpose or warranties against infringement
 * of any proprietary rights of a third party.
 *
 * Energy Micro AS will not be liable for any consequential, incidental, or
 * special damages, or any other relief, or for any claim by any third party,
 * arising from your use of this Software.
 *
 *****************************************************************************/
/**
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

/***************************************************************************//**
* @addtogroup efm32_eth
* @{
******************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "rtthread.h"
#include "dev_misc.h"

#if defined(RT_USING_LWIP) && defined(EFM32_USING_ETH_HTTPD)
#include "lwip/tcp.h"
#include "lwip/ip_addr.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* This is the data for the actual web page. */
static int temp, vdd;
static char indexdata[700];
static const char indexdata1[] =
    "HTTP/1.0 200 OK\r\n\
    Content-type: text/html\r\n\
    Pragma: no-cache\r\n\
    Refresh: 5\r\n\
    \r\n\
    <html>\
    <head><title>EFM32 HTTPD DEMO</title><head>\
    <body>\
    <h1>This is a simple http server</h1>\
    <br><br><B>Ethernet controller: ENC28J60</B>\
    <br><br><B>Refreshing timers: ";

static const char indexdata2[] =
    "<br><br><B>Current Vdd: ";

static const char indexdata3[] =
    " V</B>\
    <br><br><B>Current temperature: ";

static const char indexdata4[] =
    " C</B>\
    </body>\
    </html>";

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/* This is the callback function that is called
 * when a TCP segment has arrived in the connection. */
static err_t http_recv(void *arg, struct tcp_pcb *pcb, struct pbuf *p, err_t err)
{
  static unsigned char temp_var = 0;
  unsigned short       counter, i;
  char                 *rq;
  /* If we got a NULL pbuf in p, the remote end has closed
   * the connection. */
  if (p != NULL)
  {
    /* The payload pointer in the pbuf contains the data
     * in the TCP segment. */
    rq = p->payload;
    /* Check if the request was an HTTP "GET / HTTP/1.1". */
    if (rq[0] == 'G' && rq[1] == 'E' && rq[2] == 'T')
    {
      /* Send the web page to the remote host. A zero
       * in the last argument means that the data should
       * not be copied into internal buffers. */

      counter = 0;

      for (i = 0; i < sizeof(indexdata1) - 1; i++)
      {
        indexdata[counter] = indexdata1[i];
        counter++;
      }

      indexdata[counter] = ' ';
      counter++;

      /*Copy page counter MSB*/
      indexdata[counter] = temp_var / 10 + 0x30;
      counter++;

      /*Copy page counter LSB*/
      indexdata[counter] = temp_var % 10 + 0x30;
      counter++;

      temp_var++;
      if (temp_var > 100) temp_var = 1;

      for (i = 0; i < sizeof(indexdata2) - 1; i++)
      {
        indexdata[counter] = indexdata2[i];
        counter++;
      }

      vdd = rt_hw_get_vdd();
      rt_sprintf(&indexdata[counter], "%1d.%02d", vdd / 100, vdd % 100);
      counter += 4;

      for (i = 0; i < sizeof(indexdata3) - 1; i++)
      {
        indexdata[counter] = indexdata3[i];
        counter++;
      }

      temp = rt_hw_get_temp();
      /*Set temperature sign*/
      if (temp < 0)
      {
        indexdata[counter] = '-';
        counter++;
      }
      rt_sprintf(&indexdata[counter], "%02d.%02d\n", temp / 100, temp % 100);
      counter += 5;

      for (i = 0; i < sizeof(indexdata4); i++)
      {
        indexdata[counter] = indexdata4[i];
        counter++;
      }

      tcp_write(pcb, indexdata, counter, 1);
    }
    /* Free the pbuf. */
    pbuf_free(p);
  }
  /* Close the connection. */
  tcp_close(pcb);
  return ERR_OK;
}

/* This is the callback function that is called when
 * a connection has been accepted. */
static err_t http_accept(void *arg, struct tcp_pcb *pcb, err_t err)
{
  /* Set up the function http_recv() to be called when data
   * arrives. */
  tcp_recv(pcb, http_recv);
  return ERR_OK;
}

/* The initialization function. */
void httpd_init(void)
{
  struct tcp_pcb *pcb;
  /* Create a new TCP PCB. */
  pcb = tcp_new();
  /* Bind the PCB to TCP port 80. */
  tcp_bind(pcb, NULL, 80);
  /* Change TCP state to LISTEN. */
  pcb = tcp_listen(pcb);
  /* Set up http_accet() function to be called
   * when a new connection arrives. */
  tcp_accept(pcb, http_accept);
}

#endif /* defined(RT_USING_LWIP) && defined(EFM32_USING_ETH_HTTPD) */
/***************************************************************************//**
 * @}
 ******************************************************************************/
