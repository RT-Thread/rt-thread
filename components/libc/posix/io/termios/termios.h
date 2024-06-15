/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2017/08/30     Bernard      The first version
 * 2021/12/10     linzhenxing  put tty system
 */

#ifndef __TERMIOS_H__
#define __TERMIOS_H__

#include <sys/types.h>
#include <sys/ioctl.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef unsigned char cc_t;
typedef unsigned int speed_t;
typedef unsigned int tcflag_t;

#define NCCS 32

struct termios {
    tcflag_t c_iflag;
    tcflag_t c_oflag;
    tcflag_t c_cflag;
    tcflag_t c_lflag;
    cc_t c_line;
    cc_t c_cc[NCCS];
    speed_t __c_ispeed;
    speed_t __c_ospeed;
};

#ifndef NCC
#define NCC 8

struct termio
{
    unsigned short c_iflag;  /* input mode flags */
    unsigned short c_oflag;  /* output mode flags */
    unsigned short c_cflag;  /* control mode flags */
    unsigned short c_lflag;  /* local mode flags */
    unsigned char c_line;    /* line discipline */
    unsigned char c_cc[NCC]; /* control characters */
};
#endif

/* c_cc characters */
#define VINTR     0
#define VQUIT     1
#define VERASE    2
#define VKILL     3
#define VEOF      4
#define VTIME     5
#define VMIN      6
#define VSWTC     7
#define VSTART    8
#define VSTOP     9
#define VSUSP    10
#define VEOL     11
#define VREPRINT 12
#define VDISCARD 13
#define VWERASE  14
#define VLNEXT   15
#define VEOL2    16

/* c_iflag bits */
#define IGNBRK  0000001
#define BRKINT  0000002
#define IGNPAR  0000004
#define PARMRK  0000010
#define INPCK   0000020
#define ISTRIP  0000040
#define INLCR   0000100
#define IGNCR   0000200
#define ICRNL   0000400
#define IUCLC   0001000
#define IXON    0002000
#define IXANY   0004000
#define IXOFF   0010000
#define IMAXBEL 0020000
#define IUTF8   0040000

/* c_oflag bits */
#define OPOST  0000001
#define OLCUC  0000002
#define ONLCR  0000004

#define OCRNL  0000010
#define ONOCR  0000020
#define ONLRET 0000040

#define OFILL   00000100
#define OFDEL   00000200
#define NLDLY   00001400
#define   NL0   00000000
#define   NL1   00000400
#define   NL2   00001000
#define   NL3   00001400
#define TABDLY  00006000
#define   TAB0  00000000
#define   TAB1  00002000
#define   TAB2  00004000
#define   TAB3  00006000
#define CRDLY   00030000
#define   KCR0  00000000
#define   KCR1  00010000
#define   KCR2  00020000
#define   KCR3  00030000
#define FFDLY   00040000
#define   FF0   00000000
#define   FF1   00040000
#define BSDLY   00100000
#define   BS0   00000000
#define   BS1   00100000
#define VTDLY   00200000
#define   VT0   00000000
#define   VT1   00200000
#define XTABS   01000000

#define B0       0000000
#define B50      0000001
#define B75      0000002
#define B110     0000003
#define B134     0000004
#define B150     0000005
#define B200     0000006
#define B300     0000007
#define B600     0000010
#define B1200    0000011
#define B1800    0000012
#define B2400    0000013
#define B4800    0000014
#define B9600    0000015
#define B19200   0000016
#define B38400   0000017

#define B57600   0010001
#define B115200  0010002
#define B230400  0010003
#define B460800  0010004
#define B500000  0010005
#define B576000  0010006
#define B921600  0010007
#define B1000000 0010010
#define B1152000 0010011
#define B1500000 0010012
#define B2000000 0010013
#define B2500000 0010014
#define B3000000 0010015
#define B3500000 0010016
#define B4000000 0010017

#define CSIZE  0000060
#define CS5    0000000
#define CS6    0000020
#define CS7    0000040
#define CS8    0000060
#define CSTOPB 0000100
#define CREAD  0000200
#define PARENB 0000400
#define PARODD 0001000
#define HUPCL  0002000
#define CLOCAL 0004000

/* c_lflag bits */
#define ISIG    0000001
#define ICANON  0000002
#define XCASE   0000004
#define ECHO    0000010
#define ECHOE   0000020
#define ECHOK   0000040
#define ECHONL  0000100
#define NOFLSH  0000200
#define TOSTOP  0000400
#define ECHOCTL 0001000
#define ECHOPRT 0002000
#define ECHOKE  0004000
#define FLUSHO  0010000
#define PENDIN  0040000
#define IEXTEN  0100000
#define EXTPROC 0200000

#define TCOOFF 0
#define TCOON  1
#define TCIOFF 2
#define TCION  3

#define TCIFLUSH  0
#define TCOFLUSH  1
#define TCIOFLUSH 2

#define TCSANOW   0
#define TCSADRAIN 1
#define TCSAFLUSH 2

#define EXTA    0000016
#define EXTB    0000017
#define CBAUD   0010017
#define CBAUDEX 0010000
#define CIBAUD  002003600000
#define CMSPAR  010000000000
#define CRTSCTS 020000000000

#define XCASE   0000004
#define ECHOCTL 0001000
#define ECHOPRT 0002000
#define ECHOKE  0004000
#define FLUSHO  0010000
#define PENDIN  0040000
#define EXTPROC 0200000

/*  intr=^C     quit=^|     erase=del   kill=^U
    eof=^D      vtime=\0    vmin=\1     sxtc=\0
    start=^Q    stop=^S     susp=^Z     eol=\0
    reprint=^R  discard=^U  werase=^W   lnext=^V
    eol2=\0
*/
#define INIT_C_CC "\003\034\177\025\004\0\1\0\021\023\032\0\022\017\027\026\0"

speed_t cfgetospeed (const struct termios *);
speed_t cfgetispeed (const struct termios *);
int cfsetospeed (struct termios *, speed_t);
int cfsetispeed (struct termios *, speed_t);

int tcgetattr (int, struct termios *);
int tcsetattr (int, int, const struct termios *);

int tcsendbreak (int, int);
int tcdrain (int);
int tcflush (int, int);
int tcflow (int, int);

pid_t tcgetsid (int);

void cfmakeraw(struct termios *);
int cfsetspeed(struct termios *, speed_t);

#ifdef __cplusplus
}
#endif

#endif
