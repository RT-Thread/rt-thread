#include <stdio.h>
#include <stdlib.h>
#include <sys/fcntl.h>

#include <finsh.h>

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

void libc_printf()
{
	printf("stdout test!!\n");
	fprintf(stdout, "fprintf test!!\n");
	fprintf(stderr, "fprintf test!!\n");
	puts("puts test!!\n");

	putc('1', stderr);
	putc('2', stderr);
	putc('\n', stderr);

	printf_test();
}
FINSH_FUNCTION_EXPORT(libc_printf, printf test in libc);


void libc_dprintf()
{
	int fd;

	fd = open("/dev/console", O_WRONLY, 0);
	if (fd >0)
	{
		dprintf(fd, "fd:%d printf test!!\n", fd);
		close(fd);
	}
}
FINSH_FUNCTION_EXPORT(libc_dprintf, dprintf test);


void libc_fdopen()
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
FINSH_FUNCTION_EXPORT(libc_fdopen, fdopen test);
