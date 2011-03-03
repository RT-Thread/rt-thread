/* -rev 05-12-86
 * mode function and most of the rest of the system dependent
 * stuff for rb.c and sb.c   This file is #included so the includer
 * can set parameters such as HOWMANY.
 */

int iofd = 0;		/* File descriptor for ioctls & reads */

/*
 * mode(n)
 *  2: set a cbreak, XON/XOFF control mode if using Pro-YAM's -g option
 *  1: save old tty stat, set raw mode 
 *  0: restore original tty mode
 */
int mode(int n)
{
    return 0;
}

int sendbrk()
{
	//ioctl(iofd, TCSBRK, 0);
	return 0;
}
