#ifndef __ZDEF_H__
#define __ZDEF_H__

#include <rtthread.h>
#include "crc.h"
#define ZPAD      '*'   /* 052 padding character begins frames */
#define ZDLE      030   /* ctrl-X ZMODEM escape - `ala BISYNC DLE */
#define ZDLEE     (ZDLE^0100)   /* escaped ZDLE as transmitted */
#define ZBIN      'A'   /* binary frame indicator (CRC-16) */
#define ZHEX      'B'   /* hex frame indicator */
#define ZBIN32    'C'   /* binary frame with 32 bit FCS */
#define ZBINR32   'D'   /* RLE packed Binary frame with 32 bit FCS */
#define ZVBIN     'a'   /* binary frame indicator (CRC-16) */
#define ZVHEX     'b'   /* hex frame indicator */
#define ZVBIN32   'c'   /* binary frame with 32 bit FCS */
#define ZVBINR32  'd'   /* RLE packed Binary frame with 32 bit FCS */
#define ZRESC     0176  /* RLE flag/escape character */


/* Frame types */
#define ZRQINIT   0     /* request receive init */
#define ZRINIT    1     /* receive init */
#define ZSINIT    2     /* send init sequence (optional) */
#define ZACK      3     /* ACK to above */
#define ZFILE     4     /* file name from sender */
#define ZSKIP     5     /* ro sender: skip this file */
#define ZNAK      6     /* last packet was garbled */
#define ZABORT    7     /* abort batch transfers */
#define ZFIN      8     /* finish session */
#define ZRPOS     9     /* resume data trans at this position */
#define ZDATA     10    /* data packet(s) follow */
#define ZEOF      11    /* end of file */
#define ZFERR     12    /* fatal Read or Write error Detected */
#define ZCRC      13    /* request for file CRC and response */
#define ZCHALLENGE 14   /* receiver's Challenge */
#define ZCOMPL    15    /* request is complete */
#define ZCAN      16    /* other end canned session with CAN*5 */
#define ZFREECNT  17    /* request for free bytes on filesystem */
#define ZCOMMAND  18    /* command from sending program */

/* ZDLE sequfences */
#define ZCRCE     'h'   /* CRC next, frame ends, header packet follows */
#define ZCRCG     'i'   /* CRC next, frame continues nonstop */
#define ZCRCQ     'j'   /* CRC next, frame continues, ZACK expected */
#define ZCRCW     'k'   /* CRC next, ZACK expected, end of frame */
#define ZRUB0     'l'   /* translate to rubout 0177 */
#define ZRUB1     'm'   /* translate to rubout 0377 */

/* zdlread return values (internal) */
/* -1 is general error, -2 is timeout */
#define GOTOR     0400
#define GOTCRCE   (ZCRCE|GOTOR) /* ZDLE-ZCRCE received */
#define GOTCRCG   (ZCRCG|GOTOR) /* ZDLE-ZCRCG received */
#define GOTCRCQ   (ZCRCQ|GOTOR) /* ZDLE-ZCRCQ received */
#define GOTCRCW   (ZCRCW|GOTOR) /* ZDLE-ZCRCW received */
#define GOTCAN    (GOTOR|030)   /* CAN*5 seen */

/* Byte positions within header array */
#define ZF0       3     /* first flags byte */
#define ZF1       2
#define ZF2       1
#define ZF3       0
#define ZP0       0     /* low order 8 bits of position */
#define ZP1       1
#define ZP2       2
#define ZP3       3     /* high order 8 bits of file position */

/* parameters for ZRINIT header */
#define ZRPXWN    8     /* 9th byte in header contains window size/256 */
#define ZRPXQQ    9     /* 10th to 14th bytes contain quote mask */
/* bit Masks for ZRINIT flags byte ZF0 */
#define CANFDX    0x01  /* rx can send and receive true FDX */
#define CANOVIO   0x02  /* rx can receive data during disk I/O */
#define CANBRK    0x04  /* rx can send a break signal */
#define CANRLE    0x10  /* receiver can decode RLE */
#define CANLZW    0x20  /* receiver can uncompress */
#define CANFC32   0x28  /* receiver can use 32 bit Frame Check */
#define ESCCTL    0x64  /* receiver expects ctl chars to be escaped */
#define ESC8      0xc8  /* receiver expects 8th bit to be escaped */

/* bit Masks for ZRINIT flags byte ZF1 */
#define CANVHDR   01    /* variable headers OK */
#define ZRRQWN    8     /* receiver specified window size in ZRPXWN */
#define ZRRQQQ    16    /* additional control chars to quote in ZRPXQQ  */
#define ZRQNVH    (ZRRQWN|ZRRQQQ)   /* variable len hdr reqd to access info */

/* Parameters for ZSINIT frame */
#define ZATTNLEN  32    /* max length of attention string */
#define ALTCOFF   ZF1   /* offset to alternate canit string, 0 if not used */

/* Parameters for ZFILE frame */
/* Conversion options one of these in ZF0 */
#define ZCBIN     1    /* binary transfer - inhibit conversion */
#define ZCNL      2    /* convert NL to local end of line convention */
#define ZCRESUM   3    /* resume interrupted file transfer */
/* management include options, one of these ored in ZF1 */
#define ZMSKNOLOC 0200 /* skip file if not present at rx */
/* management options, one of these ored in ZF1 */
#define ZMMASK    037  /* mask for the choices below */
#define ZMNEWL    1    /* transfer if source newer or longer */
#define ZMCRC     2    /* transfer if different file CRC or length */
#define ZMAPND    3    /* append contents to existing file (if any) */
#define ZMCLOB    4    /* replace existing file */
#define ZMNEW     5    /* transfer if source newer */
/* number 5 is alive ... */
#define ZMDIFF    6    /* transfer if dates or lengths different */
#define ZMPROT    7    /* protect destination file */
#define ZMCHNG    8    /* change filename if destination exists */
/* transport options, one of these in ZF2 */
#define ZTLZW     1    /* lempel-Ziv compression */
#define ZTRLE     3    /* run Length encoding */
/* extended options for ZF3, bit encoded */
#define ZXSPARS   64   /* encoding for sparse file operations */
#define ZCANVHDR  01   /* variable headers OK */
/* receiver window size override */
#define ZRWOVR    4    /* byte position for receive window override/256 */

/* parameters for ZCOMMAND frame ZF0 (otherwise 0) */
#define ZCACK1    1    /* acknowledge, then do command */
extern char Attn[ZATTNLEN+1];   /* Attention string rx sends to tx on err */

/* globals used by ZMODEM functions */
extern rt_uint8_t  Rxframeind;     /* ZBIN ZBIN32, or ZHEX type of frame */
extern char header_type;           /* type of header received */
extern rt_uint8_t  rx_header[4];   /* received header */
extern rt_uint8_t  tx_header[4];   /* transmitted header */
extern rt_uint8_t  Txfcs32;        /* TRUE means send binary frames with 32 bit FCS */
extern rt_uint16_t Rxcount;        /* count of data bytes received */
extern rt_uint16_t Rxtimeout;      /* tenths of seconds to wait for something */
extern rt_uint32_t Rxpos;          /* received file position */
extern rt_uint32_t Txpos;          /* transmitted file position */
extern rt_uint8_t  Txfcs32;        /* TURE means send binary frames with 32 bit FCS */

/* ward Christensen / CP/M parameters - Don't change these! */
#define ENQ     005
#define CAN     ('X'&037)
#define XOFF    ('s'&037)
#define XON     ('q'&037)
#define SOH     1
#define STX     2
#define ETX     3
#define SYN     026
#define ESC     033
#define WANTG   0107    /* send G not NAK to get nonstop batch xmsn */
#define EOT     4
#define ACK     6
#define NAK     025
#define CPMEOF  032
#define WANTCRC 0103    /* send C not NAK to get crc not checksum */
#define TIMEOUT (-2)
#define RCDO    (-3)
#define GCOUNT  (-4)
#define ERRORMAX 5
#define RETRYMAX 5
#define WCEOT   (-10)





#define BITRATE 115200
#define TX_BUFFER_SIZE  1024
#define RX_BUFFER_SIZE  1024      /* sender or receiver's max buffer size */
extern char ZF0_CMD;              /* local ZMODEM file conversion request */
extern char ZF1_CMD;              /* local ZMODEM file management request */
extern char ZF2_CMD;              /* local ZMODEM file management request */
extern char ZF3_CMD;              /* local ZMODEM file management request */
extern rt_uint32_t Baudrate ;
extern rt_uint32_t Left_bytes;
extern rt_uint32_t Left_sizes;


struct zmodemf
{
    struct rt_semaphore zsem;
    rt_device_t device;
};
extern struct zmodemf zmodem;

struct zfile
{
    char *fname;
    rt_int32_t   fd;
    rt_uint32_t  ctime;
    rt_uint32_t  mode;
    rt_uint32_t  bytes_total;
    rt_uint32_t  bytes_sent;
    rt_uint32_t  bytes_received;
    rt_uint32_t  file_end;

};
extern struct finsh_shell* shell;

#define ZDEBUG 0
/* sz.c */
extern void zs_start(char *path);
/* rz.c */
extern void zr_start(char *path);

/* zcore.c */
extern void zinit_parameter(void);
extern rt_int16_t zget_header(rt_uint8_t *hdr);
extern void zsend_bin_header(rt_uint8_t type, rt_uint8_t *hdr);
extern void zsend_hex_header(rt_uint8_t type, rt_uint8_t *hdr);
extern rt_int16_t zget_data(rt_uint8_t *buf, rt_uint16_t len);
extern void zsend_bin_data(rt_uint8_t *buf, rt_int16_t len, rt_uint8_t frameend);
extern void zput_pos(rt_uint32_t pos);
extern void zget_pos(rt_uint32_t pos);
/* zdevice.c */
extern rt_uint32_t get_device_baud(void);
extern void zsend_byte(rt_uint16_t c);
extern void zsend_line(rt_uint16_t c);
extern rt_int16_t zread_line(rt_uint16_t timeout);
extern void zsend_break(char *cmd);
extern void zsend_can(void);

#endif  /* __ZDEF_H__ */
