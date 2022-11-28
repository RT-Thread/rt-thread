#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <rtthread.h>
#include <log.h>
#include <hal_mem.h>
#include <video/sunxi_display2.h>


struct info_mm {
    void *info_base;    /* Virtual address */
    unsigned long mem_start;    /* Start of frame buffer mem */
    /* (physical address) */
    u32 mem_len;        /* Length of frame buffer mem */
};

struct test_mem_cfg
{
    int screen_id;
    int layer_id;
    int mem_id;
    struct disp_layer_config layer_cfg;
    int addr_map;
    int width,height;//screen size
    int dispfh;//device node handle
    int fh;//picture resource file handle
    void* mem;
    int buffer_num;//is double buffer
    int clear;//is clear layer
    char filename[32];
};

static struct info_mm g_disp_mm[10];
static int g_disp_mem_id = -1;

#define DISP_TEST_BYTE_ALIGN(x) (((x + (4*1024-1)) >> 12) << 12)
static void *disp_malloc(u32 num_bytes, void *phys_addr)
{
    u32 actual_bytes;
    void *address = NULL;

    if (num_bytes != 0) {
        actual_bytes = DISP_TEST_BYTE_ALIGN(num_bytes);

        address = hal_malloc(actual_bytes);
        *(uint32_t *)phys_addr = __va_to_pa((unsigned long)address);
        if (address) {
        __wrn
                ("hal_malloc ok, phy addr=0x%p, vir addr=%p size=0x%x\n",
                 (void *)(*(unsigned long *)phys_addr), address, num_bytes);
            return address;
        }

        printf("dma_alloc_coherent fail, size=0x%x\n", num_bytes);
        return NULL;
    }

    printf("%s size is zero\n", __func__);

    return NULL;
}

static void disp_free(void *virt_addr, void *phys_addr, u32 num_bytes)
{
    u32 actual_bytes;

    actual_bytes = DISP_TEST_BYTE_ALIGN(num_bytes);
    if (phys_addr && virt_addr)
        hal_free(virt_addr);
}

static int disp_mem_release(int sel)
{
    if (g_disp_mm[sel].info_base == NULL)
        return -1;

    __inf("disp_mem_release, mem_id=%d, phy_addr=0x%p\n", sel,
          (void *)g_disp_mm[sel].mem_start);
    disp_free((void *)g_disp_mm[sel].info_base,
          (void *)g_disp_mm[sel].mem_start, g_disp_mm[sel].mem_len);
    memset(&g_disp_mm[sel], 0, sizeof(struct info_mm));
    g_disp_mem_id = -1;
    return 0;
}

static int disp_mem_request(int sel, u32 size)
{

    uintptr_t phy_addr;

    if ((sel >= 10) ||
        (g_disp_mm[sel].info_base != NULL)) {
        printf("invalid param\n");
        return -1;
    }

    g_disp_mm[sel].info_base = disp_malloc(size, (void *)&phy_addr);
    if (g_disp_mm[sel].info_base) {
        g_disp_mm[sel].mem_start = phy_addr;
        g_disp_mm[sel].mem_len = size;
        memset(g_disp_mm[sel].info_base, 0, size);
        printf("pa=0x%p va=0x%p size:0x%x\n",
              (void *)g_disp_mm[sel].mem_start,
              g_disp_mm[sel].info_base, size);
        g_disp_mem_id = sel;

        return 0;
    }

    printf("disp_malloc fail!\n");
    return -1;
}


u32 disp_mem_getadr(u32 memid)
{
    if (memid < 10)
        return g_disp_mm[memid].mem_start;
    return 0;
}

int disp_mem(u32 mem_id, u32 width, u32 height, u32 clear_flag, char *filename)
{
    unsigned long arg[6];
    int phy_adr, i, n, fb_width, fb_height;
    int ret = -1;
    FILE *fh = NULL;
    void *mem = NULL;
    unsigned long count = width*height;
    char *tmp;
    if(clear_flag) {
        /* release memory && clear layer */
        disp_mem_release(mem_id);
        return 0;
    }

    //for_test  we use r g b to set color buffer
    if(filename[0] != 'r' && filename[0] != 'g' && filename[0] != 'b') {
        if(filename != NULL)
            fh = fopen(filename, "r");
        if(!fh) {
            printf("open file %s fail. \n", filename);
            goto OUT;
        }
    }

    fb_width = width;
    fb_height = height;

    ret = disp_mem_request(mem_id, fb_width*fb_height*4);
    if(ret) {
        printf("DISP_MEM_REQUEST 0\n");
        goto FILE_CLOSE;
    }

    phy_adr = g_disp_mm[mem_id].mem_start;
    mem = g_disp_mm[mem_id].info_base;
    tmp = mem;
    if(fh != NULL) {
        memset((void*)mem, 0x0, fb_width*fb_height*4);
        fread((void *)mem, fb_width * fb_height * 4, 1, fh);
    } else {
        while(count--) {
            //for(i = 0; i < 4; i++) {
                #if 0
                *(tmp) = 0xff;//A
                *(tmp + 1) = filename[0]=='r'?0xff:0;//R
                *(tmp + 2) = filename[0]=='g'?0xff:0;//G
                *(tmp + 3) = filename[0]=='b'?0xff:0;//B
                #else
                *(tmp + 3) = 0xff;//A
                *(tmp + 2) = filename[0]=='r'?0xff:0;//R
                *(tmp + 1) = filename[0]=='g'?0xff:0;//G
                *(tmp + 0) = filename[0]=='b'?0xff:0;//B
                #endif
            //}
                tmp+=4;
        }
    }

FILE_CLOSE:
    if(fh!=NULL)
        fclose(fh);
OUT:
    return ret;
}

int disp_mem_clear(u32 mem_id)
{
    return disp_mem(mem_id, 0, 0, 1, NULL);
}


int parse_cmdline_and_alloc(int argc, char **argv)
{
    int err = 0;
    int i = 0;
    struct test_mem_cfg mem_cfg;
    struct test_mem_cfg *p = &mem_cfg;
    while(i<argc) {
        printf("%s ",argv[i]);
        i++;
    }
    memset(p, 0, sizeof(struct test_mem_cfg));
    i = 0;
    while(i < argc) {
        if ( ! strcmp(argv[i], "-mem_id")) {
            if (argc > i+1) {
                i+=1;
                p->mem_id = atoi(argv[i]);
            }
        }

        if ( ! strcmp(argv[i], "-clr")) {
            if (argc > i+1) {
                i+=1;
                p->clear = atoi(argv[i]);
            }
        }

        if ( ! strcmp(argv[i], "-file")) {
            if (argc > i+1) {
                i++;
                p->filename[0] = '\0';
                sprintf(p->filename,"%s",argv[i]);
                printf("filename=%s\n", argv[i]);
            }   else {
                printf("no file described!!\n");
                err ++;
            }
        }

        if ( ! strcmp(argv[i], "-size")) {
            if (argc > i+2) {
                i++;
                p->layer_cfg.info.fb.size[0].width = atoi(argv[i]);
                i++;
                p->layer_cfg.info.fb.size[0].height = atoi(argv[i]);
            }   else {
                printf("-size para err!\n\n");
                err ++;
            }
        }

        if ( ! strcmp(argv[i], "-buffer_num")) {
            if (argc > i+1) {
                i++;
                p->buffer_num = atoi(argv[i]);
                p->buffer_num = (p->buffer_num == 0)? 1:p->buffer_num;
            }
        }

        i++;
    }

    if(err > 0) {
        printf("example : ./disp_mem -mem_id 0 -size 1280 800 -double 0 -file ./pic/ui_1280x800_double_151.bin\n");
        return -1;
    } else {
        if (p->clear)
            return disp_mem_clear(p->mem_id);
        return disp_mem(p->mem_id, p->layer_cfg.info.fb.size[0].width, p->layer_cfg.info.fb.size[0].height, 0, p->filename);
    }
}

FINSH_FUNCTION_EXPORT_ALIAS(parse_cmdline_and_alloc, disp_mem, disp mem);

