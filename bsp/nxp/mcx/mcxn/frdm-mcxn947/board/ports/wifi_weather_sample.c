/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024-06-27     Zhang        the first version
 */

#include <rtdevice.h>
#include <rtthread.h>
#include "spi_wifi_rw007.h"
#include "webclient.h"
#include "cJSON.h"
#include "stdio.h"

#ifdef PKG_USING_CJSON
#ifdef PKG_USING_WEBCLIENT

#define  city_id               54523
#define  MAX_RESPONSE_SIZE     1024
#define  INITIAL_RESPONSE_SIZE 128

static void parse_weather_data(const char *buf);
static void get_weather_forecast(void);

static void parse_weather_data(const char *buf)
{

    cJSON *root = cJSON_Parse(buf);
    if (root == NULL) {
        rt_kprintf("Error parsing JSON data\n");
        return;
    }

    cJSON *msg = cJSON_GetObjectItem(root, "msg");
    if (msg == NULL) {
        rt_kprintf("Error getting msg object\n");
        cJSON_Delete(root);
        return;
    }
    else {
        rt_kprintf("msg: %s\n", msg->valuestring);
    }

    cJSON *code = cJSON_GetObjectItem(root, "code");
    if (code == NULL) {
        rt_kprintf("Error getting code object\n");
        cJSON_Delete(root);
        return;
    }
    else {
        rt_kprintf("code: %d\n", code->valueint);
    }

    cJSON *data = cJSON_GetObjectItem(root, "data");
    if (data == NULL) {
        rt_kprintf("Error getting data object\n");
        cJSON_Delete(root);
        return;
    }
    else {
        rt_kprintf("data: \n");
    }

    cJSON *location = cJSON_GetObjectItem(data, "location");
    if (location == NULL) {
        rt_kprintf("Error getting location object\n");
        cJSON_Delete(root);
        return;
    }
    else {
        rt_kprintf("  location: \n");
    }

    cJSON *id = cJSON_GetObjectItem(location, "id");
    cJSON *name = cJSON_GetObjectItem(location, "name");
    cJSON *path = cJSON_GetObjectItem(location, "path");

    if (id != NULL && name != NULL && path != NULL) {
        rt_kprintf("     id: %d\n", id->valueint);
        rt_kprintf("     name: %s\n", name->valuestring);
        rt_kprintf("     path: %s\n", path->valuestring);
    } else {
        rt_kprintf("Error getting fields\n");
    }

    cJSON *now = cJSON_GetObjectItem(data, "now");
    if (now == NULL) {
        rt_kprintf("Error getting now object\n");
        cJSON_Delete(root);
        return;
    }
    else {
        rt_kprintf("  now: \n");
    }

    cJSON *precipitation = cJSON_GetObjectItem(now, "precipitation");
    cJSON *temperature = cJSON_GetObjectItem(now, "temperature");
    cJSON *pressure = cJSON_GetObjectItem(now, "pressure");
    cJSON *humidity = cJSON_GetObjectItem(now, "humidity");
    cJSON *windDirection = cJSON_GetObjectItem(now, "windDirection");
    cJSON *windDirectionDegree = cJSON_GetObjectItem(now, "windDirectionDegree");
    cJSON *windSpeed = cJSON_GetObjectItem(now, "windSpeed");
    cJSON *windScale = cJSON_GetObjectItem(now, "windScale");

    if (precipitation != NULL && temperature != NULL && pressure != NULL && humidity != NULL &&
        windDirection != NULL && windDirectionDegree != NULL && windSpeed != NULL && windScale != NULL) {
        rt_kprintf("     precipitation: %d\n", precipitation->valueint);
        rt_kprintf("     temperature: %.1f\n", temperature->valuedouble);
        rt_kprintf("     pressure: %d\n", pressure->valueint);
        rt_kprintf("     humidity: %d\n", humidity->valueint);
        rt_kprintf("     windDirection: %s\n", windDirection->valuestring);
        rt_kprintf("     windDirectionDegree: %d\n", windDirectionDegree->valueint);
        rt_kprintf("     windSpeed: %.1f\n", windSpeed->valuedouble);
        rt_kprintf("     windScale: %s\n", windScale->valuestring);
    } else {
        rt_kprintf("Error getting fields\n");
    }

    cJSON *alarm = cJSON_GetObjectItem(data, "alarm");
    if (alarm == NULL) {
        rt_kprintf("Error getting alarm object\n");
        cJSON_Delete(root);
        return;
    }
    else {
        rt_kprintf("  alarm: %s\n", cJSON_Print(alarm));
    }

    cJSON *lastUpdate = cJSON_GetObjectItem(data, "lastUpdate");
    if (lastUpdate == NULL) {
        rt_kprintf("Error getting lastUpdate object\n");
        cJSON_Delete(root);
        return;
    }
    else {
        rt_kprintf("  lastUpdate: %s\n", cJSON_Print(lastUpdate));
    }

    cJSON_Delete(root);
}

static void get_weather_forecast(void)
{
    char url[256];
    snprintf(url, sizeof(url), "http://weather.cma.cn/api/now/%d", city_id);

    struct webclient_session* session = webclient_session_create(1024);
    if(session == NULL) return;

    int rc = webclient_get(session, url);
    if(rc != 200) goto free_session_exit;

    char *response = rt_malloc(INITIAL_RESPONSE_SIZE);
    if(response == NULL) goto free_session_exit;

    int data_ptr = 0;
    int buf_size = INITIAL_RESPONSE_SIZE;
    do {
        int bytes_read = webclient_read(session, &response[data_ptr], INITIAL_RESPONSE_SIZE);
        if(bytes_read <= 0) {
           break;
        }

        data_ptr += bytes_read;
        if(data_ptr > MAX_RESPONSE_SIZE) {
           break;
        }

        if((data_ptr + INITIAL_RESPONSE_SIZE) > buf_size) {
            response = rt_realloc(response, data_ptr + INITIAL_RESPONSE_SIZE);
            buf_size += INITIAL_RESPONSE_SIZE;
        }
    } while(1);

    /* response is alive */
    parse_weather_data(response);

    rt_free(response);

free_session_exit:
    webclient_close(session);
}

static void wifi_weather_sample(void)
{
    /* wifi join */;
    get_weather_forecast();
    rt_kprintf("\r\n");
    rt_kprintf("wifi_weather_sample complete\r\n");
}

MSH_CMD_EXPORT(wifi_weather_sample, wifi weather sample);

#endif

#endif
