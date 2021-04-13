/*
 * File      : rz.c
 * the core functions of implementing zmodem protocol
 * Change Logs:
 * Date           Author       Notes
 * 2011-03-29     itspy
 */

#include <rtthread.h>
#include <finsh.h>
#include <shell.h>
#include <rtdef.h>
#include <dfs.h>
#include <dfs_file.h>
#include <dfs_posix.h>
#include <stdio.h>
#include "zdef.h"

char ZF0_CMD;                    /* file conversion request */
char ZF1_CMD;                    /* file management request */
char ZF2_CMD;                    /* file transport request */
char ZF3_CMD;
rt_uint8_t   Rxframeind;         /* ZBIN ZBIN32, or ZHEX type of frame */
rt_uint16_t  Rxcount;            /* received count*/
char header_type;                /* header type */
rt_uint8_t   rx_header[4];       /* received header */
rt_uint8_t   tx_header[4];       /* transmitted header */
rt_uint32_t  Rxpos;              /* received file position */
rt_uint32_t  Txpos;              /* transmitted file position */
rt_uint8_t   Txfcs32;            /* TURE means send binary frames with 32 bit FCS */
rt_uint8_t   TxCRC;              /* controls 32 bit CRC being sent */
rt_uint8_t   RxCRC;              /* indicates/controls 32 bit CRC being received */
                                 /* 0 == CRC16,  1 == CRC32,  2 == CRC32 + RLE */
char Attn[ZATTNLEN+1];           /* attention string rx sends to tx on err */

void zinit_parameter(void);
void zsend_bin_header(rt_uint8_t type, rt_uint8_t *hdr);
void zsend_hex_header(rt_uint8_t type, rt_uint8_t *hdr);
void zsend_bin_data(rt_uint8_t *buf, rt_int16_t len, rt_uint8_t frameend);
static rt_int16_t zrec_data16(rt_uint8_t *buf, rt_uint16_t len);
static rt_int16_t zrec_data32(rt_uint8_t *buf, rt_int16_t len);
static rt_int16_t zrec_data32r(rt_uint8_t *buf, rt_int16_t len);
rt_int16_t zget_data(rt_uint8_t *buf, rt_uint16_t len);
rt_int16_t zget_header(rt_uint8_t *hdr);
static rt_int16_t zget_bin_header(rt_uint8_t *hdr);
static rt_int16_t zget_bin_fcs(rt_uint8_t *hdr);
rt_int16_t zget_hex_header(rt_uint8_t *hdr);
static void zsend_ascii(rt_uint8_t c);
void zsend_zdle_char(rt_uint16_t ch);
static rt_int16_t zget_hex(void);
rt_int16_t zread_byte(void);
rt_int16_t zxor_read(void);
void zput_pos(rt_uint32_t pos);
void zget_pos(rt_uint32_t pos);




void zinit_parameter(void)
{
    rt_uint8_t i;

    ZF0_CMD  = CANFC32|CANFDX|CANOVIO;      /*  not chose CANFC32,CANRLE,although it have been supported */
    ZF1_CMD  = 0;                               /* fix header length,not support CANVHDR */
    ZF2_CMD  = 0;
    ZF3_CMD  = 0;
    Rxframeind =0;
    header_type   = 0;
    Rxcount  = 0;
    for (i=0;i<4;i++) rx_header[i] = tx_header[i] = 0;
    Rxpos    = Txpos = 0;
    RxCRC    = 0;
    Txfcs32  = 0;

    return ;
}

/* send binary header */
void zsend_bin_header(rt_uint8_t type, rt_uint8_t *hdr)
{
    rt_uint8_t i;
    rt_uint32_t crc;

    zsend_byte(ZPAD);
    zsend_byte(ZDLE);
    TxCRC = Txfcs32;
    if (TxCRC == 0)
    {
        zsend_byte(ZBIN);
        zsend_zdle_char(type);
        /* add 16bits crc */
        crc = 0L;
        crc = updcrc16(type, 0);
        for (i=0;i<4;i++)
        {
            zsend_zdle_char(*hdr);
            crc = updcrc16((0377 & *hdr++),crc);
        }
        crc = updcrc16(0,updcrc16(0,crc));
        zsend_zdle_char(((int)(crc>>8)));
        zsend_zdle_char(crc);
    }
    else if(TxCRC == 1)
    {
        zsend_byte(ZBIN32);
        zsend_zdle_char(type);
        /* add 32bits crc */
        crc = 0xffffffffL;
        crc = updcrc32(type, crc);
        for (i=0;i<4;i++)
        {
            zsend_zdle_char(*hdr);
            crc = updcrc32((0377 & *hdr++), crc);
        }
        crc = ~crc;
        for (i=0; i<4;i++)
        {
            zsend_zdle_char(crc);
            crc >>= 8;
        }
    }
    else if (TxCRC == 2)
    {
        zsend_byte(ZBINR32);
        zsend_zdle_char(type);
        /* add 32bits crc */
        crc = 0xffffffffL;
        crc = updcrc32(type, crc);
        for (i=0;i<4;i++)
        {
            zsend_zdle_char(*hdr);
            crc = updcrc32((0377 & *hdr++), crc);
        }
        crc = ~crc;
        for (i=0; i<4;i++)
        {
            zsend_zdle_char(crc);
            crc >>= 8;
        }
    }

    return;
}

/* send hex header */
void zsend_hex_header(rt_uint8_t type, rt_uint8_t *hdr)
{
    rt_uint8_t i;
    rt_uint16_t crc;

    zsend_line(ZPAD); zsend_line(ZPAD); zsend_line(ZDLE);
    zsend_line(ZHEX);
    zsend_ascii(type);
    crc = updcrc16(type, 0);
    for (i=0; i<4; i++)
    {
        zsend_ascii(*hdr);
        crc = updcrc16((0377 & *hdr++), crc);
    }
    crc = updcrc16(0,updcrc16(0,crc));
    zsend_ascii(crc>>8);
    zsend_ascii(crc);
    /* send display control cmd */
    zsend_line(015); zsend_line(0212);
    if (type != ZFIN && type != ZACK)
        zsend_line(021);
    TxCRC = 0;               /* clear tx crc type */

    return;
}

/* send binary data,with frameend */
void zsend_bin_data(rt_uint8_t *buf, rt_int16_t len, rt_uint8_t frameend)
{
    rt_int16_t i,c,tmp;
    rt_uint32_t crc;

    if (TxCRC == 0)         /* send binary data with 16bits crc check */
    {
        crc = 0x0L;
        for (i=0;i<len;i++)
        {
            zsend_zdle_char(*buf);
            crc = updcrc16((0377 & *buf++), crc);
        }
        zsend_byte(ZDLE); zsend_byte(frameend);
        crc = updcrc16(frameend, crc);
        crc = updcrc16(0,updcrc16(0,crc));
        zsend_zdle_char(crc>>8);
        zsend_zdle_char(crc);
    }
    else if (TxCRC == 1)   /* send binary data with 32 bits crc check */
    {
        crc = 0xffffffffL;
        for (i=0;i<len;i++)
        {
            c = *buf++ & 0377;
            zsend_zdle_char(c);
            crc = updcrc32(c, crc);
        }
        zsend_byte(ZDLE); zsend_byte(frameend);
        crc = updcrc32(frameend, crc);
        crc = ~crc;
        for (i=0;i<4;i++)
        {
            zsend_zdle_char((int)crc);  crc >>= 8;
        }
    }
    else if (TxCRC == 2)   /* send binary data with 32bits crc check,RLE encode */
    {
        crc = 0xffffffffL;
        tmp = *buf++ & 0377;
        for (i = 0; --len >= 0; ++buf)
        {
           if ((c = *buf & 0377) == tmp && i < 126 && len>0)
           {
              ++i;  continue;
           }
           if (i==0)
           {
               zsend_zdle_char(tmp);
               crc = updcrc32(tmp, crc);
               if (tmp == ZRESC)
               {
                   zsend_zdle_char(0100); crc = updcrc32(0100, crc);
               }
               tmp = c;
           }
           else if (i == 1)
           {
                if (tmp != ZRESC)
                {
                    zsend_zdle_char(tmp); zsend_zdle_char(tmp);
                    crc = updcrc32(tmp, crc);
                    crc = updcrc32(tmp, crc);
                    i = 0; tmp = c;
                }

           }
           else
           {
                zsend_zdle_char(ZRESC); crc = updcrc32(ZRESC, crc);
                if (tmp == 040 && i < 34)
                {
                    i += 036;
                    zsend_zdle_char(i);
                    crc = updcrc32(i, crc);
                }
                else
                {
                    i += 0101;
                    zsend_zdle_char(i); crc = updcrc32(i, crc);
                    zsend_zdle_char(tmp); crc = updcrc32(tmp, crc);
                }
                i = 0; tmp = c;
           }
       }
       zsend_byte(ZDLE); zsend_byte(frameend);
       crc = updcrc32(frameend, crc);
       crc = ~crc;
       for (i=0;i<4;i++)
       {
           zsend_zdle_char(crc);
           crc >>= 8;
       }
    }
    if (frameend == ZCRCW)
        zsend_byte(XON);

    return;
}

/* receive data,with 16bits CRC check */
static rt_int16_t zrec_data16(rt_uint8_t *buf, rt_uint16_t len)
{
    rt_int16_t c,crc_cnt;
    rt_uint16_t crc;
    rt_err_t res = -RT_ERROR;
    rt_uint8_t *p,flag = 0;

    p = buf;
    crc_cnt = 0;  crc = 0L;
    Rxcount = 0;
    while(buf <= p+len)
    {
        if ((res = zread_byte()) & ~0377)
        {
            if (res == GOTCRCE || res == GOTCRCG ||
                res == GOTCRCQ || res == GOTCRCW)
            {
                  c = res;
                  c = res;
                  crc = updcrc16(res&0377, crc);
                  flag = 1;
                  continue;
            }
            else if (res == GOTCAN)  return ZCAN;
            else if (res == TIMEOUT) return TIMEOUT;
            else return res;

        }
        else
        {
           if (flag)
           {
               crc = updcrc16(res, crc);
               crc_cnt++;
               if (crc_cnt < 2) continue;
               if ((crc & 0xffff))
               {
#ifdef ZDEBUG
                     rt_kprintf("error code: CRC16 error \r\n");
#endif
                     return -RT_ERROR;
               }
               return c;
           }
           else
           {
              *buf++ = res;
              Rxcount++;
              crc = updcrc16(res, crc);
           }
        }
    }

    return -RT_ERROR;
}

/* receive data,with 32bits CRC check */
static rt_int16_t zrec_data32(rt_uint8_t *buf, rt_int16_t len)
{
    rt_int16_t c,crc_cnt;
    rt_uint32_t crc;
    rt_err_t res = -RT_ERROR;
    rt_uint8_t *p,flag = 0;

    crc_cnt = 0;   crc = 0xffffffffL;
    Rxcount = 0;
    while (buf <= p+len)
    {
        if ((res = zread_byte()) & ~0377)
        {
            if (res == GOTCRCE || res == GOTCRCG ||
                res == GOTCRCQ || res == GOTCRCW)
            {
                  c = res;
                  crc = updcrc32(res&0377, crc);
                  flag = 1;
                  continue;
            }
            else if (res == GOTCAN)  return ZCAN;
            else if (res == TIMEOUT) return TIMEOUT;
            else return res;

        }
        else
        {
           if (flag)
           {
               crc = updcrc32(res, crc);
               crc_cnt++;
               if (crc_cnt < 4) continue;
               if ((crc & 0xDEBB20E3))
               {
#ifdef ZDEBUG
                     rt_kprintf("error code: CRC32 error \r\n");
#endif
                     return -RT_ERROR;
               }
               return c;
           }
           else
           {
              *buf++ = res;
              Rxcount++;
              crc = updcrc32(res, crc);
           }
        }
    }

    return -RT_ERROR;
}
/* receive data,with RLE encoded,32bits CRC check */
static rt_int16_t zrec_data32r(rt_uint8_t *buf, rt_int16_t len)
{
    rt_int16_t c,crc_cnt;
    rt_uint32_t crc;
    rt_err_t res = -RT_ERROR;
    rt_uint8_t *p,flag = 0;

    crc_cnt = 0; crc = 0xffffffffL;
    Rxcount = 0;
    p = buf;
    while (buf <= p+len)
    {
        if ((res = zread_byte()) & ~0377)
        {
            if (res == GOTCRCE || res == GOTCRCG ||
                res == GOTCRCQ || res == GOTCRCW)
            {
                  c = res;
                  crc = updcrc32(res&0377, crc);
                  flag = 1;
                  continue;
            }
            else if (res == GOTCAN)  return ZCAN;
            else if (res == TIMEOUT) return TIMEOUT;
            else return res;

        }
        else
        {
           if (flag)
           {
               crc = updcrc32(res, crc);
               crc_cnt++;
               if (crc_cnt < 4) continue;
               if ((crc & 0xDEBB20E3))
               {
#ifdef ZDEBUG
                     rt_kprintf("error code: CRC32 error \r\n");
#endif
                     return -RT_ERROR;
               }
               return c;
           }
           else
           {
               crc = updcrc32(res, crc);
               switch (c)
               {
               case 0:
                    if (res == ZRESC)
                    {
                        c = -1;  continue;
                    }
                    *buf++ = res;
                    Rxcount++;
                    continue;
               case -1:
                    if (res >= 040 && res < 0100)
                    {
                        c = res - 035; res = 040;
                        goto spaces;
                    }
                    if (res == 0100)
                    {
                        c = 0;
                        *buf++ = ZRESC;
                        Rxcount++;
                        continue;
                    }
                    c = res;  continue;
               default:
                    c -= 0100;
                    if (c < 1)
                        goto end;
spaces:
                    if ((buf + c) > p+len)
                        goto end;
                    while ( --res >= 0)
                    {
                        *buf++ = res;
                        Rxcount++;
                    }
                    c = 0;  continue;
                }
           }
        }   // if -else

    }
end:
    return -RT_ERROR;
}
rt_int16_t zget_data(rt_uint8_t *buf, rt_uint16_t len)
{
    rt_int16_t res = -RT_ERROR;

    if (RxCRC == 0)
    {
         res = zrec_data16(buf,len);
    }
    else if (RxCRC == 1)
    {
        res = zrec_data32(buf, len);
    }
    else if (RxCRC == 2)
    {
        res = zrec_data32r(buf, len);
    }

    return res;
}
/* get type and cmd of header, fix lenght */
rt_int16_t zget_header(rt_uint8_t *hdr)
{
    rt_int16_t c,prev_char;
    rt_uint32_t bit;
    rt_uint16_t get_can,step_out;

    bit = get_device_baud();                 /* get console baud rate */
    Rxframeind = header_type = 0;
    step_out = 0;
    prev_char = 0xff;
    for (;;)
    {
        c = zread_line(100);
        switch(c)
        {
        case 021:
        case 0221:
             if (prev_char == CAN)   break;
             if (prev_char == ZCRCW)  goto start_again;
             break;
        case RCDO:
             goto end;
        case TIMEOUT:
             if (prev_char == CAN) break;
             if (prev_char == ZCRCW)
             {
                 c = -RT_ERROR; goto end;
             }
             goto end;
        case ZCRCW:
             if (prev_char == CAN) goto start_again;
             break;
        case CAN:
get_can:
             if (++get_can > 5)
             {
                 c = ZCAN; goto end;
             }
             break;
        case ZPAD:
             if (prev_char == CAN)   break;
             if (prev_char == ZCRCW) goto start_again;
             step_out = 1;
             break;
        default:
             if (prev_char == CAN)   break;
             if (prev_char == ZCRCW) goto start_again;
start_again:
             if (--bit == 0)
             {
                 c = GCOUNT; goto end;
             }
             get_can = 0;
             break;
        }
        prev_char = c;
        if (step_out) break;    /* exit loop */
    }
    step_out = get_can = 0;
    for (;;)
    {
        c = zxor_read();
        switch(c)
        {
        case ZPAD:
             break;
        case RCDO:
        case TIMEOUT:
             goto end;
        case ZDLE:
             step_out = 1;
             break;
        default:
             goto start_again;
        }
        if (step_out) break;
    }

    Rxframeind = c = zxor_read();
    switch (c)
    {
    case ZBIN32:
         RxCRC = 1;  c = zget_bin_fcs(hdr); break;
    case ZBINR32:
         RxCRC = 2;  c = zget_bin_fcs(hdr); break;
    case ZBIN:
         RxCRC = 0;  c = zget_bin_header(hdr); break;
    case ZHEX:
         RxCRC = 0;  c = zget_hex_header(hdr); break;
    case CAN:
        goto get_can;
    case RCDO:
    case TIMEOUT:
        goto end;
    default:
        goto start_again;
    }
end:
    return c;
}

/* receive a binary header */
static rt_int16_t zget_bin_header(rt_uint8_t *hdr)
{
    rt_int16_t res, i;
    rt_uint16_t crc;

    if ((res = zread_byte()) & ~0377)
        return res;
    header_type = res;
    crc = updcrc16(res, 0);

    for (i=0;i<4;i++)
    {
        if ((res = zread_byte()) & ~0377)
            return res;
        crc = updcrc16(res, crc);
        *hdr++ = res;
    }
    if ((res = zread_byte()) & ~0377)
        return res;
    crc = updcrc16(res, crc);
    if ((res = zread_byte()) & ~0377)
        return res;
    crc = updcrc16(res, crc);
    if (crc & 0xFFFF)
    {
        rt_kprintf("CRC error\n");
        return -RT_ERROR;
    }

    return header_type;
}

/* receive a binary header,with 32bits FCS */
static rt_int16_t zget_bin_fcs(rt_uint8_t *hdr)
{
    rt_int16_t res, i;
    rt_uint32_t crc;

    if ((res = zread_byte()) & ~0377)
        return res;
    header_type = res;
    crc = 0xFFFFFFFFL;
    crc = updcrc32(res, crc);

    for (i=0;i<4;i++)    /* 4headers */
    {
        if ((res = zread_byte()) & ~0377)
            return res;
        crc = updcrc32(res, crc);
        *hdr++ = res;

    }
    for (i=0;i<4;i++)   /* 4bytes crc */
    {
        if ((res = zread_byte()) & ~0377)
            return res;
        crc = updcrc32(res, crc);

    }
    if (crc != 0xDEBB20E3)
    {
#ifdef ZDEBUG
        rt_kprintf("CRC error\n");
#endif
        return -RT_ERROR;
    }

    return header_type;
}


/* receive a hex style header (type and position) */
rt_int16_t zget_hex_header(rt_uint8_t *hdr)
{
    rt_int16_t res,i;
    rt_uint16_t crc;

    if ((res = zget_hex()) < 0)
        return res;
    header_type = res;
    crc = updcrc16(res, 0);

    for (i=0;i<4;i++)
    {
        if ((res = zget_hex()) < 0)
            return res;
        crc = updcrc16(res, crc);
        *hdr++ = res;
    }
    if ((res = zget_hex()) < 0)
        return res;
    crc = updcrc16(res, crc);
    if ((res = zget_hex()) < 0)
        return res;
    crc = updcrc16(res, crc);
    if (crc & 0xFFFF)
    {
#ifdef ZDEBUG
        rt_kprintf("error code : CRC error\r\n");
#endif
        return -RT_ERROR;
    }
    res = zread_line(100);
    if (res < 0)
        return res;
    res = zread_line(100);
    if (res < 0)
        return res;

    return header_type;
}

/* convert to ascii */
static void zsend_ascii(rt_uint8_t c)
{
    const char hex[] = "0123456789abcdef";

    zsend_line(hex[(c&0xF0)>>4]);
    zsend_line(hex[(c)&0xF]);

    return;
}

/*
 * aend character c with ZMODEM escape sequence encoding.
 */
void zsend_zdle_char(rt_uint16_t ch)
{
    rt_uint16_t res;

    res = ch & 0377;
    switch (res)
    {
    case 0377:
        zsend_byte(res);
        break;
    case ZDLE:
        zsend_byte(ZDLE);
        res ^= 0100;
        zsend_byte(res);
        break;
    case 021:
    case 023:
    case 0221:
    case 0223:
        zsend_byte(ZDLE);
        res ^= 0100;
        zsend_byte(res);
        break;
    default:
        zsend_byte(res);
    }
}

/* decode two lower case hex digits into an 8 bit byte value */
static rt_int16_t zget_hex(void)
{
    rt_int16_t res,n;

    if ((res = zxor_read()) < 0)
        return res;
    n = res - '0';
    if (n > 9)
        n -= ('a' - ':');
    if (n & ~0x0f)
        return -RT_ERROR;
    if ((res = zxor_read()) < 0)
        return res;
    res -= '0';
    if (res > 9)
        res -= ('a' - ':');
    if (res & ~0x0f)
        return -RT_ERROR;
    res += (n<<4);

    return res;
}


/*
 * read a byte, checking for ZMODEM escape encoding
 *  including CAN*5 which represents a quick abort
 */
rt_int16_t zread_byte(void)
{
    register int res;

again:
    /* Quick check for non control characters */
    if ((res = zread_line(100)) & 0140)
        return res;
    switch (res)
    {
    case ZDLE:
        break;
    case 023:
    case 0223:
    case 021:
    case 0221:
        goto again;
    default:
        return res;
    }
again2:
    if ((res = zread_line(100)) < 0)
        return res;
    if (res == CAN && (res = zread_line(100)) < 0)
        return res;
    if (res == CAN && (res = zread_line(100)) < 0)
        return res;
    if (res == CAN && (res = zread_line(100)) < 0)
        return res;
    switch (res)
    {
    case CAN:
         return GOTCAN;
    case ZCRCE:
    case ZCRCG:
    case ZCRCQ:
    case ZCRCW:
         return (res | GOTOR);
    case ZRUB0:
         return 0177;
    case ZRUB1:
         return 0377;
    case 023:
    case 0223:
    case 021:
    case 0221:
         goto again2;
    default:
         if ((res & 0140) ==  0100)
            return (res ^ 0100);
         break;
    }

    return -RT_ERROR;
}

/*
 * @read a character from the modem line with timeout.
 * @eat parity, XON and XOFF characters.
 */
rt_int16_t zxor_read(void)
{
    rt_int16_t res;

    for (;;)
    {
        if ((res = zread_line(100)) < 0)
            return res;
        switch (res &= 0177) {
        case XON:
        case XOFF:
            continue;
        case '\r':
        case '\n':
        case ZDLE:
        default:
            return res;
        }
    }

}

/* put file posistion into the header*/
void zput_pos(rt_uint32_t pos)
{
    tx_header[ZP0] = pos;
    tx_header[ZP1] = pos>>8;
    tx_header[ZP2] = pos>>16;
    tx_header[ZP3] = pos>>24;

    return;
}

/* Recover a long integer from a header */
void zget_pos(rt_uint32_t pos)
{
    Rxpos = (rx_header[ZP3] & 0377);
    Rxpos = (Rxpos << 8) | (rx_header[ZP2] & 0377);
    Rxpos = (Rxpos << 8) | (rx_header[ZP1] & 0377);
    Rxpos = (Rxpos << 8) | (rx_header[ZP0] & 0377);

    return;
}

/* end of zcore.c */
