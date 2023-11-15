#ifndef _AVL_H_
#define _AVL_H_

struct avl_node {
    struct avl_node* left;
    struct avl_node* right;
    int height;
};

typedef int (*avl_key_node_compare_t)(void*, struct avl_node*);
typedef int (*avl_node_node_compare_t)(struct avl_node*, struct avl_node*);

struct avl_root {
    struct avl_node* node;
    avl_key_node_compare_t kn_comp;
    avl_node_node_compare_t nn_comp;
};


#define INIT_AVL_ROOT(root, kn, nn) \
    do {                            \
        (root)->node = NULL;        \
        (root)->nn_comp = nn;       \
        (root)->kn_comp = kn;       \
    } while (0)

#define avl_entry(ptr, type, member)                      \
    ({                                                    \
        const typeof(((type*)0)->member)* __mptr = (ptr); \
        (type*)((char*)__mptr - offsetof(type, member));  \
    })

#ifndef offsetof
#define offsetof(TYPE, MEMBER) ((size_t) & ((TYPE*)0)->MEMBER)
#endif

#define AVL_MAX_DEPTH 32

#define AVL_LESS          0x1
#define AVL_EQUAL         0x2
#define AVL_GREATER       0x4
#define AVL_GREATER_EQUAL (AVL_GREATER | AVL_EQUAL)
#define AVL_LESS_EQUAL    (AVL_LESS | AVL_EQUAL)

struct avl_iter {
    struct avl_root* root;
    int depth;
    unsigned long branch;
    struct avl_node* path[AVL_MAX_DEPTH];
};

static inline int avl_tree_height(struct avl_node* node)
{
    if (!node) return 0;
    return node->height;
}

static inline void avl_set_height(struct avl_node* subroot)
{
    int left_height = avl_tree_height(subroot->left);
    int right_height = avl_tree_height(subroot->right);
    subroot->height =
        ((left_height > right_height) ? left_height : right_height) + 1;
}

static inline int avl_balance_factor(struct avl_node* node)
{
    return avl_tree_height(node->right) - avl_tree_height(node->left);
}

static inline struct avl_node* avl_left_rotate(struct avl_node* subroot)
{
    struct avl_node* k1 = subroot->right;
    struct avl_node* k2 = k1->left;
    subroot->right = k2;
    k1->left = subroot;
    avl_set_height(subroot);
    avl_set_height(k1);
    return k1;
}

static inline struct avl_node* avl_right_rotate(struct avl_node* subroot)
{
    struct avl_node* k1 = subroot->left;
    struct avl_node* k2 = k1->right;
    subroot->left = k2;
    k1->right = subroot;
    avl_set_height(subroot);
    avl_set_height(k1);
    return k1;
}

static inline struct avl_node* avl_left_right_rotate(struct avl_node* subroot)
{
    subroot->left = avl_left_rotate(subroot->left);
    return avl_right_rotate(subroot);
}

static inline struct avl_node* avl_right_left_rotate(struct avl_node* subroot)
{
    subroot->right = avl_right_rotate(subroot->right);
    return avl_left_rotate(subroot);
}

static inline struct avl_node* avl_fixup(int bf, struct avl_node* subroot)
{
    if (bf == 2) {
        struct avl_node* r = subroot->right;
        if (avl_tree_height(r->left) <= avl_tree_height(r->right)) {
            subroot = avl_left_rotate(subroot);
        } else {
            subroot = avl_right_left_rotate(subroot);
        }
    } else if (bf == -2) {
        struct avl_node* l = subroot->left;
        if (avl_tree_height(l->left) >= avl_tree_height(l->right)) {
            subroot = avl_right_rotate(subroot);
        } else {
            subroot = avl_left_right_rotate(subroot);
        }
    }
    return subroot;
}

static struct avl_node* avl_insert_recur(struct avl_node* node,
                                         struct avl_node* subroot,
                                         avl_node_node_compare_t nn_comp)
{
    if (!subroot) {
        node->left = NULL;
        node->right = NULL;
        node->height = 1;
        return node;
    }

    int comp = nn_comp(node, subroot);
    if (comp == -1) {
        subroot->left = avl_insert_recur(node, subroot->left, nn_comp);
    } else {
        subroot->right = avl_insert_recur(node, subroot->right, nn_comp);
    }

    avl_set_height(subroot);

    int bf = avl_balance_factor(subroot);
    if (bf == 2 || bf == -2) {
        subroot = avl_fixup(bf, subroot);
    }

    return subroot;
}

static inline void avl_insert(struct avl_node* node, struct avl_root* root)
{
    root->node = avl_insert_recur(node, root->node, root->nn_comp);
}

static inline struct avl_node* avl_erase_min(struct avl_node* subroot,
                                             struct avl_node** it)
{
    if (!subroot) {
        if (it) *it = NULL;
        return NULL;
    } else if (subroot->left) {
        subroot->left = avl_erase_min(subroot->left, it);
        avl_set_height(subroot);
    } else {
        if (it) *it = subroot;
        subroot = subroot->right;
        if (subroot) avl_set_height(subroot);
    }
    return subroot;
}

static inline struct avl_node* avl_erase_recur(struct avl_node* node,
                                               struct avl_node* subroot,
                                               avl_node_node_compare_t nn_comp)
{
    if (!subroot) {
        return NULL;
    }

    int comp = nn_comp(node, subroot);
    if (comp == -1) {
        subroot->left = avl_erase_recur(node, subroot->left, nn_comp);
    } else if (comp == 1) {
        subroot->right = avl_erase_recur(node, subroot->right, nn_comp);
    } else {
        if (!subroot->left)
            subroot = subroot->right;
        else if (!subroot->right)
            subroot = subroot->left;
        else {
            struct avl_node* tmp;
            subroot->right = avl_erase_min(subroot->right, &tmp);
            tmp->right = subroot->right;
            tmp->left = subroot->left;
            subroot = tmp;
        }
    }

    if (!subroot) return subroot;

    avl_set_height(subroot);

    int bf = avl_balance_factor(subroot);
    if (bf == 2 || bf == -2) {
        subroot = avl_fixup(bf, subroot);
    }

    return subroot;
}

static inline void avl_erase(struct avl_node* node, struct avl_root* root)
{
    root->node = avl_erase_recur(node, root->node, root->nn_comp);
}

static inline void avl_start_iter(struct avl_root* root, struct avl_iter* iter,
                                  void* key, int flags)
{
    int depth = 0;
    iter->root = root;
    iter->depth = ~0;
    iter->branch = 0;

    struct avl_node* cur = root->node;
    if (!cur) return;

    int target;
    if (flags & AVL_LESS)
        target = 1;
    else if (flags & AVL_GREATER)
        target = -1;
    else
        target = 0;

    while (1) {
        int cmp = root->kn_comp(key, cur);
        if (cmp == 0) {
            if (flags & AVL_EQUAL) {
                iter->depth = depth;
                break;
            }
            cmp = -target;
        }

        if (target && target == cmp) {
            iter->depth = depth;
        }
        cur = cmp < 0 ? cur->left : cur->right;
        if (!cur) break;

        if (cmp < 0) {
            iter->branch &= ~(1 << depth);
        } else {
            iter->branch |= (1 << depth);
        }

        iter->path[depth++] = cur;
    }
}

static inline struct avl_node* avl_get_iter(struct avl_iter* iter)
{
    if (iter->depth == ~0) return NULL;
    return (iter->depth == 0) ? iter->root->node : iter->path[iter->depth - 1];
}

static inline void avl_inc_iter(struct avl_iter* iter)
{
    if (iter->depth != ~0) {
        struct avl_node* cur =
            (iter->depth == 0) ? iter->root->node : iter->path[iter->depth - 1];
        cur = cur->right;
        if (!cur) {
            do {
                if (iter->depth == 0) {
                    iter->depth = ~0;
                    break;
                }
                iter->depth--;
            } while (iter->branch & (1 << iter->depth));
        } else {
            iter->branch |= (1 << iter->depth);
            iter->path[iter->depth++] = cur;
            while (1) {
                cur = cur->left;
                if (!cur) break;
                iter->branch &= ~(1 << iter->depth);
                iter->path[iter->depth++] = cur;
            }
        }
    }
}

static inline void avl_dec_iter(struct avl_iter* iter)
{
    if (iter->depth != ~0) {
        struct avl_node* cur =
            (iter->depth == 0) ? iter->root->node : iter->path[iter->depth - 1];
        cur = cur->left;
        if (!cur) {
            do {
                if (iter->depth == 0) {
                    iter->depth = ~0;
                    break;
                }
                iter->depth--;
            } while (!(iter->branch & (1 << iter->depth)));
        } else {
            iter->branch &= ~(1 << iter->depth);
            iter->path[iter->depth++] = cur;
            while (1) {
                cur = cur->right;
                if (!cur) break;
                iter->branch |= (1 << iter->depth);
                iter->path[iter->depth++] = cur;
            }
        }
    }
}

#endif
