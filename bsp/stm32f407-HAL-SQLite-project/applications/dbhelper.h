#ifndef __DBHELPER_H__
#define __DBHELPER_H__
#include <sqlite3.h> 

#define DB_NAME "/spi/m.db"

#define DB_SQL_MAX_LEN 1024
void db_helper_init(void);
int db_create_database(const char* sqlstr);
//执行没有返回的SQL语句
int db_nonquery_operator(const char *sqlstr,int (*bind)(sqlite3_stmt *,int index,void * arg),void *param);
//执行没有返回的SQL语句的多值传参
int db_nonquery_by_varpara(const char *sql,const char *fmt,...);
//执行没有返回的SQL语句
int db_nonquery_transaction(int (*exec_sqls)(sqlite3 *db,void * arg),void *arg);
//执行多值传参的查询语句
int db_query_by_varpara(const char *sql,int (*create)(sqlite3_stmt *stmt,void *arg),void *arg,const char *fmt,...);
//执行查询并返回查询结果集的条数
int db_query_count_result(const char *sql);
//对sqlite3_column_blob的二次封装
int db_stmt_get_blob(sqlite3_stmt *stmt,int index,unsigned char *out);
//对sqlite3_column_text的二次封装
int db_stmt_get_text(sqlite3_stmt *stmt,int index,char *out);
//对sqlite3_column_int的二次封装
int db_stmt_get_int(sqlite3_stmt *stmt,int index);
//对sqlite3_column_double的二次封装
double db_stmt_get_double(sqlite3_stmt *stmt,int index);

#endif

