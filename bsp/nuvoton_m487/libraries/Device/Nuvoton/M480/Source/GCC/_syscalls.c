//
// This file is part of the uOS++ III distribution
// Parts of this file are from the newlib sources, issued under GPL.
// Copyright (c) 2014 Liviu Ionescu
//

// ----------------------------------------------------------------------------

int errno;
void *__dso_handle __attribute__ ((weak));

// ----------------------------------------------------------------------------

#if !defined(OS_USE_SEMIHOSTING)

#include <_ansi.h>
#include <_syslist.h>
#include <errno.h>
//#include <sys/types.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/times.h>
#include <limits.h>
#include <signal.h>

void
__initialize_args(int* p_argc, char*** p_argv);

// This is the standard default implementation for the routine to
// process args. It returns a single empty arg.
// For semihosting applications, this is redefined to get the real
// args from the debugger. You can also use it if you decide to keep
// some args in a non-volatile memory.

void __attribute__((weak))
__initialize_args(int* p_argc, char*** p_argv)
{
    // By the time we reach this, the data and bss should have been initialised.

    // The strings pointed to by the argv array shall be modifiable by the
    // program, and retain their last-stored values between program startup
    // and program termination. (static, no const)
    static char name[] = "";

    // The string pointed to by argv[0] represents the program name;
    // argv[0][0] shall be the null character if the program name is not
    // available from the host environment. argv[argc] shall be a null pointer.
    // (static, no const)
    static char* argv[2] =
    { name, NULL };

    *p_argc = 1;
    *p_argv = &argv[0];
    return;
}

// These functions are defined here to avoid linker errors in freestanding
// applications. They might be called in some error cases from library
// code.
//
// If you detect other functions to be needed, just let us know
// and we'll add them.

int
raise(int sig __attribute__((unused)))
{
    errno = ENOSYS;
    return -1;
}

int
kill(pid_t pid, int sig);

int
kill(pid_t pid __attribute__((unused)), int sig __attribute__((unused)))
{
    errno = ENOSYS;
    return -1;
}

#endif // !defined(OS_USE_SEMIHOSTING)

// ----------------------------------------------------------------------------

// If you need the empty definitions, remove the -ffreestanding option.

#if __STDC_HOSTED__ == 1

char* __env[1] =
{ 0 };
char** environ = __env;

#if !defined(OS_USE_SEMIHOSTING)

// Forward declarations

int
_chown(const char* path, uid_t owner, gid_t group);

int
_close(int fildes);

int
_execve(char* name, char** argv, char** env);

int
_fork(void);

int
_fstat(int fildes, struct stat* st);

int
_getpid(void);

int
_gettimeofday(struct timeval* ptimeval, void* ptimezone);

int
_isatty(int file);

int
_kill(int pid, int sig);

int
_link(char* existing, char* _new);

int
_lseek(int file, int ptr, int dir);

int
_open(char* file, int flags, int mode);

int
_read(int file, char* ptr, int len);

int
_readlink(const char* path, char* buf, size_t bufsize);

int
_stat(const char* file, struct stat* st);

int
_symlink(const char* path1, const char* path2);

clock_t
_times(struct tms* buf);

int
_unlink(char* name);

int
_wait(int* status);

int
_write(int file, char* ptr, int len);

// Definitions

int __attribute__((weak))
_chown(const char* path __attribute__((unused)),
       uid_t owner __attribute__((unused)), gid_t group __attribute__((unused)))
{
    errno = ENOSYS;
    return -1;
}

int __attribute__((weak))
_close(int fildes __attribute__((unused)))
{
    errno = ENOSYS;
    return -1;
}

int __attribute__((weak))
_execve(char* name __attribute__((unused)), char** argv __attribute__((unused)),
        char** env __attribute__((unused)))
{
    errno = ENOSYS;
    return -1;
}

int __attribute__((weak))
_fork(void)
{
    errno = ENOSYS;
    return -1;
}

int __attribute__((weak))
_fstat(int fildes __attribute__((unused)),
       struct stat* st __attribute__((unused)))
{
    errno = ENOSYS;
    return -1;
}

int __attribute__((weak))
_getpid(void)
{
    errno = ENOSYS;
    return -1;
}

int __attribute__((weak))
_gettimeofday(struct timeval* ptimeval __attribute__((unused)),
              void* ptimezone __attribute__((unused)))
{
    errno = ENOSYS;
    return -1;
}

int __attribute__((weak))
_isatty(int file __attribute__((unused)))
{
    errno = ENOSYS;
    return 0;
}

int __attribute__((weak))
_kill(int pid __attribute__((unused)), int sig __attribute__((unused)))
{
    errno = ENOSYS;
    return -1;
}

int __attribute__((weak))
_link(char* existing __attribute__((unused)),
      char* _new __attribute__((unused)))
{
    errno = ENOSYS;
    return -1;
}

int __attribute__((weak))
_lseek(int file __attribute__((unused)), int ptr __attribute__((unused)),
       int dir __attribute__((unused)))
{
    errno = ENOSYS;
    return -1;
}

int __attribute__((weak))
_open(char* file __attribute__((unused)), int flags __attribute__((unused)),
      int mode __attribute__((unused)))
{
    errno = ENOSYS;
    return -1;
}

int __attribute__((weak))
_read(int file __attribute__((unused)), char* ptr __attribute__((unused)),
      int len __attribute__((unused)))
{
    errno = ENOSYS;
    return -1;
}

int __attribute__((weak))
_readlink(const char* path __attribute__((unused)),
          char* buf __attribute__((unused)), size_t bufsize __attribute__((unused)))
{
    errno = ENOSYS;
    return -1;
}

int __attribute__((weak))
_stat(const char* file __attribute__((unused)),
      struct stat* st __attribute__((unused)))
{
    errno = ENOSYS;
    return -1;
}

int __attribute__((weak))
_symlink(const char* path1 __attribute__((unused)),
         const char* path2 __attribute__((unused)))
{
    errno = ENOSYS;
    return -1;
}

clock_t __attribute__((weak))
_times(struct tms* buf __attribute__((unused)))
{
    errno = ENOSYS;
    return ((clock_t) -1);
}

int __attribute__((weak))
_unlink(char* name __attribute__((unused)))
{
    errno = ENOSYS;
    return -1;
}

int __attribute__((weak))
_wait(int* status __attribute__((unused)))
{
    errno = ENOSYS;
    return -1;
}

int __attribute__((weak))
_write(int file __attribute__((unused)), char* ptr __attribute__((unused)),
       int len __attribute__((unused)))
{
    errno = ENOSYS;
    return -1;
}

// ----------------------------------------------------------------------------

#else // defined(OS_USE_SEMIHOSTING)

// ----------------------------------------------------------------------------

/* Support files for GNU libc.  Files in the system namespace go here.
 Files in the C namespace (ie those that do not start with an
 underscore) go in .c.  */

#include <_ansi.h>
#include <stdint.h>
//#include <sys/types.h>
#include <sys/stat.h>
#include <sys/fcntl.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>
#include <sys/times.h>
#include <errno.h>
#include <reent.h>
#include <unistd.h>
#include <sys/wait.h>
#include <ctype.h>
#include <signal.h>

#include "semihosting.h"

int _kill (int pid, int sig);

void __attribute__((noreturn)) _exit (int status);

// Forward declarations.
int _system (const char*);
int _rename (const char*, const char*);
int _isatty (int);
clock_t _times (struct tms*);
int _gettimeofday (struct timeval *, void*);
int _unlink (const char*);
int _link (void);

int _stat (const char*, struct stat*);

int _fstat (int, struct stat*);
int _swistat (int fd, struct stat* st);
int _getpid (int);
int _close (int);
clock_t _clock (void);
int _swiclose (int);
int _open (const char*, int, ...);
int _swiopen (const char*, int);
int _write (int, char*, int);
int _swiwrite (int, char*, int);
int _lseek (int, int, int);
int _swilseek (int, int, int);
int _read (int, char*, int);
int _swiread (int, char*, int);

void initialise_monitor_handles (void);

void __initialize_args (int* p_argc, char*** p_argv);

static int
checkerror (int);
static int
error (int);
static int
get_errno (void);

// ----------------------------------------------------------------------------

#define ARGS_BUF_ARRAY_SIZE 80
#define ARGV_BUF_ARRAY_SIZE 10

typedef struct
{
    char* pCommandLine;
    int size;
} CommandLineBlock;

void __initialize_args (int* p_argc, char*** p_argv)
{
    // Array of chars to receive the command line from the host
    static char args_buf[ARGS_BUF_ARRAY_SIZE];

    // Array of pointers to store the final argv pointers (pointing
    // in the above array).
    static char* argv_buf[ARGV_BUF_ARRAY_SIZE];

    int argc = 0;
    int isInArgument = 0;

    CommandLineBlock cmdBlock;
    cmdBlock.pCommandLine = args_buf;
    cmdBlock.size = sizeof(args_buf) - 1;

    int ret = call_host (SEMIHOSTING_SYS_GET_CMDLINE, &cmdBlock);
    if (ret == 0)
    {

        // In case the host send more than we can chew, limit the
        // string to our buffer.
        args_buf[ARGS_BUF_ARRAY_SIZE - 1] = '\0';

        // The command line is a null terminated string
        char* p = cmdBlock.pCommandLine;

        int delim = '\0';
        int ch;

        while ((ch = *p) != '\0')
        {
            if (isInArgument == 0)
            {
                if (!isblank(ch))
                {
                    if (argc >= (int) ((sizeof(argv_buf) / sizeof(argv_buf[0])) - 1))
                        break;

                    if (ch == '"' || ch == '\'')
                    {
                        // Remember the delimiter to search for the
                        // corresponding terminator
                        delim = ch;
                        ++p;                        // skip the delimiter
                        ch = *p;
                    }
                    // Remember the arg beginning address
                    argv_buf[argc++] = p;
                    isInArgument = 1;
                }
            }
            else if (delim != '\0')
            {
                if ((ch == delim))
                {
                    delim = '\0';
                    *p = '\0';
                    isInArgument = 0;
                }
            }
            else if (isblank(ch))
            {
                delim = '\0';
                *p = '\0';
                isInArgument = 0;
            }
            ++p;
        }
    }

    if (argc == 0)
    {
        // No args found in string, return a single empty name.
        args_buf[0] = '\0';
        argv_buf[0] = &args_buf[0];
        ++argc;
    }

    // Must end the array with a null pointer.
    argv_buf[argc] = NULL;

    *p_argc = argc;
    *p_argv = &argv_buf[0];

    // temporary here
    initialise_monitor_handles ();

    return;
}

// ----------------------------------------------------------------------------

void _exit (int status)
{
    /* There is only one SWI for both _exit and _kill. For _exit, call
     the SWI with the second argument set to -1, an invalid value for
     signum, so that the SWI handler can distinguish the two calls.
     Note: The RDI implementation of _kill throws away both its
     arguments.  */
    report_exception (status == 0 ? ADP_Stopped_ApplicationExit : ADP_Stopped_RunTimeError);
}

// ----------------------------------------------------------------------------

int __attribute__((weak))
_kill (int pid __attribute__((unused)), int sig __attribute__((unused)))
{
    errno = ENOSYS;
    return -1;
}

// ----------------------------------------------------------------------------

/* Struct used to keep track of the file position, just so we
 can implement fseek(fh,x,SEEK_CUR).  */
struct fdent
{
    int handle;
    int pos;
};

#define MAX_OPEN_FILES 20

/* User file descriptors (fd) are integer indexes into
 the openfiles[] array. Error checking is done by using
 findslot().

 This openfiles array is manipulated directly by only
 these 5 functions:

 findslot() - Translate entry.
 newslot() - Find empty entry.
 initilise_monitor_handles() - Initialize entries.
 _swiopen() - Initialize entry.
 _close() - Handle stdout == stderr case.

 Every other function must use findslot().  */

static struct fdent openfiles[MAX_OPEN_FILES];

static struct fdent* findslot (int);
static int newslot (void);

/* Register name faking - works in collusion with the linker.  */
register char* stack_ptr asm ("sp");

/* following is copied from libc/stdio/local.h to check std streams */
extern void _EXFUN(__sinit,(struct _reent*));
#define CHECK_INIT(ptr) \
    do                                          \
    {                                           \
        if ((ptr) && !(ptr)->__sdidinit)        \
            __sinit (ptr);                      \
    }                                           \
    while (0)

static int monitor_stdin;
static int monitor_stdout;
static int monitor_stderr;

/* Return a pointer to the structure associated with
 the user file descriptor fd. */
static struct fdent*
findslot (int fd)
{
    CHECK_INIT(_REENT);

    /* User file descriptor is out of range. */
    if ((unsigned int) fd >= MAX_OPEN_FILES)
    {
        return NULL;
    }

    /* User file descriptor is open? */
    if (openfiles[fd].handle == -1)
    {
        return NULL;
    }

    /* Valid. */
    return &openfiles[fd];
}

/* Return the next lowest numbered free file
 structure, or -1 if we can't find one. */
static int
newslot (void)
{
    int i;

    for (i = 0; i < MAX_OPEN_FILES; i++)
    {
        if (openfiles[i].handle == -1)
        {
            break;
        }
    }

    if (i == MAX_OPEN_FILES)
    {
        return -1;
    }

    return i;
}

void
initialise_monitor_handles (void)
{
    int i;

    /* Open the standard file descriptors by opening the special
     * teletype device, ":tt", read-only to obtain a descriptor for
     * standard input and write-only to obtain a descriptor for standard
     * output. Finally, open ":tt" in append mode to obtain a descriptor
     * for standard error. Since this is a write mode, most kernels will
     * probably return the same value as for standard output, but the
     * kernel can differentiate the two using the mode flag and return a
     * different descriptor for standard error.
     */

    int volatile block[3];

    block[0] = (int) ":tt";
    block[2] = 3; /* length of filename */
    block[1] = 0; /* mode "r" */
    monitor_stdin = call_host (SEMIHOSTING_SYS_OPEN, (void*) block);

    block[0] = (int) ":tt";
    block[2] = 3; /* length of filename */
    block[1] = 4; /* mode "w" */
    monitor_stdout = call_host (SEMIHOSTING_SYS_OPEN, (void*) block);

    block[0] = (int) ":tt";
    block[2] = 3; /* length of filename */
    block[1] = 8; /* mode "a" */
    monitor_stderr = call_host (SEMIHOSTING_SYS_OPEN, (void*) block);

    /* If we failed to open stderr, redirect to stdout. */
    if (monitor_stderr == -1)
    {
        monitor_stderr = monitor_stdout;
    }

    for (i = 0; i < MAX_OPEN_FILES; i++)
    {
        openfiles[i].handle = -1;
    }

    openfiles[0].handle = monitor_stdin;
    openfiles[0].pos = 0;
    openfiles[1].handle = monitor_stdout;
    openfiles[1].pos = 0;
    openfiles[2].handle = monitor_stderr;
    openfiles[2].pos = 0;
}

static int
get_errno (void)
{
    return call_host (SEMIHOSTING_SYS_ERRNO, NULL);
}

/* Set errno and return result. */
static int
error (int result)
{
    errno = get_errno ();
    return result;
}

/* Check the return and set errno appropriately. */
static int
checkerror (int result)
{
    if (result == -1)
    {
        return error (-1);
    }

    return result;
}

/* fh, is a valid internal file handle.
 ptr, is a null terminated string.
 len, is the length in bytes to read.
 Returns the number of bytes *not* written. */
int
_swiread (int fh, char* ptr, int len)
{
    int block[3];

    block[0] = fh;
    block[1] = (int) ptr;
    block[2] = len;

    return checkerror (call_host (SEMIHOSTING_SYS_READ, block));
}

/* fd, is a valid user file handle.
 Translates the return of _swiread into
 bytes read. */
int
_read (int fd, char* ptr, int len)
{
    int res;
    struct fdent *pfd;

    pfd = findslot (fd);
    if (pfd == NULL)
    {
        errno = EBADF;
        return -1;
    }

    res = _swiread (pfd->handle, ptr, len);

    if (res == -1)
    {
        return res;
    }

    pfd->pos += len - res;

    /* res == len is not an error,
     at least if we want feof() to work.  */
    return len - res;
}

/* fd, is a user file descriptor. */
int _swilseek (int fd, int ptr, int dir)
{
    int res;
    struct fdent *pfd;

    /* Valid file descriptor? */
    pfd = findslot (fd);
    if (pfd == NULL)
    {
        errno = EBADF;
        return -1;
    }

    /* Valid whence? */
    if ((dir != SEEK_CUR) && (dir != SEEK_SET) && (dir != SEEK_END))
    {
        errno = EINVAL;
        return -1;
    }

    /* Convert SEEK_CUR to SEEK_SET */
    if (dir == SEEK_CUR)
    {
        ptr = pfd->pos + ptr;
        /* The resulting file offset would be negative. */
        if (ptr < 0)
        {
            errno = EINVAL;
            if ((pfd->pos > 0) && (ptr > 0))
            {
                errno = EOVERFLOW;
            }
            return -1;
        }
        dir = SEEK_SET;
    }

    int block[2];
    if (dir == SEEK_END)
    {
        block[0] = pfd->handle;
        res = checkerror (call_host (SEMIHOSTING_SYS_FLEN, block));
        if (res == -1)
        {
            return -1;
        }
        ptr += res;
    }

    /* This code only does absolute seeks.  */
    block[0] = pfd->handle;
    block[1] = ptr;
    res = checkerror (call_host (SEMIHOSTING_SYS_SEEK, block));

    /* At this point ptr is the current file position. */
    if (res >= 0)
    {
        pfd->pos = ptr;
        return ptr;
    }
    else
    {
        return -1;
    }
}

int _lseek (int fd, int ptr, int dir)
{
    return _swilseek (fd, ptr, dir);
}

/* fh, is a valid internal file handle.
 Returns the number of bytes *not* written. */
int _swiwrite (int fh, char* ptr, int len)
{
    int block[3];

    block[0] = fh;
    block[1] = (int) ptr;
    block[2] = len;

    return checkerror (call_host (SEMIHOSTING_SYS_WRITE, block));
}

/* fd, is a user file descriptor. */
int _write (int fd, char* ptr, int len)
{
    int res;
    struct fdent *pfd;

    pfd = findslot (fd);
    if (pfd == NULL)
    {
        errno = EBADF;
        return -1;
    }

    res = _swiwrite (pfd->handle, ptr, len);

    /* Clearly an error. */
    if (res < 0)
    {
        return -1;
    }

    pfd->pos += len - res;

    /* We wrote 0 bytes?
     Retrieve errno just in case. */
    if ((len - res) == 0)
    {
        return error (0);
    }

    return (len - res);
}

int _swiopen (const char* path, int flags)
{
    int aflags = 0, fh;
    uint32_t block[3];

    int fd = newslot ();

    if (fd == -1)
    {
        errno = EMFILE;
        return -1;
    }

    /* It is an error to open a file that already exists. */
    if ((flags & O_CREAT) && (flags & O_EXCL))
    {
        struct stat st;
        int res;
        res = _stat (path, &st);
        if (res != -1)
        {
            errno = EEXIST;
            return -1;
        }
    }

    /* The flags are Unix-style, so we need to convert them. */
#ifdef O_BINARY
    if (flags & O_BINARY)
    {
        aflags |= 1;
    }
#endif

    /* In O_RDONLY we expect aflags == 0. */

    if (flags & O_RDWR)
    {
        aflags |= 2;
    }

    if ((flags & O_CREAT) || (flags & O_TRUNC) || (flags & O_WRONLY))
    {
        aflags |= 4;
    }

    if (flags & O_APPEND)
    {
        /* Can't ask for w AND a; means just 'a'.  */
        aflags &= ~4;
        aflags |= 8;
    }

    block[0] = (uint32_t) path;
    block[2] = strlen (path);
    block[1] = (uint32_t) aflags;

    fh = call_host (SEMIHOSTING_SYS_OPEN, block);

    /* Return a user file descriptor or an error. */
    if (fh >= 0)
    {
        openfiles[fd].handle = fh;
        openfiles[fd].pos = 0;
        return fd;
    }
    else
    {
        return error (fh);
    }
}

int _open (const char* path, int flags, ...)
{
    return _swiopen (path, flags);
}

/* fh, is a valid internal file handle. */
int _swiclose (int fh)
{
    return checkerror (call_host (SEMIHOSTING_SYS_CLOSE, &fh));
}

/* fd, is a user file descriptor. */
int _close (int fd)
{
    int res;
    struct fdent *pfd;

    pfd = findslot (fd);
    if (pfd == NULL)
    {
        errno = EBADF;
        return -1;
    }

    /* Handle stderr == stdout. */
    if ((fd == 1 || fd == 2) && (openfiles[1].handle == openfiles[2].handle))
    {
        pfd->handle = -1;
        return 0;
    }

    /* Attempt to close the handle. */
    res = _swiclose (pfd->handle);

    /* Reclaim handle? */
    if (res == 0)
    {
        pfd->handle = -1;
    }

    return res;
}

int __attribute__((weak))
_getpid (int n __attribute__ ((unused)))
{
    return 1;
}

int
_swistat (int fd, struct stat* st)
{
    struct fdent *pfd;
    int res;

    pfd = findslot (fd);
    if (pfd == NULL)
    {
        errno = EBADF;
        return -1;
    }

    /* Always assume a character device,
     with 1024 byte blocks. */
    st->st_mode |= S_IFCHR;
    st->st_blksize = 1024;
    res = checkerror (call_host (SEMIHOSTING_SYS_FLEN, &pfd->handle));
    if (res == -1)
    {
        return -1;
    }

    /* Return the file size. */
    st->st_size = res;
    return 0;
}

int __attribute__((weak))
_fstat (int fd, struct stat* st)
{
    memset (st, 0, sizeof(*st));
    return _swistat (fd, st);
}

int __attribute__((weak))
_stat (const char*fname, struct stat *st)
{
    int fd, res;
    memset (st, 0, sizeof(*st));
    /* The best we can do is try to open the file readonly.
     If it exists, then we can guess a few things about it. */
    if ((fd = _open (fname, O_RDONLY)) == -1)
    {
        return -1;
    }
    st->st_mode |= S_IFREG | S_IREAD;
    res = _swistat (fd, st);
    /* Not interested in the error. */
    _close (fd);
    return res;
}

int __attribute__((weak))
_link (void)
{
    errno = ENOSYS;
    return -1;
}

int _unlink (const char* path)
{
    int res;
    uint32_t block[2];
    block[0] = (uint32_t) path;
    block[1] = strlen (path);
    res = call_host (SEMIHOSTING_SYS_REMOVE, block);

    if (res == -1)
    {
        return error (res);
    }
    return 0;
}

int _gettimeofday (struct timeval* tp, void* tzvp)
{
    struct timezone* tzp = tzvp;
    if (tp)
    {
        /* Ask the host for the seconds since the Unix epoch.  */
        tp->tv_sec = call_host (SEMIHOSTING_SYS_TIME, NULL);
        tp->tv_usec = 0;
    }

    /* Return fixed data for the timezone.  */
    if (tzp)
    {
        tzp->tz_minuteswest = 0;
        tzp->tz_dsttime = 0;
    }

    return 0;
}

/* Return a clock that ticks at 100Hz.  */
clock_t _clock (void)
{
    clock_t timeval;

    timeval = (clock_t) call_host (SEMIHOSTING_SYS_CLOCK, NULL);
    return timeval;
}

/* Return a clock that ticks at 100Hz.  */
clock_t
_times (struct tms* tp)
{
    clock_t timeval = _clock ();

    if (tp)
    {
        tp->tms_utime = timeval; /* user time */
        tp->tms_stime = 0; /* system time */
        tp->tms_cutime = 0; /* user time, children */
        tp->tms_cstime = 0; /* system time, children */
    }

    return timeval;
}

int _isatty (int fd)
{
    struct fdent *pfd;
    int tty;

    pfd = findslot (fd);
    if (pfd == NULL)
    {
        errno = EBADF;
        return 0;
    }

    tty = call_host (SEMIHOSTING_SYS_ISTTY, &pfd->handle);

    if (tty == 1)
    {
        return 1;
    }

    errno = get_errno ();
    return 0;
}

int _system (const char* s)
{
    uint32_t block[2];
    int e;

    /* Hmmm.  The ARM debug interface specification doesn't say whether
     SYS_SYSTEM does the right thing with a null argument, or assign any
     meaning to its return value.  Try to do something reasonable....  */
    if (!s)
    {
        return 1; /* maybe there is a shell available? we can hope. :-P */
    }
    block[0] = (uint32_t) s;
    block[1] = strlen (s);
    e = checkerror (call_host (SEMIHOSTING_SYS_SYSTEM, block));
    if ((e >= 0) && (e < 256))
    {
        /* We have to convert e, an exit status to the encoded status of
         the command.  To avoid hard coding the exit status, we simply
         loop until we find the right position.  */
        int exit_code;

        for (exit_code = e; e && WEXITSTATUS (e) != exit_code; e <<= 1)
        {
            continue;
        }
    }
    return e;
}

int _rename (const char* oldpath, const char* newpath)
{
    uint32_t block[4];
    block[0] = (uint32_t) oldpath;
    block[1] = strlen (oldpath);
    block[2] = (uint32_t) newpath;
    block[3] = strlen (newpath);
    return checkerror (call_host (SEMIHOSTING_SYS_RENAME, block)) ? -1 : 0;
}

// ----------------------------------------------------------------------------
// Required by Google Tests

int mkdir (const char *path __attribute__((unused)), mode_t mode __attribute__((unused)))
{
#if 0
    // always return true
    return 0;
#else
    errno = ENOSYS;
    return -1;
#endif
}

char *getcwd (char *buf, size_t size)
{
    // no cwd available via semihosting, so we use the temporary folder
    strncpy (buf, "/tmp", size);
    return buf;
}

#endif // defined OS_USE_SEMIHOSTING

#endif // __STDC_HOSTED__ == 1
