# fdt load API

## 从文件系统上读取设备树
```c
void *fdt_load_from_fs(char *dtb_filename)
```

| 参数 | 描述 |
|:------------------|:------------------------------------|
|dtb_filename | 设备树文件名 |
| **返回** | **描述** |
|void* | 设备树在内存上的地址 |

## 从内存上读取设备树
```c
void *fdt_load_from_memory(void *dtb_ptr, rt_bool_t is_clone)
```

| 参数 | 描述 |
|:------------------|:------------------------------------|
|dtb_ptr | 设备树在内存上的内存地址 |
|is_clone | 是否克隆到新的内存区域 |
| **返回** | **描述** |
|void* | 设备树在内存上的地址 |

# fdt set API

## 设置Linux启动参数
```c
rt_size_t fdt_set_linux_cmdline(void *fdt, char *cmdline)
```

| 参数 | 描述 |
|:------------------|:------------------------------------|
|fdt | 设备树指针 |
|cmdline | 启动参数 |
| **返回** | **描述** |
|rt_size_t | 修改设备树后设备树的大小 |

## 设置Linux init ramdisk
```c
rt_size_t fdt_set_linux_initrd(void *fdt, rt_uint64_t initrd_addr, rt_size_t initrd_size)
```

| 参数 | 描述 |
|:------------------|:------------------------------------|
|fdt | 设备树指针 |
|initrd_addr | init ramdisk 内存地址 |
|initrd_size | init 大小 |
| **返回** | **描述** |
|rt_size_t | 修改设备树后设备树的大小 |

## 设置节点属性值
```c
rt_size_t fdt_set_dtb_property(void *fdt, char *pathname, char *property_name, rt_uint32_t *cells, rt_size_t cells_size);
```

| 参数 | 描述 |
|:------------------|:------------------------------------|
|fdt | 设备树指针 |
|pathname | 节点路径 |
|property_name | 属性名称 |
|cells | 属性值地址 |
|cells_size | 属性值长度 |
| **返回** | **描述** |
|rt_size_t | 修改设备树后设备树的大小 |

## 添加保留内存
```c
rt_size_t fdt_add_dtb_memreserve(void *fdt, rt_uint64_t address, rt_uint64_t size)
```

| 参数 | 描述 |
|:------------------|:------------------------------------|
|fdt | 设备树指针 |
|address | 保留内存起始地址 |
|size | 保留内存大小 |
| **返回** | **描述** |
|rt_size_t | 修改设备树后设备树的大小 |

## 删除保留内存
```c
rt_size_t fdt_del_dtb_memreserve(void *fdt, rt_uint64_t address)
```

| 参数 | 描述 |
|:------------------|:------------------------------------|
|fdt | 设备树指针 |
|address | 保留内存起始地址 |
| **返回** | **描述** |
|rt_size_t | 修改设备树后设备树的大小 |

# fdt get API

## 获取设备树软件包执行状态
```c
rt_err_t fdt_get_exec_status()
```

| 参数 | 描述 |
|:------------------|:------------------------------------|
|无 | 无参数 |
| **返回** | **描述** |
|FDT_RET_NO_MEMORY | 内存不足 |
|FDT_RET_NO_LOADED | 设备树还未加载进内存 |
|FDT_RET_GET_OK | 执行成功 |
|FDT_RET_GET_EMPTY | 读取数据为空 |

## 将原始设备树转换为设备节点树
```c
struct dtb_node *fdt_get_dtb_list(void *fdt)
```

| 参数 | 描述 |
|:------------------|:------------------------------------|
|fdt | 设备树在内存上的地址 |
| **返回** | **描述** |
|struct dtb_node * | 设备节点树头指针 |
## 释放设备节点树内存
```c
void fdt_free_dtb_list(struct dtb_node *dtb_node_head)
```

| 参数 | 描述 |
|:------------------|:------------------------------------|
|dtb_node_head | 设备节点树头节点 |
| **返回** | **描述** |
|无返回值 | 无描述 |

示例：加载设备树

```c
#include <rtthread.h>
#include <fdt.h>

int main()
{
    void *fdt = fdt_load_from_fs("sample.dtb");
    if (fdt != RT_NULL)
    {
        struct dtb_node *dtb_node_list = fdt_get_dtb_list(fdt);

        if (dtb_node_list != RT_NULL)
        {
            /* load dtb node list OK */

            /* free dtb_node_list here */
            fdt_free_dtb_list(dtb_node_list);
        }

        rt_free(fdt);
    }

    return 0;
}
```

## 打印设备树信息
```c
void fdt_get_dts_dump(struct dtb_node *dtb_node_head)
```

| 参数 | 描述 |
|:------------------|:------------------------------------|
|dtb_node_head | 设备节点树头节点 |
| **返回** | **描述** |
|无返回值 | 无描述 |

## 遍历设备节点树并使用程序定义的回调函数
```c
void fdt_get_enum_dtb_node(struct dtb_node *dtb_node_head, void (*callback(struct dtb_node *dtb_node)))
```

| 参数 | 描述 |
|:------------------|:------------------------------------|
|dtb_node_head | 设备节点树头节点 |
|callback | 程序定义的回调函数 |
| **返回** | **描述** |
|无返回值 | 无描述 |

示例：遍历设备树节点，并打印每个节点名称

```c
#include <rtthread.h>
#include <fdt.h>

void callback(struct dtb_node *node)
{
    rt_kprintf("this node's name is %s\n", node->name);
}

int main()
{
    /* loaded dtb_node */
    extern struct dtb_node *dtb_node_list;

    if (dtb_node_list != RT_NULL)
    {
        fdt_get_enum_dtb_node(dtb_node_list, callback);
    }

    return 0;
}
```

## 通过节点名称查找节点
```c
struct dtb_node *fdt_get_dtb_node_by_name_DFS(struct dtb_node *dtb_node, const char *nodename)
```
```c
struct dtb_node *fdt_get_dtb_node_by_name_BFS(struct dtb_node *dtb_node, const char *nodename)
```

| 参数 | 描述 |
|:------------------|:------------------------------------|
|dtb_node | 设备节点树节点 |
|nodename | 查找节点的名称 |
| **返回** | **描述** |
|struct dtb_node * | 返回查找的节点 |
|RT_NULL | 未找到为RT_NULL |

## 通过节点路径查找节点
```c
struct dtb_node *fdt_get_dtb_node_by_path(struct dtb_node *dtb_node, const char *pathname)
```

| 参数 | 描述 |
|:------------------|:------------------------------------|
|dtb_node | 设备节点树节点 |
|pathname | 查找节点的路径 |
| **返回** | **描述** |
|struct dtb_node * | 返回查找的节点 |
|RT_NULL | 未找到为RT_NULL |

## 通过节点phandle值查找节点
```c
struct dtb_node *fdt_get_dtb_node_by_phandle_DFS(struct dtb_node *dtb_node, phandle handle)
```
```c
struct dtb_node *fdt_get_dtb_node_by_phandle_BFS(struct dtb_node *dtb_node, phandle handle)
```

| 参数 | 描述 |
|:------------------|:------------------------------------|
|dtb_node | 设备节点树节点 |
|handle | 查找节点的phandle值 |
| **返回** | **描述** |
|struct dtb_node * | 返回查找的节点 |
|RT_NULL | 未找到为RT_NULL |

DFS和BFS是用于区分不同深度节点的搜索方法，时间复杂度和空间复杂度都较高，建议使用路径查找。

## 读取节点属性值的单位
```c
void fdt_get_dtb_node_cells(struct dtb_node *dtb_node, int *addr_cells, int *size_cells)
```

| 参数 | 描述 |
|:------------------|:------------------------------------|
|dtb_node | 设备节点树节点 |
|addr_cells | 返回的地址块的单位（u32）大小 |
|size_cells | 返回的尺寸块的单位（u32）大小 |
| **返回** | **描述** |
|无返回值 | 无描述 |


## 读取节点属性值
```c
void *fdt_get_dtb_node_property(struct dtb_node *dtb_node, const char *property_name, rt_size_t *property_size)
```

| 参数 | 描述 |
|:------------------|:------------------------------------|
|dtb_node | 设备节点树节点 |
|property_name | 属性名称 |
|property_size | 属性大小 |
| **返回** | **描述** |
|void * | 无描述 |
|RT_NULL | 该设备树没有该属性 |

读取的值为在设备树中存储的值，CPU小端模式下可能需要使用其他API进行转换才是正确的值

## 读取预留内存信息
```c
struct dtb_memreserve *fdt_get_dtb_memreserve(struct dtb_node *dtb_node, int *memreserve_size)
```

| 参数 | 描述 |
|:------------------|:------------------------------------|
|dtb_node | 设备节点树节点 |
|memreserve_size | 返回的内存信息数组长度 |
| **返回** | **描述** |
|struct dtb_memreserve *| 内存预留信息数组的内存地址 |
|RT_NULL | 该设备树没有预留内存信息 |

## 读取节点的状态
```c
rt_bool_t fdt_get_dtb_node_status(struct dtb_node *dtb_node)
```

| 参数 | 描述 |
|:------------------|:------------------------------------|
|dtb_node | 设备节点树节点 |
| **返回** | **描述** |
|RT_FALSE | 状态为禁用 |
|RT_TRUE | 状态为使用 |

## 用于参数为字符串列表的函数
```c
fdt_string_list(string, ...)
```
| 参数 | 描述 |
|:------------------|:------------------------------------|
|string | 字符串集合 |

## 读取节点compatible标志匹配
```c
rt_bool_t fdt_get_dtb_node_compatible_match(struct dtb_node *dtb_node, char **compatibles)
```

| 参数 | 描述 |
|:------------------|:------------------------------------|
|dtb_node | 设备节点树节点 |
|compatibles | 所有要匹配的字符串列表 |
| **返回** | **描述** |
|RT_FALSE | 匹配失败 |
|RT_TRUE | 匹配成功 |

## 读取属性值中的字符串
```c
char *fdt_get_dtb_string_list_value(void *value, int size, int index)
```

| 参数 | 描述 |
|:------------------|:------------------------------------|
|value | 节点属性的内存地址 |
|size | 节点属性的尺寸 |
|index | 要读取字符串的索引 |
| **返回** | **描述** |
|char * | 字符串的内存地址 |
|RT_NULL | 该索引没有字符串 |

## 读取值为字符串属性下一个字符串
```c
char *fdt_get_dtb_string_list_value_next(void *value, void *end)
```

| 参数 | 描述 |
|:------------------|:------------------------------------|
|value | 节点属性的内存地址 |
|end | 节点属性的结束地址 |
| **返回** | **描述** |
|char * | 字符串的内存地址 |
|RT_NULL | 没有下一个字符串 |

## 读取值为u32属性的值
```c
rt_uint32_t fdt_get_dtb_cell_value(void *value)
```

| 参数 | 描述 |
|:------------------|:------------------------------------|
|value | 节点属性的内存地址 |
| **返回** | **描述** |
|rt_uint32_t | 该值小端的值 |

## 读取值为u8属性的值
```c
rt_uint8_t fdt_get_dtb_byte_value(void *value)
```

| 参数 | 描述 |
|:------------------|:------------------------------------|
|value | 节点属性的内存地址 |
| **返回** | **描述** |
|rt_uint8_t | 该值小端的值 |

# fdt foreach API

## 遍历属性中字符串宏
```c
for_each_property_string(node_ptr, property_name, str, size)
```

| 参数 | 描述 |
|:------------------|:------------------------------------|
|node_ptr | 设备节点树节点 |
|property_name | 节点属性名称 |
|str | 每次遍历到的字符串 |
|size | 用于保存节点属性的尺寸 |

## 遍历属性中u32宏
```c
for_each_property_cell(node_ptr, property_name, value, list, size)
```

| 参数 | 描述 |
|:------------------|:------------------------------------|
|node_ptr | 设备节点树节点 |
|property_name | 节点属性名称 |
|value | 每次遍历到的值 |
|list | 用于保存节点属性的值内存地址 |
|size | 用于保存节点属性的尺寸 |

## 遍历属性中u8宏
```c
for_each_property_byte(node_ptr, property_name, value, list, size)
```

| 参数 | 描述 |
|:------------------|:------------------------------------|
|node_ptr | 设备节点树节点 |
|property_name | 节点属性名称 |
|value | 每次遍历到的值 |
|list | 用于保存节点属性的值内存地址 |
|size | 用于保存节点属性的尺寸 |

## 遍历子节点宏
```c
for_each_node_child(node_ptr)
```

| 参数 | 描述 |
|:------------------|:------------------------------------|
|node_ptr | 设备节点树节点 |

## 遍历兄弟节点宏
```c
for_each_node_sibling(node_ptr)
```

| 参数 | 描述 |
|:------------------|:------------------------------------|
|node_ptr | 设备节点树节点 |
