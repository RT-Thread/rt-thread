#ifndef	_LINUX_RBTREE_H
#define	_LINUX_RBTREE_H

#if defined (__GNUC__) 
#elif defined (MSVC)
#define __inline__ __inline 
#define inline __inline
#else
#endif

struct rb_node {
	struct rb_node *rb_left;	/* left element */
	struct rb_node *rb_right;	/* right element */
	struct rb_node *rb_parent;	/* parent element */
	int rb_color;			/* node color */
};

struct rb_root {
	struct rb_node *rb_node; /* root of the tree */
};

#ifndef NULL
#define NULL ((void *)0)
#endif

#if defined (__GNUC__) 
#define RB_ROOT ((struct rb_root){NULL})
#elif defined (MSVC)
#define RB_ROOT {NULL}//{struct rb_root _x = {NULL};}
#else
#endif

#define rb_entry(p, container, field)		\
	((container *) ((char *)p - ((char *)&(((container *)0)->field))))

#define RB_BLACK	0
#define RB_RED		1


extern void rb_insert_color(struct rb_node *, struct rb_root *);
extern void rb_erase(struct rb_node *, struct rb_root *);

/* Find logical next and previous nodes in a tree */
extern struct rb_node *rb_next(struct rb_node *);
extern struct rb_node *rb_prev(struct rb_node *);
extern struct rb_node *rb_first(struct rb_root *);

/* Fast replacement of a single node without remove/rebalance/add/rebalance */
extern void rb_replace_node(struct rb_node *victim, struct rb_node *new, 
			    struct rb_root *root);

static inline void rb_link_node(struct rb_node * node, struct rb_node * parent,
				struct rb_node ** rb_link)
{
	node->rb_parent = parent;
	node->rb_color = RB_RED;
	node->rb_left = node->rb_right = NULL;

	*rb_link = node;
}

#endif	/* _LINUX_RBTREE_H */
