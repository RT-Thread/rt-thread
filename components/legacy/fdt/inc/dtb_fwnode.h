#ifndef __DTB_FWNODE_H__
#define __DTB_FWNODE_H__

#include "libfdt_env.h"
#include <rtthread.h>
#include <stdint.h>
#include <stdbool.h>

struct fwnode_operations;
struct rt_device;

#define FWNODE_FLAG_LINKS_ADDED 0x01
#define FWNODE_FLAG_NOT_DEVICE 0x02
#define FWNODE_FLAG_INITIALIZED 0x04

#define NR_FWNODE_REFERENCE_ARGS 8

struct fwnode_handle
{
    struct fwnode_handle *secondary;
    const struct fwnode_operations *ops;
    struct rt_device *dev;
    struct rt_list_node suppliers;
    struct rt_list_node consumers;
    uint8_t flags;
};

struct fwnode_link
{
    struct fwnode_handle *supplier;
    struct rt_list_node s_hook;
    struct fwnode_handle *consumer;
    struct rt_list_node c_hook;
};

struct fwnode_endpoint
{
    unsigned int port;
    unsigned int id;
    const struct fwnode_handle *local_fwnode;
};

struct fwnode_reference_args
{
    struct fwnode_handle *fwnode;
    unsigned int nargs;
    uint64_t args[NR_FWNODE_REFERENCE_ARGS];
};

struct fwnode_operations
{
    struct fwnode_handle *(*get)(struct fwnode_handle *fwnode);
    void (*put)(struct fwnode_handle *fwnode);
    bool (*device_is_available)(const struct fwnode_handle *fwnode);
    const void *(*device_get_match_data)(const struct fwnode_handle *fwnode,
                                         const struct rt_device *dev);
    bool (*property_present)(const struct fwnode_handle *fwnode,
                             const char *propname);
    int (*property_read_int_array)(const struct fwnode_handle *fwnode,
                                   const char *propname,
                                   unsigned int elem_size, void *val,
                                   size_t nval);
    int (*property_read_string_array)(const struct fwnode_handle *fwnode_handle,
                                      const char *propname, const char **val,
                                      size_t nval);
    const char *(*get_name)(const struct fwnode_handle *fwnode);
    const char *(*get_name_prefix)(const struct fwnode_handle *fwnode);
    struct fwnode_handle *(*get_parent)(const struct fwnode_handle *fwnode);
    struct fwnode_handle *(*get_next_child_node)(const struct fwnode_handle *fwnode,
                                                 struct fwnode_handle *child);
    struct fwnode_handle *(*get_named_child_node)(const struct fwnode_handle *fwnode,
                                                  const char *name);
    int (*get_reference_args)(const struct fwnode_handle *fwnode,
                              const char *prop, const char *nargs_prop,
                              unsigned int nargs, unsigned int index,
                              struct fwnode_reference_args *args);
    struct fwnode_handle *(*graph_get_next_endpoint)(const struct fwnode_handle *fwnode,
                                                     struct fwnode_handle *prev);
    struct fwnode_handle *(*graph_get_remote_endpoint)(const struct fwnode_handle *fwnode);
    struct fwnode_handle *(*graph_get_port_parent)(struct fwnode_handle *fwnode);
    int (*graph_parse_endpoint)(const struct fwnode_handle *fwnode,
                                struct fwnode_endpoint *endpoint);
    int (*add_links)(struct fwnode_handle *fwnode);
};

#define fwnode_has_op(fwnode, op) \
    ((fwnode) && (fwnode)->ops && (fwnode)->ops->op)
#define fwnode_call_int_op(fwnode, op, ...) \
    (fwnode ? (fwnode_has_op(fwnode, op) ? (fwnode)->ops->op(fwnode, ##__VA_ARGS__) : -ENXIO) : -EINVAL)

#define fwnode_call_bool_op(fwnode, op, ...) \
    (fwnode_has_op(fwnode, op) ? (fwnode)->ops->op(fwnode, ##__VA_ARGS__) : false)

#define fwnode_call_ptr_op(fwnode, op, ...) \
    (fwnode_has_op(fwnode, op) ? (fwnode)->ops->op(fwnode, ##__VA_ARGS__) : NULL)
#define fwnode_call_void_op(fwnode, op, ...)          \
    do                                                \
    {                                                 \
        if (fwnode_has_op(fwnode, op))                \
            (fwnode)->ops->op(fwnode, ##__VA_ARGS__); \
    } while (false)

#define get_dev_from_fwnode(fwnode) ((fwnode)->dev)

static inline void fwnode_init(struct fwnode_handle *fwnode,
                               const struct fwnode_operations *ops)
{
    fwnode->ops = ops;
    rt_list_init(&fwnode->consumers);
    rt_list_init(&fwnode->suppliers);
}

static inline void fwnode_dev_initialized(struct fwnode_handle *fwnode,
                                          bool initialized)
{
    if (!fwnode)
        return;

    if (initialized)
        fwnode->flags |= FWNODE_FLAG_INITIALIZED;
    else
        fwnode->flags &= ~FWNODE_FLAG_INITIALIZED;
}

#endif //__DTB_FWNODE_H__
