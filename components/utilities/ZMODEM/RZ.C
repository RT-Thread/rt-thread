#define VERSION "1.03 05-18-86"
#define PUBDIR "/usr/spool/uucppublic"

/*% cc -DNFGVMIN -K -O % -o rz; size rz
 *
 * rz.c By Chuck Forsberg
 *
 *	cc -O rz.c -o rz		USG (3.0) Unix
 * 	cc -O -DV7  rz.c -o rz		Unix V7, BSD 2.8 - 4.3
 *
 *	ln rz rb			For either system
 *
 *	ln rz /usr/bin/rbrmail		For remote mail.  Make this the
 *					login shell. rbrmail then calls
 *					rmail(1) to deliver mail.
 *
 *  Unix is a trademark of Western Electric Company
 *
 * A program for Unix to receive files and commands from computers running
 *  Professional-YAM, PowerCom, YAM, IMP, or programs supporting XMODEM.
 *  rz uses Unix buffered input to reduce wasted CPU time.
 *
 * Iff the program is invoked by rzCOMMAND, output is piped to 
 * "COMMAND filename"
 *
 *  Some systems (Venix, Coherent, Regulus) may not support tty raw mode
 *  read(2) the same way as Unix. ONEREAD must be defined to force one
 *  character reads for these systems. Added 7-01-84 CAF
 *
 *  Alarm signal handling changed to work with 4.2 BSD 7-15-84 CAF 
 *
 *  NFGVMIN Added 1-13-85 CAF for PC-AT Xenix systems where c_cc[VMIN]
 *  doesn't seem to work (even though it compiles without error!).
 *
 *  USG UNIX (3.0) ioctl conventions courtesy  Jeff Martin
 */
#define zperr vfile

#include "rtthread.h"
#include "finsh.h"
#include "shell.h"	
#include"rtdef.h"
#include <dfs.h>
#include <dfs_file.h>
#include <dfs_posix.h>


#define OK 0
#define FALSE 0
#define TRUE 1
#define ERROR (-1)

#define HOWMANY 133
int Zmodem=0;		/* ZMODEM protocol requested */
int Nozmodem = 0;	/* If invoked as "rb" */
unsigned Baudrate;
#include "rbsb.c"	/* most of the system dependent stuff here */


int fout;

/*
 * Routine to calculate the free bytes on the current file system
 *  ~0 means many free bytes (unknown)
 */
long getfree()
{
	return(~0L);	/* many free bytes ... */
}

char *Extensions[] = {
".A",
".ARC",
".CCC",
".CL",
".CMD",
".COM",
".CRL",
".DAT",
".DIR",
".EXE",
".O",
".OBJ",
".OVL",
".PAG",
".REL",
".SAV",
".SUB",
".SWP",
".SYS",
".TAR",
".UTL",
".a",
".arc",
".com",
".dat",
".o",
".obj",
".ovl",
".sys",
".tar",
""
};

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
#define TIMEOUT (-2)
#define ERRORMAX 5
#define RETRYMAX 5
#define WCEOT (-10)
#define SECSIZ 128	/* cp/m's Magic Number record size */
#define PATHLEN 257	/* ready for 4.2 bsd ? */
#define KSIZE 1024	/* record size with k option */
#define UNIXFILE 0x8000	/* happens to the the S_IFREG file mask bit for stat */

int Lastrx;
int Crcflg;
int Firstsec;
int Eofseen;		/* indicates cpm eof (^Z) has been received */
int errors;
int Restricted=0;	/* restricted; no /.. or ../ in filenames */
int Badclose = 0;	/* Error on last close */ 
#define ONEREAD 1
#ifdef ONEREAD
/* Sorry, Regulus and some others don't work right in raw mode! */
int Readnum = 1;	/* Number of bytes to ask for in read() from modem */
#else
int Readnum = KSIZE;	/* Number of bytes to ask for in read() from modem */
#endif

#define DEFBYTL 2000000000L	/* default rx file size */
long Bytesleft;		/* number of bytes of incoming file left */
long Modtime;		/* Unix style mod time for incoming file */
short Filemode;		/* Unix style mode for incoming file */
char Pathname[PATHLEN];
char *Progname;		/* the name by which we were called */

int Batch=0;
int Wcsmask=0377;
int Topipe=0;
int MakeLCPathname=TRUE;	/* make received pathname lower case */
int Verbose=0;
int Quiet=0;		/* overrides logic that would otherwise set verbose */
int Nflag = 0;		/* Don't really transfer files */
int Rxbinary=FALSE;	/* receive all files in bin mode */
int Thisbinary;		/* current file is to be received in bin mode */
int Blklen;		/* record length of received packets */
char secbuf[KSIZE];
char linbuf[KSIZE];
int Lleft=0;		/* number of characters in linbuf */

char zconv;		/* ZMODEM file conversion request */
char zmanag;		/* ZMODEM file management request */
char ztrans;		/* ZMODEM file transport request */


int purgeline(void);
unsigned short int updcrc(int c, int crc);
int procheader(char *name);
int report(int sct);
int tryz(void);
int rzfiles(void);
int rzfile(void);
int closeit(void);
int zmputs(char *s);
int ackbibi(void);
int wcreceive(int argc, char **argp);
int wcrxpn(char *rpn);
int wcrx(void);
int wcgetsec(char *rxbuf, int maxtime);
int readline(int timeout);
int putsec(char *buf, int n);
int sendline(int c);
int xsendline(int c);
int log(const char *s,...);
int bttyout(int c);
int flushmo(void);
int canit(void);
int sys2(char *s);
int exec2(char *s);

#include "zm.c"


/* called by signal interrupt or terminate to clean things up */
int bibi(int n)
{
	if (Zmodem)
		zmputs(Attn);
	canit(); 
	mode(0);
	return 0;
}

int zrmain(void)
{
	if (wcreceive(0, 0)==ERROR) {
		canit();
		zperr("received error,exit\n");
        return 1;
	}
	return 0;
}


int usage(void)
{
	//rt_kprintf("%s %s for %s by Chuck Forsberg\n",
	 // Progname, VERSION, OS);
	//rt_kprintf("Usage:	rz [-1buv]		(ZMODEM Batch)\n");
	//rt_kprintf("or	rb [-1buv]		(YMODEM Batch)\n");
	//rt_kprintf("or	rz [-1bcv] file		(XMODEM)\n");
	//rt_kprintf("	  -1 For cu(1): Use fd 1 for input\n");
	//rt_kprintf("	  -b Binary transfer for all files\n");
	//rt_kprintf("	  -u Allow all UPPER CASE names\n");
	//rt_kprintf("	  -v Verbose more v's give more info\n");
	//rt_kprintf("	  -c Use 16 bit CRC	(XMODEM)\n");
	//exit(1);
	return 0;
}
/*
 *  Debugging information output interface routine
 */
/* VARARGS1 */
void vfile(const char *fmt,...)
{
    return;
}

/*
 * Let's receive something already.
 */
int wcreceive(int argc, char **argp)
{
	int c;

	if (Batch || argc==0) {
		Crcflg=(Wcsmask==0377);
		if ( !Quiet)
			rt_kprintf("\nrz: ready...\n");
		c = tryz();
		if (c) {
			if (c == ZCOMPL)
				return OK;
			if (c == ERROR)
				goto fubar;
			c = rzfiles();
			if (c)
				goto fubar;
		} else {
			for (;;) {
				if (wcrxpn(secbuf)== ERROR)
					goto fubar;
				if (secbuf[0]==0)
					return OK;
				if (procheader(secbuf) == ERROR)
					goto fubar;
				if (wcrx()==ERROR)
					goto fubar;
			}
		}
	} else {
		Bytesleft = DEFBYTL; Filemode = 0; Modtime = 0L;

		strcpy(Pathname, *argp);
		//checkpath(Pathname);
		//rt_kprintf(stderr, "\nrz: ready to receive %s ", Pathname);
		//if ((fout=fopen(Pathname, "w")) == NULL)
		//	return ERROR;
		if (wcrx()==ERROR)
			goto fubar;
	}
	return OK;
fubar:
	canit();
	if (Topipe && fout) {
		close(fout);  return ERROR;
	}
	if (fout)
		close(fout);
	if (Restricted) {
		unlink(Pathname);
		rt_kprintf("\r\nrz: %s removed.\r\n", Pathname);
	}
	return ERROR;
}


/*
 * Fetch a pathname from the other end as a C ctyle ASCIZ string.
 * Length is indeterminate as long as less than Blklen
 * A null string represents no more files (YMODEM)
 */
int wcrxpn(char *rpn)
{
	int c;

#ifdef NFGVMIN
	readline(1);
#else
	purgeline();
#endif

et_tu:
	Firstsec=TRUE;  Eofseen=FALSE;
	sendline(Crcflg?WANTCRC:NAK);
	Lleft=0;	/* Do read next time ... */
	while ((c = wcgetsec(rpn, 100)) != 0) {
		log( "Pathname fetch returned %d\n", c);
		if (c == WCEOT) {
			sendline(ACK);
			Lleft=0;	/* Do read next time ... */
			readline(1);
			goto et_tu;
		}
		return ERROR;
	}
	sendline(ACK);
	return OK;
}

/*
 * Adapted from CMODEM13.C, written by
 * Jack M. Wierda and Roderick W. Hart
 */

int wcrx(void)
{
	register int sectnum, sectcurr;
	register char sendchar;
	register char *p;
	int cblklen;			/* bytes to dump this block */

	Firstsec=TRUE;sectnum=0; Eofseen=FALSE;
	sendchar=Crcflg?WANTCRC:NAK;

	for (;;) {
		sendline(sendchar);	/* send it now, we're ready! */
		Lleft=0;	/* Do read next time ... */
		sectcurr=wcgetsec(secbuf, (sectnum&0177)?50:130);
		report(sectcurr);
		if (sectcurr==(sectnum+1 &Wcsmask)) {

			if (sectnum==0 && !Thisbinary) {
				p=secbuf;  sectcurr=Blklen;
				if (*p == 032)	/* A hack for .arc files */
					goto binbin;
				for (; *p != 032 && --sectcurr>=0; ++p)
					if (*p < 07 || (*p & 0200)) {
binbin:
						Thisbinary++;
						if (Verbose)
							rt_kprintf("Changed to BIN\n");
						break;
					}
			}
			sectnum++;
			cblklen = Bytesleft>Blklen ? Blklen:Bytesleft;
			if (putsec(secbuf, cblklen)==ERROR)
				return ERROR;
			if ((Bytesleft-=cblklen) < 0)
				Bytesleft = 0;
			sendchar=ACK;
		}
		else if (sectcurr==(sectnum&Wcsmask)) {
			log( "Received dup Sector\n");
			sendchar=ACK;
		}
		else if (sectcurr==WCEOT) {
			if (closeit())
				return ERROR;
			sendline(ACK);
			Lleft=0;	/* Do read next time ... */
			return OK;
		}
		else if (sectcurr==ERROR)
			return ERROR;
		else {
			log( "Sync Error\n");
			return ERROR;
		}
	}
}

/*
 * Wcgetsec fetches a Ward Christensen type sector.
 * Returns sector number encountered or ERROR if valid sector not received,
 * or CAN CAN received
 * or WCEOT if eot sector
 * time is timeout for first char, set to 4 seconds thereafter
 ***************** NO ACK IS SENT IF SECTOR IS RECEIVED OK **************
 *    (Caller must do that when he is good and ready to get next sector)
 */

int wcgetsec(char *rxbuf, int maxtime)
{
	int checksum, wcj, firstch;
    unsigned short oldcrc;
    char *p;
	int sectcurr;

	for (Lastrx=errors=0; errors<RETRYMAX; errors++) {

		if ((firstch=readline(maxtime))==STX) {
			Blklen=KSIZE; goto get2;
		}
		if (firstch==SOH) {
			Blklen=SECSIZ;
get2:
			sectcurr=readline(1);
			if ((sectcurr+(oldcrc=readline(1)))==Wcsmask) {
				oldcrc=checksum=0;
				for (p=rxbuf,wcj=Blklen; --wcj>=0; ) {
					if ((firstch=readline(1)) < 0)
						goto bilge;
					oldcrc=updcrc(firstch, oldcrc);
					checksum += (*p++ = firstch);
				}
				if ((firstch=readline(1)) < 0)
					goto bilge;
				if (Crcflg) {
					oldcrc=updcrc(firstch, oldcrc);
					if ((firstch=readline(1)) < 0)
						goto bilge;
					oldcrc=updcrc(firstch, oldcrc);
					if (oldcrc & 0xFFFF)
						log("CRC=0%o\n", oldcrc);
					else {
						Firstsec=FALSE;
						return sectcurr;
					}
				}
				else if (((checksum-firstch)&Wcsmask)==0) {
					Firstsec=FALSE;
					return sectcurr;
				}
				else
					log( "Checksum Error\n");
			}
			else
				log("Sector number garbled 0%o 0%o\n",
				 sectcurr, oldcrc);
		}
		/* make sure eot really is eot and not just mixmash */
#ifdef NFGVMIN
		else if (firstch==EOT && readline(1)==TIMEOUT)
			return WCEOT;
#else
		else if (firstch==EOT && Lleft==0)
			return WCEOT;
#endif
		else if (firstch==CAN) {
			if (Lastrx==CAN) {
				log("Sender CANcelled\n");
				return ERROR;
			} else {
				Lastrx=CAN;
				continue;
			}
		}
		else if (firstch==TIMEOUT) {
			if (Firstsec)
				goto humbug;
bilge:
			log( "Timeout\n");
		}
		else
			log( "Got 0%o sector header\n", firstch);

humbug:
		Lastrx=0;
		while(readline(1)!=TIMEOUT)
			;
		if (Firstsec) {
			sendline(Crcflg?WANTCRC:NAK);
			Lleft=0;	/* Do read next time ... */
		} else {
			maxtime=40; sendline(NAK);
			Lleft=0;	/* Do read next time ... */
		}
	}
	/* try to stop the bubble machine. */
	canit();
	return ERROR;
}

/*
 * This version of readline is reasoably well suited for
 * reading many characters.
 *  (except, currently, for the Regulus version!)
 *
 * timeout is in tenths of seconds
 */
int readline(int timeout)
{
	static char *cdq;	/* pointer for removing chars from linbuf */
	static char data_buffer[8];
	if (--Lleft >= 0) 
	{
		return (*cdq++ & Wcsmask);
	}
	while (1)
	{    
     	Lleft = zread(shell->device, 0, data_buffer, 1);
		if (Lleft)
		{
		     Lleft = Lleft;
		     cdq = &data_buffer[0];
             break;
		}
	}

	if (Lleft < 1)
		return TIMEOUT;
	--Lleft;
	return (*cdq++ & Wcsmask);
}



/*
 * Purge the modem input queue of all characters
 */
int purgeline(void)
{

	Lleft = 0;
#ifdef USG
	ioctl(iofd, TCFLSH, 0);
#else
	lseek(iofd, 0L, 2);
#endif
    return 0;
}

/*
 * Update CRC CRC-16 used by XMODEM/CRC, YMODEM, and ZMODEM.
 *  Note: Final result must be masked with 0xFFFF before testing
 *  More efficient table driven routines exist.
 */
unsigned short int 
updcrc(int c, int crc)
{
	int count;

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

/*
 * Process incoming file information header
 */
int procheader(char *name)
{
    char *openmode, *ptr;
	unsigned char i;
	char fname[100];
	/* set default parameters */
	openmode = "w"; Thisbinary=Rxbinary;

	/*
	 *  Process ZMODEM remote file management requests
	 */
	if (zconv == ZCNL)	/* Remote ASCII override */
		Thisbinary = 0;
	if (zconv == ZCBIN)	/* Remote Binary override */
		++Thisbinary;
	else if (zmanag == ZMAPND)
		openmode = "a";
	openmode = openmode;
	Bytesleft = DEFBYTL; Filemode = 0; Modtime = 0L;
	for(i=0;i<100;i++) fname[i] = 0;
	for (i=1,ptr=name;i<strlen(name)+1;i++)	 /* get file name */
	     fname[i]= *ptr++;
	fname[0] = '/';			    /* working_directory */
	if ((fout = open(fname,DFS_O_CREAT|DFS_O_WRONLY,0)) < 0)	 /* create file */
	{
		return ERROR;
	}
	return OK;
}

/* Make string s lower case */
int uncaps(char *s)
{
    return 0;
	/*
	for ( ; *s; ++s)
		if (isupper(*s))
			*s = tolower(*s);
	*/
}


/*
 * IsAnyLower returns TRUE if string s has lower case letters.
 */
int IsAnyLower(char *s)
{
    return 0;
/*
	for ( ; *s; ++s)
		if (islower(*s))
			return TRUE;
	return FALSE;
	*/
}
/*
 * Putsec writes the n characters of buf to receive file fout.
 *  If not in binary mode, carriage returns, and all characters
 *  starting with CPMEOF are discarded.
 */
int putsec(char *buf, int n)
{
	register char *p;

	if (Thisbinary) {
		for (p=buf; --n>=0; )
			write(fout,p++,1);
	}
	else {
		if (Eofseen)
			return OK;
		for (p=buf; --n>=0; ++p ) {
			if ( *p == '\r')
				continue;
			if (*p == CPMEOF) {
				Eofseen=TRUE; return OK;
			}
			write(fout,p,1);
		}
	}
	return OK;
}

/*
 *  Send a character to modem.  Small is beautiful.
 */
int sendline(int c)
{
	zwrite(c);
	return 0;
}

int xsendline(int c)
{
	sendline(c);
	return 0;
}

int flushmo(void) 
{
    return 0;
}




/*
 * substr(string, token) searches for token in string s
 * returns pointer to token within string if found, NULL otherwise
 */
char *
substr(char *s, char *t)
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

/*
 * Log an error
 */
/*VARARGS1*/
int log(const char *s,...)
{
    return 0;
}

/* send cancel string to get the other end to shut up */
int canit(void)
{  /*
	static char canistr[] = {
	 ZPAD,ZPAD,24,24,24,24,24,24,24,24,8,8,8,8,8,8,8,8,8,8,0
	};
	*/
	//printf(canistr);
	Lleft=0;	/* Do read next time ... */
	//fflush(stdout);
	return 0;
}


/*
 * Return 1 iff stdout and stderr are different devices
 *  indicating this program operating with a modem on a
 *  different line
 */
int fromcu(void)
{
	struct stat a, b;
	fstat(1, &a);
    fstat(2, &b);
	//return (a.st_rdev != b.st_rdev);
	return 0;
}

int report(int sct)
{
	//if (Verbose>1)
	//	rt_kprintf(stderr,"%03d%c",sct,sct%10? ' ' : '\r');
	return 0;
}

/*
 * If called as [-][dir/../]vrzCOMMAND set Verbose to 1
 * If called as [-][dir/../]rzCOMMAND set the pipe flag
 * If called as rb use YMODEM protocol
 */
int chkinvok(char *s)
{
	register char *p;

	p = s;
	while (*p == '-')
		s = ++p;
	while (*p)
		if (*p++ == '/')
			s = p;
	if (*s == 'v') {
		Verbose=1; ++s;
	}
	Progname = s;
	if (s[0]=='r' && s[1]=='b')
		Nozmodem = TRUE;
	if (s[2] && s[0]=='r' && s[1]=='b')
		Topipe=TRUE;
	if (s[2] && s[0]=='r' && s[1]=='z')
		Topipe=TRUE;
    return 0;
}

/*
 * Totalitarian Communist pathname processing
 */
int checkpath(char *name)
{
//	if (Restricted) {
	//	if (fopen(name, "r") != NULL) {
		//	canit();
			//rt_kprintf(stderr, "\r\nrz: %s exists\n", name);
		//	bibi();
	//	}
		/* restrict pathnames to current tree or uucppublic */
	//	if ( substr(name, "../")
		// || (name[0]== '/' && strncmp(name, PUBDIR, strlen(PUBDIR))) ) {
		//	canit();
			//rt_kprintf(stderr,"\r\nrz:\tSecurity Violation\r\n");
		//	bibi();
	//	}
//	}
     return 0;
}

/*
 * Initialize for Zmodem receive attempt, try to activate Zmodem sender
 *  Handles ZSINIT frame
 *  Return ZFILE if Zmodem filename received, -1 on error,
 *   ZCOMPL if transaction finished,  else 0
 */
int tryz(void)
{
	int n;
	int cmdzack1flg;

	if (Nozmodem)		/* Check for "rb" program name */
		return 0;
	Rxtimeout = 100;


	for (n=5; --n>=0; ) {
		/* Set buffer length (0) and capability flags */
		stohdr(0L);
		Txhdr[ZF0] = CANFDX|CANOVIO|CANBRK;
		zshhdr(Badclose?ZFERR:ZRINIT, Txhdr);
again:
		switch (zgethdr(Rxhdr, 0)) {
		case ZRQINIT:
			continue;
		case ZEOF:
			continue;
		case TIMEOUT:
			continue;
		case ZFILE:
			zconv = Rxhdr[ZF0];
			zmanag = Rxhdr[ZF1];
			ztrans = Rxhdr[ZF2];
			Badclose = FALSE;
			if (zrbdata(secbuf, KSIZE) == GOTCRCW)
				return ZFILE;
			zshhdr(ZNAK, Txhdr);
		case ZSINIT:
			if (zrbdata(Attn, ZATTNLEN) == GOTCRCW) {
				zshhdr(ZACK, Txhdr);
				goto again;
			}
			zshhdr(ZNAK, Txhdr);
			continue;
		case ZFREECNT:
			stohdr(getfree());
			zshhdr(ZACK, Txhdr);
			goto again;
		case ZCOMMAND:
			cmdzack1flg = Rxhdr[ZF0];
			if (zrbdata(secbuf, KSIZE) == GOTCRCW) {
				if (cmdzack1flg & ZCACK1)
					stohdr(0L);
				else
					stohdr((long)sys2(secbuf));
				purgeline();	/* dump impatient questions */
				do {
					zshhdr(ZCOMPL, Txhdr);
				}
				while (++errors<10 && zgethdr(Rxhdr,1) != ZFIN);
				ackbibi();
				if (cmdzack1flg & ZCACK1)
					exec2(secbuf);
				return ZCOMPL;
			}
			zshhdr(ZNAK, Txhdr); goto again;
		case ZCOMPL:
			goto again;
		default:
			continue;
		case ZFIN:
			ackbibi(); return ZCOMPL;
		case ZCAN:
			return ERROR;
		}
	}
	return 0;
}

/*
 * Receive 1 or more files with ZMODEM protocol
 */
int rzfiles(void)
{
	int c;

	for (;;) {
		switch (c = rzfile()) {
		case ZEOF:
		case ZSKIP:
			switch (tryz()) {
			case ZCOMPL:
				return OK;
			default:
				return ERROR;
			case ZFILE:
				break;
			}
			continue;
		default:
			return c;
		case ERROR:
			return ERROR;
		}
	}
}

/*
 * Receive a file with ZMODEM protocol
 *  Assumes file name frame is in secbuf
 */
int rzfile(void)
{
	int c, n;
	long int rxbytes;

	Eofseen=FALSE;
	if (procheader(secbuf) == ERROR) {
		zshhdr(ZSKIP, Txhdr);
		return ZSKIP;
	}

	n = 10; rxbytes = 0l;

	for (;;) {
		stohdr(rxbytes);
		zshhdr(ZRPOS, Txhdr);
nxthdr:
		switch (c = zgethdr(Rxhdr, 0)) {
		default:
			vfile("rzfile: zgethdr returned %d", c);
			return ERROR;
		case ZNAK:
		case TIMEOUT:
			if ( --n < 0) {
				vfile("rzfile: zgethdr returned %d", c);
				return ERROR;
			}
		case ZFILE:
			continue;
		case ZEOF:
			if (rclhdr(Rxhdr) != rxbytes) {
				continue;
			}
			if (closeit()) {
				Badclose = TRUE;
				vfile("rzfile: closeit returned <> 0");
				return ERROR;
			}
			vfile("rzfile: normal EOF");
			return c;
		case ERROR:	/* Too much garbage in header search error */
			if ( --n < 0) {
				vfile("rzfile: zgethdr returned %d", c);
				return ERROR;
			}
			zmputs(Attn);
			continue;
		case ZDATA:
			n = 10;
			if (rclhdr(Rxhdr) != rxbytes) {
				zmputs(Attn);
				continue;
			}
moredata:
			switch (c = zrbdata(secbuf, KSIZE)) {
			case ZCAN:
				vfile("rzfile: zgethdr returned %d", c);
				return ERROR;
			case ERROR:	/* CRC error */
				if ( --n < 0) {
					vfile("rzfile: zgethdr returned %d", c);
					return ERROR;
				}
				zmputs(Attn);
				continue;
			case TIMEOUT:
				if ( --n < 0) {
					vfile("rzfile: zgethdr returned %d", c);
					return ERROR;
				}
				continue;
			case GOTCRCW:
				putsec(secbuf, Rxcount);
				rxbytes += Rxcount;
				stohdr(rxbytes);
				zshhdr(ZACK, Txhdr);
				goto nxthdr;
			case GOTCRCQ:
				putsec(secbuf, Rxcount);
				rxbytes += Rxcount;
				stohdr(rxbytes);
				zshhdr(ZACK, Txhdr);
				goto moredata;
			case GOTCRCG:
				putsec(secbuf, Rxcount);
				rxbytes += Rxcount;
				goto moredata;
			case GOTCRCE:
				putsec(secbuf, Rxcount);
				rxbytes += Rxcount;
				goto nxthdr;
			}
		}
	}
}

/*
 * Send a string to the modem, processing for \336 (sleep 1 sec)
 *   and \335 (break signal)
 */
int zmputs(char *s)
{
	int c;

	while (*s) {
		switch (c = *s++) {
		case '\336':
			//sleep(1); 
			continue;
		case '\335':
			sendbrk(); continue;
		default:
			sendline(c);
		}
	}
	return 0;
}

/*
 * Close the receive dataset, return OK or ERROR
 */
int closeit(void)
{
	if (Topipe) {
		if (close(fout)) {
			return ERROR;
		}
		return OK;
	}
	if (close(fout)==ERROR) {
		//rt_kprintf(stderr, "file close ERROR\n");
		return ERROR;
	}
//	if (Modtime) {
//		timep[0] = time(NULL);
	//	timep[1] = Modtime;
	//	utime(Pathname, timep);
	//}
	//if (Filemode)
		//chmod(Pathname, (07777 & Filemode));
	return OK;
}

/*
 * Ack a ZFIN packet, let byegones be byegones
 */
int ackbibi(void)
{
	int n;

	vfile("ackbibi:");
	Readnum = 1;
	stohdr(0L);
	for (n=4; --n>=0; ) {
		zshhdr(ZFIN, Txhdr);
		for (;;) {
			switch (readline(100)) {
			case 'O':
				readline(1);	/* Discard 2nd 'O' */
				/* ***** FALL THRU TO ***** */
			case TIMEOUT:
				vfile("ackbibi complete");
				return 0;
			default:
				break;
			}
		}
	}
	return 0;
}

/*
 * Local console output simulation
 */
int bttyout(int c)
{
	//if (Verbose || fromcu)
		//putc(c, stderr);
	return 0;
}

/*
 * Strip leading ! if present, do shell escape. 
 */
int sys2(char *s)
{
	if (*s == '!')
		++s;
	return 0;
}
/*
 * Strip leading ! if present, do exec.
 */
int exec2(char *s)
{
	if (*s == '!')
		++s;
	mode(0);
	return 0;
}
