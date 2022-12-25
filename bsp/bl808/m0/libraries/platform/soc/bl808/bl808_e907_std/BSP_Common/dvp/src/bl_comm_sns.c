#include <bl808_common.h>
#include "bl_comm_sns.h"


#undef  DEBUG_MODULE
#define DEBUG_MODULE 0

bool is_param_valid(int value, int min, int max)
{
    if (value > max || value < min) {
        return false;
    }
    return true;
}

void clip_param_range(int *value, int min, int max)
{
    if (*value > max) *value = max;
    if (*value < min) *value = min;
}

intpl_point_t create_intpl_point(int position, int value)
{
    intpl_point_t intpl_point;
    intpl_point.position = position;
    intpl_point.value = value;

    return intpl_point;
}

int linear_interpolate(intpl_point_t *point_L, intpl_point_t *point_H, int pos, int *value)
{
    if (point_H->position <= point_L->position) {
        MSG("linear_interpolate: invalid param!\r\n");
        return -1;
    }

    if (pos <= point_L->position) {
        *value = point_L->value;
    } else if (pos >= point_H->position) {
        *value = point_H->value;
    } else {
        *value = DIV_ROUND_SIGNED(
                (point_H->position - pos) * point_L->value +
                (pos - point_L->position) * point_H->value,
                point_H->position - point_L->position);
    }

    MSG("linear_interpolate: (%d, %d) ~ (%d, %d) -> (%d, %d)\r\n", point_L->position, point_L->value,
        point_H->position, point_H->value, pos, *value);

    return 0;
}

