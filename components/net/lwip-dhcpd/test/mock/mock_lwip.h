/*
 * Minimal lwIP / RT-Thread stubs for the host-side DHCPD lease test.
 *
 * Only the declarations that dhcp_server_raw.c references are provided.  The
 * packet path is a no-op; the test drives the lease bookkeeping
 * (dhcp_client_find / dhcp_client_alloc / dhcp_client_remove_expired) and the
 * lifecycle entry points directly.
 *
 * The timeout and tcpip_callback stubs are not empty: they model the lwIP
 * tcpip thread closely enough to verify that start/stop register and cancel
 * the periodic recycle timer, and that the recycle handler runs from that
 * thread.  See the "tcpip thread" section below.
 *
 * This header is used by test/test_dhcpd_lease.c only; firmware builds keep
 * using the real lwIP headers.
 */

#ifndef DHCPD_TEST_MOCK_LWIP_H
#define DHCPD_TEST_MOCK_LWIP_H

#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* ---------------------------------------------------------------- types */

typedef uint8_t u8_t;
typedef uint16_t u16_t;
typedef uint32_t u32_t;
typedef int32_t s32_t;
typedef int8_t err_t;
typedef int rt_bool_t;
typedef unsigned long rt_ubase_t;

#define RT_NULL                ((void *)0)
#define RT_FALSE               0
#define RT_TRUE                1
#define SMEMCPY(dst, src, len) memcpy((dst), (src), (len))

#define ERR_OK  0
#define ERR_MEM (-1)

/* version gates evaluated by dhcp_server_raw.c (override with -DLWIP_VERSION) */
#ifndef LWIP_VERSION
#define LWIP_VERSION 0x02010000U
#endif
#ifndef LWIP_IPV4
#define LWIP_IPV4 1
#endif
#ifndef LWIP_DHCP
#define LWIP_DHCP 0
#endif

/* ---------------------------------------------------------------- debug */

#define LWIP_DBG_ON            0x80U
#define DHCP_DEBUG             LWIP_DBG_ON
#define LWIP_DBG_TRACE         0x40U
#define LWIP_DBG_LEVEL_WARNING 0x01U
#define U16_F                  "u"
#define X32_F                  "x"

#define LWIP_DEBUGF(debug, message) \
    do                              \
    {                               \
        (void)(debug);              \
    } while (0)
#define LWIP_UNUSED_ARG(x) ((void)(x))

static inline int mock_printf(const char *fmt, ...)
{
    va_list ap;
    int printed;

    va_start(ap, fmt);
    printed = vprintf(fmt, ap);
    va_end(ap);

    return printed;
}

#define rt_kprintf mock_printf

/* ---------------------------------------------------------- fake runtime */

static u32_t mock_now_ms;
static size_t mock_mem_live;

static inline void mock_reset_clock(u32_t now_ms)
{
    mock_now_ms = now_ms;
}
static inline size_t mock_mem_live_count(void)
{
    return mock_mem_live;
}

static inline u32_t sys_now(void)
{
    return mock_now_ms;
}

static inline void *mem_malloc(size_t size)
{
    void *ptr = malloc(size);

    if (ptr != NULL)
    {
        mock_mem_live++;
    }

    return ptr;
}

static inline void mem_free(void *ptr)
{
    if (ptr != NULL)
    {
        mock_mem_live--;
        free(ptr);
    }
}

/* --------------------------------------------------------- fake threads */

#ifndef RT_NAME_MAX
#define RT_NAME_MAX 8
#endif

/* lwIP port value, see components/net/lwip/port/lwipopts.h */
#define TCPIP_THREAD_NAME "tcpip"

struct rt_thread
{
    char name[RT_NAME_MAX];
};

typedef struct rt_thread *rt_thread_t;

static struct rt_thread mock_caller_thread = { "main" };

static inline rt_thread_t rt_thread_self(void)
{
    return &mock_caller_thread;
}

static inline void mock_set_caller_name(const char *name)
{
    memset(mock_caller_thread.name, 0, sizeof(mock_caller_thread.name));
    strncpy(mock_caller_thread.name, name, sizeof(mock_caller_thread.name) - 1);
}

/* only one fake thread exists; it is the tcpip thread when named so */
static inline rt_thread_t rt_thread_find(char *name)
{
    return (strcmp(mock_caller_thread.name, name) == 0) ? &mock_caller_thread : RT_NULL;
}

/* ---------------------------------------------------------------- timers */

typedef void (*sys_timeout_handler)(void *arg);
typedef void (*tcpip_callback_fn)(void *ctx);

struct mock_timer
{
    struct mock_timer *next;
    sys_timeout_handler handler;
    void *arg;
    u32_t due_ms;
};

static struct mock_timer *mock_timers;
static size_t mock_timer_live;
static unsigned long mock_timer_fires;

static inline size_t mock_timer_count(void)
{
    return mock_timer_live;
}

static inline int mock_timer_registered(sys_timeout_handler handler)
{
    struct mock_timer *timer;

    for (timer = mock_timers; timer != NULL; timer = timer->next)
    {
        if (timer->handler == handler)
        {
            return 1;
        }
    }

    return 0;
}

/* like lwIP sys_timeout(): one new entry, due at now + msecs */
static inline void sys_timeout(u32_t msecs, sys_timeout_handler handler, void *arg)
{
    struct mock_timer *timer = (struct mock_timer *)calloc(1, sizeof(*timer));

    if (timer == NULL)
    {
        printf("mock sys_timeout: out of memory\n");
        exit(1);
    }

    timer->handler = handler;
    timer->arg = arg;
    timer->due_ms = mock_now_ms + msecs;
    timer->next = mock_timers;
    mock_timers = timer;
    mock_timer_live++;
}

/* like lwIP sys_untimeout(): drop every entry with this handler/arg pair */
static inline void sys_untimeout(sys_timeout_handler handler, void *arg)
{
    struct mock_timer **link = &mock_timers;

    while (*link != NULL)
    {
        struct mock_timer *timer = *link;

        if (timer->handler == handler && timer->arg == arg)
        {
            *link = timer->next;
            free(timer);
            mock_timer_live--;
        }
        else
        {
            link = &timer->next;
        }
    }
}

/* Run every expired timeout, the way the tcpip thread does. */
static inline void mock_run_timeouts(void)
{
    for (;;)
    {
        struct mock_timer **link = &mock_timers;
        struct mock_timer *timer = NULL;
        sys_timeout_handler handler;
        void *arg;

        while (*link != NULL)
        {
            /* TIME_LESS_THAN(): wrap-safe "now >= due" */
            if ((s32_t)(mock_now_ms - (*link)->due_ms) >= 0)
            {
                timer = *link;
                break;
            }
            link = &(*link)->next;
        }

        if (timer == NULL)
        {
            return;
        }

        /* lwIP frees the entry before invoking the handler, and the handler
         * may register the next period from inside the call. */
        *link = timer->next;
        handler = timer->handler;
        arg = timer->arg;
        free(timer);
        mock_timer_live--;

        mock_timer_fires++;
        handler(arg);
    }
}

/* Advance the mock clock and run the timeouts that became due. */
static inline void mock_advance_clock(u32_t elapsed_ms)
{
    mock_now_ms += elapsed_ms;
    mock_run_timeouts();
}

/* ------------------------------------------------ tcpip thread marshalling */

#define MOCK_TCPIP_QUEUE_DEPTH 4

struct mock_tcpip_msg
{
    tcpip_callback_fn fn;
    void *ctx;
};

static struct mock_tcpip_msg mock_tcpip_queue[MOCK_TCPIP_QUEUE_DEPTH];
static size_t mock_tcpip_queued;
static unsigned long mock_tcpip_callbacks;

static inline unsigned long mock_tcpip_callback_count(void)
{
    return mock_tcpip_callbacks;
}

/* like lwIP tcpip_callback(): queue the function for the tcpip thread */
static inline err_t tcpip_callback(tcpip_callback_fn fn, void *ctx)
{
    if (mock_tcpip_queued == MOCK_TCPIP_QUEUE_DEPTH)
    {
        return ERR_MEM;
    }

    mock_tcpip_queue[mock_tcpip_queued].fn = fn;
    mock_tcpip_queue[mock_tcpip_queued].ctx = ctx;
    mock_tcpip_queued++;
    mock_tcpip_callbacks++;

    return ERR_OK;
}

/* Run queued tcpip callbacks in order, as the tcpip thread would. */
static inline void mock_tcpip_run(void)
{
    while (mock_tcpip_queued > 0)
    {
        struct mock_tcpip_msg msg = mock_tcpip_queue[0];
        size_t i;

        for (i = 1; i < mock_tcpip_queued; i++)
        {
            mock_tcpip_queue[i - 1] = mock_tcpip_queue[i];
        }
        mock_tcpip_queued--;

        msg.fn(msg.ctx);
    }
}

/* -------------------------------------------------------------- semaphores */

typedef struct
{
    int count;
} sys_sem_t;

static inline err_t sys_sem_new(sys_sem_t *sem, u8_t count)
{
    sem->count = count;
    return ERR_OK;
}

/*
 * A thread that waits for a tcpip callback lets the "tcpip thread" run the
 * queued message.  If nothing signals it, the production code would sleep
 * forever, so fail loudly instead of hanging the test.
 */
static inline u32_t sys_sem_wait(sys_sem_t *sem)
{
    mock_tcpip_run();

    if (sem->count == 0)
    {
        printf("mock sys_sem_wait: callback never signaled (deadlock)\n");
        exit(1);
    }

    sem->count--;
    return 0;
}

static inline void sys_sem_signal(sys_sem_t *sem)
{
    sem->count++;
}

static inline void sys_sem_free(sys_sem_t *sem)
{
    (void)sem;
}

/* ----------------------------------------------------------- core locking */

/*
 * The production code never takes the core lock itself: every lifecycle call
 * is marshalled to the tcpip thread.  Keep the macros around so a future
 * regression that reintroduces LOCK_TCPIP_CORE() still compiles.
 */
#define LOCK_TCPIP_CORE() \
    do                    \
    {                     \
    } while (0)
#define UNLOCK_TCPIP_CORE() \
    do                      \
    {                       \
    } while (0)

/* ------------------------------------------------------------- addresses */

typedef struct
{
    u32_t addr;
} ip4_addr_t;

typedef struct
{
    ip4_addr_t ip4;
} ip_addr_t;

static inline u32_t mock_bswap32(u32_t value)
{
#if defined(__BYTE_ORDER__) && (__BYTE_ORDER__ == __ORDER_BIG_ENDIAN__)
    return value;
#else
    return ((value & 0x000000ffU) << 24) | ((value & 0x0000ff00U) << 8) |
           ((value & 0x00ff0000U) >> 8) | ((value & 0xff000000U) >> 24);
#endif
}

#undef htonl
#undef ntohl
#define htonl(value)    mock_bswap32((u32_t)(value))
#define ntohl(value)    mock_bswap32((u32_t)(value))
#define PP_HTONL(value) htonl(value)

#define INADDR_BROADCAST 0xffffffffUL
#define IP_ADDR_ANY      ((const ip_addr_t *)0)

#define ip_2_ip4(ipaddr) (&(ipaddr)->ip4)

static inline int ip4_addr_cmp(const ip4_addr_t *left, const ip4_addr_t *right)
{
    return left->addr == right->addr;
}

static inline int ip4addr_aton(const char *cp, ip4_addr_t *addr)
{
    unsigned int part[4];

    if (sscanf(cp, "%u.%u.%u.%u", &part[0], &part[1], &part[2], &part[3]) != 4)
    {
        return 0;
    }

    addr->addr = htonl((part[0] << 24) | (part[1] << 16) | (part[2] << 8) | part[3]);

    return 1;
}

/* ---------------------------------------------------------------- netif */

struct netif
{
    char name[2];
    ip_addr_t ip_addr;
    ip_addr_t netmask;
    struct netif *next;
};

static struct netif *netif_list;

static inline void netif_set_up(struct netif *netif)
{
    (void)netif;
}

static inline void dhcp_stop(struct netif *netif)
{
    (void)netif;
}

/*
 * Matches the extern declaration inside dhcp_server_raw.c (defined by
 * components/net/lwip/port/ethernetif.c in a firmware build).  Do not make it
 * static: the test translation unit includes the production source file.
 */
void set_if(const char *netif_name, const char *ip_addr,
            const char *gw_addr, const char *nm_addr)
{
    (void)netif_name;
    (void)ip_addr;
    (void)gw_addr;
    (void)nm_addr;
}

/* ------------------------------------------------------------ udp / pbuf */

struct udp_pcb;
struct pbuf;

typedef void (*mock_udp_recv_fn)(void *arg, struct udp_pcb *pcb, struct pbuf *p,
                                 const ip_addr_t *addr, u16_t port);

struct udp_pcb
{
    int unused;
};

struct pbuf
{
    void *payload;
    u16_t len;
    u16_t tot_len;
};

#define SOF_BROADCAST 0x0020U

#define PBUF_TRANSPORT 0
#define PBUF_RAM       0

#define ip_set_option(pcb, option) \
    do                             \
    {                              \
        (void)(pcb);               \
        (void)(option);            \
    } while (0)

#define MOCK_UDP_PCB_POOL 4
static struct udp_pcb mock_udp_pcbs[MOCK_UDP_PCB_POOL];
static size_t mock_udp_used;

static inline struct udp_pcb *udp_new(void)
{
    if (mock_udp_used == MOCK_UDP_PCB_POOL)
    {
        return NULL;
    }

    return &mock_udp_pcbs[mock_udp_used++];
}

static inline err_t udp_bind(struct udp_pcb *pcb, const ip_addr_t *local_ip,
                             u16_t local_port)
{
    (void)pcb;
    (void)local_ip;
    (void)local_port;

    return ERR_OK;
}

static inline void udp_remove(struct udp_pcb *pcb)
{
    (void)pcb;
}

static inline void udp_disconnect(struct udp_pcb *pcb)
{
    (void)pcb;
}

static inline void udp_recv(struct udp_pcb *pcb, mock_udp_recv_fn recv, void *recv_arg)
{
    (void)pcb;
    (void)recv;
    (void)recv_arg;
}

static inline err_t udp_sendto_if(struct udp_pcb *pcb, struct pbuf *p,
                                  const ip_addr_t *dst_ip, u16_t dst_port,
                                  struct netif *netif)
{
    (void)pcb;
    (void)p;
    (void)dst_ip;
    (void)dst_port;
    (void)netif;

    return ERR_OK;
}

static inline struct pbuf *pbuf_alloc(int layer, u16_t length, int type)
{
    (void)layer;
    (void)length;
    (void)type;

    return NULL;
}

static inline void pbuf_free(struct pbuf *p)
{
    (void)p;
}

static inline u16_t pbuf_copy(struct pbuf *dst, const struct pbuf *src)
{
    (void)dst;
    (void)src;

    return 0;
}

static inline void pbuf_realloc(struct pbuf *p, u16_t size)
{
    (void)p;
    (void)size;
}

/* ------------------------------------------------------------ DHCP wire */

#define DHCP_BOOTREQUEST 1
#define DHCP_BOOTREPLY   2

#define DHCP_OPTION_PAD          0
#define DHCP_OPTION_SUBNET_MASK  1
#define DHCP_OPTION_ROUTER       3
#define DHCP_OPTION_DNS_SERVER   6
#define DHCP_OPTION_REQUESTED_IP 50
#define DHCP_OPTION_LEASE_TIME   51
#define DHCP_OPTION_MESSAGE_TYPE 53
#define DHCP_OPTION_SERVER_ID    54
#define DHCP_OPTION_END          255

#define DHCP_DISCOVER 1
#define DHCP_OFFER    2
#define DHCP_REQUEST  3
#define DHCP_DECLINE  4
#define DHCP_ACK      5
#define DHCP_NAK      6
#define DHCP_RELEASE  7
#define DHCP_INFORM   8

#define DHCP_MAGIC_COOKIE 0x63825363UL

struct __attribute__((packed)) dhcp_msg
{
    u8_t op;
    u8_t htype;
    u8_t hlen;
    u8_t hops;
    u32_t xid;
    u16_t secs;
    u16_t flags;
    u8_t ciaddr[4];
    u8_t yiaddr[4];
    u8_t siaddr[4];
    u8_t giaddr[4];
    u8_t chaddr[16];
    u8_t sname[64];
    u8_t file[128];
    u32_t cookie;
};

/* matches the lwIP DHCP wire layout used by dhcp_server_raw.c */
#define DHCP_OPTIONS_OFS 240

typedef char dhcp_msg_layout_check[(sizeof(struct dhcp_msg) == DHCP_OPTIONS_OFS) ? 1 : -1];

#endif /* DHCPD_TEST_MOCK_LWIP_H */
