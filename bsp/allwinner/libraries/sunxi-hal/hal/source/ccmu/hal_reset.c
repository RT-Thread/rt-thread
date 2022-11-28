#include <aw_list.h>
#include <stdlib.h>
#include <hal_log.h>
#include <hal_reset.h>

static LIST_HEAD(reset_control_list);

int reset_control_register(struct reset_control_dev *rcdev) //for reset system
{
    if (rcdev)
    {
        list_add_tail(&rcdev->node, &reset_control_list);
        return 0;
    }
    return -1;
}

int reset_control_unregister(struct reset_control *reset) //for reset system
{
    struct reset_control_dev *rcdev = NULL;

    if (!rcdev)
    {
        return 0;
    }

    list_for_each_entry(rcdev, &reset_control_list, node)
    {
        if (rcdev->type != reset->rcdev->type)
        {
            continue;
        }
        list_del(&rcdev->node);
        return 0;
    }

    return 0;
}

#ifdef CONFIG_DRIVERS_SUNXI_CCU

struct reset_control *hal_reset_control_get(hal_reset_type_t type, hal_reset_id_t id)
{
    struct reset_control_dev *rcdev = NULL;
    struct reset_control *rc = NULL;

    rc = (struct reset_control *)malloc(sizeof(*rc));
    if (!rc)
    {
        return NULL;
    }

    list_for_each_entry(rcdev, &reset_control_list, node)
    {
        if (rcdev->type != type)
        {
            continue;
        }
        if (rcdev->nr_resets < id)
        {
            continue;
        }
        rc->rcdev = rcdev;
        rc->id = id;
        rc->enable_count = 0;
        return rc;
    }
    return NULL;
}

int hal_reset_control_put(struct reset_control *reset)
{
    if (!reset)
    return 0;

    free(reset);
    return 0;
}


int hal_reset_control_assert(struct reset_control *reset)
{
    struct reset_control_dev *rcdev;

    if (!reset || !reset->rcdev)
    {
        return 0;
    }

    rcdev = reset->rcdev;

    if (rcdev->ops && rcdev->ops->assert)
    {
        return rcdev->ops->assert(rcdev, reset->id);
    }

    return -1;
}

int hal_reset_control_deassert(struct reset_control *reset)
{
    struct reset_control_dev *rcdev;

    if (!reset || !reset->rcdev)
    {
        return 0;
    }

    rcdev = reset->rcdev;

    if (rcdev->ops && rcdev->ops->deassert)
    {
        return rcdev->ops->deassert(rcdev, reset->id);
    }

    return -1;
}

int hal_reset_control_reset(struct reset_control *reset)
{
    struct reset_control_dev *rcdev;

    if (!reset || !reset->rcdev)
    {
        return 0;
    }

    rcdev = reset->rcdev;

    if (rcdev->ops && rcdev->ops->deassert)
    {
        return rcdev->ops->reset(rcdev, reset->id);
    }

    return -1;
}


int hal_reset_control_status(struct reset_control *reset)
{

    struct reset_control_dev *rcdev;

    if (!reset || !reset->rcdev)
    {
        return 0;
    }

    rcdev = reset->rcdev;

    if (rcdev->ops && rcdev->ops->deassert)
    {
        return rcdev->ops->status(rcdev, reset->id);
    }

    return 0;
}

#else

struct reset_control *hal_reset_control_get(hal_reset_type_t type_id, u32 reset_id)
{
    return NULL;
}

int hal_reset_control_put(struct reset_control *reset)
{
    return 0;
}


int hal_reset_control_assert(struct reset_control *reset)
{
    return 0;
}

int hal_reset_control_deassert(struct reset_control *reset)
{
    return 0;
}

int hal_reset_control_reset(struct reset_control *reset)
{
    return 0;
}

int hal_reset_control_status(struct reset_control *reset)
{
    return 0;
}
#endif
