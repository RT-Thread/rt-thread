#ifndef __RZ_H__
#define __RZ_H__

#include "zmodem.h"


unsigned short int updcrc(int c, unsigned int crc);
void zmputs(char *s);
int closeit(void);
int sys2(char *s);
int exec2(char *s);
int rzfile(void);
void ackbibi(void);
unsigned int IsAnyLower(char *s);
void usage(void);
static int wcrx(void);
char *substr(char *s, char *t);

void alrm(void);
void bibi(int n);
int zreceive_main(void);
void usage(void);
static int wcreceive(unsigned int argc, char **argp);
static int wcrxpn(char *rpn);
static int wcgetsec(char *rxbuf, int maxtime);
int readline(int timeout);
unsigned short int updcrc(int c, unsigned int crc);
int procheader(char *name);
int purgeline(void);
int putsec(char *buf, int n);  
int readline(int timeout);
unsigned short int updcrc(int c, unsigned int crc);

int bttyout(int c);
int sys2(char *s);
int exec2(char *s);
void sendline(char c);
void xsendline(char c);
void canit(void);
int tryz(void);
int rzfiles(void);


extern int Verbose;
extern int iofd;		/* File descriptor for ioctls & reads */
extern int Zmodem;		/* ZMODEM protocol requested */
extern int Nozmodem;	/* If invoked as "rb" */
/* Ward Christensen / CP/M parameters - Don't change these! */
#define ENQ 005
#define CAN ('X'&037)
//#define XOFF ('s'&037)
//#define XON ('q'&037)
#define SOH 1
#define STX 2
#define EOT 4
#define ACK 6
#define NAK 025
#define CPMEOF 032
#define WANTCRC 0103	/* send C not NAK to get crc not checksum */
#define TIMEOUT (-2)
#define ERRORMAX 5
#define RETRYMAX 5
#define WCEOT (-10)
#define SECSIZ 128	/* cp/m's Magic Number record size */
#define PATHLEN 257	/* ready for 4.2 bsd ? */
#define KSIZE 1024	/* record size with k option */
#define UNIXFILE 0x8000	/* happens to the the S_IFREG file mask bit for stat */
/**************************zm.c **************************/








#endif
