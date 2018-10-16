#ifndef __USER_INFO_H__
#define __USER_INFO_H__

#include <na_queue.h>

#define ENTITY_TYPE		userinfo_t

typedef struct userinfo_s{
	unsigned int id;
    unsigned int userid;
    char username[32];
    na_queue_t queue;
}ENTITY_TYPE;

int userinfo_get_by_id(ENTITY_TYPE *e, int id);
int userinfo_get_all(na_queue_t * q);
int userinfo_add(ENTITY_TYPE * e);
int userinfo_del(int id);
int userinfo_del_all(void);
int userinfo_update(ENTITY_TYPE * e);
void userinfo_free_queue(na_queue_t *h);
void userinfo_print_queue(na_queue_t *q);

#endif

