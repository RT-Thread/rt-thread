#ifndef _NA_QUEUE_H_
#define _NA_QUEUE_H_

#include <stddef.h>

typedef struct na_queue_s na_queue_t;

struct na_queue_s {
  na_queue_t * prev;
  na_queue_t * next;
};


/* 初始化队列 */
#define na_queue_init(q)                      \
  (q)->prev = (q);        \
  (q)->next = (q)

/* 判断队列是否为空 */
#define na_queue_empty(h) \
  ((h) == (h)->prev)

/* 从头插入节点 */
#define na_queue_insert_head(h,x)     \
  (x)->next = (h)->next;              \
  (x)->next->prev = (x);              \
  (x)->prev = (h);                    \
  (h)->next = (x)

#define na_queue_insert_after na_queue_insert_head

/* 从末尾插入节点 */
#define na_queue_insert_tail(h,x)      \
  (x)->prev = (h)->prev;               \
  (x)->prev->next = x;                 \
  (x)->next = h;                       \
  (h)->prev = x 


/* 头指针对应的头节点 */
#define na_queue_head(h) (h)->next

/* 最后一个节点 */
#define na_queue_last(h) (h)->prev


#define na_queue_sentinel(h) (h)

/*下一个节点*/
#define na_queue_next(q) (q)->next

/* 前一个节点 */
#define na_queue_prev(q) (q)->prev

/* 移除一个节点 */
#define na_queue_remove(x)             \
  (x)->next->prev = (x)->prev;         \
  (x)->prev->next = (x)->next;         \
  (x)->prev = NULL;                    \
  (x)->next = NULL

/* 切分一个队列
 * h 头指针
 * q 需要拆分的头指针
 * n 拆分完成后另外一个队列的头指针
 */
#define na_queue_split(h,q,n)           \
    (n)->prev = (h)->prev;              \
    (n)->prev->next = n;                \
    (n)->next = q;                      \
    (h)->prev = (q)->prev;              \
    (h)->prev->next = h;                \
    (q)->prev = n;

/* 合并两个队列 */
#define na_queue_add(h,n)               \
  (h)->prev->next = (n)->next;          \
  (n)->next->prev = (h)->prev;          \
  (h)->prev = (n)->prev;                \
  (h)->prev->next = (h);

/* 根据队列指针，得到包含此队列指针的结构体
 * q 队列指针
 * type 返回的数据类型
 * link 数据项中对应的队列项名字
 */
#define na_queue_data(q, type, link)   \
    (type *) ((unsigned char *) q - offsetof(type, link))

/* 查找中间节点 */
na_queue_t *
na_queue_middle(na_queue_t * queue);

/* 对队列排序 */
void na_queue_sort(na_queue_t *queue,int (*cmp)(const na_queue_t *, const na_queue_t *));

/*遍历队列中节点的数据
 *q:传入的包含队列类型的结构体指针
 *s:队列的哨兵指针
 *type:包含队列的结构体类型
 *link:队列在结构体中的名字
*/
#define na_queue_foreach(q,s,type,link)          \
  na_queue_t * _head_ =NULL;                         \
  for(_head_=na_queue_head(s),q=na_queue_data(_head_,type,link);_head_!=s;_head_=na_queue_next(_head_),q=na_queue_data(_head_,type,link))

// add by hc
#define NA_QUEUE_INIT(name) {&(name),&(name)}
#define na_queue_is_last(head,node) ((node)->next == (head))
#define na_queue_for_each(pos,head) \
    for(pos = (head)->next;pos != head;pos = pos->next)
#define na_queue_for_each_safe(pos,n,head) \
    for(pos = (head)->next,n = pos->next;pos != (head);pos = n,n = pos->next)

#endif /* _NA_QUEUE_H_ */

