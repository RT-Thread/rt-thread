/*
*******************************************************************************
*                                              usb host module
*
*                             Copyright(C), 2006-2008, SoftWinners Co., Ltd.
*                                                  All Rights Reserved
*
* File Name :
*
* Author : GLHuang(HoLiGun)
*
* Version : 1.0
*
* Date : 2008.05.xx
*
* Description :
*           usb 配置描述符以及其下游的子描述符的解析
* History :
********************************************************************************************************************
*/
//#include "usb_host_config.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <hal_osal.h>

//#include <usb/usb_os_platform.h>
#include <usb_host_common.h>
#include <sunxi_hal_common.h>

//#include "usb_host_base_types.h"
#include <usb_list.h>
#include "usb_msg.h"


#define USB_MAXALTSETTING       128 /* Hard limit */
#define USB_MAXENDPOINTS        30  /* Hard limit */

#define USB_MAXCONFIG           8   /* Arbitrary limit */


static inline const char *plural(int n)
{
    return (n == 1 ? "" : "s");
}


/* 查找,直到遇到dt1,dt2类型的desc */
static int _find_next_desc(unsigned char *buffer,
                           int size,
                           int dt1,
                           int dt2,
                           int *num_skipped)
{
    struct usb_descriptor_header *h;
    int n = 0;
    unsigned char *buffer0 = buffer;

    /* Find the next descriptor of type dt1 or dt2 */
    while (size > 0)
    {
        h = (struct usb_descriptor_header *) buffer;

        if (h->bDescriptorType == dt1 || h->bDescriptorType == dt2)
        {
            break;
        }

        buffer += h->bLength;
        size -= h->bLength;
        ++n;
    }

    /* Store the number of descriptors skipped and return the
     * number of bytes skipped */
    if (num_skipped)
    {
        *num_skipped = n;
    }

    return buffer - buffer0;
}

static int _usb_parse_endpoint_desc(int cfgno, int inum,
                                    int asnum,
                                    struct usb_host_virt_interface *ifp,
                                    int num_ep,
                                    u8 *buffer,
                                    int size)
{
    u8 *buffer0 = buffer;
    struct usb_endpoint_descriptor *d = NULL;
    struct usb_host_virt_endpoint *endpoint = NULL;
    int n = 0, i = 0;
    d = (struct usb_endpoint_descriptor *) buffer;
    buffer += d->bLength;
    size -= d->bLength;

    if (d->bLength >= USB_DT_ENDPOINT_AUDIO_SIZE)
    {
        n = USB_DT_ENDPOINT_AUDIO_SIZE;
    }
    else if (d->bLength >= USB_DT_ENDPOINT_SIZE)
    {
        n = USB_DT_ENDPOINT_SIZE;
    }
    else
    {
        hal_log_err("WARNING : config %d interface %d altsetting %d has an "
                   "invalid endpoint descriptor of length %d, skipping\n",
                   cfgno, inum, asnum, d->bLength);
        goto skip_to_next_endpoint_or_interface_descriptor;
    }

    i = d->bEndpointAddress & ~USB_ENDPOINT_DIR_MASK;

    if (i >= 16 || i == 0)
    {
        hal_log_err("WARNING : config %d interface %d altsetting %d has an "
                   "invalid endpoint with address 0x%X, skipping\n",
                   cfgno, inum, asnum, d->bEndpointAddress);
        goto skip_to_next_endpoint_or_interface_descriptor;
    }

    /* Only store as many endpoints as we have room for */
    if (ifp->desc.bNumEndpoints >= num_ep)
    {
        goto skip_to_next_endpoint_or_interface_descriptor;
    }

    endpoint = &ifp->endpoint[ifp->desc.bNumEndpoints];
    ++ifp->desc.bNumEndpoints;
    memcpy((void *)(&endpoint->desc), (void *)d, n);
    INIT_LIST_HEAD(&endpoint->urb_list);
    /* Skip over any Class Specific or Vendor Specific descriptors;
     * find the next endpoint or interface descriptor */
    endpoint->extra = buffer;
    i = _find_next_desc(buffer, size, USB_DT_ENDPOINT, USB_DT_INTERFACE, &n);
    endpoint->extralen = i;

    if (n > 0)
    {
        hal_log_info("skipped %d descriptor%s after %s\n", n, plural(n), "endpoint");
    }

    return buffer - buffer0 + i;
skip_to_next_endpoint_or_interface_descriptor:
    i = _find_next_desc(buffer, size, USB_DT_ENDPOINT,
                        USB_DT_INTERFACE, NULL);
    return buffer - buffer0 + i;
}


//cfgno :
//cofnig    :
//buffer    :   指向本interface的开始
static int _usb_parse_interface_desc(int cfgno,
                                     struct usb_host_virt_config *config,
                                     unsigned char *buffer,
                                     int size,
                                     u8 inums[],
                                     u8 nalts[])
{
    unsigned char *buffer0 = buffer;
    struct usb_interface_descriptor *interface_desc = NULL;
    int inum = 0, asnum = 0;
    struct usb_interface_cache *intfc = NULL;
    struct usb_host_virt_interface *alt = NULL;
    int i = 0, n = 0;
    int len = 0, retval = 0;
    int num_ep = 0, num_ep_orig = 0;
    interface_desc = (struct usb_interface_descriptor *) buffer;
    buffer += interface_desc->bLength;
    size -= interface_desc->bLength;

    if (interface_desc->bLength < USB_DT_INTERFACE_SIZE)
    {
        goto skip_to_next_interface_descriptor;
    }

    //Which interface entry is this?
    //根据该interface的index，
    //在config中找到其对应的intf_cache[]中的entry
    intfc = NULL;
    inum = interface_desc->bInterfaceNumber;

    for (i = 0; i < config->desc.bNumInterfaces; ++i)
    {
        if (inums[i] == inum)
        {
            intfc = config->intf_cache[i];
            break;
        }
    }

    if (!intfc || intfc->num_altsetting >= nalts[i])
    {
        goto skip_to_next_interface_descriptor;
    }

    /* Check for duplicate altsetting entries */
    asnum = interface_desc->bAlternateSetting;

    for ((i = 0, alt = &(intfc->altsetting_array[0])); i < intfc->num_altsetting; (++i, ++alt))
    {
        if (alt->desc.bAlternateSetting == asnum)
        {
            hal_log_err("WARNING : Duplicate descriptor for config %d "
                       "interface %d altsetting %d, skipping\n",
                       cfgno, inum, asnum);
            goto skip_to_next_interface_descriptor;
        }
    }

    ++intfc->num_altsetting;
    memcpy((void *)(&alt->desc), (void *)interface_desc, USB_DT_INTERFACE_SIZE);
    /* Skip over any Class Specific or Vendor Specific descriptors;
     * find the first endpoint or interface descriptor */
    //跳到endpoint desc
    alt->extra = buffer;
    i = _find_next_desc(buffer, size, USB_DT_ENDPOINT, USB_DT_INTERFACE, &n);
    alt->extralen = i;

    if (n > 0)
    {
        hal_log_info("skipped %d descriptor%s after %s\n", n, plural(n), "interface");
    }

    buffer += i;
    size -= i;
    /* Allocate space for the right(?) number of endpoints */
    num_ep = num_ep_orig = alt->desc.bNumEndpoints;
    alt->desc.bNumEndpoints = 0;        // Use as a counter
    if (num_ep == 0) {
        hal_log_info("num_ep:%d", num_ep);
        return buffer - buffer0;
    }

    if (num_ep > USB_MAXENDPOINTS)
    {
        hal_log_err("WARNING : too many endpoints for config %d interface %d "
                   "altsetting %d: %d, using maximum allowed: %d\n",
                   cfgno, inum, asnum, num_ep, USB_MAXENDPOINTS);
        num_ep = USB_MAXENDPOINTS;
    }

    //分配endpoint desc的空间
    len = sizeof(struct usb_host_virt_endpoint) * num_ep;
    alt->endpoint = malloc(len);

    if (!alt->endpoint)
    {
        hal_log_err("ERR: MALLOC failed\n");
        return -ENOMEM;
    }

    memset(alt->endpoint, 0, len);
    /* Parse all the endpoint descriptors */
    n = 0;

    while (size > 0)
    {
        if (((struct usb_descriptor_header *) buffer)->bDescriptorType == USB_DT_INTERFACE)
        {
            break;
        }

        retval = _usb_parse_endpoint_desc(cfgno, inum, asnum, alt, num_ep, buffer, size);

        if (retval < 0)
        {
            return retval;
        }

        ++n;
        buffer += retval;
        size -= retval;
    }

    if (n != num_ep_orig)
    {
        hal_log_err("WARNING : config %d interface %d altsetting %d has %d "
                   "endpoint descriptor%s, different from the interface "
                   "descriptor's value: %d\n",
                   cfgno, inum, asnum, n, plural(n), num_ep_orig);
    }

    return buffer - buffer0;
skip_to_next_interface_descriptor:
    i = _find_next_desc(buffer, size, USB_DT_INTERFACE, USB_DT_INTERFACE, NULL);
    return buffer - buffer0 + i;
}


//cfgidx    :   config index
//config    :   为本config准备的usb_host_virt_config
//buff  :   完整config的内容(包括下游的)
//size  :   完整config的长度
static int _usb_parse_config_desc(int cfgidx,
                                  struct usb_host_virt_config *config,
                                  unsigned char *buffer,
                                  int size)
{
    unsigned char *buffer0 = buffer;
    int cfgno = 0;
    s32 interface_nr = 0;                   //本config的interface数
    s32 nintf_orig = 0;
    int i = 0, j = 0, n = 0;
    struct usb_interface_cache *intfc = NULL;
    u8 *buffer2 = NULL;                     //临时buff,
    int size2 = 0;
    struct usb_descriptor_header *header = NULL;
    int len = 0, retval = 0;
    u8 inums[USB_MAXINTERFACES];            //记录interface的编号
    u8 alt_setting_nr[USB_MAXINTERFACES];   //本config中各个interface的AlertateSetting的数目
    //--<1>--将config自身保存到config->desc
    memcpy((void *)(&config->desc), (void *)buffer, USB_DT_CONFIG_SIZE);

    if (config->desc.bDescriptorType != USB_DT_CONFIG ||
        config->desc.bLength < USB_DT_CONFIG_SIZE)
    {
        hal_log_err("PANIC : [hub] :invalid descriptor for config index %d: "
                   "type = 0x%X, length = %d\n", cfgidx,
                   config->desc.bDescriptorType, config->desc.bLength);
        return -EINVAL;
    }

    cfgno = config->desc.bConfigurationValue;   //本config的nr
    //--<2>--跳过config自身
    buffer += config->desc.bLength;
    size -= config->desc.bLength;
    interface_nr = nintf_orig = config->desc.bNumInterfaces;    //本config的interface数

    if (interface_nr > USB_MAXINTERFACES)
    {
        hal_log_err("PANIC : [hub] :config %d has too many interfaces: %d, "
                   "using maximum allowed: %d\n",
                   cfgno, interface_nr, USB_MAXINTERFACES);
        interface_nr = USB_MAXINTERFACES;
    }

    //--<3>--遍历完整config中余下的desc, 其实只关心Interface，统计各个interface的数目
    n = 0;

    for ((buffer2 = buffer, size2 = size);
         size2 > 0;
         (buffer2 += header->bLength, size2 -= header->bLength))
    {
        //toutine check
        if (size2 < sizeof(struct usb_descriptor_header))
        {
            hal_log_err("PANIC : [hub] :config %d descriptor has %d excess "
                       "byte%s, ignoring\n",
                       cfgno, size2, plural(size2));
            break;
        }

        header = (struct usb_descriptor_header *) buffer2;

        if ((header->bLength > size2) || (header->bLength < 2))
        {
            hal_log_err("PANIC : [hub] :config %d has an invalid descriptor "
                       "of length %d, skipping remainder of the config\n",
                       cfgno, header->bLength);
            break;
        }

        //--<3_1>--Interface描述符号
        if (header->bDescriptorType == USB_DT_INTERFACE)
        {
            struct usb_interface_descriptor *d = NULL;
            int inum = 0;
            d = (struct usb_interface_descriptor *) header;

            if (d->bLength < USB_DT_INTERFACE_SIZE)
            {
                hal_log_err("PANIC : [hub] :config %d has an invalid "
                           "interface descriptor of length %d, "
                           "skipping\n", cfgno, d->bLength);
                continue;
            }

            inum = d->bInterfaceNumber;

            if (inum >= nintf_orig)
            {
                hal_log_err("PANIC : [hub] :config %d has an invalid "
                           "interface number: %d but max is %d\n",
                           cfgno, inum, nintf_orig - 1);
            }

            /* Have we already encountered this interface?
             * Count its altsettings */
            for (i = 0; i < n; ++i)
            {
                if (inums[i] == inum)
                {
                    break;
                }
            }

            if (i < n)
            {
                if (alt_setting_nr[i] < 255)
                {
                    ++alt_setting_nr[i];
                }
            }
            else if (n < USB_MAXINTERFACES)
            {
                inums[n] = inum;
                alt_setting_nr[n] = 1;
                ++n;
            }
        }
        else if (header->bDescriptorType == USB_DT_DEVICE ||
                 header->bDescriptorType == USB_DT_CONFIG)
        {
            hal_log_err("PANIC : [hub] :config %d contains an unexpected "
                       "descriptor of type 0x%X, skipping\n",
                       cfgno, header->bDescriptorType);
        }
    }   /* for ((buffer2 = buffer, size2 = size); ...) */

    size = buffer2 - buffer;
    config->desc.wTotalLength = cpu_to_le16(buffer2 - buffer0);

    if (n != interface_nr)
    {
        hal_log_err("PANIC : [hub] :config %d has %d interface%s, different from "
                   "the descriptor's value: %d\n",
                   cfgno, n, plural(n), nintf_orig);
    }
    else if (n == 0)
    {
        hal_log_err("PANIC : [hub] :config %d has no interfaces?\n", cfgno);
    }

    //记录interface的数目
    config->desc.bNumInterfaces = interface_nr = n;

    /* Check for missing interface numbers */
    for (i = 0; i < interface_nr; ++i)
    {
        for (j = 0; j < interface_nr; ++j)
        {
            if (inums[j] == i)
            {
                break;
            }
        }

        if (j >= interface_nr)
        {
            hal_log_err("PANIC : [hub] :config %d has no interface number "
                       "%d\n", cfgno, i);
        }
    }

    //--<4>--为各个interface分配存储空间
    /* Allocate the usb_interface_caches and altsetting arrays */
    for (i = 0; i < interface_nr; ++i)
    {
        //u8 * buff_addr = 0;
        //u32 temp = 0;
        j = alt_setting_nr[i];

        if (j > USB_MAXALTSETTING)
        {
            hal_log_err("PANIC : [hub] :oo many alternate settings for "
                       "config %d interface %d: %d, "
                       "using maximum allowed: %d\n",
                       cfgno, inums[i], j, USB_MAXALTSETTING);
            alt_setting_nr[i] = j = USB_MAXALTSETTING;
        }

        //--<4_1>--分配存储usb_interface_cache的空间
        len = sizeof(struct usb_interface_cache) ;
        config->intf_cache[i] = intfc = malloc(len);

        if (!intfc)
        {
            hal_log_err("ERR: malloc failed\n");
            return -ENOMEM;
        }

        memset(intfc, 0, len);
        //--<4_2>--分配存储usb_host_virt_interface[]的空间
        len =  sizeof(struct usb_host_virt_interface) * j;
        intfc->altsetting_array = malloc(len);

        if (!intfc->altsetting_array)
        {
            hal_log_err("ERR: malloc failed\n");
            free(config->intf_cache[i]);
            config->intf_cache[i] = NULL;
            return -ENOMEM;
        }

        memset(intfc->altsetting_array, 0, len);
    }

    //--<4>--后移，直到Interface desc
    /* Skip over any Class Specific or Vendor Specific descriptors;
     * find the first interface descriptor */
    config->extra = buffer;
    i = _find_next_desc(buffer, size, USB_DT_INTERFACE, USB_DT_INTERFACE, &n);
    config->extralen = i;

    if (n > 0)
    {
        hal_log_info("  [hub] :skipped %d descriptor%s after %s\n", n, plural(n), "configuration");
    }

    buffer += i;
    size -= i;

    /* Parse all the interface/altsetting descriptors */
    while (size > 0)
    {
        retval = _usb_parse_interface_desc(cfgno,
                                           config,
                                           buffer,
                                           size,
                                           inums,
                                           alt_setting_nr);

        if (retval < 0)
        {
            hal_log_err("ERR: _usb_parse_interface_desc failed\n");
            return retval;
        }

        buffer += retval;
        size -= retval;
    }

    /* Check for missing altsettings */
    for (i = 0; i < interface_nr; ++i)
    {
        intfc = config->intf_cache[i];

        for (j = 0; j < intfc->num_altsetting; ++j)
        {
            for (n = 0; n < intfc->num_altsetting; ++n)
            {
                if (intfc->altsetting_array[n].desc.bAlternateSetting == j)
                {
                    break;
                }
            }

            if (n >= intfc->num_altsetting)
            {
                hal_log_err("PANIC : [hub] :config %d interface %d has no "
                           "altsetting %d\n", cfgno, inums[i], j);
            }
        }
    }

    return 0;
}

/* 获得confg描述符，并parser之 */
int usb_get_all_config_desc_and_parser(struct usb_host_virt_dev *dev)
{
    int result      = -ENOMEM;
    int ncfg        = dev->descriptor.bNumConfigurations;   //config的总数目
    u32 cur_cfg_nr  = 0;    //当前cfg的编号
    u32 length      = 0;
    u8 *buffer      = NULL;
    u8 *bigbuffer   = NULL;
    struct usb_config_descriptor *desc = NULL;

    if (ncfg > USB_MAXCONFIG)
    {
        hal_log_info("INFO : [hub] too many configurations: %d, "
                  "using maximum allowed: %d\n", ncfg, USB_MAXCONFIG);
        dev->descriptor.bNumConfigurations = ncfg = USB_MAXCONFIG;
    }

    if (ncfg < 1)
    {
        hal_log_err("PANIC : no configurations\n");
        return -EINVAL;
    }

    length = ncfg * sizeof(struct usb_host_virt_config);
    dev->config = malloc(length);

    if (!dev->config)
    {
        hal_log_err("ERR: malloc failed\n");
        goto err2;
    }

    memset(dev->config, 0, length);
    length = ncfg * sizeof(char *);
    dev->rawdescriptors = malloc(length);

    if (!dev->rawdescriptors)
    {
        hal_log_err("ERR: malloc failed\n");
        goto err2;
    }

    memset(dev->rawdescriptors, 0, length);
    buffer = malloc(USB_DT_CONFIG_SIZE);

    if (!buffer)
    {
        hal_log_err("ERR: malloc failed\n");
        goto err2;
    }

    memset(buffer, 0, USB_DT_CONFIG_SIZE);
    desc = (struct usb_config_descriptor *)buffer;

    //逐个获取config,并解析该config
    for (cur_cfg_nr = 0; cur_cfg_nr < ncfg; cur_cfg_nr++)
    {
        //--<1>--试探性的获取config，主要目的是获取整个config的total len
        result = usb_get_descriptor(dev, USB_DT_CONFIG, cur_cfg_nr, buffer, USB_DT_CONFIG_SIZE);

        if (result < 0)
        {
            hal_log_err("PANIC : [hub] : unable to read config index %d "
                       "descriptor/%s\n", cur_cfg_nr, "start");
            goto err;
        }
        else if (result < 4)
        {
            hal_log_err("PANIC : [hub] : config index %d descriptor too short "
                       "(expected %i, got %i)\n", cur_cfg_nr,
                       USB_DT_CONFIG_SIZE, result);
            result = -EINVAL;
            goto err;
        }

        length = max((int) le16_to_cpu(desc->wTotalLength), USB_DT_CONFIG_SIZE);
        //Now that we know the length, get the whole thing //
        bigbuffer = malloc(length);

        if (!bigbuffer)
        {
            hal_log_err("ERR: malloc failed\n");
            result = -ENOMEM;
            goto err;
        }

        memset(bigbuffer, 0, length);
        //--<2>--完整的获取config
        result = usb_get_descriptor(dev, USB_DT_CONFIG, cur_cfg_nr, bigbuffer, length);

        if (result < 0)
        {
            hal_log_err("PANIC : [ hub] : unable to read config index %d "
                       "descriptor/%s\n", cur_cfg_nr, "all");
            free(bigbuffer);
            bigbuffer = NULL;
            goto err;
        }

        if (result < length)
        {
            hal_log_err("PANIC : [ hub] : config index %d descriptor too short "
                       "(expected %i, got %i)\n", cur_cfg_nr, length, result);
            length = result;
        }

        dev->rawdescriptors[cur_cfg_nr] = bigbuffer;
        //--<3>--解析该config
        result = _usb_parse_config_desc(cur_cfg_nr, &dev->config[cur_cfg_nr], bigbuffer, length);

        if (result < 0)
        {
            ++cur_cfg_nr;
            goto err;
        }
    }

    result = 0;
err:

    if (buffer)
    {
        free(buffer);
        buffer = NULL;
    }
    else
    {
        hal_log_err("ERR: parameter is NULL, can't free\n");
    }

    dev->descriptor.bNumConfigurations = cur_cfg_nr;
err2:

    if (result == -ENOMEM)
    {
        hal_log_err("out of memory\n");
    }

    return result;
}


void usb_release_interface_cache(struct usb_interface_cache *intfc)
{
    s32 j = 0;

    if (intfc == NULL)
    {
        hal_log_err("ERR: usb_release_interface_cache: input = NULL\n");
        return ;
    }

    for (j = 0; j < intfc->num_altsetting; j++)
    {
        if (intfc->altsetting_array[j].endpoint)
        {
            free(intfc->altsetting_array[j].endpoint);
            intfc->altsetting_array[j].endpoint = NULL;
        }
        else
        {
            hal_log_err("ERR: parameter is NULL, can't free\n");
        }
    }

    free(intfc);
    // intfc = NULL;
    return ;
}

// hub-only!! ... and only exported for reset/reinit path.
// otherwise used internally on disconnect/destroy path
void usb_destroy_configuration(struct usb_host_virt_dev *dev)
{
    int c = 0, i = 0;

    if (!dev->config)
    {
        hal_log_err("ERR: dev is not config\n");
        return;
    }

    if (dev->rawdescriptors)
    {
        for (i = 0; i < dev->descriptor.bNumConfigurations; i++)
        {
            if (dev->rawdescriptors[i])
            {
                free(dev->rawdescriptors[i]);
                dev->rawdescriptors[i] = NULL;
            }
            else
            {
                hal_log_err("ERR: parameter is NULL, can't free\n");
            }
        }

        if (dev->rawdescriptors)
        {
            free(dev->rawdescriptors);
            dev->rawdescriptors = NULL;
        }
        else
        {
            hal_log_err("ERR: parameter is NULL, can't free\n");
        }
    }

    for (c = 0; c < dev->descriptor.bNumConfigurations; c++)
    {
        struct usb_host_virt_config *cf = &dev->config[c];

        if (cf->string)
        {
            free(cf->string);
            cf->string = NULL;
        }
        else
        {
            hal_log_err("ERR: parameter is NULL, can't free\n");
        }

        for (i = 0; i < cf->desc.bNumInterfaces; i++)
        {
            if (cf->intf_cache[i])
            {
                usb_release_interface_cache(cf->intf_cache[i]);
                cf->intf_cache[i] = NULL;
            }
        }
    }

    if (dev->config)
    {
        free(dev->config);
        dev->config = NULL;
    }
    else
    {
        hal_log_err("ERR: parameter is NULL, can't free\n");
    }

    return ;
}


