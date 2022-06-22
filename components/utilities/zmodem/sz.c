/*
 * File      : sz.c
 * the implemention of sending files to the remote computers
 * through the zmodem protocol.
 * Change Logs:
 * Date           Author       Notes
 * 2011-03-29     itspy
 */

#include <rtthread.h>
#include <finsh.h>
#include <shell.h>
#include <rtdef.h>
#include <dfs.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/statfs.h>
#include "zdef.h"


static rt_uint8_t TX_BUFFER[TX_BUFFER_SIZE];         /* sender buffer */
static rt_uint8_t file_cnt = 0;                      /* count of number of files opened */
static rt_uint8_t Rxflags  = 0;                      /* rx parameter flags */
static rt_uint8_t ZF2_OP;                            /* file transfer option */

void zs_start(char *path);
static void zsend_init(void);
static rt_err_t zsend_files(struct zfile *zf);
static rt_err_t zsend_file(struct zfile *zf, rt_uint8_t *buf, rt_uint16_t len);
static rt_err_t zsend_file_data(struct zfile *zf);
static rt_uint16_t zfill_buffer(struct zfile *zf, rt_uint8_t *buf, rt_uint16_t size);
static rt_err_t zget_sync(void);
static void zsay_bibi(void);




/* start zmodem send process */
void zs_start(char *path)
{
    struct zfile *zf;
    rt_err_t res = RT_ERROR;
    char *p,*q;
    zf = rt_malloc(sizeof(struct zfile));
    if (zf == RT_NULL)
    {
        rt_kprintf("zf: out of memory\r\n");
        return;
    }
    rt_kprintf("\r\nsz: ready...\r\n");    /* here ready to send things */
    rt_memset(zf, 0, sizeof(struct zfile));
    zf->fname = path;
    zf->fd = -1;
    res = zsend_files(zf);
    p = zf->fname;
    for (;;)
    {
        q = strstr(p,"/");
        if (q == RT_NULL)  break;
        p = q+1;
    }
    if (res == RT_EOK)
    {
        rt_kprintf("\r\nfile: %s \r\nsize: %ld bytes\r\nsend completed.\r\n",
                  p,zf->bytes_received);
    }
    else
    {
        rt_kprintf("\r\nfile: %s \r\nsize: 0 bytes\r\nsend failed.\r\n",p);
    }
    rt_free(zf);

    return;
}

/* init the parameters */
static void zsend_init(void)
{
    rt_err_t res = -RT_ERROR;

    zinit_parameter();
    for(;;)          /* wait ZPAD */
    {
        res = zread_line(800);
        if (res == ZPAD) break;
    }
    for (;;)
    {
        res = zget_header(rx_header);
        if (res == ZRINIT) break;
    }
    if ((rx_header[ZF1] & ZRQNVH))
    {
        zput_pos(0x80L);    /* Show we can var header */
        zsend_hex_header(ZRQINIT, tx_header);
    }
    Rxflags = rx_header[ZF0] & 0377;
    if (Rxflags & CANFC32) Txfcs32 = 1;    /* used 32bits CRC check */

    if (ZF2_OP == ZTRLE && (Rxflags & CANRLE))    /* for RLE packet */
         Txfcs32 = 2;
    else
        ZF2_OP = 0;
    /* send SINIT cmd */
    return;
}

/* send files */
static rt_err_t zsend_files(struct zfile *zf)
{
    char *p,*q;
    char *str = "/";
    struct stat finfo;
    rt_err_t res = -RT_ERROR;

    if (zf->fname == RT_NULL)
    {
        rt_kprintf("\r\nerror: no file to be send.\r\n");
        return res;
    }
    if ((zf->fd=open(zf->fname, DFS_O_RDONLY,0)) <0)
    {
        rt_kprintf("\r\ncan not open file:%s\r\n",zf->fname+1);
        return res;
    }

    zf->file_end = 0;
    ++file_cnt;
    /* extract file name */
    p = zf->fname;
    for (;;)
    {
        q = strstr(p,str);
        if (q == RT_NULL)  break;
        p = q+1;
    }
    q = (char*)TX_BUFFER;
    for (;;)
    {
        *q++ = *p++;
        if (*p == 0) break;
    }
    *q++ = 0;
    p=q;
    while (q < (char*)(TX_BUFFER + 1024))
        *q++ = 0;
    /* get file attributes */
    fstat(zf->fd,&finfo);
    Left_sizes += finfo.st_size;
    rt_sprintf(p, "%lu %lo %o 3 %d %ld", (long)finfo.st_size, finfo.st_mtime,
              finfo.st_mode, file_cnt, Left_sizes);
    Left_sizes -= finfo.st_size;
    TX_BUFFER[127] = (finfo.st_size + 127) >>7;
    TX_BUFFER[126] = (finfo.st_size + 127) >>15;

    zsend_init();
    /* start sending files */
    res = zsend_file(zf,TX_BUFFER, (p-(char*)TX_BUFFER)+strlen(p)+1);
    zsay_bibi();
    close(zf->fd);

    return res;
}

/* send file name and related info */
static rt_err_t zsend_file(struct zfile *zf, rt_uint8_t *buf, rt_uint16_t len)
{
    rt_uint8_t cnt;
    rt_err_t res = -RT_ERROR;

    for (cnt=0;cnt<5;cnt++)
    {
        tx_header[ZF0] = ZF0_CMD;               /* file conversion option */
        tx_header[ZF1] = ZF1_CMD;               /* file management option */
        tx_header[ZF2] = (ZF3_CMD|ZF2_OP);      /* file transfer option   */
        tx_header[ZF3] = ZF3_CMD;
        zsend_bin_header(ZFILE, tx_header);
        zsend_bin_data(buf, len, ZCRCW);
loop:
        res = zget_header(rx_header);
        switch (res)
        {
        case ZRINIT:
             while ((res = zread_line(50)) > 0)
             {
                 if (res == ZPAD)
                 {
                    goto loop;
                 }
             }
             break;
        case ZCAN:
        case TIMEOUT:
        case ZABORT:
        case ZFIN:
             break;
        case -RT_ERROR:
        case ZNAK:
             break;
        case ZCRC:                           /* no CRC request */
             goto loop;
        case ZFERR:
        case ZSKIP:
             break;
        case ZRPOS:                          /* here we want */
             zget_pos(Rxpos);
             Txpos = Rxpos;
             return(zsend_file_data(zf));
        default:
             break;
        }
    }

    return res;
}

/* send the file data */
static rt_err_t zsend_file_data(struct zfile *zf)
{
    rt_int16_t cnt;
    rt_uint8_t cmd;
    rt_err_t res = -RT_ERROR;
    /* send ZDATA packet, start to send data */
start_send:
    zput_pos(Txpos);
    zsend_bin_header(ZDATA, tx_header);
    do
    {
        cnt = zfill_buffer(zf,TX_BUFFER,RX_BUFFER_SIZE);
        if (cnt < RX_BUFFER_SIZE )
            cmd = ZCRCE;
        else
            cmd = ZCRCG;
        zsend_bin_data(TX_BUFFER, cnt, cmd);
        zf->bytes_received= Txpos += cnt;
        if (cmd == ZCRCW)
            goto get_syn1;
    } while (cnt == RX_BUFFER_SIZE);
    for (;;)                         /*  get ack and check if send finish */
    {
        zput_pos(Txpos);
        zsend_bin_header(ZEOF, tx_header);
get_syn1:
        res = zget_sync();
        switch (res)
        {
        case ZACK:
             goto get_syn1;
        case ZNAK:
             continue;
        case ZRPOS:                     /* resend here */
             lseek(zf->fd,Txpos,0);
             goto start_send;
        case ZRINIT:                   /*  send finish,then begin to send next file */
             return RT_EOK;
        case ZSKIP:
        case -RT_ERROR:
             return res;
        default:
             return res;
        }
    }
}

/* fill file data to buffer*/
static rt_uint16_t zfill_buffer(struct zfile *zf, rt_uint8_t *buf, rt_uint16_t size)
{
    return (read(zf->fd,buf,size));
}

/* wait sync(ack) from the receiver */
static rt_err_t zget_sync(void)
{
    rt_err_t res = -RT_ERROR;

    for (;;)
    {
        res = zget_header(rx_header);
        switch (res)
        {
        case ZCAN:
        case ZABORT:
        case ZFIN:
        case TIMEOUT:
             return -RT_ERROR;
        case ZRPOS:                  /* get pos, need to resend */
             zget_pos(Rxpos);
             Txpos = Rxpos;
             return res;
        case ZACK:
             return res;
        case ZRINIT:                 /* get ZRINIT indicate that the prev file send completed */
             return res;
        case ZSKIP:
             return res;
        case -RT_ERROR:
        default:
             zsend_bin_header(ZNAK, tx_header);
             continue;
        }
    }
}

/* say "bibi" to the receiver */
static void zsay_bibi(void)
{
    for (;;)
    {
        zput_pos(0L);                         /* reninit position of next file*/
        zsend_hex_header(ZFIN, tx_header);    /* send finished session cmd */
        switch (zget_header(rx_header))
        {
        case ZFIN:
            zsend_line('O');
            zsend_line('O');
        case ZCAN:
        case TIMEOUT:
            return;
        }
    }
}
/* end of sz.c */
