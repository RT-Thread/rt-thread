/*
 *   Z M . C
 *    ZMODEM protocol primitives
 *    5-18-86  Chuck Forsberg Omen Technology Inc
 *
 * Entry point Functions:
 *	zsbhdr(type, hdr) send binary header
 *	zshhdr(type, hdr) send hex header
 *	zgethdr(hdr, eflag) receive header - binary or hex
 *	zsbdata(buf, len, frameend) send binary data
 *	zrbdata(buf, len) receive binary data
 *	stohdr(pos) store position data in Txhdr
 *	long rclhdr(hdr) recover position offset from header
 */

//#ifndef CANFDX
#include "zmodem.h"
int Rxtimeout = 100;		/* Tenths of seconds to wait for something */
//#endif
#define ERROR (-1)
static char *frametypes[] = {
	"TIMEOUT",
	"ERROR",
	"ZRQINIT",
	"ZRINIT",
	"ZSINIT",
	"ZACK",
	"ZFILE",
	"ZSKIP",
	"ZNAK",
	"ZABORT",
	"ZFIN",
	"ZRPOS",
	"ZDATA",
	"ZEOF",
	"ZFERR",
	"ZCRC",
	"ZCHALLENGE",
	"ZCOMPL",
	"ZCAN",
	"ZFREECNT",
	"ZCOMMAND",
	"ZCACK"
#define FRTYPES 21	/* Total number of frame types in this array */
};

long int rclhdr(char *hdr);
int zputhex(int c);
int zsendline(int c);
int zgethex(void);
int zgeth1(void);
int zrbhdr(char *hdr);
int zrhhdr(char *hdr);
int zdlread(void);
int noxread7(void);


/* Send ZMODEM binary header hdr of type type */
int zsbhdr(int type, char *hdr)
{
	int n;
    unsigned short oldcrc;

	vfile("zsbhdr: %s %lx", frametypes[type+2], rclhdr(hdr));
	xsendline(ZPAD); xsendline(ZDLE); xsendline(ZBIN);

	zsendline(type); oldcrc = updcrc(type, 0);

	for (n=4; --n >= 0;) {
		zsendline(*hdr);
		oldcrc = updcrc(*hdr++, oldcrc);
	}
	oldcrc = updcrc(0,updcrc(0,oldcrc));
	zsendline(oldcrc>>8);
	zsendline(oldcrc);
	if (type != ZDATA)
		flushmo();
	return 0;
}

/* Send ZMODEM HEX header hdr of type type */
int zshhdr(int type, char *hdr)
{
	int n;
    unsigned short oldcrc;

	vfile("zshhdr: %s %lx", frametypes[type+2], rclhdr(hdr));
	
	sendline(ZPAD); sendline(ZPAD); sendline(ZDLE); sendline(ZHEX);
	zputhex(type);

	oldcrc = updcrc(type, 0);
	for (n=4; --n >= 0;) {
		zputhex(*hdr); oldcrc = updcrc(*hdr++, oldcrc);
	}
	oldcrc = updcrc(0,updcrc(0,oldcrc));
	zputhex(oldcrc>>8); zputhex(oldcrc);
	
	/* Make it printable on remote machine */
	sendline(015); sendline(0212);	 /*012*/
	/*
	 * Uncork the remote in case a fake XOFF has stopped data flow
	 */
	if (type != ZFIN)
		sendline(021);
	flushmo();
	return 0;
}

/*
 * Send binary array buf of length length, with ending ZDLE sequence frameend
 */
int zsbdata(char *buf, int length, int frameend)
{
	register unsigned short oldcrc;

	vfile("zsbdata: length=%d end=%x", length, frameend);
	oldcrc = 0;
	for (;--length >= 0;) {
		zsendline(*buf);
		oldcrc = updcrc(*buf++, oldcrc);
	}
	xsendline(ZDLE); xsendline(frameend);
	oldcrc = updcrc(frameend, oldcrc);

	oldcrc = updcrc(0,updcrc(0,oldcrc));
	zsendline(oldcrc>>8);
	zsendline(oldcrc);
	if (frameend == ZCRCW)
		flushmo();
	return 0;
}

/*
 * Receive binary array buf of max length with ending ZDLE sequence
 *  and CRC.  Returns the ending character or error code.
 */
int zrbdata(char *buf, int length)
{
	int c;
    unsigned short oldcrc;
	int d;

	oldcrc = Rxcount = 0;
	for (;;) {
		if ((c = zdlread()) & ~0377) {
			switch (c) {
			case GOTCRCE:
			case GOTCRCG:
			case GOTCRCQ:
			case GOTCRCW:
				oldcrc = updcrc((d=c)&0377, oldcrc);
				if ((c = zdlread()) & ~0377)
					goto badcrc;
				oldcrc = updcrc(c, oldcrc);
				if ((c = zdlread()) & ~0377)
					goto badcrc;
				oldcrc = updcrc(c, oldcrc);
				if (oldcrc & 0xFFFF) {
badcrc:
					zperr("Bad data packet CRC");
					return ERROR;
				}
				vfile("zrbdata: Rxcount = %d ret = %x",
				  Rxcount, d);
				return d;
			case GOTCAN:
				zperr("ZMODEM: Sender Canceled");
				return ZCAN;
			case TIMEOUT:
				zperr("ZMODEM data packet TIMEOUT");
				return c;
			default:
				zperr("ZMODEM bad data packet ret=%x", c);
				return c;
			}
		}
		if (--length < 0) {
			zperr("ZMODEM binary data packet too long");
			return ERROR;
		}
		++Rxcount;
		*buf++ = c;
		oldcrc = updcrc(c, oldcrc);
		continue;
	}
}

/*
 * Read a ZMODEM header to hdr, either binary or hex.
 *  eflag controls local display of non zmodem characters:
 *	0:  no display
 *	1:  display printing characters only
 *	2:  display all non ZMODEM characters
 *  On success, set Zmodem to 1 and return type of header.
 *   Otherwise return negative on error
 */
int zgethdr(char *hdr, int eflag)
{
	int c, n;

	n = Baudrate;	/* Max characters before start of frame */
again:
	Rxframeind = Rxtype = 0;
	switch (c = noxread7()) {
	case TIMEOUT:
		goto fifi;
	case ZDLE:
		if (noxread7() == ZDLE) {
			c = ZCAN; goto fifi;
		}
	/* **** FALL THRU TO **** */
	default:
		if ( --n == 0) {
			zperr("ZMODEM Garbage count exceeded");
			return(ERROR);
		}
		if (eflag && ((c &= 0177) & 0140))
			bttyout(c);
		else if (eflag > 1)
			bttyout(c);
		goto again;
	case ZPAD:
		break;
	}
splat:
	switch (c = noxread7()) {
	case ZPAD:
		goto splat;
	case TIMEOUT:
		goto fifi;
	default:
		goto again;
	case ZDLE:
		break;
	}

	switch (c = noxread7()) {
	case TIMEOUT:
		goto fifi;
	case ZBIN:
		Rxframeind = ZBIN;
		c =  zrbhdr(hdr);
		break;
	case ZHEX:
		Rxframeind = ZHEX;
		c =  zrhhdr(hdr);
		break;
	case ZDLE:
		if (noxread7() == ZDLE) {
			c = ZCAN; goto fifi;
		}
	/* **** FALL THRU TO **** */
	default:
		goto again;
	}
	Rxpos = hdr[ZP3] & 0377;
	Rxpos = (Rxpos<<8) + (hdr[ZP2] & 0377);
	Rxpos = (Rxpos<<8) + (hdr[ZP1] & 0377);
	Rxpos = (Rxpos<<8) + (hdr[ZP0] & 0377);
fifi:
	switch (c) {
	case GOTCAN:
		c = ZCAN;
	/* **** FALL THRU TO **** */
	case ZNAK:
	case ZCAN:
	case ERROR:
	case TIMEOUT:
		zperr("ZMODEM: Got %s header", frametypes[c+2]);
	default:
		if (c >= -2 && c <= FRTYPES)
			vfile("zgethdr: %s %lx", frametypes[c+2], Rxpos);
		else
			vfile("zgethdr: %d %lx", c, Rxpos);
	}
	return c;
}

/* Receive a binary style header (type and position) */
int zrbhdr(char *hdr)
{
	int c, n;
    unsigned short oldcrc;

	if ((c = zdlread()) & ~0377)
		return c;
	Rxtype = c;
	oldcrc = updcrc(c, 0);

	for (n=4; --n >= 0;) {
		if ((c = zdlread()) & ~0377)
			return c;
		oldcrc = updcrc(c, oldcrc);
		*hdr++ = c;
	}
	if ((c = zdlread()) & ~0377)
		return c;
	oldcrc = updcrc(c, oldcrc);
	if ((c = zdlread()) & ~0377)
		return c;
	oldcrc = updcrc(c, oldcrc);
	if (oldcrc & 0xFFFF) {
		zperr("Bad Header CRC"); return ERROR;
	}
	Zmodem = 1;
	return Rxtype;
}

/* Receive a hex style header (type and position) */
int zrhhdr(char *hdr)
{
	int c;
	unsigned short oldcrc;
	int n;

	if ((c = zgethex()) < 0)
		return c;
	Rxtype = c;
	oldcrc = updcrc(c, 0);

	for (n=4; --n >= 0;) {
		if ((c = zgethex()) < 0)
			return c;
		oldcrc = updcrc(c, oldcrc);
		*hdr++ = c;
	}
	if ((c = zgethex()) < 0)
		return c;
	oldcrc = updcrc(c, oldcrc);
	if ((c = zgethex()) < 0)
		return c;
	oldcrc = updcrc(c, oldcrc);
	if (oldcrc & 0xFFFF) {
		zperr("Bad Header CRC"); return ERROR;
	}
	if (readline(1) == '\r')	/* Throw away possible cr/lf */
		readline(1);
	Zmodem = 1; return Rxtype;
}

/* Send a byte as two hex digits */
int zputhex(int c)
{
	static char	digits[]	= "0123456789abcdef";

	if (Verbose>4)
		vfile("zputhex: %x", c);
	sendline(digits[(c&0xF0)>>4]);
	sendline(digits[(c)&0xF]);
	return 0;
}

/* Send character c with ZMODEM escape sequence encoding */
int zsendline(int c)
{
	switch (c & 0377) {
	case ZDLE:
	case 021:
	case 023:
	case 0221:
	case 0223:
		xsendline(ZDLE);
		c ^= 0100;
	/* **** FALL THRU TO **** */
	default:
		xsendline(c);
	}
	return 0;
}

/* Decode two lower case hex digits into an 8 bit byte value */
int zgethex(void)
{
	int c;

	c = zgeth1();
	if (Verbose>4)
		vfile("zgethex: %x", c);
	return c;
}
int zgeth1(void)
{
	int c, n;

	if ((c = noxread7()) < 0)
		return c;
	n = c - '0';
	if (n > 9)
		n -= ('a' - ':');
	if (n & ~0xF)
		return ERROR;
	if ((c = noxread7()) < 0)
		return c;
	c -= '0';
	if (c > 9)
		c -= ('a' - ':');
	if (c & ~0xF)
		return ERROR;
	c += (n<<4);
	return c;
}

/*
 * Read a byte, checking for ZMODEM escape encoding
 *  including CAN-CAN which represents a quick abort
 */
int zdlread(void)
{
	int c;

	if ((c = readline(Rxtimeout)) != ZDLE)
		return c;
	if ((c = readline(Rxtimeout)) < 0)
		return c;
	switch (c) {
	case ZDLE:
		return GOTCAN;
	case ZCRCE:
	case ZCRCG:
	case ZCRCQ:
	case ZCRCW:
		return (c | GOTOR);
	case ZRUB0:
		return 0177;
	case ZRUB1:
		return 0377;
	default:
		if ((c & 0140) ==  0100)
			return (c ^ 0100);
		break;
	}
	zperr("Got bad ZMODEM escape sequence %x", c);
	return ERROR;
}

/*
 * Read a character from the modem line with timeout.
 *  Eat parity, XON and XOFF characters.
 */
int noxread7(void)
{
	int c;

	for (;;) {
		if ((c = readline(Rxtimeout)) < 0)
			return c;
		switch (c &= 0177) {
		case XON:
		case XOFF:
			continue;
		default:
			return c;
		}
	}
}

/* Store long integer pos in Txhdr */
int stohdr(long int pos)
{
	Txhdr[ZP0] = pos;
	Txhdr[ZP1] = pos>>8;
	Txhdr[ZP2] = pos>>16;
	Txhdr[ZP3] = pos>>24;
	return 0;
}

/* Recover a long integer from a header */
long
int rclhdr(char *hdr)
{
    long int l;

	l = (hdr[ZP3] & 0377);
	l = (l << 8) | (hdr[ZP2] & 0377);
	l = (l << 8) | (hdr[ZP1] & 0377);
	l = (l << 8) | (hdr[ZP0] & 0377);
	return l;
}

