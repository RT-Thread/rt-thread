/*-
 * Copyright (c) 1982, 1986, 1988, 1993
 *  The Regents of the University of California.
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
 * 3. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 *  @(#)mbuf.h  8.5 (Berkeley) 2/19/95
 * $FreeBSD: releng/10.1/sys/sys/mbuf.h 269047 2014-07-24 06:03:45Z kevlo $
 */

#ifndef _SYS_MBUF_0_H_
#define _SYS_MBUF_0_H_

#if (__CONFIG_MBUF_IMPL_MODE == 0)

#include <stdint.h>
#ifdef __CONFIG_ARCH_DUAL_CORE
#include "sys/ducc/ducc_addr.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Callback structure
 */
struct m_cb {
    void *func;
    void *arg;
};

/*
 * Record/packet header in first mbuf of chain; always valid and M_PKTHDR is set.
 * Size : 24
 */
struct pkthdr {
    void    *rcvif; /* rcv interface */
    int32_t len;    /* total packet length */

    union {
        uint8_t   eigth[8];
        uint16_t  sixteen[4];
        uint32_t  thirtytwo[2];
        uint64_t  sixtyfour[1];
        uintptr_t unintptr[1];
        void      *ptr;
    } PH_per;

    struct m_cb cb;
};

struct ext_info {
    uint8_t eigth[32];
};

#define ether_vtag  PH_per.sixteen[0]
#define PH_vt       PH_per
#define vt_nrecs    sixteen[0]
#define tso_segsz   PH_per.sixteen[1]
#define csum_phsum  PH_per.sixteen[2]
#define csum_data   PH_per.thirtytwo[1]

/*
 * The core of the mbuf object along with some shortcut defines for practical
 * purposes.
 */
struct mbuf { // Size : 48 + 32 = 80
    /*
     * Header present at the beginning of every mbuf.
     * Size : 24
     */
    uint8_t       *m_buf;         /* a continuous buffer */ // useless now
    struct mbuf   *m_nextpkt;     /* next chain in queue/record */
    uint8_t       *m_data;        /* location of data */
    int32_t       m_len;          /* amount of data in this mbuf */
    uint16_t      m_headspace;    /* empty space available at the head */
    uint16_t      m_tailspace;    /* empty space available at the tail */
    uint32_t      m_type  :8,     /* type of data in this mbuf */ // use as flag
                  m_flags :24;    /* flags; see below */
    /*** End of the mbuf header ***/

    struct pkthdr m_pkthdr; /* M_PKTHDR always set */
    struct ext_info m_ext_info;   /* extend info */
};

#if (defined(__CONFIG_ARCH_NET_CORE) || !defined(__CONFIG_ARCH_DUAL_CORE))

#define MBUF_HEAD_SPACE 68 /* reserved head space in mbuf::m_buf, align to 4 */
#define MBUF_TAIL_SPACE 16 /* reserved tail space in mbuf::m_buf, align to 4 */

/*
 * mbuf flags of global significance and layer crossing.
 * Those of only protocol/layer specific significance are to be mapped
 * to M_PROTO[1-12] and cleared at layer handoff boundaries.
 * NB: Limited to the lower 24 bits.
 */
#define M_EXT           0x00000001 /* has associated external storage */
#define M_PKTHDR        0x00000002 /* start of record */ // always set
#define M_EOR           0x00000004 /* end of record */
#define M_RDONLY        0x00000008 /* associated data is marked read-only */
#define M_BCAST         0x00000010 /* send/received as link-level broadcast */
#define M_MCAST         0x00000020 /* send/received as link-level multicast */
#define M_PROMISC       0x00000040 /* packet was not for us */
#define M_VLANTAG       0x00000080 /* ether_vtag is valid */
#define M_FLOWID        0x00000100 /* deprecated: flowid is valid */
#define M_NOFREE        0x00000200 /* do not free mbuf, embedded in cluster */

#define M_PROTO1        0x00001000 /* protocol-specific */
#define M_PROTO2        0x00002000 /* protocol-specific */
#define M_PROTO3        0x00004000 /* protocol-specific */
#define M_PROTO4        0x00008000 /* protocol-specific */
#define M_PROTO5        0x00010000 /* protocol-specific */
#define M_PROTO6        0x00020000 /* protocol-specific */
#define M_PROTO7        0x00040000 /* protocol-specific */
#define M_PROTO8        0x00080000 /* protocol-specific */
#define M_PROTO9        0x00100000 /* protocol-specific */
#define M_PROTO10       0x00200000 /* protocol-specific */
#define M_PROTO11       0x00400000 /* protocol-specific */
#define M_PROTO12       0x00800000 /* protocol-specific */

/*
 * Flags to purge when crossing layers.
 */
#define M_PROTOFLAGS \
    (M_PROTO1|M_PROTO2|M_PROTO3|M_PROTO4|M_PROTO5|M_PROTO6|M_PROTO7|M_PROTO8|\
     M_PROTO9|M_PROTO10|M_PROTO11|M_PROTO12)

/*
 * Flags preserved when copying m_pkthdr.
 */
#define M_COPYFLAGS \
    (M_PKTHDR|M_EOR|M_RDONLY|M_BCAST|M_MCAST|M_VLANTAG|M_PROMISC| \
     M_PROTOFLAGS)

/*
 * Mbuf flag description for use with printf(9) %b identifier.
 */
#define M_FLAG_BITS \
    "\20\1M_EXT\2M_PKTHDR\3M_EOR\4M_RDONLY\5M_BCAST\6M_MCAST" \
    "\7M_PROMISC\10M_VLANTAG\11M_FLOWID"
#define M_FLAG_PROTOBITS \
    "\15M_PROTO1\16M_PROTO2\17M_PROTO3\20M_PROTO4\21M_PROTO5" \
    "\22M_PROTO6\23M_PROTO7\24M_PROTO8\25M_PROTO9\26M_PROTO10" \
    "\27M_PROTO11\30M_PROTO12"
#define M_FLAG_PRINTF (M_FLAG_BITS M_FLAG_PROTOBITS)


/*
 * mbuf types describing the content of the mbuf (including external storage).
 */
#define MT_NOTMBUF      0       /* USED INTERNALLY ONLY! Object is not mbuf */
#define MT_DATA         1       /* dynamic (data) allocation */
#define MT_HEADER       MT_DATA /* packet header, use M_PKTHDR instead */

#define MT_VENDOR1      4       /* for vendor-internal use */
#define MT_VENDOR2      5       /* for vendor-internal use */
#define MT_VENDOR3      6       /* for vendor-internal use */
#define MT_VENDOR4      7       /* for vendor-internal use */

#define MT_SONAME       8       /* socket name */

#define MT_EXP1         9       /* for experimental use */
#define MT_EXP2         10      /* for experimental use */
#define MT_EXP3         11      /* for experimental use */
#define MT_EXP4         12      /* for experimental use */

#define MT_CONTROL      14      /* extra-data protocol message */
#define MT_OOBDATA      15      /* expedited data  */
#define MT_NTYPES       16      /* number of mbuf types for mbtypes[] */

#define MT_NOINIT       255     /* Not a type but a flag to allocate
                                   a non-initialized mbuf */

#endif /* (defined(__CONFIG_ARCH_NET_CORE) || !defined(__CONFIG_ARCH_DUAL_CORE)) */

#ifdef __CONFIG_ARCH_DUAL_CORE
/*
 * NB: mbuf is allocated from net core, pointer conversion MUST be done when
 *     transfer mbuf from app core to net core, or vice versa.
 */

#ifdef __CONFIG_ARCH_NET_CORE
/* convert mbuf's pointers in net core, the new mbuf is used by net core */
#define MBUF_APP2NET(m)                                             \
    do {                                                            \
        (m) = (struct mbuf *)DUCC_NETMEM_APP2NET(m);                \
        (m)->m_data = (uint8_t *)DUCC_NETMEM_APP2NET((m)->m_data);  \
    } while (0)

/* convert mbuf's pointers in net core, the new mbuf is used by app core */
#define MBUF_NET2APP(m)                                             \
    do {                                                            \
        (m)->m_data = (uint8_t *)DUCC_NETMEM_NET2APP((m)->m_data);  \
        (m) = (struct mbuf *)DUCC_NETMEM_NET2APP(m);                \
    } while (0)
#endif /* __CONFIG_ARCH_NET_CORE */

#ifdef __CONFIG_ARCH_APP_CORE
/* convert mbuf's pointers in app core, the new mbuf is used by net core */
#define MBUF_APP2NET(m)                                             \
    do {                                                            \
        (m)->m_data = (uint8_t *)DUCC_NETMEM_APP2NET((m)->m_data);  \
        (m) = (struct mbuf *)DUCC_NETMEM_APP2NET(m);                \
    } while (0)

/* convert mbuf's pointers in app core, the new mbuf is used by app core */
#define MBUF_NET2APP(m)                                             \
    do {                                                            \
        (m) = (struct mbuf *)DUCC_NETMEM_NET2APP(m);                \
        (m)->m_data = (uint8_t *)DUCC_NETMEM_NET2APP((m)->m_data);  \
    } while (0)
#endif /* __CONFIG_ARCH_APP_CORE */

#endif /* __CONFIG_ARCH_DUAL_CORE */

#if (defined(__CONFIG_ARCH_NET_CORE) || !defined(__CONFIG_ARCH_DUAL_CORE))

struct mbuf *mb_get(int len, int tx);
void mb_free(struct mbuf *m);
int mb_adj(struct mbuf *m, int req_len);
int mb_copydata(const struct mbuf *m, int off, int len, uint8_t *cp);
struct mbuf *mb_dup(struct mbuf *m);
struct mbuf *mb_pullup(struct mbuf *m, int len); // NOT really support!
struct mbuf *mb_split(struct mbuf *m0, int len0);
int mb_append(struct mbuf *m, int len, const uint8_t *cp);
int mb_reserve(struct mbuf *m, int len, uint16_t headspace, uint16_t tailspace);

#define m_freem(m)              mb_free(m)
#define m_adj(m, l)             mb_adj(m, l)
#define m_copydata(m, o, l, p)  mb_copydata(m, o, l, p)
#define m_dup(m, h)             mb_dup(m)
#define m_pullup(m, l)          mb_pullup(m, l)
#define m_split(m, l, w)        mb_split(m, l)
#define m_append(m, l, c)       mb_append(m, l, c)

#endif /* (defined(__CONFIG_ARCH_NET_CORE) || !defined(__CONFIG_ARCH_DUAL_CORE)) */

/*
 * Macro for type conversion: convert mbuf pointer to data pointer of correct
 * type:
 *
 * mtod(m, t)   -- Convert mbuf pointer to data pointer of correct type.
 */
#define mtod(m, t)          ((t)((m)->m_data))

#if (defined(__CONFIG_ARCH_NET_CORE) || !defined(__CONFIG_ARCH_DUAL_CORE))

/*
 * Compute the amount of space available before the current start of data in
 * an mbuf.
 */
#define M_LEADINGSPACE(m)   ((m)->m_headspace)

/*
 * Compute the amount of space available after the end of data in an mbuf.
 */
#define M_TRAILINGSPACE(m)  ((m)->m_tailspace)


/*
 * Arrange to prepend space of size plen to mbuf m.  If a new mbuf must be
 * allocated, how specifies whether to wait.  If the allocation fails, the
 * original mbuf chain is freed and m is set to NULL.
 */
#define MB_PREPEND(m, plen)                             \
    do {                                                \
        int _plen = (plen);                             \
        if (_plen >= 0 && M_LEADINGSPACE(m) >= _plen) { \
            (m)->m_headspace -= (_plen);                \
            (m)->m_data -= (_plen);                     \
            (m)->m_len += (_plen);                      \
            (m)->m_pkthdr.len += (_plen);               \
        } else {                                        \
            mb_free(m);                                 \
            (m) = NULL;                                 \
        }                                               \
    } while (0)

#define M_PREPEND(m, plen, how) MB_PREPEND(m, plen)

static __inline void m_clrprotoflags(struct mbuf *m)
{
    m->m_flags &= ~M_PROTOFLAGS;
}

/* option of limiting memory usage */
#define MBUF_OPT_LIMIT_MEM  1

#if MBUF_OPT_LIMIT_MEM
/*
 * Flags for @param tx in mb_get(), which also saved in struct mbuf::m_type
 *   - MBUF_GET_FLAG_LIMIT_TX: memory usage limit by MBUF_TX_MEM_MAX
 *   - MBUF_GET_FLAG_LIMIT_RX: memory usage limit by MBUF_RX_MEM_MAX
 */
#define MBUF_GET_FLAG_MASK      (0xF << 4)
#define MBUF_GET_FLAG_LIMIT_TX  (1 << 4)
#define MBUF_GET_FLAG_LIMIT_RX  (1 << 5)

void mb_mem_set_limit(uint32_t tx, uint32_t rx, uint32_t txrx);
void mb_mem_get_limit(uint32_t *tx, uint32_t *rx, uint32_t *txrx);

#else /* MBUF_OPT_LIMIT_MEM */

#define MBUF_GET_FLAG_LIMIT_TX  0
#define MBUF_GET_FLAG_LIMIT_RX  0

#endif /* MBUF_OPT_LIMIT_MEM */

#if 0 // only for test, no need to implement
#define MCLSHIFT    11      /* convert bytes to mbuf clusters */
#define MCLBYTES    (1 << MCLSHIFT) /* size of an mbuf cluster */

/*
 * Concatenate mbuf chain n to m.
 * Both chains must be of the same type (e.g. MT_DATA).
 * Any m_pkthdr is not updated.
 */
void m_cat(struct mbuf *m, struct mbuf *n);
struct mbuf *m_getcl(int how, short type, int flags);
void m_align(struct mbuf *m, int len);
#endif

#endif /* (defined(__CONFIG_ARCH_NET_CORE) || !defined(__CONFIG_ARCH_DUAL_CORE)) */

#ifdef __cplusplus
}
#endif

#endif /* (__CONFIG_MBUF_IMPL_MODE == 0) */
#endif /* !_SYS_MBUF_0_H_ */
