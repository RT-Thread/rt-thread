/**
 * \addtogroup apps
 * @{
 */

/**
 * \defgroup helloworld Hello, world
 * @{
 *
 * A small example showing how to write applications with
 * \ref psock "protosockets".
 */

/**
 * \file
 *         Header file for an example of how to write uIP applications
 *         with protosockets.
 * \author
 *         Adam Dunkels <adam@sics.se>
 */

#ifndef __HELLO_WORLD_H__
#define __HELLO_WORLD_H__

/* Since this file will be included by uip.h, we cannot include uip.h
   here. But we might need to include uipopt.h if we need the u8_t and
   u16_t datatypes. */
#include "uipopt.h"

#include "psock.h"

/* Next, we define the uip_tcp_appstate_t datatype. This is the state
   of our application, and the memory required for this state is
   allocated together with each TCP connection. One application state
   for each TCP connection. */
#define BUF_SIZE 200
typedef struct hello_world_state {
  struct psock p;
  char inputbuffer[BUF_SIZE];
  char name[BUF_SIZE];
} uip_tcp_appstate_t;

/* Finally we define the application function to be called by uIP. */
void hello_world_appcall(void);
#ifndef UIP_APPCALL
#define UIP_APPCALL hello_world_appcall
#endif /* UIP_APPCALL */

void hello_world_init(void);

#endif /* __HELLO_WORLD_H__ */
/** @} */
/** @} */
