
/**
 * Here is the assertions to ensure rightness of bst maintenance
 * After each insertion and delete, a tree must still be binary search tree,
 * and still remain balanced
 */

#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <mm_aspace.h>
#include <mm_private.h>

#define BUF_SIZE 1000000
static void *_start;
static void *_boundary;
static int _count;
static rt_varea_t _buf[BUF_SIZE];
#define RT_ASSERT assert

static void _print_varea(rt_varea_t varea, int depth)
{
    if (depth == 0)
    {
        printf("%p ", varea->start);
    }
    else
    {
        rt_varea_t lchild = VAREA_ENTRY(varea->node.node.avl_left);
        rt_varea_t rchild = VAREA_ENTRY(varea->node.node.avl_right);
        depth--;
        if (lchild)
            _print_varea(lchild, depth);
        else
            printf("0x**** ");

        if (rchild)
            _print_varea(rchild, depth);
        else
            printf("0x**** ");
    }
}
static void _print_tree(rt_aspace_t aspace)
{
    rt_varea_t varea = VAREA_ENTRY(aspace->tree.tree.root_node);
    if (!varea)
        return ;

    for (size_t i = 0; i < aspace->tree.tree.root_node->height; i++) {
        _print_varea(varea, i);
        putchar('\n');
    }

    return ;
}

static int _is_bst(rt_varea_t varea)
{
    rt_varea_t lchild = VAREA_ENTRY(varea->node.node.avl_left);
    rt_varea_t rchild = VAREA_ENTRY(varea->node.node.avl_right);
    if (lchild)
    {
        RT_ASSERT(lchild->node.node.parent == &varea->node.node);
        RT_ASSERT(varea->start > lchild->start);
    }
    if (rchild)
    {
        RT_ASSERT(rchild->node.node.parent == &varea->node.node);
        if (varea->start >= rchild->start)
        {
            RT_ASSERT(0);
        }
    }
    return 1;
}

/* return height of current varea */
static int _is_balanced(rt_varea_t varea)
{
    if (!varea)
    {
        return 1;
    }

    rt_varea_t lchild = VAREA_ENTRY(varea->node.node.avl_left);
    rt_varea_t rchild = VAREA_ENTRY(varea->node.node.avl_right);
    int lbal = _is_balanced(lchild);
    int rbal = _is_balanced(rchild);

    if (lbal && rbal)
    {
        int diff = lbal - rbal;
        if (diff > 1 || diff < -1)
        {
            printf("lbal %d, rbal %d\n", lbal, rbal);
            return 0;
        }
        else
        {
            int height = lbal > rbal ? lbal : rbal;
            return height + 1;
        }
    }
}

/* add bst assertion */
static int _check_asc_before(rt_varea_t varea, void *arg)
{
    if (varea->start >= _start && (!_boundary || varea->start >= _boundary) && _is_bst(varea))
    {
        _buf[_count] = varea;
        _start = varea->start;
        _boundary = varea->start + varea->size;
        _count++;
        RT_ASSERT(_count < BUF_SIZE);
    }
    else
    {
        RT_ASSERT(0);
    }
    return 0;
}

static int _check_asc_before_rev(rt_varea_t varea, void *arg)
{
    _count--;
    RT_ASSERT(varea == _buf[_count]);
    return 0;
}

static int _check_asc_after(rt_varea_t varea, void *arg)
{
    rt_varea_t add_elem = (rt_varea_t)arg;
    if (!_is_bst(varea))
    {
        RT_ASSERT(0);
    }

    if (varea == _buf[_count])
    {
        _buf[_count] = 0;
        _count++;
        RT_ASSERT(_count < BUF_SIZE);
    }
    else if (add_elem && add_elem == varea)
    {
        /* adding, skip adding elem */
    }
    else if (!add_elem && varea == _buf[_count + 1])
    {
        /* deleting */
        _buf[_count] = 0;
        _buf[_count] = 0;
        _count++;
        RT_ASSERT(_count < BUF_SIZE);
    }
    else
    {
        printf("add_elem %p, varea %p, _count %d, in buf %p\n",
            add_elem->start, varea->start, _count, _buf[_count]);
        RT_ASSERT(0);
    }
    return 0;
}

static int _aspace_traversal(rt_aspace_t aspace, int (*fn)(rt_varea_t varea, void *arg), void *arg)
{
    rt_varea_t varea = ASPACE_VAREA_FIRST(aspace);
    while (varea)
    {
        fn(varea, arg);
        varea = ASPACE_VAREA_NEXT(varea);
    }

    return 0;
}

static int _aspace_traversal_reverse(rt_aspace_t aspace, int (*fn)(rt_varea_t varea, void *arg), void *arg)
{
    rt_varea_t varea = ASPACE_VAREA_LAST(aspace);
    while (varea)
    {
        fn(varea, arg);
        varea = ASPACE_VAREA_PREV(varea);
    }

    return 0;
}

static int _check_bst_before(struct rt_aspace *aspace, struct rt_varea *varea)
{
    rt_varea_t root = VAREA_ENTRY(aspace->tree.tree.root_node);
    int height = _is_balanced(root);

    if (root)
        RT_ASSERT(height);

    memset(_buf, 0, sizeof(_buf)); // clear first avoiding none tree error
    _start = 0;
    _boundary = 0;
    _count = 0;

    _aspace_traversal(aspace, _check_asc_before, varea);
    int saved = _count;
    _aspace_traversal_reverse(aspace, _check_asc_before_rev, varea);
    _count = saved;

    return 1;
}

static int _check_bst_after(struct rt_aspace *aspace, struct rt_varea *varea, int isdel)
{
    rt_varea_t root = VAREA_ENTRY(aspace->tree.tree.root_node);
    int height = _is_balanced(root);

    if (root)
        RT_ASSERT(height);

    int prev_count = _count;
    _start = 0;
    _boundary = 0;
    _count = 0;
    _aspace_traversal(aspace, _check_asc_after, isdel ? NULL : varea);
    _count = isdel ? _count : _count + 1;

    if (isdel)
    {
        RT_ASSERT(prev_count - 1 == _count);
    }
    else
    {
        RT_ASSERT(prev_count + 1 == _count);
    }

    return 1;
}

/* test library */
#define RANDOM(n) (xrand() % (n))
static unsigned int xseed = 0x11223344;

static inline unsigned int xrand(void)
{
    return (((xseed = xseed * 214013L + 2531011L) >> 16) & 0x7fffffff);
}

// generate keys
static inline void init_random_keys(int *keys, int count, int seed)
{
    int save_seed = time(NULL);
    int *array = (int*)malloc(sizeof(int) * count);
    int length = count, i;
    xseed = seed;
    for (i = 0; i < count; i++) {
        array[i] = i;
    }
    for (i = 0; i < length; i++) {
        int pos = xrand() % count;
        int key = array[pos];
        keys[i] = key;
        array[pos] = array[--count];
    }
    free(array);
    xseed = save_seed;
}

// A utility function to swap to integers
static inline void swap (int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

// A function to generate a random permutation of arr[]
static void randomize ( int arr[], int n )
{
    // Use a different seed value so that we don't get same
    // result each time we run this program
    srand ( time(NULL) );

    // Start from the last element and swap one by one. We don't
    // need to run for the first element that's why i > 0
    for (int i = n-1; i > 0; i--)
    {
        // Pick a random index from 0 to i
        int j = rand() % (i+1);

        // Swap arr[i] with the element at random index
        swap(&arr[i], &arr[j]);
    }
}

/* time */
#include <time.h>

static int gettime(void)
{
    struct timespec ts;
    clock_gettime(CLOCK_REALTIME_COARSE, &ts);
    time_t seconds = ts.tv_sec;
    int millisecond = ts.tv_nsec / 1000000;
    return millisecond + seconds * 1000;
}

/* Adapt Layer */

/**
 * @brief Adapter Layer for lwp AVL BST
 */

int _aspace_bst_init(struct rt_aspace *aspace)
{
    aspace->tree.tree.root_node = AVL_ROOT;
    return 0;
}

static int compare_overlap(void *as, void *ae, void *bs, void *be)
{
    LOG_D("as %lx, ae %lx, bs %lx, be %lx", as, ae, bs, be);
    int cmp;
    if (as > be)
    {
        cmp = 1;
    }
    else if (ae < bs)
    {
        cmp = -1;
    }
    else
    {
        cmp = 0;
    }
    LOG_D("ret %d", cmp);
    return cmp;
}

static int compare_exceed(void *as, void *ae, void *bs, void *be)
{
    LOG_D("as %lx, ae %lx, bs %lx, be %lx", as, ae, bs, be);
    int cmp;
    if (as > bs)
    {
        cmp = 1;
    }
    else if (as < bs)
    {
        cmp = -1;
    }
    else
    {
        cmp = 0;
    }
    LOG_D("ret %d", cmp);
    return cmp;
}

static struct rt_varea *search(struct util_avl_root *root,
                               struct _mm_range range,
                               int (*compare)(void *as, void *ae, void *bs,
                                              void *be))
{
    struct util_avl_struct *node = root->root_node;
    while (node)
    {
        rt_varea_t varea = VAREA_ENTRY(node);
        int cmp = compare(range.start, range.end, varea->start,
                          varea->start + varea->size - 1);

        if (cmp < 0)
        {
            node = node->avl_left;
        }
        else if (cmp > 0)
        {
            node = node->avl_right;
        }
        else
        {
            return varea;
        }
    }
    return NULL;
}

struct rt_varea *_aspace_bst_search(struct rt_aspace *aspace, void *key)
{
    struct util_avl_root *root = &aspace->tree.tree;
    struct _mm_range range = {key, key};
    return search(root, range, compare_overlap);
}

rt_varea_t _aspace_bst_search_exceed(struct rt_aspace *aspace, void *start)
{
    struct util_avl_root *root = &aspace->tree.tree;
    struct util_avl_struct *node = root->root_node;
    rt_varea_t closest = NULL;
    ptrdiff_t min_off = PTRDIFF_MAX;
    while (node)
    {
        rt_varea_t varea = VAREA_ENTRY(node);
        void *va_s = varea->start;
        int cmp = compare_exceed(start, start, va_s, va_s);

        if (cmp < 0)
        {
            ptrdiff_t off = va_s - start;
            if (off < min_off)
            {
                min_off = off;
                closest = varea;
            }
            node = node->avl_left;
        }
        else if (cmp > 0)
        {
            node = node->avl_right;
        }
        else
        {
            return varea;
        }
    }
    return closest;
}

struct rt_varea *_aspace_bst_search_overlap(struct rt_aspace *aspace,
                                            struct _mm_range range)
{
    struct util_avl_root *root = &aspace->tree.tree;
    return search(root, range, compare_overlap);
}

#ifdef ENABLE_DEBUG
#include "bst_assert.h"
#else
#define _check_bst_before(x, ...)
#define _check_bst_after(x, ...)
#endif

void _aspace_bst_insert(struct rt_aspace *aspace, struct rt_varea *varea)
{
    struct util_avl_root *root = &aspace->tree.tree;
    struct util_avl_struct *current = NULL;
    struct util_avl_struct **next = &(root->root_node);
    rt_ubase_t key = (rt_ubase_t)varea->start;

    /* Figure out where to put new node */
    while (*next)
    {
        current = *next;
        struct rt_varea *data = VAREA_ENTRY(current);

        if (key < (rt_ubase_t)data->start)
            next = &(current->avl_left);
        else if (key > (rt_ubase_t)data->start)
            next = &(current->avl_right);
        else
            return;
    }

    /* Add new node and rebalance tree. */
    _check_bst_before(aspace, varea);
    util_avl_link(&varea->node.node, current, next);
    util_avl_rebalance(current, root);
    _check_bst_after(aspace, varea, 0);
    return;
}

void _aspace_bst_remove(struct rt_aspace *aspace, struct rt_varea *varea)
{
    struct util_avl_struct *node = &varea->node.node;
    _check_bst_before(aspace, varea);
    util_avl_remove(node, &aspace->tree.tree);
    _check_bst_after(aspace, varea, 1);
}

struct rt_aspace aspace;

/**
 * @brief Simulate environment of varea and BSTs
 */

/* test data set */
int *dataset;
int loop_count;

/* preallocate varea to decrease influence by malloc routine */
struct rt_varea *_varea_buf;

#define STOPWATCH(fun, time) do {   \
    unsigned int _time;             \
    _time = gettime();              \
    fun();                          \
    _time = gettime()-_time;        \
    time = _time;                   \
    } while (0);

static void init_test(void)
{
    _aspace_bst_init(&aspace);

    dataset = malloc(loop_count * sizeof(*dataset));
    assert(dataset);

    _varea_buf = malloc(loop_count * sizeof(*_varea_buf));
    assert(_varea_buf);

    init_random_keys(dataset, loop_count, 0xabcdabcd);
}

static void insert_test(void)
{
    for (size_t i = 0; i < loop_count; i++)
    {
        struct rt_varea *varea;
        varea = &_varea_buf[i];
        varea->start = (void *)(uintptr_t)dataset[i];
        varea->size = 1;
        _aspace_bst_insert(&aspace, varea);
    }
}

static void search_test(void)
{
    for (size_t i = 0; i < loop_count; i++)
    {
        void *start = (void *)(uintptr_t)dataset[i];
        struct rt_varea *varea;
        varea = _aspace_bst_search(&aspace, start);
        assert(varea);
        assert(varea->start == start);
    }
}

static void delete_test(void)
{
    for (size_t i = 0; i < loop_count; i++)
    {
        void *start = (void *)(uintptr_t)dataset[i];
        struct rt_varea *varea;
        varea = _aspace_bst_search(&aspace, start);
        _aspace_bst_remove(&aspace, varea);
    }
}

static void cleanup(void)
{
    free(dataset);

    free(_varea_buf);
}

int main(int argc, char *argv[])
{
    if (argc == 2)
    {
        sscanf(argv[1], "%d", &loop_count);
    }
    else
    {
        loop_count = 1000;
    }

    puts("Benchmark");
    printf("looping times: %d\n", loop_count);

    init_test();
    int endurance;
    STOPWATCH(insert_test, endurance);
    printf("Insertion: %d ms\n", endurance);

    randomize(dataset, loop_count);
    STOPWATCH(search_test, endurance);
    printf("Search: %d ms\n", endurance);

    randomize(dataset, loop_count);
    STOPWATCH(delete_test, endurance);
    printf("Delete: %d ms\n", endurance);

    cleanup();
    puts("Benchmark exit");
    return 0;
}
