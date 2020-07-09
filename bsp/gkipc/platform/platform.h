#ifndef __PLATFORM_H__
#define __PLATFORM_H__

#ifdef __cplusplus
extern "C" {
#endif


struct gk_platform_driver
{
    char *name;
    int (*probe)(void *);
    int (*remove)(void *);
};

int gk_platform_driver_init(struct gk_platform_driver *plat_drv);
int gk_platform_driver_uninit(struct gk_platform_driver *plat_drv);

#ifdef __cplusplus
}
#endif

#endif

