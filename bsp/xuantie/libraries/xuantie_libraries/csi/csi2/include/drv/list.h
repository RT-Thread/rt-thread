#ifndef AOS_LIST_H
#define AOS_LIST_H

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Get offset of a member variable.
 *
 * @param[in]   type     the type of the struct this is embedded in.
 * @param[in]   member   the name of the variable within the struct.
 */
#define aos_offsetof(type, member)   ((size_t)&(((type *)0)->member))

/*
 * Get the struct for this entry.
 *
 * @param[in]   ptr     the list head to take the element from.
 * @param[in]   type    the type of the struct this is embedded in.
 * @param[in]   member  the name of the variable within the struct.
 */
#define aos_container_of(ptr, type, member) \
    ((type *) ((char *) (ptr) - aos_offsetof(type, member)))

/* for double link list */
typedef struct dlist_s {
    struct dlist_s *prev;
    struct dlist_s *next;
} dlist_t;

static inline void __dlist_add(dlist_t *node, dlist_t *prev, dlist_t *next)
{
    node->next = next;
    node->prev = prev;

    prev->next = node;
    next->prev = node;
}

/*
 * Get the struct for this entry.
 *
 * @param[in]   addr    the list head to take the element from.
 * @param[in]   type    the type of the struct this is embedded in.
 * @param[in]   member  the name of the dlist_t within the struct.
 */
#define dlist_entry(addr, type, member) \
    ((type *)((long)addr - aos_offsetof(type, member)))


static inline void dlist_add(dlist_t *node, dlist_t *queue)
{
    __dlist_add(node, queue, queue->next);
}

static inline void dlist_add_tail(dlist_t *node, dlist_t *queue)
{
    __dlist_add(node, queue->prev, queue);
}

static inline void dlist_del(dlist_t *node)
{
    dlist_t *prev = node->prev;
    dlist_t *next = node->next;

    prev->next = next;
    next->prev = prev;
}

static inline void dlist_init(dlist_t *node)
{
    node->next = node->prev = node;
}

static inline void INIT_AOS_DLIST_HEAD(dlist_t *list)
{
    list->next = list;
    list->prev = list;
}

static inline int dlist_empty(const dlist_t *head)
{
    return head->next == head;
}

/*
 * Initialise the list.
 *
 * @param[in]   list    the list to be inited.
 */
#define AOS_DLIST_INIT(list)  {&(list), &(list)}

/*
 * Get the first element from a list
 *
 * @param[in]   ptr     the list head to take the element from.
 * @param[in]   type    the type of the struct this is embedded in.
 * @param[in]   member  the name of the dlist_t within the struct.
 */
#define dlist_first_entry(ptr, type, member) \
    dlist_entry((ptr)->next, type, member)

/*
 * Iterate over a list.
 *
 * @param[in]   pos     the &struct dlist_t to use as a loop cursor.
 * @param[in]   head    he head for your list.
 */
#define dlist_for_each(pos, head) \
    for (pos = (head)->next; pos != (head); pos = pos->next)

/*
 * Iterate over a list safe against removal of list entry.
 *
 * @param[in]   pos     the &struct dlist_t to use as a loop cursor.
 * @param[in]   n       another &struct dlist_t to use as temporary storage.
 * @param[in]   head    he head for your list.
 */
#define dlist_for_each_safe(pos, n, head) \
    for (pos = (head)->next, n = pos->next; pos != (head); \
    pos = n, n = pos->next)

/*
 * Iterate over list of given type.
 *
 * @param[in]   queue   he head for your list.
 * @param[in]   node    the &struct dlist_t to use as a loop cursor.
 * @param[in]   type    the type of the struct this is embedded in.
 * @param[in]   member  the name of the dlist_t within the struct.
 */
#define dlist_for_each_entry(queue, node, type, member) \
    for (node = aos_container_of((queue)->next, type, member); \
         &node->member != (queue); \
         node = aos_container_of(node->member.next, type, member))

/*
 * Iterate over list of given type safe against removal of list entry.
 *
 * @param[in]   queue   the head for your list.
 * @param[in]   n       the type * to use as a temp.
 * @param[in]   node    the type * to use as a loop cursor.
 * @param[in]   type    the type of the struct this is embedded in.
 * @param[in]   member  the name of the dlist_t within the struct.
 */
#define dlist_for_each_entry_safe(queue, n, node, type, member) \
    for (node = aos_container_of((queue)->next, type, member),  \
         n = (queue)->next ? (queue)->next->next : NULL;        \
         &node->member != (queue);                              \
         node = aos_container_of(n, type, member), n = n ? n->next : NULL)

/*
 * Get the struct for this entry.
 * @param[in]   ptr     the list head to take the element from.
 * @param[in]   type    the type of the struct this is embedded in.
 * @param[in]   member  the name of the variable within the struct.
 */
#define list_entry(ptr, type, member) \
        aos_container_of(ptr, type, member)


/*
 * Iterate backwards over list of given type.
 *
 * @param[in]   pos     the type * to use as a loop cursor.
 * @param[in]   head    he head for your list.
 * @param[in]   member  the name of the dlist_t within the struct.
 * @param[in]   type    the type of the struct this is embedded in.
 */
#define dlist_for_each_entry_reverse(pos, head, member, type) \
    for (pos = list_entry((head)->prev, type, member);        \
         &pos->member != (head);                              \
         pos = list_entry(pos->member.prev, type, member))


/*
 * Get the list length.
 *
 * @param[in]  queue  the head for your list.
 */
int dlist_entry_number(dlist_t *queue);



/*
 * Initialise the list.
 *
 * @param[in]   name    the list to be initialized.
 */
#define AOS_DLIST_HEAD_INIT(name) { &(name), &(name) }

/*
 * Initialise the list.
 *
 * @param[in]   name    the list to be initialized.
 */
#define AOS_DLIST_HEAD(name) \
        dlist_t name = AOS_DLIST_HEAD_INIT(name)

/* for single link list */
typedef struct slist_s {
    struct slist_s *next;
} slist_t;

static inline void slist_add(slist_t *node, slist_t *head)
{
    node->next = head->next;
    head->next = node;
}

void slist_add_tail(slist_t *node, slist_t *head);

static inline void slist_del(slist_t *node, slist_t *head)
{
    while (head->next) {
        if (head->next == node) {
            head->next = node->next;
            break;
        }

        head = head->next;
    }
}

static inline int slist_empty(const slist_t *head)
{
    return !head->next;
}

static inline void slist_init(slist_t *head)
{
    head->next = 0;
}

static inline slist_t *slist_remove(slist_t *l, slist_t *n)
{
    /* remove slist head */
    struct slist_s *node = l;
    while (node->next && node->next != n) node = node->next;

    /* remove node */
    if (node->next != (slist_t *)0) node->next = node->next->next;

    return l;
}

static inline slist_t *slist_first(slist_t *l)
{
    return l->next;
}

static inline slist_t *slist_tail(slist_t *l)
{
    while (l->next) l = l->next;

    return l;
}

static inline slist_t *slist_next(slist_t *n)
{
    return n->next;
}

/*
* Iterate over list of given type.
*
* @param[in]   queue   he head for your list.
* @param[in]   node    the type * to use as a loop cursor.
* @param[in]   type    the type of the struct this is embedded in.
* @param[in]   member  the name of the slist_t within the struct.
*/
#define slist_for_each_entry(queue, node, type, member)        \
    for (node = (queue)->next? aos_container_of((queue)->next, type, member) : NULL; \
         node;                                        \
         node = node->member.next ? aos_container_of(node->member.next, type, member) : NULL)

/*
 * Iterate over list of given type safe against removal of list entry.
 *
 * @param[in]   queue   the head for your list.
 * @param[in]   tmp     the type * to use as a temp.
 * @param[in]   node    the type * to use as a loop cursor.
 * @param[in]   type    the type of the struct this is embedded in.
 * @param[in]   member  the name of the slist_t within the struct.
 */
#define slist_for_each_entry_safe(queue, tmp, node, type, member) \
    for (node = (queue)->next? aos_container_of((queue)->next, type, member) : NULL, \
         tmp = (queue)->next ? (queue)->next->next : NULL;        \
         node;                                           \
         node = tmp ? aos_container_of(tmp, type, member) : NULL, tmp = tmp ? tmp->next : NULL)

/*
 * Initialise the list.
 *
 * @param[in]   name    the list to be initialized.
 */
#define AOS_SLIST_HEAD_INIT(name) {0}

/*
 * Initialise the list.
 *
 * @param[in]   name    the list to be initialized.
 */
#define AOS_SLIST_HEAD(name) \
        slist_t name = AOS_SLIST_HEAD_INIT(name)

/*
 * Get the struct for this entry.
 * @param[in]   addr     the list head to take the element from.
 * @param[in]   type     the type of the struct this is embedded in.
 * @param[in]   member   the name of the slist_t within the struct.
 */
#define slist_entry(addr, type, member) (                                   \
    addr ? (type *)((long)addr - aos_offsetof(type, member)) : (type *)addr \
)

/*
* Get the first element from a list.
*
* @param[in]   ptr     the list head to take the element from.
* @param[in]   type    the type of the struct this is embedded in.
* @param[in]   member  the name of the slist_t within the struct.
*/
#define slist_first_entry(ptr, type, member) \
    slist_entry((ptr)->next, type, member)

/**
 * slist_tail_entry - get the tail element from a slist
 * @ptr:    the slist head to take the element from.
 * @type:   the type of the struct this is embedded in.
 * @member: the name of the slist_struct within the struct.
 *
 * Note, that slist is expected to be not empty.
 */
#define slist_tail_entry(ptr, type, member) \
    slist_entry(slist_tail(ptr), type, member)

/*
 * Get the list length.
 *
 * @param[in]   queue    the head for your list.
 */
int slist_entry_number(slist_t *queue);

#ifdef __cplusplus
}
#endif

#endif /* AOS_LIST_H */

