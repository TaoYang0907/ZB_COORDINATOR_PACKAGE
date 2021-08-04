#include <at_device_mg21.h>
/*
 * File      : at_device_mg21.c

 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-07-16     yangtao     first version
 */

#include <stdio.h>
#include <string.h>


#define LOG_TAG                        "at.dev.mg"

#include <at_log.h>

#ifdef PKG_USING_ZB_COORDINATOR

/* =============================  mg21 operations ============================= */

static int mg21_info(struct at_device *device)
{
    at_response_t resp = RT_NULL;

    if(device == RT_NULL)
    {
        rt_kprintf("wrong device\r\n");
        at_delete_resp(resp);
        return -RT_ERROR;
    }

    resp = at_create_resp(512, 0, rt_tick_from_millisecond(5000));
    if (!resp)
    {
        rt_kprintf("No memory for response structure!\r\n");
        at_delete_resp(resp);
        return -RT_ENOMEM;
    }

    if (at_obj_exec_cmd(device -> client, resp, "ATI") != RT_EOK)
    {
        rt_kprintf("AT client send commands failed, response error or timeout !\r\n");
        at_delete_resp(resp);
        return -RT_ERROR;
    }

    /* Command sent successfully */
    rt_kprintf("AT Client send commands to AT Server success!\r\n");

    /* Processing response structure */
    for(int i = 1; i <= resp ->line_counts; i++)
    {
        rt_kprintf("%s\r\n", at_resp_get_line(resp, i));
    }

    /* Delete response structure */
    at_delete_resp(resp);

    return RT_EOK;
}

static int mg21_reset(struct at_device *device)
{
    at_response_t resp = RT_NULL;

    if(device == RT_NULL)
    {
        rt_kprintf("wrong device\r\n");
        at_delete_resp(resp);
        return -RT_ERROR;
    }

    resp = at_create_resp(512, 0, rt_tick_from_millisecond(5000));
    if (!resp)
    {
        rt_kprintf("No memory for response structure!\r\n");
        at_delete_resp(resp);
        return -RT_ENOMEM;
    }

    if (at_obj_exec_cmd(device -> client, resp, "ATF") != RT_EOK)
    {
        rt_kprintf("AT client send commands failed, response error or timeout !\r\n");
        at_delete_resp(resp);
        return -RT_ERROR;
    }

    /* Command sent successfully */
    rt_kprintf("AT Client send commands to AT Server success!\r\n");

    /* Processing response structure */
    for(int i = 1; i <= resp ->line_counts; i++)
    {
        rt_kprintf("%s\r\n", at_resp_get_line(resp, i));
    }

    /* Delete response structure */
    at_delete_resp(resp);

    return RT_EOK;
}

static int mg21_pj(struct at_device *device, void *arg)
{
    at_response_t resp = RT_NULL;

    if(device == RT_NULL)
    {
        rt_kprintf("wrong device\r\n");
        at_delete_resp(resp);
        return -RT_ERROR;
    }

    resp = at_create_resp(512, 0, rt_tick_from_millisecond(5000));
    if (!resp)
    {
        rt_kprintf("No memory for response structure!\r\n");
        at_delete_resp(resp);
        return -RT_ENOMEM;
    }

    char* cmd = rt_malloc(AT_MAX_CMD_LEN);

    if(arg == NULL)
    {
        sprintf(cmd, "AT+PJ");
        if (at_obj_exec_cmd(device -> client, resp, (const char *)cmd) != RT_EOK)
        {
            rt_kprintf("AT client send commands failed, response error or timeout !\r\n");
            at_delete_resp(resp);
            rt_free(cmd);
            return -RT_ERROR;
        }
    }
    else
    {
        sprintf(cmd, "AT+PJ:%02x,%04x", ((PJReq_t *)arg)->sec, ((PJReq_t *)arg)->nodeId);
        if (at_obj_exec_cmd(device -> client, resp, (const char *)cmd) != RT_EOK)
        {
            rt_kprintf("AT client send commands failed, response error or timeout !\r\n");
            at_delete_resp(resp);
            rt_free(cmd);
            return -RT_ERROR;
        }
    }

    /* Command sent successfully */
    rt_kprintf("AT Client send %s to AT Server success!\r\n", cmd);

    /* Processing response structure */
    for(int i = 1; i <= resp ->line_counts; i++)
    {
        rt_kprintf("%s\r\n", at_resp_get_line(resp, i));
    }

    /* Delete response structure */
    at_delete_resp(resp);

    rt_free(cmd);

    return RT_EOK;
}

static int mg21_set_radio_ch(struct at_device *device, void *arg)
{
    at_response_t resp = RT_NULL;

    if(device == RT_NULL)
    {
        rt_kprintf("wrong device\r\n");
        at_delete_resp(resp);
        return -RT_ERROR;
    }

    resp = at_create_resp(512, 0, rt_tick_from_millisecond(5000));
    if (!resp)
    {
        rt_kprintf("No memory for response structure!\r\n");
        at_delete_resp(resp);
        return -RT_ENOMEM;
    }

    char* cmd = rt_malloc(AT_MAX_CMD_LEN);

    if(arg == NULL || ((ChannelReq_t *)arg) -> channel > 26 || ((ChannelReq_t *)arg) -> channel < 11)
    {
        rt_kprintf("Set Radionch parameter error, please check the parameter !\r\n");
        at_delete_resp(resp);
        rt_free(cmd);
        return -RT_ERROR;
    }
    else
    {
        sprintf(cmd, "AT+RADIOCH:%d", ((ChannelReq_t *)arg) -> channel);
        if (at_obj_exec_cmd(device -> client, resp, (const char *)cmd) != RT_EOK)
        {
            rt_kprintf("AT client send commands failed, response error or timeout !\r\n");
            at_delete_resp(resp);
            rt_free(cmd);
            return -RT_ERROR;
        }
    }

    /* Command sent successfully */
    rt_kprintf("AT Client send %s to AT Server success!\r\n", cmd);

    /* Processing response structure */
    for(int i = 1; i <= resp ->line_counts; i++)
    {
        rt_kprintf("%s\r\n", at_resp_get_line(resp, i));
    }

    /* Delete response structure */
    at_delete_resp(resp);

    rt_free(cmd);

    return RT_EOK;
}

static int mg21_act_ep_desc(struct at_device *device, void *arg)
{
    at_response_t resp = RT_NULL;

    if(device == RT_NULL)
    {
        rt_kprintf("wrong device\r\n");
        at_delete_resp(resp);
        return -RT_ERROR;
    }

    resp = at_create_resp(512, 0, rt_tick_from_millisecond(5000));
    if (!resp)
    {
        rt_kprintf("No memory for response structure!\r\n");
        at_delete_resp(resp);
        return -RT_ENOMEM;
    }

    char* cmd = rt_malloc(AT_MAX_CMD_LEN);

    sprintf(cmd, "AT+ACTEPDESC:%04x,%04x", ((ActiveEpReq_t *)arg) -> nodeId, ((ActiveEpReq_t *)arg) -> nodeId);
    if (at_obj_exec_cmd(device -> client, resp, (const char *)cmd) != RT_EOK)
    {
        rt_kprintf("AT client send commands failed, response error or timeout !\r\n");
        at_delete_resp(resp);
        rt_free(cmd);
        return -RT_ERROR;
    }

    /* Command sent successfully */
    rt_kprintf("AT Client send %s to AT Server success!\r\n", cmd);

    rt_thread_delay(500);
    /* Processing response structure */
    for(int i = 1; i <= resp ->line_counts; i++)
    {
        rt_kprintf("%s\r\n", at_resp_get_line(resp, i));
    }

    /* Delete response structure */
    at_delete_resp(resp);

    rt_free(cmd);

    return RT_EOK;
}

static int mg21_simple_desc(struct at_device *device, void *arg)
{
    at_response_t resp = RT_NULL;

    if(device == RT_NULL)
    {
        rt_kprintf("wrong device\r\n");
        at_delete_resp(resp);
        return -RT_ERROR;
    }

    resp = at_create_resp(512, 0, rt_tick_from_millisecond(5000));
    if (!resp)
    {
        rt_kprintf("No memory for response structure!\r\n");
        at_delete_resp(resp);
        return -RT_ENOMEM;
    }

    char* cmd = rt_malloc(AT_MAX_CMD_LEN);

    sprintf(cmd, "AT+SIMPLEDESC:%04x,%04x,%02x", ((SimpleDescReq_t *)arg) -> nodeId, ((SimpleDescReq_t *)arg) -> nodeId, ((SimpleDescReq_t *)arg) -> endpoint);
    if (at_obj_exec_cmd(device -> client, resp, (const char *)cmd) != RT_EOK)
    {
        rt_kprintf("AT client send commands failed, response error or timeout !\r\n");
        at_delete_resp(resp);
        rt_free(cmd);
        return -RT_ERROR;
    }

    /* Command sent successfully */
    rt_kprintf("AT Client send %s to AT Server success!\r\n", cmd);

    rt_thread_delay(500);
    /* Processing response structure */
    for(int i = 1; i <= resp ->line_counts; i++)
    {
        rt_kprintf("%s\r\n", at_resp_get_line(resp, i));
    }

    /* Delete response structure */
    at_delete_resp(resp);

    rt_free(cmd);

    return RT_EOK;
}

static int mg21_write_attr(struct at_device *device, void *arg)
{
    at_response_t resp = RT_NULL;

    if(device == RT_NULL)
    {
        rt_kprintf("wrong device\r\n");
        at_delete_resp(resp);
        return -RT_ERROR;
    }

    resp = at_create_resp(512, 0, rt_tick_from_millisecond(5000));
    if (!resp)
    {
        rt_kprintf("No memory for response structure!\r\n");
        at_delete_resp(resp);
        return -RT_ENOMEM;
    }

    char* cmd = rt_malloc(AT_MAX_CMD_LEN);

    sprintf(cmd, "AT+WRITEATTR:%04x,%02x,0,%04x,%04x,%02x,%s", ((WriteAttrsReq_t *)arg) -> nwkAddr, ((WriteAttrsReq_t *)arg) -> endpoint,
                                                                 ((WriteAttrsReq_t *)arg) -> clusterID, ((WriteAttrsReq_t *)arg) -> attrID,
                                                                 ((WriteAttrsReq_t *)arg) -> dataType, ((WriteAttrsReq_t *)arg) -> data);
    if (at_obj_exec_cmd(device -> client, resp, (const char *)cmd) != RT_EOK)
    {
        rt_kprintf("AT client send commands failed, response error or timeout !\r\n");
        at_delete_resp(resp);
        rt_free(cmd);
        return -RT_ERROR;
    }

    /* Command sent successfully */
    rt_kprintf("AT Client send %s to AT Server success!\r\n", cmd);

    rt_thread_delay(500);
    /* Processing response structure */
    for(int i = 1; i <= resp ->line_counts; i++)
    {
        rt_kprintf("%s\r\n", at_resp_get_line(resp, i));
    }

    /* Delete response structure */
    at_delete_resp(resp);

    rt_free(cmd);

    return RT_EOK;
}

static int mg21_read_attr(struct at_device *device, void *arg)
{
    at_response_t resp = RT_NULL;

    if(device == RT_NULL)
    {
        rt_kprintf("wrong device\r\n");
        at_delete_resp(resp);
        return -RT_ERROR;
    }

    resp = at_create_resp(512, 0, rt_tick_from_millisecond(5000));
    if (!resp)
    {
        rt_kprintf("No memory for response structure!\r\n");
        at_delete_resp(resp);
        return -RT_ENOMEM;
    }

    char* cmd = rt_malloc(AT_MAX_CMD_LEN);

    sprintf(cmd, "AT+READATTR:%04x,%02x,0,%04x,%04x", ((ReadAttrsReq_t *)arg) -> nwkAddr, ((ReadAttrsReq_t *)arg) -> endpoint,
                                                      ((ReadAttrsReq_t *)arg) -> clusterID, ((ReadAttrsReq_t *)arg) -> attrID);
    if (at_obj_exec_cmd(device -> client, resp, (const char *)cmd) != RT_EOK)
    {
        rt_kprintf("AT client send commands failed, response error or timeout !\r\n");
        at_delete_resp(resp);
        rt_free(cmd);
        return -RT_ERROR;
    }

    /* Command sent successfully */
    rt_kprintf("AT Client send %s to AT Server success!\r\n", cmd);

    rt_thread_delay(500);
    /* Processing response structure */
    for(int i = 1; i <= resp ->line_counts; i++)
    {
        rt_kprintf("%s\r\n", at_resp_get_line(resp, i));
    }

    /* Delete response structure */
    at_delete_resp(resp);

    rt_free(cmd);

    return RT_EOK;
}

static int mg21_onoff(struct at_device *device, void *arg)
{
    at_response_t resp = RT_NULL;

    if(device == RT_NULL)
    {
        rt_kprintf("wrong device\r\n");
        at_delete_resp(resp);
        return -RT_ERROR;
    }

    resp = at_create_resp(512, 0, rt_tick_from_millisecond(5000));
    if (!resp)
    {
        rt_kprintf("No memory for response structure!\r\n");
        at_delete_resp(resp);
        return -RT_ENOMEM;
    }

    char* cmd = rt_malloc(AT_MAX_CMD_LEN);

    sprintf(cmd, "AT+ONOFF:%04x,%02x,%d", ((zclOnoffCmd_t *)arg) -> nwkAddr, ((zclOnoffCmd_t *)arg) -> endpoint,
                                          ((zclOnoffCmd_t *)arg) -> mode);
    if (at_obj_exec_cmd(device -> client, resp, (const char *)cmd) != RT_EOK)
    {
        rt_kprintf("AT client send commands failed, response error or timeout !\r\n");
        at_delete_resp(resp);
        rt_free(cmd);
        return -RT_ERROR;
    }

    /* Command sent successfully */
    rt_kprintf("AT Client send %s to AT Server success!\r\n", cmd);

    rt_thread_delay(500);
    /* Processing response structure */
    for(int i = 1; i <= resp ->line_counts; i++)
    {
        rt_kprintf("%s\r\n", at_resp_get_line(resp, i));
    }

    /* Delete response structure */
    at_delete_resp(resp);

    rt_free(cmd);

    return RT_EOK;
}

/* =============================  mg21 device operations ============================= */

#define AT_SEND_CMD(client, resp, cmd)                                     \
    do {                                                                   \
        (resp) = at_resp_set_info((resp), 256, 0, 5 * RT_TICK_PER_SECOND); \
        if (at_obj_exec_cmd((client), (resp), (cmd)) < 0)                  \
        {                                                                  \
            result = -RT_ERROR;                                            \
            goto __exit;                                                   \
        }                                                                  \
    } while(0)                                                             \


static void urc_print_func(struct at_client *client, const char *data, rt_size_t size)
{
    rt_kprintf("%s", data);
}

static void urc_func(struct at_client *client, const char *data, rt_size_t size)
{
    struct at_device *device = RT_NULL;
    char *client_name = client->device->parent.name;

    RT_ASSERT(client && data && size);

    device = at_device_get_by_name(AT_DEVICE_NAMETYPE_CLIENT, client_name);
    if (device == RT_NULL)
    {
        LOG_E("get device(%s) failed.", client_name);
        return;
    }

    if (rt_strstr(data, "REPORT"))
    {
        LOG_I("this is a report messege");
        rt_kprintf("%s", data);
    }
    else if (rt_strstr(data, "RECENE"))
    {
        LOG_I("this is a scene report");
		rt_kprintf("%s", data);
    }
}

static const struct at_urc urc_table[] =
{
    {"REPORT",           "\r\n",           urc_func},
    {"RECENE",           "\r\n",           urc_func},
    {"RPTATTR",          "\r\n",           urc_print_func},
    {"FFD",              "\r\n",           urc_print_func},
    {"END",              "\r\n",           urc_print_func},
    {"ActEpDesc",        "\r\n",           urc_print_func},
    {"SimpleDesc",       "\r\n",           urc_print_func},
    {"EP",               "\r\n",           urc_print_func},
    {"ProfileID",        "\r\n",           urc_print_func},
    {"DeviceID",         "\r\n",           urc_print_func},
    {"InCluster",        "\r\n",           urc_print_func},
    {"OutCluster",       "\r\n",           urc_print_func},
    {"----",             "\r\n",           urc_print_func},
    {"ReadAttr",         "\r\n",           urc_print_func},
    {"WriteAttr",        "\r\n",           urc_print_func},
    {"ERROR",            "\r\n",           urc_print_func},
};

static int mg21_init(struct at_device *device)
{
    struct at_device_mg21 *mg21 = (struct at_device_mg21 *) device->user_data;

    /* initialize AT client */
    at_client_init(mg21->client_name, mg21->recv_line_num);

    device->client = at_client_get(mg21->client_name);
    if (device->client == RT_NULL)
    {
        LOG_E("get AT client(%s) failed.", mg21->client_name);
        return -RT_ERROR;
    }

    /* register URC data execution function  */
    at_obj_set_urc_table(device->client, urc_table, sizeof(urc_table) / sizeof(urc_table[0]));

    /* initialize OK */
    return RT_EOK;
}

static int mg21_deinit(struct at_device *device)
{
    if (device->is_init == RT_TRUE)
    {
        device->is_init = RT_FALSE;
        LOG_D("mg21 has deinit");
    }

    return RT_EOK;
}

static int mg21_control(struct at_device *device, int cmd, void *arg)
{
    int result = -RT_ERROR;

    RT_ASSERT(device);

    switch (cmd)
    {
    case AT_DEVICE_CTRL_INFO:
        mg21_info(device);
        break;
    case AT_DEVICE_CTRL_RESET:
        mg21_reset(device);
        break;
    case AT_DEVICE_CTRL_PJ:
        mg21_pj(device, arg);
        break;
    case AT_DEVICE_CTRL_SETRADIOCH:
        mg21_set_radio_ch(device, arg);
        break;
    case AT_DEVICE_CTRL_ACTEPDESC:
        mg21_act_ep_desc(device, arg);
        break;
    case AT_DEVICE_CTRL_SIMPLEDESC:
        mg21_simple_desc(device, arg);
        break;
    case AT_DEVICE_CTRL_WRITEATTR:
        mg21_write_attr(device, arg);
        break;
    case AT_DEVICE_CTRL_READATTR:
        mg21_read_attr(device, arg);
        break;
    case AT_DEVICE_CTRL_ONOFF:
        mg21_onoff(device, arg);
        break;

    case AT_DEVICE_CTRL_GET_GPS:
    case AT_DEVICE_CTRL_GET_VER:
    case AT_DEVICE_CTRL_SET_WIFI_INFO:
        LOG_W("not support the control cmd(%d).", cmd);
        break;
    default:
        LOG_E("input error control cmd(%d).", cmd);
        break;
    }

    return result;
}

static const struct at_device_ops mg21_device_ops =
{
    mg21_init,
    mg21_deinit,
    mg21_control,
};

static int mg21_device_class_register(void)
{
    struct at_device_class *class = RT_NULL;

    class = (struct at_device_class *) rt_calloc(1, sizeof(struct at_device_class));
    if (class == RT_NULL)
    {
        LOG_E("no memory for class create.");
        return -RT_ENOMEM;
    }

    class->device_ops = &mg21_device_ops;

    return at_device_class_register(class, AT_DEVICE_CLASS_MG21);
}

INIT_DEVICE_EXPORT(mg21_device_class_register);

#endif /* AT_DEVICE_USING_MG21 */
