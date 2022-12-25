
/*
 * Copyright (c) 2016-2022 Bouffalolab.
 *
 * This file is part of
 *     *** Bouffalolab Software Dev Kit ***
 *      (see www.bouffalolab.com).
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *   1. Redistributions of source code must retain the above copyright notice,
 *      this list of conditions and the following disclaimer.
 *   2. Redistributions in binary form must reproduce the above copyright notice,
 *      this list of conditions and the following disclaimer in the documentation
 *      and/or other materials provided with the distribution.
 *   3. Neither the name of Bouffalo Lab nor the names of its contributors
 *      may be used to endorse or promote products derived from this software
 *      without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */


#ifndef _UTILS_LIST_H_
#define _UTILS_LIST_H_

#include <stddef.h>

struct utils_list_hdr
{
    struct utils_list_hdr *next;
};

struct utils_list
{
    /// pointer to first element of the list
    struct utils_list_hdr *first;
    /// pointer to the last element
    struct utils_list_hdr *last;
};


/*
 * FUNCTION DECLARATIONS
 ****************************************************************************************
 */
/**
 ****************************************************************************************
 * @brief Initialize a list to defaults values.
 * @param[in] list           Pointer to the list structure.
 ****************************************************************************************
 */
void utils_list_init(struct utils_list *list);

/**
 ****************************************************************************************
 * @brief Initialize a pool to default values, and initialize the relative free list.
 *
 * @param[in] list           Pointer to the list structure
 * @param[in] pool           Pointer to the pool to be initialized
 * @param[in] elmt_size      Size of one element of the pool
 * @param[in] elmt_cnt       Nb of elements available in the pool
 * @param[in] default_value  Pointer to the default value of each element (may be NULL)
 ****************************************************************************************
 */
void utils_list_pool_init(struct utils_list *list, void *pool, size_t elmt_size, unsigned int elmt_cnt, void *default_value);

/**
 ****************************************************************************************
 * @brief Add an element as last on the list.
 *
 * @param[in] list           Pointer to the list structure
 * @param[in] list_hdr       Pointer to the header to add at the end of the list
 ****************************************************************************************
 */
void utils_list_push_back(struct utils_list *list,
                       struct utils_list_hdr *list_hdr);

/**
 ****************************************************************************************
 * @brief Add an element as first on the list.
 *
 * @param[in] list           Pointer to the list structure
 * @param[in] list_hdr       Pointer to the header to add at the beginning of the list
 ****************************************************************************************
 */
void utils_list_push_front(struct utils_list *list, struct utils_list_hdr *list_hdr);
/**
 ****************************************************************************************
 * @brief Extract the first element of the list.
 *
 * @param[in] list           Pointer to the list structure
 *
 * @return The pointer to the element extracted, and NULL if the list is empty.
 ****************************************************************************************
 */
struct utils_list_hdr *utils_list_pop_front(struct utils_list *list);

/**
 ****************************************************************************************
 * @brief Search for a given element in the list, and extract it if found.
 *
 * @param[in] list           Pointer to the list structure
 * @param[in] list_hdr       Pointer to the searched element
 *
 * @return CO_EMPTY if the list is empty, CO_FAIL if the element not found in the list,
 * CO_OK else.
 ****************************************************************************************
 */
void utils_list_extract(struct utils_list *list, struct utils_list_hdr *list_hdr);

/**
 ****************************************************************************************
 * @brief Searched a given element in the list.
 *
 * @param[in] list           Pointer to the list structure
 * @param[in] list_hdr       Pointer to the searched element
 *
 * @return true if the element is found in the list, false otherwise
 ****************************************************************************************
 */
int utils_list_find(struct utils_list *list, struct utils_list_hdr *list_hdr);

/**
 ****************************************************************************************
 * @brief Insert an element in a sorted list.
 *
 * This primitive use a comparison function from the parameter list to select where the
 * element must be inserted.
 *
 * @param[in]  list     Pointer to the list.
 * @param[in]  element  Pointer to the element to insert.
 * @param[in]  cmp      Comparison function (return true if first element has to be inserted
 *                      before the second one).
 *
 * @return              Pointer to the element found and removed (NULL otherwise).
 ****************************************************************************************
 */
void utils_list_insert(struct utils_list * const list, struct utils_list_hdr * const element,
        int (*cmp)(struct utils_list_hdr const *elementA,
        struct utils_list_hdr const *elementB));

/**
 ****************************************************************************************
 * @brief Insert an element in a sorted list after the provided element.
 *
 * This primitive use a comparison function from the parameter list to select where the
 * element must be inserted.
 *
 * @param[in]  list           Pointer to the list.
 * @param[in]  prev_element   Pointer to the element to find in the list
 * @param[in]  element        Pointer to the element to insert.
 *
 * If prev_element is not found, the provided element is not inserted
 ****************************************************************************************
 */
void utils_list_insert_after(struct utils_list * const list, struct utils_list_hdr * const prev_element, struct utils_list_hdr * const element);

/**
 ****************************************************************************************
 * @brief Insert an element in a sorted list before the provided element.
 *
 * This primitive use a comparison function from the parameter list to select where the
 * element must be inserted.
 *
 * @param[in]  list           Pointer to the list.
 * @param[in]  next_element   Pointer to the element to find in the list
 * @param[in]  element        Pointer to the element to insert.
 *
 * If next_element is not found, the provided element is not inserted
 ****************************************************************************************
 */
void utils_list_insert_before(struct utils_list * const list, struct utils_list_hdr * const next_element, struct utils_list_hdr * const element);

/**
 ****************************************************************************************
 * @brief Concatenate two lists.
 * The resulting list is the list passed as the first parameter. The second list is
 * emptied.
 *
 * @param[in]  list1          First list (will get the result of the concatenation)
 * @param[in]  list2          Second list (will be emptied after the concatenation)
 ****************************************************************************************
 */
void utils_list_concat(struct utils_list *list1, struct utils_list *list2);

/**
 ****************************************************************************************
 * @brief Remove the element in the list after the provided element.
 *
 * This primitive removes an element in the list. It is assume that element is part of
 * the list.
 *
 * @param[in] list          Pointer to the list.
 * @param[in] prev_element  Pointer to the previous element.
 *                          NULL if @p element is the first element in the list
 * @param[in] element       Pointer to the element to remove.
 *
 ****************************************************************************************
 */
void utils_list_remove(struct utils_list *list, struct utils_list_hdr *prev_element, struct utils_list_hdr *element);
/**
 ****************************************************************************************
 * @brief Test if the list is empty.
 *
 * @param[in] list           Pointer to the list structure.
 *
 * @return true if the list is empty, false else otherwise.
 ****************************************************************************************
 */
static inline int utils_list_is_empty(const struct utils_list *const list)
{
    return (NULL == list->first);
}

/**
 ****************************************************************************************
 * @brief Return the number of element of the list.
 *
 * @param[in] list           Pointer to the list structure.
 *
 * @return The number of elements in the list.
 ****************************************************************************************
 */
unsigned int utils_list_cnt(const struct utils_list *const list);

/**
 ****************************************************************************************
 * @brief Pick the first element from the list without removing it.
 *
 * @param[in] list           Pointer to the list structure.
 *
 * @return First element address. Returns NULL pointer if the list is empty.
 ****************************************************************************************
 */
static inline struct utils_list_hdr *utils_list_pick(const struct utils_list *const list)
{
    return list->first;
}

static inline struct utils_list_hdr *utils_list_pick_last(const struct utils_list *const list)
{
    return list->last;
}

static inline struct utils_list_hdr *utils_list_next(const struct utils_list_hdr *const list_hdr)
{
    return list_hdr->next;
}


/*
 * Get offset of a member variable.
 *
 * @param[in]   type     the type of the struct this is embedded in.
 * @param[in]   member   the name of the variable within the struct.
 */
#define utils_offsetof(type, member)   ((size_t)&(((type *)0)->member))

/*
 * Get the struct for this entry.
 *
 * @param[in]   ptr     the list head to take the element from.
 * @param[in]   type    the type of the struct this is embedded in.
 * @param[in]   member  the name of the variable within the struct.
 */
#define utils_container_of(ptr, type, member) \
    ((type *) ((char *) (ptr) - utils_offsetof(type, member)))

/* for double link list */
typedef struct utils_dlist_s {
    struct utils_dlist_s *prev;
    struct utils_dlist_s *next;
} utils_dlist_t;

static inline void __utils_dlist_add(utils_dlist_t *node, utils_dlist_t *prev, utils_dlist_t *next)
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
 * @param[in]   member  the name of the utils_dlist_t within the struct.
 */
#define utils_dlist_entry(addr, type, member) \
    ((type *)((long)addr - utils_offsetof(type, member)))


static inline void utils_dlist_add(utils_dlist_t *node, utils_dlist_t *queue)
{
    __utils_dlist_add(node, queue, queue->next);
}

static inline void utils_dlist_add_tail(utils_dlist_t *node, utils_dlist_t *queue)
{
    __utils_dlist_add(node, queue->prev, queue);
}

static inline void utils_dlist_del(utils_dlist_t *node)
{
    utils_dlist_t *prev = node->prev;
    utils_dlist_t *next = node->next;

    prev->next = next;
    next->prev = prev;
}

static inline void utils_dlist_init(utils_dlist_t *node)
{
    node->next = node->prev = node;
}

static inline void INIT_UTILS_DLIST_HEAD(utils_dlist_t *list)
{
    list->next = list;
    list->prev = list;
}

static inline int utils_dlist_empty(const utils_dlist_t *head)
{
    return head->next == head;
}

/*
 * Initialise the list.
 *
 * @param[in]   list    the list to be inited.
 */
#define UTILS_DLIST_INIT(list)  {&(list), &(list)}

/*
 * Get the first element from a list
 *
 * @param[in]   ptr     the list head to take the element from.
 * @param[in]   type    the type of the struct this is embedded in.
 * @param[in]   member  the name of the utils_dlist_t within the struct.
 */
#define utils_dlist_first_entry(ptr, type, member) \
    utils_dlist_entry((ptr)->next, type, member)

/*
 * Iterate over a list.
 *
 * @param[in]   pos     the &struct utils_dlist_t to use as a loop cursor.
 * @param[in]   head    he head for your list.
 */
#define utils_dlist_for_each(pos, head) \
    for (pos = (head)->next; pos != (head); pos = pos->next)

/*
 * Iterate over a list safe against removal of list entry.
 *
 * @param[in]   pos     the &struct utils_dlist_t to use as a loop cursor.
 * @param[in]   n       another &struct utils_dlist_t to use as temporary storage.
 * @param[in]   head    he head for your list.
 */
#define utils_dlist_for_each_safe(pos, n, head) \
    for (pos = (head)->next, n = pos->next; pos != (head); \
    pos = n, n = pos->next)

/*
 * Iterate over list of given type.
 *
 * @param[in]   queue   he head for your list.
 * @param[in]   node    the &struct utils_dlist_t to use as a loop cursor.
 * @param[in]   type    the type of the struct this is embedded in.
 * @param[in]   member  the name of the utils_dlist_t within the struct.
 */
#define utils_dlist_for_each_entry(queue, node, type, member) \
    for (node = utils_container_of((queue)->next, type, member); \
         &node->member != (queue); \
         node = utils_container_of(node->member.next, type, member))

/*
 * Iterate over list of given type safe against removal of list entry.
 *
 * @param[in]   queue   the head for your list.
 * @param[in]   n       the type * to use as a temp.
 * @param[in]   node    the type * to use as a loop cursor.
 * @param[in]   type    the type of the struct this is embedded in.
 * @param[in]   member  the name of the utils_dlist_t within the struct.
 */
#define utils_dlist_for_each_entry_safe(queue, n, node, type, member) \
    for (node = utils_container_of((queue)->next, type, member),  \
         n = (queue)->next ? (queue)->next->next : NULL;        \
         &node->member != (queue);                              \
         node = utils_container_of(n, type, member), n = n ? n->next : NULL)

/*
 * Get the struct for this entry.
 * @param[in]   ptr     the list head to take the element from.
 * @param[in]   type    the type of the struct this is embedded in.
 * @param[in]   member  the name of the variable within the struct.
 */
#define utils_list_entry(ptr, type, member) \
        utils_container_of(ptr, type, member)


/*
 * Iterate backwards over list of given type.
 *
 * @param[in]   pos     the type * to use as a loop cursor.
 * @param[in]   head    he head for your list.
 * @param[in]   member  the name of the utils_dlist_t within the struct.
 * @param[in]   type    the type of the struct this is embedded in.
 */
#define utils_dlist_for_each_entry_reverse(pos, head, member, type) \
    for (pos = utils_list_entry((head)->prev, type, member);        \
         &pos->member != (head);                              \
         pos = utils_list_entry(pos->member.prev, type, member))


/*
 * Get the list length.
 *
 * @param[in]  queue  the head for your list.
 */
static inline int utils_dlist_entry_number(utils_dlist_t *queue)
{
	int num;
	utils_dlist_t *cur = queue;  
	for (num=0;cur->next != queue;cur=cur->next, num++)
		;
	
	return num; 
}



/*
 * Initialise the list.
 *
 * @param[in]   name    the list to be initialized.
 */
#define UTILS_DLIST_HEAD_INIT(name) { &(name), &(name) }

/*
 * Initialise the list.
 *
 * @param[in]   name    the list to be initialized.
 */
#define UTILS_DLIST_HEAD(name) \
        utils_dlist_t name = UTILS_DLIST_HEAD_INIT(name)

/* for single link list */
typedef struct utils_slist_s {
    struct utils_slist_s *next;
} utils_slist_t;

static inline void utils_slist_add(utils_slist_t *node, utils_slist_t *head)
{
    node->next = head->next;
    head->next = node;
}

static inline void utils_slist_add_tail(utils_slist_t *node, utils_slist_t *head)
{
    while (head->next) {
        head = head->next;
    }

    utils_slist_add(node, head);
}

static inline void utils_slist_append(utils_slist_t *l, utils_slist_t *n)
{
    utils_slist_t *node;

    node = l;
    while (node->next) node = node->next;

    /* append the node to the tail */
    node->next = n;
    n->next = NULL;
}

static inline void utils_slist_del(utils_slist_t *node, utils_slist_t *head)
{
    while (head->next) {
        if (head->next == node) {
            head->next = node->next;
            break;
        }

        head = head->next;
    }
}

static inline int utils_slist_empty(const utils_slist_t *head)
{
    return !head->next;
}

static inline void utils_slist_init(utils_slist_t *head)
{
    head->next = 0;
}

static inline utils_slist_t* utils_slist_first(utils_slist_t *l)
{
    return l->next;
}

static inline utils_slist_t* utils_slist_tail(utils_slist_t *l)
{
    while (l->next) l = l->next;

    return l;
}

static inline utils_slist_t* utils_slist_next(utils_slist_t *l)
{
    return l->next;
}

/*
* Iterate over list of given type.
*
* @param[in]   queue   he head for your list.
* @param[in]   node    the type * to use as a loop cursor.
* @param[in]   type    the type of the struct this is embedded in.
* @param[in]   member  the name of the utils_slist_t within the struct.
*/
#define utils_slist_for_each_entry(queue, node, type, member)        \
    for (node = utils_container_of((queue)->next, type, member); \
         &node->member;                                        \
         node = utils_container_of(node->member.next, type, member))

/*
 * Iterate over list of given type safe against removal of list entry.
 *
 * @param[in]   queue   the head for your list.
 * @param[in]   tmp     the type * to use as a temp.
 * @param[in]   node    the type * to use as a loop cursor.
 * @param[in]   type    the type of the struct this is embedded in.
 * @param[in]   member  the name of the utils_slist_t within the struct.
 */
#define utils_slist_for_each_entry_safe(queue, tmp, node, type, member) \
    for (node = utils_container_of((queue)->next, type, member),    \
         tmp = (queue)->next ? (queue)->next->next : NULL;        \
         &node->member;                                           \
         node = utils_container_of(tmp, type, member), tmp = tmp ? tmp->next : tmp)

/*
 * Initialise the list.
 *
 * @param[in]   name    the list to be initialized.
 */
#define UTILS_SLIST_HEAD_INIT(name) {0}

/*
 * Initialise the list.
 *
 * @param[in]   name    the list to be initialized.
 */
#define UTILS_SLIST_HEAD(name) \
        utils_slist_t name = UTILS_SLIST_HEAD_INIT(name)

/*
 * Get the struct for this entry.
 * @param[in]   addr     the list head to take the element from.
 * @param[in]   type     the type of the struct this is embedded in.
 * @param[in]   member   the name of the utils_slist_t within the struct.
 */
#define utils_slist_entry(addr, type, member) (                                   \
    addr ? (type *)((long)addr - utils_offsetof(type, member)) : (type *)addr \
)

/*
* Get the first element from a list.
*
* @param[in]   ptr     the list head to take the element from.
* @param[in]   type    the type of the struct this is embedded in.
* @param[in]   member  the name of the utils_slist_t within the struct.
*/
#define utils_slist_first_entry(ptr, type, member) \
    utils_slist_entry(utils_slist_next(ptr), type, member)


/*
* Get the last element from a list.
*
* @param[in]   ptr     the list head to take the element from.
* @param[in]   type    the type of the struct this is embedded in.
* @param[in]   member  the name of the utils_slist_t within the struct.
*/
#define utils_slist_tail_entry(ptr, type, member) \
    utils_slist_entry(utils_slist_tail(ptr), type, member)


/*
 * Get the list length.
 *
 * @param[in]   queue    the head for your list.
 */
static inline int utils_slist_entry_number(utils_slist_t *queue)
{
	int num;
    utils_slist_t *cur = queue;  
    for (num=0;cur->next;cur=cur->next, num++)
		;
	
    return num; 
}
#endif
