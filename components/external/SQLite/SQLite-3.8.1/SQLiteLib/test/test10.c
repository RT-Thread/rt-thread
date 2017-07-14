#include <stdio.h>
#include <sqlite3.h>
#include "finsh.h"

static int callback(void *NotUsed, int argc, char **argv, char **azColName){
  int i;
  for(i=0; i<argc; i++){
    rt_kprintf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
  }
  rt_kprintf("\n");
  return 0;
}

int test10_main(void){
  static int step = 0;
  int argc = 4;
  char *argv[4] = {"test10_main", "test.db", 
            "create table mytable(entry1 int)",
            "drop table mytable"};
  sqlite3 *db;
  char *zErrMsg = 0;
  int rc;

  if( argc<3 ){
    rt_kprintf("Usage: %s DATABASE SQL-STATEMENT\n", argv[0]);
    return(1);
  }
  rt_kprintf("ready open %s\n", argv[1]);
  rc = sqlite3_open(argv[1], &db);

  if( rc ){
    rt_kprintf("Can't open database: %s\n", sqlite3_errmsg(db));
    sqlite3_close(db);
    return(1);
  }
  else{
    rt_kprintf("open %s success\n", argv[1]);
  }

  if (step == 0) {
      rt_kprintf("SQL exec: %s\n", argv[2]);
      rc = sqlite3_exec(db, argv[2], callback, 0, &zErrMsg);
      if( rc!=SQLITE_OK ){
        rt_kprintf("SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
      }
      else{
        rt_kprintf("SQL exec: %s success\n", argv[2]);
      }
  }
  else {
      rt_kprintf("SQL exec: %s\n", argv[3]);
      rc = sqlite3_exec(db, argv[3], callback, 0, &zErrMsg);
      if( rc!=SQLITE_OK ){
        rt_kprintf("SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
      }
      else{
        rt_kprintf("SQL exec: %s success\n", argv[3]);
      }
  }

  step = !step;
  
  sqlite3_close(db);
  return 0;
}
FINSH_FUNCTION_EXPORT(test10_main, sqlite test)