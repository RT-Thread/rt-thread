#include <reent.h>
#include <sys/errno.h>
#include <rtthread.h>

/* Reentrant versions of system calls.  */

int
_close_r(struct _reent *ptr, int fd)
{
	return close(fd);
}

int
_execve_r(struct _reent *ptr, const char * name, char *const *argv, char *const *env)
{
	/* return "not supported" */
	ptr->_errno = ENOTSUP;
	return -1;
}

int
_fcntl_r(struct _reent *ptr, int fd, int cmd, int arg)
{
	/* return "not supported" */
	ptr->_errno = ENOTSUP;
	return -1;
}

int
_fork_r(struct _reent *ptr)
{
	/* return "not supported" */
	ptr->_errno = ENOTSUP;
	return -1;
}

int
_fstat_r(struct _reent *ptr, int fd, struct stat *pstat)
{
	/* return "not supported" */
	ptr->_errno = ENOTSUP;
	return -1;
}

int
_getpid_r(struct _reent *ptr)
{
	return 0;
}

int
_isatty_r(struct _reent *ptr, int fd)
{
	if (fd >=0 && fd < 3) return 1;

	/* return "not supported" */
	ptr->_errno = ENOTSUP;
	return -1;
}

int
_kill_r(struct _reent *ptr, int pid, int sig)
{
	/* return "not supported" */
	ptr->_errno = ENOTSUP;
	return -1;
}

int
_link_r(struct _reent *ptr, const char *old, const char *new)
{
	/* return "not supported" */
	ptr->_errno = ENOTSUP;
	return -1;
}

_off_t
_lseek_r(struct _reent *ptr, int fd, _off_t pos, int whence)
{
	_off_t rc;

	rc = lseek(fd, pos, whence);
	return rc;
}

int
_mkdir_r(struct _reent *ptr, const char *name, int mode)
{
	int rc;

	rc = mkdir(name, mode);
	return rc;
}

int
_open_r(struct _reent *ptr, const char *file, int flags, int mode)
{
	int rc;

	rc = open(file, flags, mode);
	return rc;
}

_ssize_t 
_read_r(struct _reent *ptr, int fd, void *buf, size_t nbytes)
{
	_ssize_t rc;

	rc = read(fd, buf, nbytes);
	return rc;
}

int
_rename_r(struct _reent *ptr, const char *old, const char *new)
{
	int rc;

	rc = rename(old, new);
	return rc;
}

void *
_sbrk_r(struct _reent *ptr, ptrdiff_t incr)
{
	/* no use this routine to get memory */
	return RT_NULL;
}

int
_stat_r(struct _reent *ptr, const char *file, struct stat *pstat)
{
	int rc;

	rc = stat(file, pstat);
	return rc;
}

_CLOCK_T_
_times_r(struct _reent *ptr, struct tms *ptms)
{
	/* return "not supported" */
	ptr->_errno = ENOTSUP;
	return -1;
}

int
_unlink_r(struct _reent *ptr, const char *file)
{
	int rc;

	rc = unlink(file);
	return rc;
}

int
_wait_r(struct _reent *ptr, int *status)
{
	/* return "not supported" */
	ptr->_errno = ENOTSUP;
	return -1;
}

_ssize_t
_write_r(struct _reent *ptr, int fd, const void *buf, size_t nbytes)
{
	_ssize_t rc;

	rc = write(fd, buf, nbytes);
	return rc;
}

int
_gettimeofday_r(struct _reent *ptr, struct timeval *__tp, void *__tzp)
{
	/* return "not supported" */
	ptr->_errno = ENOTSUP;
	return -1;
}

/* Memory routine */
void *
_malloc_r (struct _reent *ptr, size_t size)
{
	return (void*)rt_malloc (size);
}

void *
_realloc_r (struct _reent *ptr, void *old, size_t newlen)
{
	return (void*)rt_realloc (old, newlen);
}

void *_calloc_r (struct _reent *ptr, size_t size, size_t len)
{
  return (void*)rt_calloc (size, len);
}

void 
_free_r (struct _reent *ptr, void *addr)
{
	rt_free (addr);
}

void __assert(const char *file, int line, const char *failedexpr)
{
    rt_kprintf("assertion \"%s\" failed: file \"%s\", line %d\n",
               failedexpr, file, line);
    RT_ASSERT(0);
}

void
_exit (int status)
{
	rt_kprintf("thread:%s exit with %d\n", rt_thread_self()->name, status);
    RT_ASSERT(0);
}

#ifdef RT_USING_FINSH
#include <finsh.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>

char * format[] = {
  "%",
  "%0.",
  "%.0",
  "%+0.",
  "%+.0",
  "%.5",
  "%+.5",
  "%2.5",
  "%22.5",
  "%022.5",
  "%#022.5",
  "%-#022.5",
  "%+#022.5",
  "%-22.5",
  "%+22.5",
  "%--22.5",
  "%++22.5",
  "%+-22.5",
  "%-+22.5",
  "%-#022.5",
  "%-#22.5",
  "%-2.22",
  "%+2.22",
  "%-#02.22",
  "%-#2.22",
  "%-1.5",
  "%1.5",
  "%-#01.5",
  "%-#1.5",
  "%-#.5",
  "%-#1.",
  "%-#.",
  NULL
};
 

static void
intchk (const char *fmt)
{
  (void) printf("%15s :, \"", fmt);
  (void) printf(fmt, 0);
  (void) printf("\", \"");
  (void) printf(fmt, 123);
  (void) printf("\", \"");
  (void) printf(fmt, -18);
  (void) printf("\"\n");
}

static void
fltchk (const char *fmt)
{
  (void) printf("%15s :, \"", fmt);
  (void) printf(fmt, 0.0);
  (void) printf("\", \"");
  (void) printf(fmt, 123.0001);
  (void) printf("\", \"");
  (void) printf(fmt, -18.0002301);
  (void) printf("\"\n");
}

void fprintf_test()
{
	printf("stdout test!!\n");
	fprintf(stdout, "fprintf test!!\n");
	fprintf(stderr, "fprintf test!!\n");
	puts("puts test!!\n");
}

int speed()
{
  int i;
  time_t t;
  
  printf("%d\n", time(0));
  for (i=0; i<10000000; ++i)
    t=time(0);

 printf("%d\n", time(0));
 return 0;   
}

int printf_test()
{
  char buf[256];
  int i;
  
  printf("%s\n\n", "# vim:syntax=off:");
  
  /* integers */
  for(i=0;format[i];i++) {
    strcpy(buf, format[i]);
    strcat(buf, "d");
    intchk(buf);
  }
  
  /* floats */
  for(i=0;format[i];i++) {
    strcpy(buf, format[i]);
    strcat(buf, "f");
    fltchk(buf);
  }
  /* hexa */
  for(i=0;format[i];i++) {
    strcpy(buf, format[i]);
    strcat(buf, "x");
    intchk(buf);
  }
  
  printf("#%.4x %4x#\n", 4, 88);
  printf("#%4x#\n",4);
  printf("#%#22.8x#\n",1234567);
  
  printf("#%+2i#\n",18);
  printf("#%i#\n",18);
  printf("#%llu#\n",4294967297ULL);
  printf("#%#x#\n",44444);
  printf("#%-8i#\n",33);
  printf("#%i#\n",18);
  printf("#%d#\n",18);
  printf("#%u#\n",18);
  printf("#%lu#\n",18);
  printf("#%li#\n",18);
  printf("#%-+#06d#\n", -123);
  printf("#%-+#6d#\n", -123);
  printf("#%+#06d#\n", -123);
  printf("#%06d#\n", -123);
  printf("#%+15s#\n","ABCDEF");
  /* from ncurses make_keys */
  printf("{ %4d, %-*.*s },\t/* %s */\n", 139, 16, 16, "KEY_A1", "key_a1");
  printf("{ %4d, %-*.*s },\t/* %s */\n", 139, 16,  2, "KEY_A1", "key_a1");
  printf("{ %4d, %-*.*s },\t/* %s */\n", 139,  2, 16, "KEY_A1", "key_a1");
  printf("{ %4d, %-*.*s },\t/* %s */\n", 139, 16,  0, "KEY_A1", "key_a1");
  printf("{ %4d, %-*.*s },\t/* %s */\n", 139,  0, 16, "KEY_A1", "key_a1");
  printf("{ %4d, %-*.*s },\t/* %s */\n", 139,  0,  0, "KEY_A1", "key_a1");
  printf("{ %4d, %*.*s },\t/* %s */\n", 139, 16, 16, "KEY_A1", "key_a1");
  printf("{ %4d, %*.*s },\t/* %s */\n", 139, 16,  2, "KEY_A1", "key_a1");
  printf("{ %4d, %*.*s },\t/* %s */\n", 139,  2, 16, "KEY_A1", "key_a1");
  printf("{ %4d, %*.*s },\t/* %s */\n", 139, 16,  0, "KEY_A1", "key_a1");
  printf("{ %4d, %*.*s },\t/* %s */\n", 139,  0, 16, "KEY_A1", "key_a1");
  printf("{ %4d, %*.*s },\t/* %s */\n", 139,  0,  0, "KEY_A1", "key_a1");
  printf("%*.*f\n",  0, 16, 0.0);
  printf("%*.*f\n", 16, 16, 0.0);
  printf("%*.*f\n",  2, 2,  -0.0);
  printf("%*.*f\n", 20, 0,  -123.123);
  printf("%*.*f\n", 10, 0,  +123.123);
  
  
  i = printf("\"%s\"\n","A");
  printf("%i\n", i); 
  /* from glibc's tst-printf.c */
  
  {
    char buf[20];
    char buf2[512];
    int i;

    printf ("snprintf (\"%%30s\", \"foo\") == %d, \"%.*s\"\n",
	    snprintf (buf, sizeof (buf), "%30s", "foo"), (int) sizeof (buf),
	    buf);
    memset(buf2,0,sizeof(buf));
    i=snprintf(buf2, 256, "%.9999u", 10);
    printf("%i %i\n",i,strlen(buf2));
    
    printf ("snprintf (\"%%.999999u\", 10) == %d\n",
    	    snprintf(buf2, sizeof(buf2), "%.999999u", 10));
  }
  return 0;
}

#if 0	// FAILED: no glob
#include <glob.h>
int glob_test()
{
  glob_t g;
  int i;
  printf("%d\n", glob("/*.hdc",0,0,&g));
  for (i=0; i<g.gl_pathc; ++i)
    printf("  %s\n",g.gl_pathv[i]);
return 0;
}
#endif

#include <assert.h>

int getenv_test()
{
  printf("PATH=%s\n", getenv("PATH"));
  putenv("foo=bar");
  printf("foo=%s\n", getenv("foo"));
  return 0;
}

void dprintf_test()
{
	int fd;

	fd = open("/dev/console", O_WRONLY, 0);
	if (fd >0)
	{
		dprintf(fd, "fd:%d printf test!!\n", fd);
		close(fd);
	}
}

#if 0 // FAILED: no dirname
#include <libgen.h>
#include <assert.h>

int dirname_test()
{
     char s[80];

     strncpy(s,"/usr/lib",80);       assert(strcmp(dirname(s),   "/usr")==0);
     strncpy(s,"/usr/",80);          assert(strcmp(dirname(s),   "/")==0);
     strncpy(s,"usr",80);            assert(strcmp(dirname(s),   ".")==0);
     strncpy(s,"usr/test",80);       assert(strcmp(dirname(s),   "usr")==0);
     strncpy(s,"usr/test/test2",80); assert(strcmp(dirname(s),   "usr/test")==0);
     strncpy(s,"/usr",80);           assert(strcmp(dirname(s),   "/")==0);
     strncpy(s,"/",80);              assert(strcmp(dirname(s),   "/")==0);
     strncpy(s,".",80);              assert(strcmp(dirname(s),   ".")==0);
     strncpy(s,"..",80);             assert(strcmp(dirname(s),   ".")==0);
     strncpy(s,"////",80);           assert(strcmp(dirname(s),   "/")==0);
     strncpy(s,"//",80);             assert(strcmp(dirname(s),   "/")==0);
                                     assert(strcmp(dirname(NULL),".")==0);
     s[0]=0;                         assert(strcmp(dirname(s),   ".")==0);

     puts("OK");
     return 0;
}
#endif

void fdopen_test()
{
	int fd;
	FILE* fp;

	fd = open("/dev/console", O_WRONLY, 0);
	if (fd >0)
	{
		fp = fdopen(fd, "w");
		fprintf(fp, "fdopen test, fd %d!!\n", fileno(fp));
		fclose(fp);
	}
}

static int errors = 0;

static void
merror (const char *msg)
{
  ++errors;
  printf ("Error: %s\n", msg);
}

int malloc_test (void)
{
  void *p;
  int save;

  errno = 0;

  p = malloc (-1);
  save = errno;

  if (p != NULL)
    merror ("malloc (-1) succeeded.");

  if (p == NULL && save != ENOMEM)
    merror ("errno is not set correctly");

  p = malloc (10);
  if (p == NULL)
    merror ("malloc (10) failed.");

  /* realloc (p, 0) == free (p).  */
  p = realloc (p, 0);
  if (p != NULL)
    merror ("realloc (p, 0) failed.");

  p = malloc (0);
  if (p == NULL)
    merror ("malloc (0) failed.");

  p = realloc (p, 0);
  if (p != NULL)
    merror ("realloc (p, 0) failed.");

  return errors != 0;
}

void putc_test()
{
  putc ('1', stderr);
  putc ('2', stderr);
  putc ('\n', stderr);
}

#include <dirent.h>
int dirent_test ()
{
  DIR * dirp;
  long int save3 = 0;
  long int cur;
  int i = 0;
  int result = 0;
  struct dirent *dp;

  dirp = opendir ("/");
  for (dp = readdir (dirp); dp != NULL; dp = readdir (dirp))
    {
      /* save position 3 (after fourth entry) */
      if (i++ == 3)
	save3 = telldir (dirp);

      printf ("%s\n", dp->d_name);

      /* stop at 400 (just to make sure dirp->__offset and dirp->__size are
	 scrambled */
      if (i == 400)
	break;
    }

  printf ("going back past 4-th entry...\n");

  /* go back to saved entry */
  seekdir (dirp, save3);

  /* Check whether telldir equals to save3 now.  */
  cur = telldir (dirp);
  if (cur != save3)
    {
      printf ("seekdir (d, %ld); telldir (d) == %ld\n", save3, cur);
      result = 1;
    }

  /* print remaining files (3-last) */
  for (dp = readdir (dirp); dp != NULL; dp = readdir (dirp))
    printf ("%s\n", dp->d_name);


  closedir (dirp);
  return result;
}

int
rand_test (void)
{
  int i1, i2;
  int j1, j2;

  /* The C standard says that "If rand is called before any calls to
     srand have been made, the same sequence shall be generated as
     when srand is first called with a seed value of 1." */
  i1 = rand();
  i2 = rand();
  srand (1);
  j1 = rand();
  j2 = rand();
  if (i1 < 0 || i2 < 0 || j1 < 0 || j2 < 0) {
      puts ("Test FAILED!");
  }
  if (j1 == i1 && j2 == i2)
    {
      puts ("Test succeeded.");
      return 0;
    }
  else
    {
      if (j1 != i1)
	printf ("%d != %d\n", j1, i1);
      if (j2 != i2)
	printf ("%d != %d\n", j2, i2);
      puts ("Test FAILED!");
      return 1;
    }
}

void sleep(int tick)
{
	rt_thread_sleep(tick);
}

#include <sys/stat.h>
int
fseek_test (void)
{
  const char *tmpdir;
  char *fname;
  int fd;
  FILE *fp;
  const char outstr[] = "hello world!\n";
  char strbuf[sizeof outstr];
  char buf[200];
  struct stat st1;
  struct stat st2;
  int result = 0;

  tmpdir = getenv ("TMPDIR");
  if (tmpdir == NULL || tmpdir[0] == '\0')
    tmpdir = "/tmp";

  asprintf (&fname, "%s/tst-fseek.XXXXXX", tmpdir);
  if (fname == NULL) {
    fprintf(stderr, "cannot generate name for temporary file: %s\n",strerror(errno));
    return 1;
  }  

  /* Create a temporary file.   */
  fd = mkstemp (fname);
  if (fd == -1) {
    fprintf(stderr, "cannot open temporary file: %s\n",strerror(errno));
    return 1;
  }  

  fp = fdopen (fd, "w+");
  if (fp == NULL) {
    fprintf(stderr, "cannot get FILE for temporary file: %s\n",strerror(errno));
    return 1;
  }
  setbuffer (fp, strbuf, sizeof (outstr) -1);

  if (fwrite (outstr, sizeof (outstr) - 1, 1, fp) != 1)
    {
      printf ("%d: write error\n", __LINE__);
      result = 1;
      goto out;
    }

  /* The EOF flag must be reset.  */
  if (fgetc (fp) != EOF)
    {
      printf ("%d: managed to read at end of file\n", __LINE__);
      result = 1;
    }
  else if (! feof (fp))
    {
      printf ("%d: EOF flag not set\n", __LINE__);
      result = 1;
    }
  if (fseek (fp, 0, SEEK_CUR) != 0)
    {
      printf ("%d: fseek(fp, 0, SEEK_CUR) failed\n", __LINE__);
      result = 1;
    }
  else if (feof (fp))
    {
      printf ("%d: fseek() didn't reset EOF flag\n", __LINE__);
      result = 1;
    }

  /* Do the same for fseeko().  */
    if (fgetc (fp) != EOF)
    {
      printf ("%d: managed to read at end of file\n", __LINE__);
      result = 1;
    }
  else if (! feof (fp))
    {
      printf ("%d: EOF flag not set\n", __LINE__);
      result = 1;
    }
  if (fseeko (fp, 0, SEEK_CUR) != 0)
    {
      printf ("%d: fseek(fp, 0, SEEK_CUR) failed\n", __LINE__);
      result = 1;
    }
  else if (feof (fp))
    {
      printf ("%d: fseek() didn't reset EOF flag\n", __LINE__);
      result = 1;
    }

  /* Go back to the beginning of the file: absolute.  */
  if (fseek (fp, 0, SEEK_SET) != 0)
    {
      printf ("%d: fseek(fp, 0, SEEK_SET) failed\n", __LINE__);
      result = 1;
    }
  else if (fflush (fp) != 0)
    {
      printf ("%d: fflush() failed\n", __LINE__);
      result = 1;
    }
  else if (lseek (fd, 0, SEEK_CUR) != 0)
    {
      int pos = lseek (fd, 0, SEEK_CUR);
      printf ("%d: lseek() returned different position, pos %d\n", __LINE__, pos);
      result = 1;
    }
  else if (fread (buf, sizeof (outstr) - 1, 1, fp) != 1)
    {
      printf ("%d: fread() failed\n", __LINE__);
      result = 1;
    }
  else if (memcmp (buf, outstr, sizeof (outstr) - 1) != 0)
    {
      printf ("%d: content after fseek(,,SEEK_SET) wrong\n", __LINE__);
      result = 1;
    }

  /* Now with fseeko.  */
  if (fseeko (fp, 0, SEEK_SET) != 0)
    {
      printf ("%d: fseeko(fp, 0, SEEK_SET) failed\n", __LINE__);
      result = 1;
    }
  else if (fflush (fp) != 0)
    {
      printf ("%d: fflush() failed\n", __LINE__);
      result = 1;
    }
  else if (lseek (fd, 0, SEEK_CUR) != 0)
    {
      printf ("%d: lseek() returned different position\n", __LINE__);
      result = 1;
    }
  else if (fread (buf, sizeof (outstr) - 1, 1, fp) != 1)
    {
      printf ("%d: fread() failed\n", __LINE__);
      result = 1;
    }
  else if (memcmp (buf, outstr, sizeof (outstr) - 1) != 0)
    {
      printf ("%d: content after fseeko(,,SEEK_SET) wrong\n", __LINE__);
      result = 1;
    }

  /* Go back to the beginning of the file: relative.  */
  if (fseek (fp, -((int) sizeof (outstr) - 1), SEEK_CUR) != 0)
    {
      printf ("%d: fseek(fp, 0, SEEK_SET) failed\n", __LINE__);
      result = 1;
    }
  else if (fflush (fp) != 0)
    {
      printf ("%d: fflush() failed\n", __LINE__);
      result = 1;
    }
  else if (lseek (fd, 0, SEEK_CUR) != 0)
    {
      printf ("%d: lseek() returned different position\n", __LINE__);
      result = 1;
    }
  else if (fread (buf, sizeof (outstr) - 1, 1, fp) != 1)
    {
      printf ("%d: fread() failed\n", __LINE__);
      result = 1;
    }
  else if (memcmp (buf, outstr, sizeof (outstr) - 1) != 0)
    {
      printf ("%d: content after fseek(,,SEEK_SET) wrong\n", __LINE__);
      result = 1;
    }

  /* Now with fseeko.  */
  if (fseeko (fp, -((int) sizeof (outstr) - 1), SEEK_CUR) != 0)
    {
      printf ("%d: fseeko(fp, 0, SEEK_SET) failed\n", __LINE__);
      result = 1;
    }
  else if (fflush (fp) != 0)
    {
      printf ("%d: fflush() failed\n", __LINE__);
      result = 1;
    }
  else if (lseek (fd, 0, SEEK_CUR) != 0)
    {
      printf ("%d: lseek() returned different position\n", __LINE__);
      result = 1;
    }
  else if (fread (buf, sizeof (outstr) - 1, 1, fp) != 1)
    {
      printf ("%d: fread() failed\n", __LINE__);
      result = 1;
    }
  else if (memcmp (buf, outstr, sizeof (outstr) - 1) != 0)
    {
      printf ("%d: content after fseeko(,,SEEK_SET) wrong\n", __LINE__);
      result = 1;
    }

  /* Go back to the beginning of the file: from the end.  */
  if (fseek (fp, -((int) sizeof (outstr) - 1), SEEK_END) != 0)
    {
      printf ("%d: fseek(fp, 0, SEEK_SET) failed\n", __LINE__);
      result = 1;
    }
  else if (fflush (fp) != 0)
    {
      printf ("%d: fflush() failed\n", __LINE__);
      result = 1;
    }
  else if (lseek (fd, 0, SEEK_CUR) != 0)
    {
      printf ("%d: lseek() returned different position\n", __LINE__);
      result = 1;
    }
  else if (fread (buf, sizeof (outstr) - 1, 1, fp) != 1)
    {
      printf ("%d: fread() failed\n", __LINE__);
      result = 1;
    }
  else if (memcmp (buf, outstr, sizeof (outstr) - 1) != 0)
    {
      printf ("%d: content after fseek(,,SEEK_SET) wrong\n", __LINE__);
      result = 1;
    }

  /* Now with fseeko.  */
  if (fseeko (fp, -((int) sizeof (outstr) - 1), SEEK_END) != 0)
    {
      printf ("%d: fseeko(fp, 0, SEEK_SET) failed\n", __LINE__);
      result = 1;
    }
  else if (fflush (fp) != 0)
    {
      printf ("%d: fflush() failed\n", __LINE__);
      result = 1;
    }
  else if (lseek (fd, 0, SEEK_CUR) != 0)
    {
      printf ("%d: lseek() returned different position\n", __LINE__);
      result = 1;
    }
  else if (fread (buf, sizeof (outstr) - 1, 1, fp) != 1)
    {
      printf ("%d: fread() failed\n", __LINE__);
      result = 1;
    }
  else if (memcmp (buf, outstr, sizeof (outstr) - 1) != 0)
    {
      printf ("%d: content after fseeko(,,SEEK_SET) wrong\n", __LINE__);
      result = 1;
    }

  if (fwrite (outstr, sizeof (outstr) - 1, 1, fp) != 1)
    {
      printf ("%d: write error 2\n", __LINE__);
      result = 1;
      goto out;
    }

  if (fwrite (outstr, sizeof (outstr) - 1, 1, fp) != 1)
    {
      printf ("%d: write error 3\n", __LINE__);
      result = 1;
      goto out;
    }

  if (fwrite (outstr, sizeof (outstr) - 1, 1, fp) != 1)
    {
      printf ("%d: write error 4\n", __LINE__);
      result = 1;
      goto out;
    }

  if (fwrite (outstr, sizeof (outstr) - 1, 1, fp) != 1)
    {
      printf ("%d: write error 5\n", __LINE__);
      result = 1;
      goto out;
    }

  if (fputc ('1', fp) == EOF || fputc ('2', fp) == EOF)
    {
      printf ("%d: cannot add characters at the end\n", __LINE__);
      result = 1;
      goto out;
    }

  /* Check the access time.  */
  if (fstat (fd, &st1) < 0)
    {
      printf ("%d: fstat64() before fseeko() failed\n\n", __LINE__);
      result = 1;
    }
  else
    {
      sleep (1);

      if (fseek (fp, -(2 + 2 * (sizeof (outstr) - 1)), SEEK_CUR) != 0)
	{
	  printf ("%d: fseek() after write characters failed\n", __LINE__);
	  result = 1;
	  goto out;
	}
      else
	{

	  time_t t;
	  /* Make sure the timestamp actually can be different.  */
	  sleep (1);
	  t = time (NULL);

	  if (fstat (fd, &st2) < 0)
	    {
	      printf ("%d: fstat64() after fseeko() failed\n\n", __LINE__);
	      result = 1;
	    }
	  if (st1.st_ctime >= t)
	    {
	      printf ("%d: st_ctime not updated\n", __LINE__);
	      result = 1;
	    }
	  if (st1.st_mtime >= t)
	    {
	      printf ("%d: st_mtime not updated\n", __LINE__);
	      result = 1;
	    }
	  if (st1.st_ctime >= st2.st_ctime)
	    {
	      printf ("%d: st_ctime not changed\n", __LINE__);
	      result = 1;
	    }
	  if (st1.st_mtime >= st2.st_mtime)
	    {
	      printf ("%d: st_mtime not changed\n", __LINE__);
	      result = 1;
	    }
	}
    }

  if (fread (buf, 1, 2 + 2 * (sizeof (outstr) - 1), fp)
      != 2 + 2 * (sizeof (outstr) - 1))
    {
      printf ("%d: reading 2 records plus bits failed\n", __LINE__);
      result = 1;
    }
  else if (memcmp (buf, outstr, sizeof (outstr) - 1) != 0
	   || memcmp (&buf[sizeof (outstr) - 1], outstr,
		      sizeof (outstr) - 1) != 0
	   || buf[2 * (sizeof (outstr) - 1)] != '1'
	   || buf[2 * (sizeof (outstr) - 1) + 1] != '2')
    {
      printf ("%d: reading records failed\n", __LINE__);
      result = 1;
    }
  else if (ungetc ('9', fp) == EOF)
    {
      printf ("%d: ungetc() failed\n", __LINE__);
      result = 1;
    }
  else if (fseek (fp, -(2 + 2 * (sizeof (outstr) - 1)), SEEK_END) != 0)
    {
      printf ("%d: fseek after ungetc failed\n", __LINE__);
      result = 1;
    }
  else if (fread (buf, 1, 2 + 2 * (sizeof (outstr) - 1), fp)
      != 2 + 2 * (sizeof (outstr) - 1))
    {
      printf ("%d: reading 2 records plus bits failed\n", __LINE__);
      result = 1;
    }
  else if (memcmp (buf, outstr, sizeof (outstr) - 1) != 0
	   || memcmp (&buf[sizeof (outstr) - 1], outstr,
		      sizeof (outstr) - 1) != 0
	   || buf[2 * (sizeof (outstr) - 1)] != '1')
    {
      printf ("%d: reading records for the second time failed\n", __LINE__);
      result = 1;
    }
  else if (buf[2 * (sizeof (outstr) - 1) + 1] == '9')
    {
      printf ("%d: unget character not ignored\n", __LINE__);
      result = 1;
    }
  else if (buf[2 * (sizeof (outstr) - 1) + 1] != '2')
    {
      printf ("%d: unget somehow changed character\n", __LINE__);
      result = 1;
    }

  fclose (fp);

  fp = fopen (fname, "r");
  if (fp == NULL)
    {
      printf ("%d: fopen() failed\n\n", __LINE__);
      result = 1;
    }
  else if (fstat (fileno (fp), &st1) < 0)
    {
      printf ("%d: fstat64() before fseeko() failed\n\n", __LINE__);
      result = 1;
    }
  else if (fseeko (fp, 0, SEEK_END) != 0)
    {
      printf ("%d: fseeko(fp, 0, SEEK_END) failed\n", __LINE__);
      result = 1;
    }
  else if (ftello (fp) != st1.st_size)
    {
      printf ("%d: fstat64 st_size %zd ftello %zd\n", __LINE__,
	      (size_t) st1.st_size, (size_t) ftello (fp));
      result = 1;
    }
  else
    printf ("%d: SEEK_END works\n", __LINE__);
  if (fp != NULL)
    fclose (fp);

  fp = fopen (fname, "r");
  if (fp == NULL)
    {
      printf ("%d: fopen() failed\n\n", __LINE__);
      result = 1;
    }
  else if (fstat (fileno (fp), &st1) < 0)
    {
      printf ("%d: fstat64() before fgetc() failed\n\n", __LINE__);
      result = 1;
    }
  else if (fgetc (fp) == EOF)
    {
      printf ("%d: fgetc() before fseeko() failed\n\n", __LINE__);
      result = 1;
    }
  else if (fseeko (fp, 0, SEEK_END) != 0)
    {
      printf ("%d: fseeko(fp, 0, SEEK_END) failed\n", __LINE__);
      result = 1;
    }
  else if (ftello (fp) != st1.st_size)
    {
      printf ("%d: fstat64 st_size %zd ftello %zd\n", __LINE__,
	      (size_t) st1.st_size, (size_t) ftello (fp));
      result = 1;
    }
  else
    printf ("%d: SEEK_END works\n", __LINE__);
  if (fp != NULL)
    fclose (fp);

 out:
  unlink (fname);

  return result;
}

const char* text = "this is a test string\n";
void lseek_test()
{
	int fd;

	fd = open("/tmp/tt.txt", O_WRONLY | O_CREAT, 0);
	if (fd < 0) 
	{
		printf("open failed\n");
		return ;
	}

	write(fd, text, strlen(text) + 1);
	printf("begin: %d\n", lseek(fd, 0, SEEK_SET));
	printf("end: %d\n", lseek(fd, 0, SEEK_END));
	close(fd);
}

void fstat_test()
{
	int fd;
  	struct stat s;

	fd = open("/tmp/tt.txt", O_WRONLY | O_CREAT, 0);
	if (fd < 0) 
	{
		printf("open failed\n");
		return ;
	}

	write(fd, text, strlen(text) + 1);
	printf("begin: %d\n", lseek(fd, 0, SEEK_SET));
	printf("end: %d\n", lseek(fd, 0, SEEK_END));

	printf("fstat result: %d\n", fstat(fd, &s));
	close(fd);
}

void nltest()
{
	fseek_test();
}
FINSH_FUNCTION_EXPORT(nltest, newlib test);
#endif

