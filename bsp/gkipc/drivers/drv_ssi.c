#include <rtdevice.h>
#include "gtypes.h"
#include "gd_spi.h"
#include "drv_ssi.h"
#include "platform.h"

/*---------------------------------------------------------------------------*/
/* local defines                                                             */
/*---------------------------------------------------------------------------*/


/*---------------------------------------------------------------------------*/
/* local data types                                                          */
/*---------------------------------------------------------------------------*/



/*---------------------------------------------------------------------------*/
/* local data                                                                */
/*---------------------------------------------------------------------------*/



/*---------------------------------------------------------------------------*/
/* local  functions                                                          */
/*---------------------------------------------------------------------------*/
static void *gk_get_spi_dev_pri_data(struct rt_spi_device *device)
{
    return device->parent.user_data;
}

static rt_err_t gk_spi_configure(struct rt_spi_device *device, struct rt_spi_configuration *configuration)
{
	struct gk_spi_slave_info *spi_slave;
	struct gk_spi_controller *spi_control;
	GD_SPI_OPEN_PARAMS_S openParamsP;
	rt_uint32_t spi_hz;
	rt_int32_t	ret;
	rt_uint8_t	data_width = 8,polarity;

	if(!device || !configuration)
	{
		rt_kprintf("%s,%d,param wrong!\n",__FUNCTION__,__LINE__);
		return RT_ERROR;
	}

	spi_slave   = (struct gk_spi_slave_info *)gk_get_spi_dev_pri_data(device);
	spi_control = spi_slave->control;

	rt_sem_take(&spi_control->xfer_lock, RT_WAITING_FOREVER);

	if(spi_slave->spihandle > 0)
	{
		GD_SPI_Close(&spi_slave->spihandle);
		spi_slave->spihandle = -1;
	}

	 openParamsP.spi 	    = spi_control->id;
	 openParamsP.slave      = spi_slave->id;
	 openParamsP.csgpio     = spi_slave->cs_pin;
	 openParamsP.used_irq   = 1;

	 if (configuration->max_hz > GD_SPI_FREQ_81M)
		 spi_hz = GD_SPI_FREQ_81M;
	 else
		 spi_hz = configuration->max_hz;

	 openParamsP.baudrate = spi_hz;

	 /* CPOL */
	 if (configuration->mode & RT_SPI_CPOL && configuration->mode & RT_SPI_CPHA)
	 {
	 	polarity = SPI_POLARITY_MODE3;
	 }
	 else if(configuration->mode & RT_SPI_CPOL && !configuration->mode & RT_SPI_CPHA)
	 {
	 	polarity = SPI_POLARITY_MODE2;
	 }
	 else if(!configuration->mode & RT_SPI_CPOL && configuration->mode & RT_SPI_CPHA)
	 {
	 	polarity = SPI_POLARITY_MODE1;
	 }
	 else
		 polarity = SPI_POLARITY_MODE0;

	 openParamsP.polarity = polarity;

	 ret = GD_SPI_Open(&openParamsP,&(spi_slave->spihandle));
	 if(ret != GD_OK)
	 {
	     rt_kprintf("GD_SPI_Open failed!\n");
		 rt_sem_release(&spi_control->xfer_lock);
	     return RT_ERROR;
	 }

	 /* data_width */
	 if (configuration->data_width <= 8)
	 {
	 	data_width = 8;
	 }
	 else if (configuration->data_width <= 16)
	 {

	 	data_width = 16;
	 }

	 ret = GD_SPI_SetDatFormat(spi_slave->spihandle, data_width);;
	 if(ret != GD_OK)
	 {
	     rt_kprintf("GD_SPI_SetDatFormat failed!\n");
		 rt_sem_release(&spi_control->xfer_lock);
	     return RT_ERROR;
	 }

	 rt_sem_release(&spi_control->xfer_lock);

	return RT_EOK;
}

static rt_uint32_t gk_spi_xfer(struct rt_spi_device *device, struct rt_spi_message *message)
{
	struct gk_spi_slave_info *spi_slave;
	struct gk_spi_controller *spi_control;
	GERR ret = GD_OK;

	if(!device || !message)
	{
		rt_kprintf("%s,%d,param wrong!\n",__FUNCTION__,__LINE__);
		return 0;
	}

	spi_slave   = (struct gk_spi_slave_info *)gk_get_spi_dev_pri_data(device);

	if(!spi_slave)
	{
		rt_kprintf("%s,%d,param wrong!\n",__FUNCTION__,__LINE__);
		return 0;
	}

	spi_control = spi_slave->control;

	if(spi_slave->spihandle < 0)
	{
		rt_kprintf("%s,%d,spi channel not configured!\n",__FUNCTION__,__LINE__);
		return 0;
	}

	if(!message)
	{
		rt_kprintf("%s,%d,params wrong!\n",__FUNCTION__,__LINE__);
		return 0;
	}

	rt_sem_take(&spi_control->xfer_lock, RT_WAITING_FOREVER);

	if(message->cs_take)
		GD_SPI_GetDevice(spi_slave->spihandle);

	if(message->recv_buf && message->send_buf)
    	ret = GD_SPI_WriteThenReadBytes(spi_slave->spihandle,(rt_uint8_t *)message->send_buf,message->length,
    	(rt_uint8_t *)message->recv_buf,message->length);
	else if(message->send_buf && !message->recv_buf)
		ret = GD_SPI_WriteBytes(spi_slave->spihandle,(rt_uint8_t *)message->send_buf,message->length);
	else if(!message->send_buf && message->recv_buf)
		ret = GD_SPI_WriteThenReadBytes(spi_slave->spihandle,NULL,0,(rt_uint8_t *)message->recv_buf,message->length);


	if(message->cs_release)
		GD_SPI_ReleaseDevice(spi_slave->spihandle);

	rt_sem_release(&spi_control->xfer_lock);


	if(ret != GD_OK)
	{
		rt_kprintf("%s,%d,transfer error!\n",__FUNCTION__,__LINE__);
		return 0;
	}
	else
	{
		return message->length;
	}

}

static struct rt_spi_ops gk_spi_ops = {

    .configure = gk_spi_configure, .xfer = gk_spi_xfer,

};

int gk_spi_probe(void *priv_data)
{
	int ret,i;
    char spi_dev_name[20]  = {0};
    char spi_bus_name[20]  = {0};
    char spi_lock_name[20] = {0};
    struct gk_spi_controller *spi_control;
	struct gk_spi_controller_data *spi_controller_data = (struct gk_spi_controller_data *)priv_data;
    struct gk_spi_slave_info **control_slave;
    struct gk_spi_slave_info *spi_slave,*next_slave;

	if (!spi_controller_data)
	{
		rt_kprintf("%s,%d input param wrong!\n",__FUNCTION__,__LINE__);
		return -1;
	}

    spi_control = (struct gk_spi_controller *)rt_malloc(sizeof(struct gk_spi_controller));
    if (!spi_control)
    {
        rt_kprintf("%s,%d malloc failed!\n",__FUNCTION__,__LINE__);
        return -1;
    }

    rt_memset(spi_control, 0, sizeof(struct gk_spi_controller));

	spi_control->id = spi_controller_data->id;

    rt_sprintf(spi_lock_name, "%s%d", "spi_lock", spi_control->id);
    rt_sprintf(spi_bus_name, "%s%d", "spi_bus", spi_control->id);

    rt_sem_init(&spi_control->xfer_lock, spi_lock_name, 1, RT_IPC_FLAG_FIFO);

    ret = rt_spi_bus_register(&spi_control->spi_bus, spi_bus_name, &gk_spi_ops);

	control_slave = &spi_control->spi_slave;

    for (i = 0; i < spi_controller_data->total_slave; i++)
    {
        spi_slave = (struct gk_spi_slave_info *)rt_malloc(sizeof(struct gk_spi_slave_info));
        if (!spi_slave)
        {
			rt_kprintf("%s,%d malloc failed!\n",__FUNCTION__,__LINE__);
            goto exit;
        }
        rt_memset(spi_slave, 0, sizeof(struct gk_spi_slave_info));

        spi_slave->id      = i;
        spi_slave->control = spi_control;
        spi_slave->cs_pin  = spi_controller_data->slave_cs_pin[i];
		spi_slave->spihandle = -1;

        rt_sprintf(spi_dev_name, "%s%d%s%d", "ssi", spi_control->id, "_", spi_slave->id);

        *control_slave = spi_slave;
        control_slave  = &spi_slave->next;

        ret = rt_spi_bus_attach_device(&spi_slave->spi_device, spi_dev_name,spi_bus_name, spi_slave);
        if (ret != RT_EOK)
        {
            rt_kprintf("register dev to bus failed...\n");
            goto exit;
        }
    }

	spi_controller_data->control = spi_control;

	GD_SPI_Init();

    return RT_EOK;

exit:

	spi_slave = spi_control->spi_slave;
	while (spi_slave != RT_NULL)
	{
		next_slave = spi_slave->next;
		rt_free(spi_slave);
		spi_slave = next_slave;
	}

    rt_sem_detach(&spi_control->xfer_lock);

    rt_free(spi_control);

	return RT_ERROR;
}

int gk_spi_exit(void *priv_data)
{

    struct gk_spi_controller *spi_control;
    struct gk_spi_controller_data *plat_data;
    struct gk_spi_slave_info *spi_slave;
    struct gk_spi_slave_info *next_slave;

    plat_data   = (struct gk_spi_controller_data *)priv_data;
    spi_control = plat_data->control;
    spi_slave   = spi_control->spi_slave;

    while (spi_slave != RT_NULL)
    {
        next_slave = spi_slave->next;
        rt_free(spi_slave);
        spi_slave = next_slave;
    }

    rt_sem_detach(&spi_control->xfer_lock);

    rt_free(spi_control);

    return RT_EOK;
}

struct gk_platform_driver gk_spi_driver_ops = {

    .name = "spi", .probe = gk_spi_probe, .remove = gk_spi_exit,

};

void rt_hw_spi_init(void)
{

	gk_platform_driver_init(&gk_spi_driver_ops);
}

