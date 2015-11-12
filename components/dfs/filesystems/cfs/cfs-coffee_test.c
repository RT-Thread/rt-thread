/*********************************************************************************************************
**
**                                苏州诺金智通信息科技有限公司
**
**                               Copyright All Rights Reserved
**
**--------------文件信息--------------------------------------------------------------------------------
**
** 文 件 名: cfs_test.c
**
** 创 建 人: Urey(风飘柳絮)
**
** 创建日期: 2015年11月12日
**
** 描    述: TODO
*********************************************************************************************************/

#include <cfs.h>

#define FILE_SIZE 512

/*--------------------------------------------------------------------------*/
int
coffee_file_test(void)
{
  int error;
  int wfd, rfd, afd;
  unsigned char buf[256], buf2[11];
  int r, i, j, total_read;
  unsigned offset;

  cfs_remove("T1.bin");
  cfs_remove("T2");
  cfs_remove("T3");
  cfs_remove("T4");
  cfs_remove("T5");
  wfd = rfd = afd = -1;

  for(r = 0; r < sizeof(buf); r++) {
    buf[r] = r;
  }

  PRINTF("TEST 1\n");

  /* Test 1: Open for writing. */
  wfd = cfs_open("T1.bin", CFS_WRITE);
  if(wfd < 0) {
    FAIL(-1);
  }

  PRINTF("PASSED\n");
  PRINTF("TEST ");
  PRINTF("2\n");

  /* Test 2: Write buffer. */
  r = cfs_write(wfd, buf, sizeof(buf));
  if(r < 0) {
    FAIL(-2);
  } else if(r < sizeof(buf)) {
    FAIL(-3);
  }

  PRINTF("PASSED\n");
  PRINTF("TEST ");
  PRINTF("3\n");

  /* Test 3: Deny reading. */
  r = cfs_read(wfd, buf, sizeof(buf));
  if(r >= 0) {
    FAIL(-4);
  }

  PRINTF("PASSED\n");
  PRINTF("TEST ");
  PRINTF("4\n");

  /* Test 4: Open for reading. */
  rfd = cfs_open("T1", CFS_READ);
  if(rfd < 0) {
    FAIL(-5);
  }

  PRINTF("PASSED\n");
  PRINTF("TEST ");
  PRINTF("5\n");

  /* Test 5: Write to read-only file. */
  r = cfs_write(rfd, buf, sizeof(buf));
  if(r >= 0) {
    FAIL(-6);
  }
  PRINTF("PASSED\n");
  PRINTF("TEST ");
  PRINTF("7\n");

  /* Test 7: Read the buffer written in Test 2. */
  rt_memset(buf, 0, sizeof(buf));
  r = cfs_read(rfd, buf, sizeof(buf));
  if(r < 0) {
    FAIL(-8);
  } else if(r < sizeof(buf)) {
    PRINTF("r=%d\n", r);
    FAIL(-9);
  }

  PRINTF("PASSED\n");
  PRINTF("TEST ");
  PRINTF("8\n");

  /* Test 8: Verify that the buffer is correct. */
  for(r = 0; r < sizeof(buf); r++) {
    if(buf[r] != r) {
      PRINTF("r=%d. buf[r]=%d\n", r, buf[r]);
      FAIL(-10);
    }
  }

  PRINTF("PASSED\n");
  PRINTF("TEST ");
  PRINTF("9\n");

  /* Test 9: Seek to beginning. */
  if(cfs_seek(wfd, 0, CFS_SEEK_SET) != 0) {
    FAIL(-11);
  }

  PRINTF("PASSED\n");
  PRINTF("TEST ");
  PRINTF("10\n");

  /* Test 10: Write to the log. */
  r = cfs_write(wfd, buf, sizeof(buf));
  if(r < 0) {
    FAIL(-12);
  } else if(r < sizeof(buf)) {
    FAIL(-13);
  }

  PRINTF("PASSED\n");
  PRINTF("TEST ");
  PRINTF("11\n");

  /* Test 11: Read the data from the log. */
  cfs_seek(rfd, 0, CFS_SEEK_SET);
  rt_memset(buf, 0, sizeof(buf));
  r = cfs_read(rfd, buf, sizeof(buf));
  if(r < 0) {
    FAIL(-14);
  } else if(r < sizeof(buf)) {
    FAIL(-15);
  }

  PRINTF("PASSED\n");
  PRINTF("TEST ");
  PRINTF("12\n");

  /* Test 12: Verify that the data is correct. */
  for(r = 0; r < sizeof(buf); r++) {
    if(buf[r] != r) {
      FAIL(-16);
    }
  }

  PRINTF("PASSED\n");
  PRINTF("TEST ");
  PRINTF("13\n");

  /* Test 13: Write a reversed buffer to the file. */
  for(r = 0; r < sizeof(buf); r++) {
    buf[r] = sizeof(buf) - r - 1;
  }
  if(cfs_seek(wfd, 0, CFS_SEEK_SET) != 0) {
    FAIL(-17);
  }
  r = cfs_write(wfd, buf, sizeof(buf));
  if(r < 0) {
    FAIL(-18);
  } else if(r < sizeof(buf)) {
    FAIL(-19);
  }
  if(cfs_seek(rfd, 0, CFS_SEEK_SET) != 0) {
    FAIL(-20);
  }

  PRINTF("PASSED\n");
  PRINTF("TEST ");
  PRINTF("14\n");

  /* Test 14: Read the reversed buffer. */
  cfs_seek(rfd, 0, CFS_SEEK_SET);
  rt_memset(buf, 0, sizeof(buf));
  r = cfs_read(rfd, buf, sizeof(buf));
  if(r < 0) {
    FAIL(-21);
  } else if(r < sizeof(buf)) {
    PRINTF("r = %d\n", r);
    FAIL(-22);
  }

  PRINTF("PASSED\n");
  PRINTF("TEST ");
  PRINTF("15\n");

  /* Test 15: Verify that the data is correct. */
  for(r = 0; r < sizeof(buf); r++) {
    if(buf[r] != sizeof(buf) - r - 1) {
      FAIL(-23);
    }
  }

  cfs_close(rfd);
  cfs_close(wfd);

  if(cfs_coffee_reserve("T2", FILE_SIZE) < 0) {
    FAIL(-24);
  }

  PRINTF("PASSED\n");
  PRINTF("TEST ");
  PRINTF("16\n");

  /* Test 16: Test multiple writes at random offset. */
  for(r = 0; r < 100; r++) {
    wfd = cfs_open("T2", CFS_WRITE | CFS_READ);
    if(wfd < 0) {
      FAIL(-25);
    }
    offset = rand() % FILE_SIZE;
    for(r = 0; r < sizeof(buf); r++) {
      buf[r] = r;
    }
    if(cfs_seek(wfd, offset, CFS_SEEK_SET) != offset) {
      FAIL(-26);
    }
    if(cfs_write(wfd, buf, sizeof(buf)) != sizeof(buf)) {
      FAIL(-27);
    }
    if(cfs_seek(wfd, offset, CFS_SEEK_SET) != offset) {
      FAIL(-28);
    }
    rt_memset(buf, 0, sizeof(buf));
    if(cfs_read(wfd, buf, sizeof(buf)) != sizeof(buf)) {
      FAIL(-29);
    }
    for(i = 0; i < sizeof(buf); i++) {
      if(buf[i] != i) {
        PRINTF("buf[%d] != %d\n", i, buf[i]);
        FAIL(-30);
      }
    }
  }
  PRINTF("PASSED\n");
  PRINTF("TEST ");
  PRINTF("17\n");

  /* Test 17: Append data to the same file many times. */
#define APPEND_BYTES 3000
#define BULK_SIZE 10
  for(i = 0; i < APPEND_BYTES; i += BULK_SIZE) {
    afd = cfs_open("T3", CFS_WRITE | CFS_APPEND);
    if(afd < 0) {
      FAIL(-31);
    }
    for(j = 0; j < BULK_SIZE; j++) {
      buf[j] = 1 + ((i + j) & 0x7f);
    }
    if((r = cfs_write(afd, buf, BULK_SIZE)) != BULK_SIZE) {
      PRINTF("Count:%d, r=%d\n", i, r);
      FAIL(-32);
    }
    cfs_close(afd);
  }

  PRINTF("PASSED\n");
  PRINTF("TEST ");
  PRINTF("18\n");

  /* Test 18: Read back the data written in Test 17 and verify. */
  afd = cfs_open("T3", CFS_READ);
  if(afd < 0) {
    FAIL(-33);
  }
  total_read = 0;
  while((r = cfs_read(afd, buf2, sizeof(buf2))) > 0) {
    for(j = 0; j < r; j++) {
      if(buf2[j] != 1 + ((total_read + j) & 0x7f)) {
        FAIL(-34);
      }
    }
    total_read += r;
  }
  if(r < 0) {
    PRINTF("FAIL:-35 r=%d\n", r);
    FAIL(-35);
  }
  if(total_read != APPEND_BYTES) {
    PRINTF("FAIL:-35 total_read=%d\n", total_read);
    FAIL(-35);
  }
  cfs_close(afd);

  PRINTF("PASSED\n");
  PRINTF("TEST ");
  PRINTF("19\n");

  /* T4 */
  /*
   * file T4 and T5 writing forces to use garbage collector in greedy mode
   * this test is designed for 10kb of file system
   */
#define APPEND_BYTES_1 2000
#define BULK_SIZE_1 10
  for(i = 0; i < APPEND_BYTES_1; i += BULK_SIZE_1) {
    afd = cfs_open("T4", CFS_WRITE | CFS_APPEND);
    if(afd < 0) {
      FAIL(-36);
    }
    for(j = 0; j < BULK_SIZE_1; j++) {
      buf[j] = 1 + ((i + j) & 0x7f);
    }

    if((r = cfs_write(afd, buf, BULK_SIZE_1)) != BULK_SIZE_1) {
      PRINTF("Count:%d, r=%d\n", i, r);
      FAIL(-37);
    }
    cfs_close(afd);
  }

  afd = cfs_open("T4", CFS_READ);
  if(afd < 0) {
    FAIL(-38);
  }

  total_read = 0;
  while((r = cfs_read(afd, buf2, sizeof(buf2))) > 0) {
    for(j = 0; j < r; j++) {
      if(buf2[j] != 1 + ((total_read + j) & 0x7f)) {
        PRINTF("FAIL:-39, total_read=%d r=%d\n", total_read, r);
        FAIL(-39);
      }
    }
    total_read += r;
  }
  if(r < 0) {
    PRINTF("FAIL:-40 r=%d\n", r);
    FAIL(-40);
  }
  if(total_read != APPEND_BYTES_1) {
    PRINTF("FAIL:-41 total_read=%d\n", total_read);
    FAIL(-41);
  }
  cfs_close(afd);

  /* T5 */
  PRINTF("PASSED\n");
  PRINTF("TEST ");
  PRINTF("20\n");
#define APPEND_BYTES_2 1000
#define BULK_SIZE_2 10
  for(i = 0; i < APPEND_BYTES_2; i += BULK_SIZE_2) {
    afd = cfs_open("T5", CFS_WRITE | CFS_APPEND);
    if(afd < 0) {
      FAIL(-42);
    }
    for(j = 0; j < BULK_SIZE_2; j++) {
      buf[j] = 1 + ((i + j) & 0x7f);
    }

    if((r = cfs_write(afd, buf, BULK_SIZE_2)) != BULK_SIZE_2) {
      PRINTF("Count:%d, r=%d\n", i, r);
      FAIL(-43);
    }

    cfs_close(afd);
  }

  afd = cfs_open("T5", CFS_READ);
  if(afd < 0) {
    FAIL(-44);
  }
  total_read = 0;
  while((r = cfs_read(afd, buf2, sizeof(buf2))) > 0) {
    for(j = 0; j < r; j++) {
      if(buf2[j] != 1 + ((total_read + j) & 0x7f)) {
        PRINTF("FAIL:-45, total_read=%d r=%d\n", total_read, r);
        FAIL(-45);
      }
    }
    total_read += r;
  }
  if(r < 0) {
    PRINTF("FAIL:-46 r=%d\n", r);
    FAIL(-46);
  }
  if(total_read != APPEND_BYTES_2) {
    PRINTF("FAIL:-47 total_read=%d\n", total_read);
    FAIL(-47);
  }
  cfs_close(afd);

  PRINTF("PASSED\n");

  error = 0;
      cfs_close(wfd);
  cfs_close(rfd);
  cfs_close(afd);
    return error;
end:
  cfs_close(wfd);
  cfs_close(rfd);
  cfs_close(afd);
  return error;
}
