/*
 * Copyright (c) mlibc & plct lab
 *
 * SPDX-License-Identifier: MIT
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024/8/8   0Bitbiscuits the first version
 */
#ifndef MLIBC_SYS_IOCTL_H__
#define MLIBC_SYS_IOCTL_H__
#ifdef __cplusplus
extern "C" {
#endif

#include <alltypes.h>

#define _IOC(a, b, c, d)    (((a) << 29) | ((b) << 8) | (c) | ((d) << 16))
#define _IOC_NONE           1U
#define _IOC_READ           2U
#define _IOC_WRITE          4U

#define _IO(a, b)           _IOC(_IOC_NONE,(a),(b),0)
#define _IOW(a, b, c)       _IOC(_IOC_WRITE, (a), (b), sizeof(c))
#define _IOR(a, b, c)       _IOC(_IOC_READ, (a), (b), sizeof(c))
#define _IOWR(a, b, c)      _IOC(_IOC_READ | _IOC_WRITE, (a), (b), sizeof(c))

/* Line Discipline Definitions */
#define N_TTY               0
#define N_SLIP              1
#define N_MOUSE             2
#define N_PPP               3
#define N_STRIP             4
#define N_AX25              5
#define N_X25               6
#define N_6PACK             7
#define N_MASC              8
#define N_R3964             9
#define N_PROFIBUS_FDL      10
#define N_IRDA              11
#define N_SMSBLOCK          12
#define N_HDLC              13
#define N_SYNC_PPP          14
#define N_HCI               15
#define N_GIGASET_M101      16
#define N_SLCAN             17
#define N_PPS               18
#define N_V253              19
#define N_CAIF              20
#define N_GSM0710           21
#define N_TI_WL             22
#define N_TRACESINK         23
#define N_TRACEROUTER       24
#define N_NCI               25
#define N_SPEAKUP           26
#define N_NULL              27

/* Definitions for pseudo-terminal (PTY) packet mode flags */
#define TIOCPKT_DATA        0
#define TIOCPKT_FLUSHREAD   1
#define TIOCPKT_FLUSHWRITE  2
#define TIOCPKT_STOP        4
#define TIOCPKT_START       8
#define TIOCPKT_NOSTOP      16
#define TIOCPKT_DOSTOP      32
#define TIOCPKT_IOCTL       64

/*
** Used to check if the transmit FIFO
** buffer of the serial port is empty
*/
#define TIOCSER_TEMT 1

#define SIOCADDRT           0x890B
#define SIOCDELRT           0x890C
#define SIOCRTMSG           0x890D

#define SIOCGIFNAME         0x8910
#define SIOCSIFLINK         0x8911
#define SIOCGIFCONF         0x8912
#define SIOCGIFFLAGS        0x8913
#define SIOCSIFFLAGS        0x8914
#define SIOCGIFADDR         0x8915
#define SIOCSIFADDR         0x8916
#define SIOCGIFDSTADDR      0x8917
#define SIOCSIFDSTADDR      0x8918
#define SIOCGIFBRDADDR      0x8919
#define SIOCSIFBRDADDR      0x891a
#define SIOCGIFNETMASK      0x891b
#define SIOCSIFNETMASK      0x891c
#define SIOCGIFMETRIC       0x891d
#define SIOCSIFMETRIC       0x891e
#define SIOCGIFMEM          0x891f
#define SIOCSIFMEM          0x8920
#define SIOCGIFMTU          0x8921
#define SIOCSIFMTU          0x8922
#define SIOCSIFNAME         0x8923
#define SIOCSIFHWADDR       0x8924
#define SIOCGIFENCAP        0x8925
#define SIOCSIFENCAP        0x8926
#define SIOCGIFHWADDR       0x8927
#define SIOCGIFSLAVE        0x8929
#define SIOCSIFSLAVE        0x8930
#define SIOCADDMULTI        0x8931
#define SIOCDELMULTI        0x8932
#define SIOCGIFINDEX        0x8933
#define SIOGIFINDEX         SIOCGIFINDEX
#define SIOCSIFPFLAGS       0x8934
#define SIOCGIFPFLAGS       0x8935
#define SIOCDIFADDR         0x8936
#define SIOCSIFHWBROADCAST  0x8937
#define SIOCGIFCOUNT        0x8938

#define SIOCGIFBR           0x8940
#define SIOCSIFBR           0x8941

#define SIOCGIFTXQLEN       0x8942
#define SIOCSIFTXQLEN       0x8943

#define SIOCDARP            0x8953
#define SIOCGARP            0x8954
#define SIOCSARP            0x8955

#define SIOCDRARP           0x8960
#define SIOCGRARP           0x8961
#define SIOCSRARP           0x8962

#define SIOCGIFMAP          0x8970
#define SIOCSIFMAP          0x8971

#define SIOCADDDLCI         0x8980
#define SIOCDELDLCI         0x8981

#define SIOCDEVPRIVATE      0x89F0
#define SIOCPROTOPRIVATE    0x89E0

#ifndef FIONWRITE
#define FIONWRITE _IOR('f', 121, int) /* get # bytes outstanding in send queue */
#endif

/* Terminal control commands.*/
#define TCGETS              0x5401
#define TCSETS              0x5402
#define TCSETSW             0x5403
#define TCSETSF             0x5404
#define TCGETA              0x5405
#define TCSETA              0x5406
#define TCSETAW             0x5407
#define TCSETAF             0x5408
#define TCSBRK              0x5409
#define TCXONC              0x540A
#define TCFLSH              0x540B
#define TIOCEXCL            0x540C
#define TIOCNXCL            0x540D
#define TIOCSCTTY           0x540E
#define TIOCGPGRP           0x540F
#define TIOCSPGRP           0x5410
#define TIOCOUTQ            0x5411
#define TIOCSTI             0x5412
#define TIOCGWINSZ          0x5413
#define TIOCSWINSZ          0x5414
#define TIOCMGET            0x5415
#define TIOCMBIS            0x5416
#define TIOCMBIC            0x5417
#define TIOCMSET            0x5418
#define TIOCGSOFTCAR        0x5419
#define TIOCSSOFTCAR        0x541A
#define FIONREAD            0x541B
#define TIOCINQ             FIONREAD
#define TIOCLINUX           0x541C
#define TIOCCONS            0x541D
#define TIOCGSERIAL         0x541E
#define TIOCSSERIAL         0x541F
#define TIOCPKT             0x5420
#define FIONBIO             0x5421
#define TIOCNOTTY           0x5422
#define TIOCSETD            0x5423
#define TIOCGETD            0x5424
#define TCSBRKP             0x5425
#define TIOCSBRK            0x5427
#define TIOCCBRK            0x5428
#define TIOCGSID            0x5429
#define TIOCGRS485          0x542E
#define TIOCSRS485          0x542F
#define TIOCGPTN            0x80045430
#define TIOCSPTLCK          0x40045431
#define TIOCGDEV            0x80045432
#define TCGETX              0x5432
#define TCSETX              0x5433
#define TCSETXF             0x5434
#define TCSETXW             0x5435
#define TIOCSIG             0x40045436
#define TIOCVHANGUP         0x5437
#define TIOCGPKT            0x80045438
#define TIOCGPTLCK          0x80045439
#define TIOCGEXCL           0x80045440
#define TIOCGPTPEER         0x5441
#define TIOCGISO7816        0x80285442
#define TIOCSISO7816        0xc0285443

/* File descriptor control commands */
#define FIONCLEX            0x5450
#define FIOCLEX             0x5451
#define FIOASYNC            0x5452
#define FIOQSIZE            0x5460

/* Uart control command */
#define TIOCSERCONFIG       0x5453
#define TIOCSERGWILD        0x5454
#define TIOCSERSWILD        0x5455
#define TIOCGLCKTRMIOS      0x5456
#define TIOCSLCKTRMIOS      0x5457
#define TIOCSERGSTRUCT      0x5458
#define TIOCSERGETLSR       0x5459
#define TIOCSERGETMULTI     0x545A
#define TIOCSERSETMULTI     0x545B
#define TIOCMIWAIT          0x545C
#define TIOCGICOUNT         0x545D

/* Modem control lines */
#define TIOCM_LE            0x001
#define TIOCM_DTR           0x002
#define TIOCM_RTS           0x004
#define TIOCM_ST            0x008
#define TIOCM_SR            0x010
#define TIOCM_CTS           0x020
#define TIOCM_CAR           0x040
#define TIOCM_RNG           0x080
#define TIOCM_DSR           0x100
#define TIOCM_CD            TIOCM_CAR
#define TIOCM_RI            TIOCM_RNG
#define TIOCM_OUT1          0x2000
#define TIOCM_OUT2          0x4000
#define TIOCM_LOOP          0x8000

/* Socket control commands */
#define FIOSETOWN           0x8901
#define SIOCSPGRP           0x8902
#define FIOGETOWN           0x8903
#define SIOCGPGRP           0x8904
#define SIOCATMARK          0x8905
#if __LONG_MAX == 0x7fffffff
#define SIOCGSTAMP          _IOR(0x89, 6, char[16])
#define SIOCGSTAMPNS        _IOR(0x89, 7, char[16])
#else
#define SIOCGSTAMP          0x8906
#define SIOCGSTAMPNS        0x8907
#endif

struct winsize
{
    unsigned short ws_row;
    unsigned short ws_col;
    unsigned short ws_xpixel;
    unsigned short ws_ypixel;
};

int ioctl (int, int, ...);

#ifdef __cplusplus
}
#endif

#endif /* MLIBC_SYS_IOCTL_H__ */
