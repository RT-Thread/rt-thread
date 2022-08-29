/*
 * This test tests if error.h is exist and useble
 *author:ysun@lnxw.com
 */

#include <sys/errno.h>

static int errno_test;

__attribute__((unused)) static int dummy1 = E2BIG;
__attribute__((unused)) static int dummy2 = EACCES;
__attribute__((unused)) static int dummy3 = EADDRINUSE;
__attribute__((unused)) static int dummy4 = EADDRNOTAVAIL;
__attribute__((unused)) static int dummy5 = EAFNOSUPPORT;
__attribute__((unused)) static int dummy6 = EAGAIN;
__attribute__((unused)) static int dummy7 = EALREADY;
__attribute__((unused)) static int dummy8 = EBADF;
#ifdef EBADMSG
__attribute__((unused)) static int dummy9 = EBADMSG;
#endif
__attribute__((unused)) static int dummy10 = EBUSY;
__attribute__((unused)) static int dummy11 = ECANCELED;
__attribute__((unused)) static int dummy12 = ECHILD;
__attribute__((unused)) static int dummy13 = ECONNABORTED;
__attribute__((unused)) static int dummy14 = ECONNREFUSED;
__attribute__((unused)) static int dummy15 = ECONNRESET;
__attribute__((unused)) static int dummy16 = EDEADLK;
__attribute__((unused)) static int dummy17 = EDESTADDRREQ;
__attribute__((unused)) static int dummy18 = EDOM;
__attribute__((unused)) static int dummy19 = EDQUOT;
__attribute__((unused)) static int dummy20 = EEXIST;
__attribute__((unused)) static int dummy21 = EFAULT;
__attribute__((unused)) static int dummy22 = EFBIG;
__attribute__((unused)) static int dummy23 = EHOSTUNREACH;
__attribute__((unused)) static int dummy24 = EIDRM;
__attribute__((unused)) static int dummy25 = EILSEQ;
__attribute__((unused)) static int dummy26 = EINPROGRESS;
__attribute__((unused)) static int dummy27 = EINTR;
__attribute__((unused)) static int dummy28 = EINVAL;
__attribute__((unused)) static int dummy29 = EIO;
__attribute__((unused)) static int dummy30 = EISCONN;
__attribute__((unused)) static int dummy31 = EISDIR;
__attribute__((unused)) static int dummy32 = ELOOP;
__attribute__((unused)) static int dummy33 = EMFILE;
__attribute__((unused)) static int dummy34 = EMLINK;
__attribute__((unused)) static int dummy35 = EMSGSIZE;
__attribute__((unused)) static int dummy36 = EMULTIHOP;
__attribute__((unused)) static int dummy37 = ENAMETOOLONG;
__attribute__((unused)) static int dummy38 = ENETDOWN;
__attribute__((unused)) static int dummy39 = ENETRESET;
__attribute__((unused)) static int dummy40 = ENETUNREACH;
__attribute__((unused)) static int dummy41 = ENFILE;
__attribute__((unused)) static int dummy42 = ENOBUFS;
#ifdef ENODATA
__attribute__((unused)) static int dummy43 = ENODATA;
#endif
__attribute__((unused)) static int dummy44 = ENODEV;
__attribute__((unused)) static int dummy45 = ENOENT;
__attribute__((unused)) static int dummy46 = ENOEXEC;
__attribute__((unused)) static int dummy47 = ENOLCK;
__attribute__((unused)) static int dummy48 = ENOLINK;
__attribute__((unused)) static int dummy49 = ENOMEM;
__attribute__((unused)) static int dummy50 = ENOMSG;
__attribute__((unused)) static int dummy51 = ENOPROTOOPT;
__attribute__((unused)) static int dummy52 = ENOSPC;
#ifdef ENOSR
__attribute__((unused)) static int dummy53 = ENOSR;
#endif
#ifdef ENOSTR
__attribute__((unused)) static int dummy54 = ENOSTR;
#endif
__attribute__((unused)) static int dummy55 = ENOSYS;
__attribute__((unused)) static int dummy56 = ENOTCONN;
__attribute__((unused)) static int dummy57 = ENOTDIR;
__attribute__((unused)) static int dummy58 = ENOTEMPTY;
__attribute__((unused)) static int dummy59 = ENOTSOCK;
__attribute__((unused)) static int dummy60 = ENOTSUP;
__attribute__((unused)) static int dummy61 = ENOTTY;
__attribute__((unused)) static int dummy62 = ENXIO;
__attribute__((unused)) static int dummy63 = EOPNOTSUPP;
__attribute__((unused)) static int dummy64 = EOVERFLOW;
__attribute__((unused)) static int dummy65 = EPERM;
__attribute__((unused)) static int dummy66 = EPIPE;
__attribute__((unused)) static int dummy67 = EPROTO;
__attribute__((unused)) static int dummy68 = EPROTONOSUPPORT;
__attribute__((unused)) static int dummy69 = EPROTOTYPE;
__attribute__((unused)) static int dummy70 = ERANGE;
__attribute__((unused)) static int dummy71 = EROFS;
__attribute__((unused)) static int dummy72 = ESPIPE;
__attribute__((unused)) static int dummy73 = ESRCH;
__attribute__((unused)) static int dummy74 = ESTALE;
#ifdef ETIME
__attribute__((unused)) static int dummy75 = ETIME;
#endif
__attribute__((unused)) static int dummy76 = ETIMEDOUT;
__attribute__((unused)) static int dummy77 = ETXTBSY;
__attribute__((unused)) static int dummy78 = EWOULDBLOCK;
__attribute__((unused)) static int dummy79 = EXDEV;

__attribute__((unused))static int dummyfcn(void)
{
    errno_test = errno;
    return 0;
}
