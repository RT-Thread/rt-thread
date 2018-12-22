#ifndef __DRV_SDIO_H__
#define __DRV_SDIO_H__

#include <rtthread.h>

#ifdef __cplusplus
extern "C" {
#endif

 typedef enum
 {
    SDIO_DEVICE_TYPE_NORMAL = 0,     //!< Normal transfer type for SD/SDHC/MMC cards (default)
    SDIO_DEVICE_TYPE_WIFI,
    
} SDIO_DEVICE_TYPE_E;


struct gk_sdio_info
{
    rt_uint32_t id;
	SDIO_DEVICE_TYPE_E type;
};

struct gk_sdio
{
    struct rt_mmcsd_host *host;
    struct rt_mmcsd_req  *req;
    struct rt_mmcsd_cmd  *cmd;
	
    struct rt_completion completion;
    void *priv;
};
void rt_hw_sdio_init(void);

#ifdef __cplusplus
}
#endif


#endif

