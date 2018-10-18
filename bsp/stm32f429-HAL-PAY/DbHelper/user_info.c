#include <rtthread.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>
#include <dbhelper.h>
#include <user_info.h>

static int userinfo_bind_for_insert(sqlite3_stmt * stmt,int index,void * arg)
{
	int rc;
	ENTITY_TYPE * e = arg;
	sqlite3_bind_int(stmt,1,e->userid);
	sqlite3_bind_text(stmt,2,e->username,strlen(e->username),NULL);
	rc = sqlite3_step(stmt);
	if (rc != SQLITE_DONE)
		return rc;
	return SQLITE_OK;
}
static int userinfo_bind_for_update(sqlite3_stmt * stmt,int index,void * arg)
{
	int rc;
	ENTITY_TYPE * e = arg;
	sqlite3_bind_int(stmt,1,e->userid);
	sqlite3_bind_text(stmt,2,e->username,strlen(e->username),NULL);
	sqlite3_bind_int(stmt,3,e->id);
	rc = sqlite3_step(stmt);
	if (rc != SQLITE_DONE)
		return rc;
	return SQLITE_OK;
}
static int userinfo_create(sqlite3_stmt * stmt,void * arg)
{	
	ENTITY_TYPE * e = arg;
	int ret = sqlite3_step(stmt);
	if(ret != SQLITE_ROW)
	{
		return 0;
	}
	else
	{
		e->id = db_stmt_get_int(stmt,0);
		e->userid = db_stmt_get_int(stmt,1);
        db_stmt_get_text(stmt,2,e->username);
	}
	return ret;
}

//返回队列的成员个数
static int userinfo_create_queue(sqlite3_stmt * stmt,void * arg)
{
	na_queue_t * q = arg;
	na_queue_init(q);
	ENTITY_TYPE * e;
	int ret,count = 0;
	ret = sqlite3_step(stmt);
	if(ret != SQLITE_ROW)
	{
		return 0;
	}
	do
	{
		e = rt_calloc(sizeof(ENTITY_TYPE),1);
		if(!e)
		{
			goto CREATE_USERINFO_FAIL;
		}
		e->id = db_stmt_get_int(stmt,0);
		e->userid = db_stmt_get_int(stmt,1);
		db_stmt_get_text(stmt,2,e->username);
		na_queue_insert_tail(q,&(e->queue));
		count ++;
	}
	while((ret = sqlite3_step(stmt)) == SQLITE_ROW);
	return count;
CREATE_USERINFO_FAIL:
	userinfo_free_queue(q);
	return 0;
}

void userinfo_print_queue(na_queue_t *q)
{
	ENTITY_TYPE * e=NULL;
	na_queue_foreach(e,q,ENTITY_TYPE,queue)
	{
		rt_kprintf("id:%d\tuserid:%d\tusername:%s\n",e->id, e->userid, e->username);
	}
}

//返回查询到的记录数
int userinfo_get_by_id(ENTITY_TYPE *e, int id)
{
	int res = db_query_by_varpara("select * from userinfo where id=?;", userinfo_create, e, "%d", id);
	return res;
}

//返回查询到的记录数
int userinfo_get_all(na_queue_t * q)
{
    return db_query_by_varpara("select * from userinfo;",userinfo_create_queue,q,NULL);
}

//操作成功返回0
int userinfo_add(ENTITY_TYPE * e)
{
    //return db_nonquery_operator("insert into userinfo(userid,username) values (?,?);",userinfo_bind_for_insert,e);
	return db_nonquery_by_varpara("insert into userinfo(userid,username) values (?,?);", "%d%s", e->userid, e->username);
}

int userinfo_update(ENTITY_TYPE * e)
{
	return db_nonquery_operator("update userinfo set userid=?,username=? where id=?;",userinfo_bind_for_update,e);
}

//操作成功返回0
int userinfo_del(int id)
{
	return db_nonquery_by_varpara("delete from userinfo where id=?;", "%d", id);
}

//操作成功返回0
int userinfo_del_all(void)
{
	return db_nonquery_operator("delete from userinfo;", 0, 0);
}

void userinfo_free_queue(na_queue_t *h)
{
    na_queue_t *head = h,*pos,*n;
    ENTITY_TYPE *p = RT_NULL;
    na_queue_for_each_safe(pos,n,head){
        p = na_queue_data(pos,ENTITY_TYPE,queue);
        rt_free(p);
    }
    na_queue_init(head);
}

static void list_all_user(void)
{
	rt_kprintf("test get all userinfo\n");
	na_queue_t *h = rt_calloc(sizeof(userinfo_t), 1);
	int ret = userinfo_get_all(h);
	userinfo_print_queue(h);
	rt_kprintf("record(s):%d\n", ret);
	userinfo_free_queue(h);
	rt_free(h);
}
static void user(uint8_t argc, char **argv)
{	
	if(argc<2)
	{
		list_all_user();
		return;
	}
	else
	{
		userinfo_t *u = rt_calloc(sizeof(userinfo_t),1);
		char* cmd = argv[1];
		if(rt_strcmp(cmd,"add")==0)
		{
			rt_uint16_t i, count = 0;			
			if(argc>=3)
			{
				count = atol(argv[2]);
			}
			if(count==0)count = 1;			
			rt_tick_t ticks = rt_tick_get();
			for(i=0;i<count;i++)
			{				
				u->userid = rt_tick_get()%9999;
				sprintf(u->username, "UserName%d", u->userid);
				int res = userinfo_add(u);
				if(res!=0)
				{
					rt_kprintf("add failed!userid:%d,username:%s\n", u->userid, u->username);
				}
			}
			ticks = rt_tick_get() - ticks;
			rt_kprintf("Add %d record(s): %dms, speed: %dms/record\n", count, ticks*1000/RT_TICK_PER_SECOND, ticks*1000/RT_TICK_PER_SECOND/count);
		}
		else if(rt_strcmp(cmd,"del")==0)
		{
			if(argc==2)
			{
				if(userinfo_del_all()==0)
				{
					rt_kprintf("Del all record success!\n");
				}
				else
				{
					rt_kprintf("Del all record failed!\n");
				}
			}
			else
			{
				rt_uint32_t id = atol(argv[2]);
				if(userinfo_del(id)==0)
				{
					rt_kprintf("Del record success with id:%d\n",id);
				}
				else
				{
					rt_kprintf("Del record failed with id:%d\n",id);
				}
			}
		}
		else if(rt_strcmp(cmd, "update")==0)
		{
			if(argc >= 5)
			{
				userinfo_t *u = rt_calloc(sizeof(userinfo_t), 1);
				u->id = atol(argv[2]);
				u->userid = atol(argv[3]);
				rt_strncpy(u->username, argv[4], rt_strlen(argv[4]));
				if(userinfo_update(u)==0)
				{
					rt_kprintf("update record success!\n");
				}
				else
				{
					rt_kprintf("update record failed!\n");
				}
				rt_free(u);
			}
			else
			{
				rt_kprintf("usage: user update id userid username\n");
			}
		}
		else
		{
			rt_uint32_t id = atol(argv[1]);
			if(userinfo_get_by_id(u, id)>0)
			{
				rt_kprintf("id:%d\t\tuserid:%d\tusername:%s\n", u->id, u->userid, u->username);
			}
			else
			{
				rt_kprintf("no record with id:%d\n", id);
			}
		}
		rt_free(u);
	}
}
MSH_CMD_EXPORT(user, user add del update query);
