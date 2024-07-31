#define __BF_FIELD_CHECK(...)

#define FIELD_GET(_mask, _reg)                      \
    ({                              \
        __BF_FIELD_CHECK(_mask, _reg, 0U, "FIELD_GET: ");   \
        (typeof(_mask))(((_reg) & (_mask)) >> __bf_shf(_mask)); \
    })

#define FIELD_PREP(_mask, _val)                     \
    ({                              \
        __BF_FIELD_CHECK(_mask, 0ULL, _val, "FIELD_PREP: ");    \
        ((typeof(_mask))(_val) << __bf_shf(_mask)) & (_mask);   \
    })

#define DIV_ROUND_UP(n, d) (((n) + (d) - 1) / (d))

#define min_t(type, x, y)   (((type)x < (type)y)? x : y)
#define max_t(type, x, y)   (((type)x > (type)y)? x : y)
#define min(x, y) ((x) < (y)? (x) : (y))

#define from_timer(var, callback_timer, timer_fieldname) \
    container_of(callback_timer, typeof(*var), timer_fieldname)



#define le32_to_cpu(x) (x)
#define le16_to_cpu(x) (x)
#define cpu_to_le16(x) (x)
#define cpu_to_le32(x) (x)
#define lower_32_bits(n) ((rt_uint32_t)((n) & 0xffffffff))
#define upper_32_bits(n) ((rt_uint32_t)(((n) >> 16) >> 16))

#define DIV_ROUND_UP(n, d) (((n) + (d) - 1) / (d))


unsigned long nsecs_to_jiffies(rt_uint64_t n)
{
    return 0;
}

#define do_div(n,base) ({                   \
    uint32_t __base = (base);               \
    uint32_t __rem;                     \
    __rem = ((uint64_t)(n)) % __base;           \
    (n) = ((uint64_t)(n)) / __base;             \
    __rem;                          \
 })


void usleep_range(unsigned long min, unsigned long max)
{
    rt_int32_t msecs;

    msecs = (min + max)/2000;
    if (msecs)
        rt_thread_mdelay(msecs);
    else
        udelay((min + max)/2);
}

int regulator_is_supported_voltage(struct regulator *regulator,
				   int min_uV, int max_uV)
{
	// struct regulator_dev *rdev = regulator->rdev;
	// int i, voltages, ret;

	// /* If we can't change voltage check the current voltage */
	// if (!regulator_ops_is_valid(rdev, REGULATOR_CHANGE_VOLTAGE)) {
	// 	ret = regulator_get_voltage(regulator);
	// 	if (ret >= 0)
	// 		return min_uV <= ret && ret <= max_uV;
	// 	else
	// 		return ret;
	// }

	// /* Any voltage within constrains range is fine? */
	// if (rdev->desc->continuous_voltage_range)
	// 	return min_uV >= rdev->constraints->min_uV &&
	// 			max_uV <= rdev->constraints->max_uV;

	// ret = regulator_count_voltages(regulator);
	// if (ret < 0)
	// 	return 0;
	// voltages = ret;

	// for (i = 0; i < voltages; i++) {
	// 	ret = regulator_list_voltage(regulator, i);

	// 	if (ret >= min_uV && ret <= max_uV)
	// 		return 1;
	// }

	// return 0;
}

int regulator_enable(struct regulator *regulator)
{
	// struct regulator_dev *rdev = regulator->rdev;
	// struct ww_acquire_ctx ww_ctx;
	// int ret;

	// regulator_lock_dependent(rdev, &ww_ctx);
	// ret = _regulator_enable(regulator);
	// regulator_unlock_dependent(rdev, &ww_ctx);

	// return ret;
}


int regulator_get_current_limit(struct regulator *regulator)
{
    // return 0;
}

void dma_free_coherent(struct rt_device *dev, size_t size,
        void *cpu_addr, dma_addr_t dma_handle)
{
}

rt_bool_t mmc_can_gpio_cd(struct mmc_host *host)
{
    if(host->slot.handler_priv->cd)
    {
        struct mmc_gpio *ctx = host->slot.handler_priv;

	    return ctx->cd_gpio ? true : false;

    }
    return false;
}

