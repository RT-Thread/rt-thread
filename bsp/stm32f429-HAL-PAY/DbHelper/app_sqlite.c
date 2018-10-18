#include <rtthread.h>
#include <dfs_posix.h>
#include <dbhelper.h>

static int create_sqlite_db(void)
{
	int fd = open(DB_NAME, O_RDONLY);
	if(fd<0)
	{
		const char *sql = "CREATE TABLE userinfo(		\
				id INTEGER PRIMARY KEY AUTOINCREMENT,	\
				userid		INT			NOT NULL,		\
				username	varchar(32)	NOT NULL);";	
		return db_create_database(sql);
	}	
	else
	{
		close(fd);
		rt_kprintf("The database has already existed!\n");
	}	
	return -1;
}
MSH_CMD_EXPORT(create_sqlite_db, create sqlite db);

int app_sqlite_init(void)
{	
	db_helper_init();
	return 0;
}
INIT_APP_EXPORT(app_sqlite_init);

