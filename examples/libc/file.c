/*
 * fstat.c
 *
 *  Created on: 2010-11-17
 *      Author: bernard
 */
#include <stdio.h>
#include <stdlib.h>
#include <finsh.h>
#include <errno.h>
#include <sys/fcntl.h>
#include <sys/stat.h>

const char* text = "this is a test string\n";
void libc_fstat()
{
	int fd;
	struct stat s;

	fd = open("/tmp/tt.txt", O_WRONLY | O_CREAT, 0);
	if (fd < 0)
	{
		printf("open failed\n");
		return;
	}

	write(fd, text, strlen(text) + 1);
	printf("begin: %d\n", lseek(fd, 0, SEEK_SET));
	printf("end: %d\n", lseek(fd, 0, SEEK_END));

	printf("fstat result: %d\n", fstat(fd, &s));
	close(fd);
}
FINSH_FUNCTION_EXPORT(libc_fstat, fstat test for libc);

void libc_lseek()
{
	int fd;

	fd = open("/tmp/tt.txt", O_WRONLY | O_CREAT, 0);
	if (fd < 0)
	{
		printf("open failed\n");
		return;
	}

	write(fd, text, strlen(text) + 1);
	printf("begin: %d\n", lseek(fd, 0, SEEK_SET));
	printf("end: %d\n", lseek(fd, 0, SEEK_END));
	close(fd);
}
FINSH_FUNCTION_EXPORT(libc_lseek, lseek test for libc);

void sleep(int tick)
{
	rt_thread_sleep(tick);
}

int libc_fseek(void)
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

	tmpdir = getenv("TMPDIR");
	if (tmpdir == NULL || tmpdir[0] == '\0')
		tmpdir = "/tmp";

	asprintf(&fname, "%s/tst-fseek.XXXXXX", tmpdir);
	if (fname == NULL)
	{
		fprintf(stderr, "cannot generate name for temporary file: %s\n",
				strerror(errno));
		return 1;
	}

	/* Create a temporary file.   */
	fd = mkstemp(fname);
	if (fd == -1)
	{
		fprintf(stderr, "cannot open temporary file: %s\n", strerror(errno));
		return 1;
	}

	fp = fdopen(fd, "w+");
	if (fp == NULL)
	{
		fprintf(stderr, "cannot get FILE for temporary file: %s\n", strerror(
				errno));
		return 1;
	}
	setbuffer(fp, strbuf, sizeof(outstr) - 1);

	if (fwrite(outstr, sizeof(outstr) - 1, 1, fp) != 1)
	{
		printf("%d: write error\n", __LINE__);
		result = 1;
		goto out;
	}

	/* The EOF flag must be reset.  */
	if (fgetc(fp) != EOF)
	{
		printf("%d: managed to read at end of file\n", __LINE__);
		result = 1;
	}
	else if (!feof(fp))
	{
		printf("%d: EOF flag not set\n", __LINE__);
		result = 1;
	}
	if (fseek(fp, 0, SEEK_CUR) != 0)
	{
		printf("%d: fseek(fp, 0, SEEK_CUR) failed\n", __LINE__);
		result = 1;
	}
	else if (feof(fp))
	{
		printf("%d: fseek() didn't reset EOF flag\n", __LINE__);
		result = 1;
	}

	/* Do the same for fseeko().  */
	if (fgetc(fp) != EOF)
	{
		printf("%d: managed to read at end of file\n", __LINE__);
		result = 1;
	}
	else if (!feof(fp))
	{
		printf("%d: EOF flag not set\n", __LINE__);
		result = 1;
	}
	if (fseeko(fp, 0, SEEK_CUR) != 0)
	{
		printf("%d: fseek(fp, 0, SEEK_CUR) failed\n", __LINE__);
		result = 1;
	}
	else if (feof(fp))
	{
		printf("%d: fseek() didn't reset EOF flag\n", __LINE__);
		result = 1;
	}

	/* Go back to the beginning of the file: absolute.  */
	if (fseek(fp, 0, SEEK_SET) != 0)
	{
		printf("%d: fseek(fp, 0, SEEK_SET) failed\n", __LINE__);
		result = 1;
	}
	else if (fflush(fp) != 0)
	{
		printf("%d: fflush() failed\n", __LINE__);
		result = 1;
	}
	else if (lseek(fd, 0, SEEK_CUR) != 0)
	{
		int pos = lseek(fd, 0, SEEK_CUR);
		printf("%d: lseek() returned different position, pos %d\n", __LINE__,
				pos);
		result = 1;
	}
	else if (fread(buf, sizeof(outstr) - 1, 1, fp) != 1)
	{
		printf("%d: fread() failed\n", __LINE__);
		result = 1;
	}
	else if (memcmp(buf, outstr, sizeof(outstr) - 1) != 0)
	{
		printf("%d: content after fseek(,,SEEK_SET) wrong\n", __LINE__);
		result = 1;
	}

	/* Now with fseeko.  */
	if (fseeko(fp, 0, SEEK_SET) != 0)
	{
		printf("%d: fseeko(fp, 0, SEEK_SET) failed\n", __LINE__);
		result = 1;
	}
	else if (fflush(fp) != 0)
	{
		printf("%d: fflush() failed\n", __LINE__);
		result = 1;
	}
	else if (lseek(fd, 0, SEEK_CUR) != 0)
	{
		printf("%d: lseek() returned different position\n", __LINE__);
		result = 1;
	}
	else if (fread(buf, sizeof(outstr) - 1, 1, fp) != 1)
	{
		printf("%d: fread() failed\n", __LINE__);
		result = 1;
	}
	else if (memcmp(buf, outstr, sizeof(outstr) - 1) != 0)
	{
		printf("%d: content after fseeko(,,SEEK_SET) wrong\n", __LINE__);
		result = 1;
	}

	/* Go back to the beginning of the file: relative.  */
	if (fseek(fp, -((int) sizeof(outstr) - 1), SEEK_CUR) != 0)
	{
		printf("%d: fseek(fp, 0, SEEK_SET) failed\n", __LINE__);
		result = 1;
	}
	else if (fflush(fp) != 0)
	{
		printf("%d: fflush() failed\n", __LINE__);
		result = 1;
	}
	else if (lseek(fd, 0, SEEK_CUR) != 0)
	{
		printf("%d: lseek() returned different position\n", __LINE__);
		result = 1;
	}
	else if (fread(buf, sizeof(outstr) - 1, 1, fp) != 1)
	{
		printf("%d: fread() failed\n", __LINE__);
		result = 1;
	}
	else if (memcmp(buf, outstr, sizeof(outstr) - 1) != 0)
	{
		printf("%d: content after fseek(,,SEEK_SET) wrong\n", __LINE__);
		result = 1;
	}

	/* Now with fseeko.  */
	if (fseeko(fp, -((int) sizeof(outstr) - 1), SEEK_CUR) != 0)
	{
		printf("%d: fseeko(fp, 0, SEEK_SET) failed\n", __LINE__);
		result = 1;
	}
	else if (fflush(fp) != 0)
	{
		printf("%d: fflush() failed\n", __LINE__);
		result = 1;
	}
	else if (lseek(fd, 0, SEEK_CUR) != 0)
	{
		printf("%d: lseek() returned different position\n", __LINE__);
		result = 1;
	}
	else if (fread(buf, sizeof(outstr) - 1, 1, fp) != 1)
	{
		printf("%d: fread() failed\n", __LINE__);
		result = 1;
	}
	else if (memcmp(buf, outstr, sizeof(outstr) - 1) != 0)
	{
		printf("%d: content after fseeko(,,SEEK_SET) wrong\n", __LINE__);
		result = 1;
	}

	/* Go back to the beginning of the file: from the end.  */
	if (fseek(fp, -((int) sizeof(outstr) - 1), SEEK_END) != 0)
	{
		printf("%d: fseek(fp, 0, SEEK_SET) failed\n", __LINE__);
		result = 1;
	}
	else if (fflush(fp) != 0)
	{
		printf("%d: fflush() failed\n", __LINE__);
		result = 1;
	}
	else if (lseek(fd, 0, SEEK_CUR) != 0)
	{
		printf("%d: lseek() returned different position\n", __LINE__);
		result = 1;
	}
	else if (fread(buf, sizeof(outstr) - 1, 1, fp) != 1)
	{
		printf("%d: fread() failed\n", __LINE__);
		result = 1;
	}
	else if (memcmp(buf, outstr, sizeof(outstr) - 1) != 0)
	{
		printf("%d: content after fseek(,,SEEK_SET) wrong\n", __LINE__);
		result = 1;
	}

	/* Now with fseeko.  */
	if (fseeko(fp, -((int) sizeof(outstr) - 1), SEEK_END) != 0)
	{
		printf("%d: fseeko(fp, 0, SEEK_SET) failed\n", __LINE__);
		result = 1;
	}
	else if (fflush(fp) != 0)
	{
		printf("%d: fflush() failed\n", __LINE__);
		result = 1;
	}
	else if (lseek(fd, 0, SEEK_CUR) != 0)
	{
		printf("%d: lseek() returned different position\n", __LINE__);
		result = 1;
	}
	else if (fread(buf, sizeof(outstr) - 1, 1, fp) != 1)
	{
		printf("%d: fread() failed\n", __LINE__);
		result = 1;
	}
	else if (memcmp(buf, outstr, sizeof(outstr) - 1) != 0)
	{
		printf("%d: content after fseeko(,,SEEK_SET) wrong\n", __LINE__);
		result = 1;
	}

	if (fwrite(outstr, sizeof(outstr) - 1, 1, fp) != 1)
	{
		printf("%d: write error 2\n", __LINE__);
		result = 1;
		goto out;
	}

	if (fwrite(outstr, sizeof(outstr) - 1, 1, fp) != 1)
	{
		printf("%d: write error 3\n", __LINE__);
		result = 1;
		goto out;
	}

	if (fwrite(outstr, sizeof(outstr) - 1, 1, fp) != 1)
	{
		printf("%d: write error 4\n", __LINE__);
		result = 1;
		goto out;
	}

	if (fwrite(outstr, sizeof(outstr) - 1, 1, fp) != 1)
	{
		printf("%d: write error 5\n", __LINE__);
		result = 1;
		goto out;
	}

	if (fputc('1', fp) == EOF || fputc('2', fp) == EOF)
	{
		printf("%d: cannot add characters at the end\n", __LINE__);
		result = 1;
		goto out;
	}

	/* Check the access time.  */
	if (fstat(fd, &st1) < 0)
	{
		printf("%d: fstat64() before fseeko() failed\n\n", __LINE__);
		result = 1;
	}
	else
	{
		sleep(1);

		if (fseek(fp, -(2 + 2 * (sizeof(outstr) - 1)), SEEK_CUR) != 0)
		{
			printf("%d: fseek() after write characters failed\n", __LINE__);
			result = 1;
			goto out;
		}
		else
		{

			time_t t;
			/* Make sure the timestamp actually can be different.  */
			sleep(1);
			t = time(NULL);

			if (fstat(fd, &st2) < 0)
			{
				printf("%d: fstat64() after fseeko() failed\n\n", __LINE__);
				result = 1;
			}
			if (st1.st_ctime >= t)
			{
				printf("%d: st_ctime not updated\n", __LINE__);
				result = 1;
			}
			if (st1.st_mtime >= t)
			{
				printf("%d: st_mtime not updated\n", __LINE__);
				result = 1;
			}
			if (st1.st_ctime >= st2.st_ctime)
			{
				printf("%d: st_ctime not changed\n", __LINE__);
				result = 1;
			}
			if (st1.st_mtime >= st2.st_mtime)
			{
				printf("%d: st_mtime not changed\n", __LINE__);
				result = 1;
			}
		}
	}

	if (fread(buf, 1, 2 + 2 * (sizeof(outstr) - 1), fp) != 2 + 2
			* (sizeof(outstr) - 1))
	{
		printf("%d: reading 2 records plus bits failed\n", __LINE__);
		result = 1;
	}
	else if (memcmp(buf, outstr, sizeof(outstr) - 1) != 0 || memcmp(
			&buf[sizeof(outstr) - 1], outstr, sizeof(outstr) - 1) != 0 || buf[2
			* (sizeof(outstr) - 1)] != '1' || buf[2 * (sizeof(outstr) - 1) + 1]
			!= '2')
	{
		printf("%d: reading records failed\n", __LINE__);
		result = 1;
	}
	else if (ungetc('9', fp) == EOF)
	{
		printf("%d: ungetc() failed\n", __LINE__);
		result = 1;
	}
	else if (fseek(fp, -(2 + 2 * (sizeof(outstr) - 1)), SEEK_END) != 0)
	{
		printf("%d: fseek after ungetc failed\n", __LINE__);
		result = 1;
	}
	else if (fread(buf, 1, 2 + 2 * (sizeof(outstr) - 1), fp) != 2 + 2
			* (sizeof(outstr) - 1))
	{
		printf("%d: reading 2 records plus bits failed\n", __LINE__);
		result = 1;
	}
	else if (memcmp(buf, outstr, sizeof(outstr) - 1) != 0 || memcmp(
			&buf[sizeof(outstr) - 1], outstr, sizeof(outstr) - 1) != 0 || buf[2
			* (sizeof(outstr) - 1)] != '1')
	{
		printf("%d: reading records for the second time failed\n", __LINE__);
		result = 1;
	}
	else if (buf[2 * (sizeof(outstr) - 1) + 1] == '9')
	{
		printf("%d: unget character not ignored\n", __LINE__);
		result = 1;
	}
	else if (buf[2 * (sizeof(outstr) - 1) + 1] != '2')
	{
		printf("%d: unget somehow changed character\n", __LINE__);
		result = 1;
	}

	fclose(fp);

	fp = fopen(fname, "r");
	if (fp == NULL)
	{
		printf("%d: fopen() failed\n\n", __LINE__);
		result = 1;
	}
	else if (fstat(fileno(fp), &st1) < 0)
	{
		printf("%d: fstat64() before fseeko() failed\n\n", __LINE__);
		result = 1;
	}
	else if (fseeko(fp, 0, SEEK_END) != 0)
	{
		printf("%d: fseeko(fp, 0, SEEK_END) failed\n", __LINE__);
		result = 1;
	}
	else if (ftello(fp) != st1.st_size)
	{
		printf("%d: fstat64 st_size %zd ftello %zd\n", __LINE__,
				(size_t) st1.st_size, (size_t) ftello(fp));
		result = 1;
	}
	else
		printf("%d: SEEK_END works\n", __LINE__);
	if (fp != NULL)
		fclose(fp);

	fp = fopen(fname, "r");
	if (fp == NULL)
	{
		printf("%d: fopen() failed\n\n", __LINE__);
		result = 1;
	}
	else if (fstat(fileno(fp), &st1) < 0)
	{
		printf("%d: fstat64() before fgetc() failed\n\n", __LINE__);
		result = 1;
	}
	else if (fgetc(fp) == EOF)
	{
		printf("%d: fgetc() before fseeko() failed\n\n", __LINE__);
		result = 1;
	}
	else if (fseeko(fp, 0, SEEK_END) != 0)
	{
		printf("%d: fseeko(fp, 0, SEEK_END) failed\n", __LINE__);
		result = 1;
	}
	else if (ftello(fp) != st1.st_size)
	{
		printf("%d: fstat64 st_size %zd ftello %zd\n", __LINE__,
				(size_t) st1.st_size, (size_t) ftello(fp));
		result = 1;
	}
	else
		printf("%d: SEEK_END works\n", __LINE__);
	if (fp != NULL)
		fclose(fp);

	out: unlink(fname);

	return result;
}
FINSH_FUNCTION_EXPORT(libc_fseek, lseek test for libc);
