
#ifndef __UIP_PBUF_H__
#define __UIP_PBUF_H__

//#include "lwip/opt.h"
//#include "lwip/err.h"
#include "uip-conf.h"
#include "uip_etharp.h"

typedef rt_int16_t	s16_t;
typedef rt_int8_t	err_t;
#ifdef __cplusplus
extern "C" {
#endif

#define PBUF_TRANSPORT_HLEN 20
#define PBUF_IP_HLEN        20

typedef enum {
  PBUF_TRANSPORT,
  PBUF_IP,
  PBUF_LINK,
  PBUF_RAW
} pbuf_layer;

typedef enum {
  PBUF_RAM, /* pbuf data is stored in RAM */
  PBUF_ROM, /* pbuf data is stored in ROM */
  PBUF_REF, /* pbuf comes from the pbuf pool */
  PBUF_POOL /* pbuf payload refers to RAM */
} pbuf_type;


/** indicates this packet's data should be immediately passed to the application */
#define PBUF_FLAG_PUSH 0x01U
#ifdef RT_USING_LWIP
struct pbuf {
  /** next pbuf in singly linked pbuf chain */
  struct pbuf *next;

  /** pointer to the actual data in the buffer */
  void *payload;
  
  /**
   * total length of this buffer and all next buffers in chain
   * belonging to the same packet.
   *
   * For non-queue packet chains this is the invariant:
   * p->tot_len == p->len + (p->next? p->next->tot_len: 0)
   */
  u16_t tot_len;
  
  /** length of this buffer */
  u16_t len;  

  /** pbuf_type as u8_t instead of enum to save space */
  u8_t /*pbuf_type*/ type;

  /** misc flags */
  u8_t flags;

  /**
   * the reference count always equals the number of pointers
   * that refer to this pbuf. This can be pointers from an application,
   * the stack itself, or pbuf->next pointers from a chain.
   */
  u16_t ref;
  
};
#else    /* RT_USING_UIP */
struct pbuf
{
   /** pointer to the actual data in the buffer */
    void *payload;
    rt_uint16_t len;
};
#endif
/* Initializes the pbuf module. This call is empty for now, but may not be in future. */


struct pbuf *pbuf_alloc(pbuf_layer l, u16_t size, pbuf_type type);
 
u8_t pbuf_header(struct pbuf *p, s16_t header_size);

u8_t pbuf_free(struct pbuf *p);

#endif /* __UIP_PBUF_H__ */
