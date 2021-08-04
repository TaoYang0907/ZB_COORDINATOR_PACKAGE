/*
 * File      : at_sample_mg21.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006 - 2018, RT-Thread Development Team
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with this program; if not, write to the Free Software Foundation, Inc.,
 *  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-08-03     yangtao     first version
 */

#include <rtthread.h>
#include <finsh.h>
#include <at_device_mg21.h>

#define LOG_TAG                        "at.sample.mg"
#include <at_log.h>

#define AT_MG21_SAMPLE_DEIVCE_NAME        "mg0"

static struct at_device_mg21 mg0 =
{
    AT_MG21_SAMPLE_DEIVCE_NAME,
    AT_MG21_SAMPLE_CLIENT_NAME,
    AT_MG21_SAMPLE_RECV_BUFF_LEN,
};

static int mg21_device_register(void)
{
    struct at_device_mg21 *mg21 = &mg0;

    LOG_I("mg21 register");
    return at_device_register(&(mg21->device),
                              mg21->device_name,
                              mg21->client_name,
                              AT_DEVICE_CLASS_MG21,
                              (void *) mg21);
}
INIT_APP_EXPORT(mg21_device_register);

int zb_pj(int argc, char**argv)
{
    pj_req_t *pjCmd = rt_malloc(sizeof(pj_req_t));

    pjCmd -> sec = 0x3C;
    pjCmd -> nodeId = 0xFFFF;
    struct at_device *device = RT_NULL;

    device = at_device_get_by_name(AT_DEVICE_NAMETYPE_DEVICE, "mg0");
    if(device == RT_NULL)
    {
        rt_kprintf("can't find device\r\n");
        return -RT_ERROR;
    }

    at_device_control(device, AT_DEVICE_CTRL_PJ, (void *)pjCmd);

    rt_free(pjCmd);

    return RT_EOK;
}

/* Export open network function to msh  */
MSH_CMD_EXPORT(zb_pj, Coordinator Open Network);

int zb_on(int argc, char**argv)
{
    zcl_onoff_cmd_t *onCmd = rt_malloc(sizeof(zcl_onoff_cmd_t));
    //Suppose there is a switch device with network short address 0xABCD and port number 0x0A connected to the coordinator  
    onCmd -> nwkAddr = 0xABCD;
    onCmd -> endpoint = 0x0A;
    onCmd -> mode = 1;

    struct at_device *device = RT_NULL;

    device = at_device_get_by_name(AT_DEVICE_NAMETYPE_DEVICE, "mg0");
    if(device == RT_NULL)
    {
        rt_kprintf("can't find device\r\n");
        return -RT_ERROR;
    }

    at_device_control(device, AT_DEVICE_CTRL_ONOFF, (void *)onCmd);

    rt_free(onCmd);

    return RT_EOK;
}

/* Export onoff function to msh */
MSH_CMD_EXPORT(zb_on, Control devices with onoff attribute);

int zb_off(int argc, char**argv)
{
    zcl_onoff_cmd_t *offCmd = rt_malloc(sizeof(zcl_onoff_cmd_t));
    //Suppose there is a switch device with network short address 0xABCD and port number 0x0A connected to the coordinator 
    offCmd -> nwkAddr = 0xABCD;
    offCmd -> endpoint = 0x0A;
    offCmd -> mode = 1;

    struct at_device *device = RT_NULL;

    device = at_device_get_by_name(AT_DEVICE_NAMETYPE_DEVICE, "mg0");
    if(device == RT_NULL)
    {
        rt_kprintf("can't find device\r\n");
        return -RT_ERROR;
    }

    at_device_control(device, AT_DEVICE_CTRL_ONOFF, (void *)offCmd);

    rt_free(offCmd);

    return RT_EOK;
}

/* Export onoff function to msh */
MSH_CMD_EXPORT(zb_off, Control devices with onoff attribute);

int zb_readAttr(int argc, char**argv)
{
    read_attrs_req_t *readAttrCmd = rt_malloc(sizeof(read_attrs_req_t));
    //Suppose there is a switch device with network short address 0xABCD and port number 0x0A connected to the coordinator 
    readAttrCmd -> nwkAddr = 0xABCD;
    readAttrCmd -> endpoint = 0x0A;
    readAttrCmd -> clusterID = 0x0006;
    readAttrCmd -> attrID = 0x0000;

    struct at_device *device = RT_NULL;

    device = at_device_get_by_name(AT_DEVICE_NAMETYPE_DEVICE, "mg0");
    if(device == RT_NULL)
    {
        rt_kprintf("can't find device\r\n");
        return -RT_ERROR;
    }

    at_device_control(device, AT_DEVICE_CTRL_READATTR, (void *)readAttrCmd);

    rt_free(readAttrCmd);

    return RT_EOK;
}

/* Export read device attribute function to msh */
MSH_CMD_EXPORT(zb_readAttr, Read attribute from the device);
