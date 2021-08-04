/*
 * File      : at_device_esp8266.h

 * Change Logs:
 * Date           Author       Notes
 * 2021-07-16     yangtao     first version
 */

#ifndef __AT_DEVICE_MG21_H__

#define __AT_DEVICE_MG21_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <stdlib.h>

#include <mg21_device.h>

struct at_device_mg21
{
    char *device_name;
    char *client_name;

    size_t recv_line_num;
    struct at_device device;

    void *user_data;
};

#ifdef __cplusplus
}
#endif

#endif /* __AT_DEVICE_MG21_H__ */
