#define VERSION "sz 1.03 05-18-86"
#define PUBDIR "/usr/spool/uucppublic"

/*% cc -O -K sz.c -o sz; size sz

 * sz.c By Chuck Forsberg
 *
 *	cc -O sz.c -o sz		USG (SYS III/V) Unix
 * 	cc -O -DV7  sz.c -o sz		Unix Version 7, 2.8 - 4.3 BSD
 *
 *  ******* Some systems (Venix, Coherent, Regulus) do not *******
 *  ******* support tty raw mode read(2) identically to    *******
 *  ******* Unix. ONEREAD must be defined to force one     *******
 *  ******* character reads for these systems.		   *******
 *
 * A program for Unix to send files and commands to computers running
 *  Professional-YAM, PowerCom, YAM, IMP, or programs supporting XMODEM.
 *
 *  Sz uses buffered I/O to greatly reduce CPU time compared to UMODEM.
 *
 *  USG UNIX (3.0) ioctl conventions courtesy Jeff Martin
 */

/*
 * Attention string to be executed by receiver to interrupt streaming data
 *  when an error is detected.  A pause (0336) may be needed before the
 *  ^C (03) or after it.
 */
char Myattn[] = { 03, 0336, 0 };

unsigned updcrc();
char *substr(), *getenv();

#define LOGFILE "/tmp/szlog"
#define zperr vfile

/*
#include <stdio.h>
#include <signal.h>
#include <setjmp.h>
#include <ctype.h>
*/
#include "rtthread.h"
#include "finsh.h"
#include "shell.h"	
#include"rtdef.h"
#include <dfs.h>
#include <dfs_file.h>
#include <dfs_posix.h>
#include "zmodem.h"

#define PATHLEN 256
#define OK 0
#define FALSE 0
#define TRUE 1
#define ERROR (-1)

#define HOWMANY 2
int Zmodem=0;		/* ZMODEM protocol requested */
unsigned Baudrate;
#include "rbsb.c"	/* most of the system dependent stuff here */

int in;

/* Ward Christensen / CP/M parameters - Don't change these! */
#define ENQ 005
#define CAN ('X'&037)
#define XOFF ('s'&037)
#define XON ('q'&037)
#define SOH 1
#define STX 2
#define EOT 4
#define ACK 6
#define NAK 025
#define CPMEOF 032
#define WANTCRC 0103	/* send C not NAK to get crc not checksum */
#define WANTG 0107	/* Send G not NAK to get nonstop batch xmsn */
#define TIMEOUT (-2)
#define RETRYMAX 10
#define SECSIZ 128	/* cp/m's Magic Number record size */
#define KSIZE 1024

char Lastrx;
char Crcflg;
int Wcsmask=0377;
int Verbose=0;
int Modem=0;		/* MODEM - don't send pathnames */
int Restricted=0;	/* restricted; no /.. or ../ in filenames */
int Quiet=0;		/* overrides logic that would otherwise set verbose */
int Ascii=0;		/* Add CR's for brain damaged programs */
int Fullname=0;		/* transmit full pathname */
int Unlinkafter=0;	/* Unlink file after it is sent */
int Dottoslash=0;	/* Change foo.bar.baz to foo/bar/baz */
int firstsec;
int errcnt=0;		/* number of files unreadable */
int blklen=SECSIZ;		/* length of transmitted records */
int Optiong;		/* Let it rip no wait for sector ACK's */
int Noeofseen;
int Totsecs;		/* total number of sectors this file */
char txbuf[KSIZE];
int Filcnt=0;		/* count of number of files opened */
int Lfseen=0;
unsigned Rxbuflen = 16384;	/* Receiver's max buffer length */
int Rxflags = 0;
char Lzconv;	/* Local ZMODEM file conversion request */
char Lzmanag;	/* Local ZMODEM file management request */
char Lztrans;
char zconv;		/* ZMODEM file conversion request */
char zmanag;		/* ZMODEM file management request */
char ztrans;		/* ZMODEM file transport request */
int Command;		/* Send a command, then exit. */
char *Cmdstr;		/* Pointer to the command string */
int Cmdtries = 11;
int Cmdack1;		/* Rx ACKs command, then do it */
int Exitcode;
int Testattn;		/* Force receiver to send Attn, etc with qbf. */
char *qbf="The quick brown fox jumped over the lazy dog's back 1234567890\r\n";


//jmp_buf tohere;		/* For the interrupt on RX timeout */
//jmp_buf intrjmp;	/* For the interrupt on RX CAN */

/* called by signal interrupt or terminate to clean things up */
bibi(n)
{
	canit(); 
	//fflush(stdout); 
	mode(0);
	//rt_kprintf(stderr, "sz: caught signal %d; exiting\n", n);
    //if (n == SIGQUIT)
	//	abort();
	//exit(128+n);
}
/* Called when Zmodem gets an interrupt (^X) */
onintr()
{
	//signal(SIGINT, SIG_IGN);
	//longjmp(intrjmp, -1);
}


//#define sendline(c) putchar(c & Wcsmask)

//#define xsendline(c) putchar(c)
int sendline (int c)
{
	c = c&Wcsmask;
	zwrite(c);

}
int xsendline(int c)
{
     zwrite(c);
}


flushmo()
{
	//fflush(stdout);
}

#include "zm.c"

zsmain(argc, argv)
char *argv[];
{
	register char *cp;
	register npats;
	int agcnt; char **agcv;
	char **patts;
	static char xXbuf[BUFSIZ];

	//if ((cp=getenv("SHELL")) && (substr(cp, "rsh") || substr(cp, "rsh")))
	//	Restricted=TRUE;

	Rxtimeout = 600;
	npats=0;
	/*
	if (argc<2)
		usage();
	//setbuf(stdout, xXbuf);		
	while (--argc) {
		cp = *++argv;
		if (*cp++ == '-' && *cp) {
			while ( *cp) {
				switch(*cp++) {
				case '+':
					Lzmanag = ZMAPND; break;
				case '1':
					iofd = 1; break;
				case '7':
					Wcsmask=0177; break;
				case 'a':
					Lzconv = ZCNL;
					Ascii = TRUE; break;
				case 'b':
					Lzconv = ZCBIN; break;
				case 'C':
					if (--argc < 1) {
						usage();
					}
					Cmdtries = atoi(*++argv);
					break;
				case 'i':
					Cmdack1 = ZCACK1;
					//* **** FALL THROUGH TO ****  
				case 'c':
					if (--argc != 1) {
						usage();
					}
					Command = TRUE;
					Cmdstr = *++argv;
					break;
				case 'd':
					++Dottoslash;
					//* **** FALL THROUGH TO **** * 
				case 'f':
					Fullname=TRUE; break;
				case 'k':
					blklen=KSIZE; break;
				case 'N':
					Lzmanag = ZMCRC;  break;
				case 'n':
					Lzmanag = ZMNEW;  break;
				case 'r':
					Lzconv = ZCRESUM;
				case 'q':
					Quiet=TRUE; Verbose=0; break;
				case 'T':
					Testattn = TRUE; break;
				case 'u':
					++Unlinkafter; break;
				case 'v':
					++Verbose; break;
				case 'X':
					++Modem; break;
				case 'y':
					Lzmanag = ZMCLOB; break;
				default:
					usage();
				}
			}
		}
		else if ( !npats && argc>0) {
			if (argv[0][0]) {
				npats=argc;
				patts=argv;
				if ( !strcmp(*patts, "-"))
					iofd = 1;
			}
		}
	}
	if (npats < 1 && !Command) 
		usage();
	if (Verbose) {
		if (freopen(LOGFILE, "a", stderr)==NULL) {
			printf("Can't open log file %s\n",LOGFILE);
			exit(0200);
		}
		setbuf(stderr, NULL);
	}
	if (fromcu() && !Quiet) {
		if (Verbose == 0)
			Verbose = 2;
	}

	mode(1);

//	if (signal(SIGINT, bibi) == SIG_IGN) {
//		signal(SIGINT, SIG_IGN); signal(SIGKILL, SIG_IGN);
//	}
//	else {
	//	signal(SIGINT, bibi); signal(SIGKILL, bibi);
//		signal(SIGQUIT, bibi);
//	}

	if ( !Modem) {
		if (!Command) {
			printf("rz\r");  fflush(stdout);
		}
		if (!Command && !Quiet && Verbose != 1) {
			rt_kprintf(stderr, "sz: %d file%s requested:\r\n",
			 npats, npats>1?"s":"");
			for ( agcnt=npats, agcv=patts; --agcnt>=0; ) {
				rt_kprintf(stderr, "%s ", *agcv++);
			}
			rt_kprintf(stderr, "\r\n");
			printf("\r\n\bSending in Batch Mode\r\n");
		}
		stohdr(0L);
		if (Command)
			Txhdr[ZF0] = ZCOMMAND;
		zshhdr(ZRQINIT, Txhdr);
	}
	fflush(stdout);
	*/
	if (Command) {
		if (getzrxinit()) {
			Exitcode=0200; canit();
		}
		else if (zsendcmd(Cmdstr, 1+strlen(Cmdstr))) {
			Exitcode=0200; canit();
		}
	} else if (wcsend(npats, patts)==ERROR) {
		Exitcode=0200;
		canit();
	}
	//fflush(stdout);
	//mode(0);
	//exit((errcnt != 0) | Exitcode);
	/*NOTREACHED*/
}

wcsend(argc, argp)
char *argp[];
{
	register n;

	Crcflg=FALSE;
	firstsec=TRUE;
	//for (n=0; n<argc; ++n) {
		Totsecs = 0;
		if (wcs(argp[n])==ERROR)
			return ERROR;
	//}
	Totsecs = 0;
	if (Filcnt==0) {	/* bitch if we couldn't open ANY files */
		//rt_kprintf(stderr,"\r\nCan't open any requested files.\r\n");
		return ERROR;
	}
	if (Zmodem)
		saybibi();
	else
		wctxpn("");
	return OK;
}

wcs(oname)
char *oname;
{
	register c;
	register char *p;
	struct stat f;
	char name[PATHLEN];
	 char *filename ="/tt2.txt";
	 oname = filename;
	strcpy(name, oname);

	if (Restricted) {
		/* restrict pathnames to current tree or uucppublic */
		if ( substr(name, "../")
		 || (name[0]== '/' && strncmp(name, PUBDIR, strlen(PUBDIR))) ) {
			canit();
			//rt_kprintf(stderr,"\r\nsz:\tSecurity Violation\r\n");
			return ERROR;
		}
	}

	//if ( !strcmp(oname, "-")) {
	//	if ((p = getenv("ONAME")) && *p)
		//	strcpy(name, p);
		//else
			//sprintf(name, "s%d.sz", getpid());
/////////////////////////////////////////////////////////////////////////////////////////////////
		//in = stdin;
//	}
	//else if ((in=fopen(oname, "r"))==NULL) {
	//	++errcnt;
		//return OK;	/* pass over it, there may be others */
	//}
	if ((in=open(oname, DFS_O_RDONLY,0)) <0)
	{
	    ++errcnt;
	    return OK;
	}
	++Noeofseen;
	/* Check for directory or block special files */
	fstat(in, &f);
	c = f.st_mode & S_IFMT;
	if (c == S_IFDIR || c == S_IFBLK) {
		close(in);
		return OK;
	}

	++Filcnt;
	switch (wctxpn(name)) {
	case ERROR:
		return ERROR;
	case ZSKIP:
		return OK;
	}
	if (!Zmodem && wctx()==ERROR)
		return ERROR;
	if (Unlinkafter)
		unlink(oname);
	return 0;
}

/*
 * generate and transmit pathname block consisting of
 *  pathname (null terminated),
 *  file length, mode time and file mode in octal
 *  as provided by the Unix fstat call.
 *  N.B.: modifies the passed name, may extend it!
 */
wctxpn(name)
char *name;
{
	register char *p, *q;
	char name2[PATHLEN];
	struct stat f;

	if (Modem) {
		//if ((in!=stdin) && *name && fstat(fileno(in), &f)!= -1) {
		//	rt_kprintf(stderr, "Sending %s, %ld blocks: ",
			 // name, f.st_size>>7);
		//}
		//rt_kprintf(stderr, "Give your local XMODEM receive command now.\r\n");
		return OK;
	}
	logent("\r\nAwaiting pathname nak for %s\r\n", *name?name:"<END>");
	if ( !Zmodem)
		if (getnak())
			return ERROR;

	q = (char *) 0;
	if (Dottoslash) {		/* change . to . */
		for (p=name; *p; ++p) {
			if (*p == '/')
				q = p;
			else if (*p == '.')
				*(q=p) = '/';
		}
		if (q && strlen(++q) > 8) {	/* If name>8 chars */
			q += 8;			/*   make it .ext */
			strcpy(name2, q);	/* save excess of name */
			*q = '.';
			strcpy(++q, name2);	/* add it back */
		}
	}

	for (p=name, q=txbuf ; *p; )
		if ((*q++ = *p++) == '/' && !Fullname)
			q = txbuf;
	*q++ = 0;
	p=q;
	while (q < (txbuf + KSIZE))
		*q++ = 0;
	//if (!Ascii && (in!=stdin) && *name && fstat(fileno(in), &f)!= -1)
		//sprintf(p, "%lu %lo %o", f.st_size, f.st_mtime, f.st_mode);
	fstat(in,&f);
	/* force 1k blocks if name won't fit in 128 byte block */
	if (txbuf[125])
		blklen=KSIZE;
	else {		/* A little goodie for IMP/KMD */
		if (Zmodem)
			blklen = SECSIZ;
		txbuf[127] = f.st_size >>7;
		txbuf[126] = f.st_size >>15;
	}
	if (Zmodem)
		return zsendfile(txbuf, 1+strlen(p)+(p-txbuf));
	if (wcputsec(txbuf, 0, SECSIZ)==ERROR)
		return ERROR;
	return OK;
}

getnak()
{
	register firstch;

	Lastrx = 0;
	for (;;) {
		switch (firstch = readock(800,1)) {
		case ZPAD:
			if (getzrxinit())
				return ERROR;
			Ascii = 0;
			return FALSE;
		case TIMEOUT:
			logent("Timeout on pathname\n");
			return TRUE;
		case WANTG:
			mode(2);	/* Set cbreak, XON/XOFF, etc. */
			Optiong = TRUE;
			blklen=KSIZE;
		case WANTCRC:
			Crcflg = TRUE;
		case NAK:
			return FALSE;
		case CAN:
			if (Lastrx == CAN)
				return TRUE;
		default:
			break;
		}
		Lastrx = firstch;
	}
}


wctx()
{
	register int sectnum, attempts, firstch;

	firstsec=TRUE;

	while ((firstch=readock(400, 2))!=NAK && firstch != WANTCRC
	  && firstch != WANTG && firstch!=TIMEOUT && firstch!=CAN)
		;
	if (firstch==CAN) {
		logent("Receiver CANcelled\n");
		return ERROR;
	}
	if (firstch==WANTCRC)
		Crcflg=TRUE;
	if (firstch==WANTG)
		Crcflg=TRUE;
	sectnum=1;
	while (filbuf(txbuf, blklen)) {
		if (wcputsec(txbuf, sectnum, blklen)==ERROR) {
			return ERROR;
		} else
			sectnum++;
	}
	//if (Verbose>1)
	//	rt_kprintf(stderr, " Closing ");
	close(in);
	attempts=0;
	do {
		logent(" EOT ");
		purgeline();
		sendline(EOT);
		//fflush(stdout);
		++attempts;
	}
		while ((firstch=(readock(100, 1)) != ACK) && attempts < RETRYMAX);
	if (attempts == RETRYMAX) {
		logent("No ACK on EOT\n");
		return ERROR;
	}
	else
		return OK;
}

wcputsec(buf, sectnum, cseclen)
char *buf;
int sectnum;
int cseclen;	/* data length of this sector to send */
{
	register checksum, wcj;
	register char *cp;
	unsigned oldcrc;
	int firstch;
	int attempts;

	firstch=0;	/* part of logic to detect CAN CAN */

	//if (Verbose>1)
	//	rt_kprintf(stderr, "\rSector %3d %2dk ", Totsecs, Totsecs/8 );
	for (attempts=0; attempts <= RETRYMAX; attempts++) {
		Lastrx= firstch;
		sendline(cseclen==KSIZE?STX:SOH);
		sendline(sectnum);
		sendline(-sectnum -1);
		oldcrc=checksum=0;
		for (wcj=cseclen,cp=buf; --wcj>=0; ) {
			sendline(*cp);
			oldcrc=updcrc(*cp, oldcrc);
			checksum += *cp++;
		}
		if (Crcflg) {
			oldcrc=updcrc(0,updcrc(0,oldcrc));
			sendline((int)oldcrc>>8);
			sendline((int)oldcrc);
		}
		else
			sendline(checksum);

		if (Optiong) {
			firstsec = FALSE; return OK;
		}
		firstch = readock(400, (Noeofseen&&sectnum) ? 2:1);
gotnak:
		switch (firstch) {
		case CAN:
			if(Lastrx == CAN) {
cancan:
				logent("Cancelled\n");  return ERROR;
			}
			break;
		case TIMEOUT:
			logent("Timeout on sector ACK\n"); continue;
		case WANTCRC:
			if (firstsec)
				Crcflg = TRUE;
		case NAK:
			logent("NAK on sector\n"); continue;
		case ACK: 
			firstsec=FALSE;
			Totsecs += (cseclen>>7);
			return OK;
		case ERROR:
			logent("Got burst for sector ACK\n"); break;
		default:
			logent("Got %02x for sector ACK\n", firstch); break;
		}
		for (;;) {
			Lastrx = firstch;
			if ((firstch = readock(400, 2)) == TIMEOUT)
				break;
			if (firstch == NAK || firstch == WANTCRC)
				goto gotnak;
			if (firstch == CAN && Lastrx == CAN)
				goto cancan;
		}
	}
	logent("Retry Count Exceeded\n");
	return ERROR;
}

/* fill buf with count chars padding with ^Z for CPM */
filbuf(buf, count)
register char *buf;
{
	register c, m;

	if ( !Ascii) {
		m = read(in, buf, count);
		if (m <= 0)
			return 0;
		while (m < count)
			buf[m++] = 032;
		return count;
	}
	m=count;
	if (Lfseen) {
		*buf++ = 012; --m; Lfseen = 0;
	}
	/////////////////////////////////////////////////////////////////////////////////////
	/*
	while ((c=getc(in))!=EOF) {
		if (c == 012) {
			*buf++ = 015;
			if (--m == 0) {
				Lfseen = TRUE; break;
			}
		}
		*buf++ =c;
		if (--m == 0)
			break;
	}
	*/
	if (m==count)
		return 0;
	else
		while (--m>=0)
			*buf++ = CPMEOF;
	return count;
}
/* fill buf with count chars */
zfilbuf(buf, count)
register char *buf;
{  //int read(int fd, void *buf, size_t len)
	int c, m;
	int res;

	m=count;
	res = 0;
	while (1) {
	    res = read(in,&c,1);
		if (res == 0) break;
		*buf++ =c;
		res = 0;
		if (--m == 0)
			break;
	}
	return (count - m);
}

/* VARARGS1 */
vfile(f, a, b, c)
register char *f;
{
//	if (Verbose > 1) {
	//	rt_kprintf(stderr, f, a, b, c);
	//	rt_kprintf(stderr, "\n");
//	}
}


alarm()
{
	//longjmp(tohere, -1);
}


/*
 * readock(timeout, count) reads character(s) from file descriptor 0
 *  (1 <= count <= 3)
 * it attempts to read count characters. If it gets more than one,
 * it is an error unless all are CAN
 * (otherwise, only normal response is ACK, CAN, or C)
 *  Only looks for one if Optiong, which signifies cbreak, not raw input
 *
 * timeout is in tenths of seconds
 */
readock(timeout, count)
{
	register int c;
	static char byt[5];
	int ch;
	if (Optiong)
		count = 1;	/* Special hack for cbreak */

	//fflush(stdout);
	//if (setjmp(tohere)) {
	//	logent("TIMEOUT\n");
	//	return TIMEOUT;
	//}
    c = 0;
	while (1)
	{
     	  c = zread(shell->device, 0, byt, 1);
          if (c > 0) break;
	}
	//if (Verbose>5)
	//	rt_kprintf(stderr, "ret cnt=%d %x %x\n", c, byt[0], byt[1]);
	if (c<1)
		return TIMEOUT;
	if (c==1)
		return (byt[0]&0377);
	else
		while (c)
			if (byt[--c] != CAN)
				return ERROR;
	return CAN;
}
readline(n)
{
	return (readock(n, 1));
}


purgeline()
{
#ifdef USG
	ioctl(iofd, TCFLSH, 0);
#else
	lseek(iofd, 0L, 2);
#endif
}

/* update CRC */
unsigned
updcrc(c, crc)
register c;
register unsigned crc;
{
	register count;

	for (count=8; --count>=0;) {
		if (crc & 0x8000) {
			crc <<= 1;
			crc += (((c<<=1) & 0400)  !=  0);
			crc ^= 0x1021;
		}
		else {
			crc <<= 1;
			crc += (((c<<=1) & 0400)  !=  0);
		}
	}
	return crc;	
}

/* send cancel string to get the other end to shut up */
canit()
{
	static char canistr[] = {
	 ZPAD,ZPAD,24,24,24,24,24,24,24,24,8,8,8,8,8,8,8,8,8,8,0
	};

	//printf(canistr);
	//fflush(stdout);
}

/*VARARGS1*/
logent(a, b, c)
char *a, *b, *c;
{
//	if(Verbose)
	//	rt_kprintf(stderr, a, b, c);
}

/*
 * return 1 iff stdout and stderr are different devices
 *  indicating this program operating with a modem on a
 *  different line
 */
fromcu()
{
	struct stat a, b;
	fstat(1, &a); fstat(2, &b);
//	return (a.st_rdev != b.st_rdev);
}

/*
 * substr(string, token) searches for token in string s
 * returns pointer to token within string if found, NULL otherwise
 */
char *
substr(s, t)
register char *s,*t;
{
	register char *ss,*tt;
	/* search for first char of token */
	for (ss=s; *s; s++)
		if (*s == *t)
			/* compare token with substring */
			for (ss=s,tt=t; ;) {
				if (*tt == 0)
					return s;
				if (*ss++ != *tt++)
					break;
			}
	return NULL;
}

usage()
{

}

/*
 * Get the receiver's init parameters
 */
getzrxinit()
{
	register n;
	struct stat f;

	for (n=10; --n>=0; ) {
		
		switch (zgethdr(Rxhdr, 1)) {
		case ZCHALLENGE:	/* Echo receiver's challenge numbr */
			stohdr(Rxpos);
			zshhdr(ZACK, Txhdr);
			continue;
		case ZCOMMAND:		/* They didn't see out ZRQINIT */
			stohdr(0L);
			zshhdr(ZRQINIT, Txhdr);
			continue;
		case ZRINIT:
			Rxflags = Rxhdr[ZF0];
			Rxbuflen = Rxhdr[ZP0] + (Rxhdr[ZP1]<<8);
			//signal(SIGINT, SIG_IGN);
			mode(2);	/* Set cbreak, XON/XOFF, etc. */

			/* If using a pipe for testing set lower buf len */
			fstat(iofd, &f);
			if ((f.st_mode & S_IFMT) != S_IFCHR
			  && (Rxbuflen == 0 || Rxbuflen > 4096))
				Rxbuflen = 4096;
			/*
			 * If input is not a regular file, force ACK's each 1024
			 *  (A smarter strategey could be used here ...)
			 */
			fstat(in, &f);
			if (((f.st_mode & S_IFMT) != S_IFREG)
			  && (Rxbuflen == 0 || Rxbuflen > 1024))
				Rxbuflen = 1024;

			return (sendzsinit());
		case ZCAN:
		case TIMEOUT:
			return ERROR;
		case ZRQINIT:
			if (Rxhdr[ZF0] == ZCOMMAND)
				continue;
		default:
			zshhdr(ZNAK, Txhdr);
			continue;
		}
	}
	return ERROR;
}

/* Send send-init information */
sendzsinit()
{
	register c;
	register errors;

	errors = 0;
	for (;;) {
		stohdr(0L);
		zsbhdr(ZSINIT, Txhdr);
		zsbdata(Myattn, 1+strlen(Myattn), ZCRCW);
		c = zgethdr(Rxhdr, 1);
		switch (c) {
		case ZCAN:
			return ERROR;
		case ZACK:
			return OK;
		default:
			if (++errors > 9)
				return ERROR;
			continue;
		}
	}
}

/* Send file name and related info */
zsendfile(buf, blen)
char *buf;
{
	register c;

	for (;;) {
		Txhdr[ZF0] = Lzconv;	/* file conversion request */
		Txhdr[ZF1] = Lzmanag;	/* file management request */
		Txhdr[ZF2] = Lztrans;	/* file transport request */
		Txhdr[ZF3] = 0;
		zsbhdr(ZFILE, Txhdr);
		zsbdata(buf, blen, ZCRCW);
again:
		c = zgethdr(Rxhdr, 1);
		switch (c) {
		case ZRINIT:
			goto again;
		case ZCAN:
		case TIMEOUT:
		case ZABORT:
		case ZFIN:
			return ERROR;
		case ZSKIP:
			close(in); return c;
		case ZRPOS:
			lseek(in, Rxpos, 0);
			Txpos = Rxpos;
			return zsendfdata();
		case ERROR:
		default:
			continue;
		}
	}
}

/* Send the data in the file */
zsendfdata()
{
	register c, e;
	register newcnt;
	register long tcount = 0;
	static int tleft = 6;	/* Counter for test mode */

	if (Baudrate > 300)
		blklen = 256;
	if (Baudrate > 2400)
		blklen = KSIZE;
	if (Rxbuflen && blklen>Rxbuflen)
		blklen = Rxbuflen;
somemore:
	//if (setjmp(intrjmp)) {
waitack:
	//	switch (c = getinsync()) {
	//	default:
	//	case ZCAN:
	//		close(in);
		//	return ERROR;
	//	case ZSKIP:
	//		close(in);
		//	return c;
	//	case ZACK:
	//	case ZRPOS:
	//		break;
	//	}
//	}

	//signal(SIGINT, onintr);
	newcnt = Rxbuflen;
	stohdr(Txpos);
	zsbhdr(ZDATA, Txhdr);

	/*
	 * Special testing mode.  This should force receiver to Attn,ZRPOS
	 *  many times.  Each time the signal should be caught, causing the
	 *  file to be started over from the beginning.
	 */
	if (Testattn) {
		if ( --tleft)
			while (tcount < 20000) {
				//printf(qbf); 
				//fflush(stdout);
				tcount += strlen(qbf);
			}
		//signal(SIGINT, SIG_IGN); 
		canit();
		//sleep(3); 
		purgeline(); mode(0);
		//printf("\nsz: Tcount = %ld\n", tcount);
		if (tleft) {
			//printf("ERROR: Interrupts Not Caught\n");
			//exit(1);
		}
		//exit(0);
	}

	do {
		c = zfilbuf(txbuf, blklen);
		if (c < blklen)
			e = ZCRCE;
		else if (Rxbuflen && (newcnt -= c) <= 0)
			e = ZCRCW;
		else
			e = ZCRCG;
		zsbdata(txbuf, c, e);
		Txpos += c;
		if (e == ZCRCW)
			goto waitack;
#ifdef NOTDEF_DOS
		if ( !carrier()) {
			return ERROR;
		}
		/*
		 * If the reverse channel can be tested for data,
		 *  this logic may be used to detect error packets
		 *  sent by the receiver, in place of setjmp/longjmp
		 *	miready() returns non 0 if a character is available
		 */
		while (miready()) {
			if (readline(1) == ZPAD) {
				zsbdata(U.ubuf, 0, ZCRCW);
				goto somemore;
			}
		}
#endif
	} while (c == blklen);
	//signal(SIGINT, SIG_IGN);

	for (;;) {
		stohdr(Txpos);
		zsbhdr(ZEOF, Txhdr);
		switch (getinsync()) {
		case ZRPOS:
			goto somemore;
		case ZRINIT:
			close(in);
			return OK;
		case ZSKIP:
			close(in);
			return c;
		default:
			close(in);
			return ERROR;
		}
	}
}

/*
 * Respond to receiver's complaint, get back in sync with receiver
 */
getinsync()
{
	register c;

	for (;;) {
		if (Testattn) {
			//printf("\r\n\n\n***** Signal Caught *****\r\n");
			Rxpos = 0; c = ZRPOS;
		} else
			c = zgethdr(Rxhdr, 0);
		switch (c) {
		case ZCAN:
		case ZABORT:
		case ZFIN:
		case TIMEOUT:
			return ERROR;
		case ZRPOS:
			//clearerr(in);	/* In case file EOF seen */
			lseek(in, Rxpos, 0);
			Txpos = Rxpos;
			return c;
		case ZACK:
			return c;
		case ZRINIT:
		case ZSKIP:
			close(in);
			return c;
		case ERROR:
		default:
			zsbhdr(ZNAK, Txhdr);
			continue;
		}
	}
}
/* Say "bibi" to the receiver, try to do it cleanly */
saybibi()
{
	for (;;) {
		stohdr(0L);
		zsbhdr(ZFIN, Txhdr);
		switch (zgethdr(Rxhdr, 0)) {
		case ZFIN:
			sendline('O'); sendline('O'); flushmo();
		case ZCAN:
		case TIMEOUT:
			return;
		}
	}
}

/* Local screen character display function */
bttyout(c)
{
	//if (Verbose)
	//	putc(c, stderr);
}

/* Send command and related info */
zsendcmd(buf, blen)
char *buf;
{
	register c, errors;
	long cmdnum;

//	cmdnum = getpid();
	errors = 0;
	for (;;) {
		stohdr(cmdnum);
		Txhdr[ZF0] = Cmdack1;
		zsbhdr(ZCOMMAND, Txhdr);
		zsbdata(buf, blen, ZCRCW);
listen:
		Rxtimeout = 100;		/* Ten second wait for resp. */
		c = zgethdr(Rxhdr, 1);

		switch (c) {
		case ZRINIT:
			continue;
		case ERROR:
		case TIMEOUT:
			if (++errors > Cmdtries)
				return ERROR;
			continue;
		case ZCAN:
		case ZABORT:
		case ZFIN:
		case ZSKIP:
		case ZRPOS:
			return ERROR;
		default:
			if (++errors > 10)
				return ERROR;
			continue;
		case ZCOMPL:
			Exitcode = Rxpos;
			saybibi();
			return OK;
		case ZRQINIT:
			vfile("******** RZ *******");
			system("rz");
			vfile("******** SZ *******");
			goto listen;
		}
	}
}

