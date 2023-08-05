/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author            Notes
 * 2019-12-13     qiyongzhong       first version
 */

#include <at_device_ec200x.h>

#define LOG_TAG                        "at.ec200x"
#include <at_log.h>

#define EC200X_DEIVCE_NAME        "ec200x"

void ec200x_power_ctrl(int is_on);

static struct at_device_ec200x _dev =
{
    EC200X_DEIVCE_NAME,
    EC200X_CLIENT_NAME,

    EC200X_POWER_PIN,
    EC200X_STATUS_PIN,
    EC200X_WAKEUP_PIN,
    EC200X_RECV_BUFF_LEN,

    ec200x_power_ctrl,
    RT_NULL
};

void ec200x_power_ctrl(int is_on)
{
    if(EC200X_PWREN_PIN==-1 || EC200X_PWRKEY_PIN==-1)
        return;
    rt_pin_write(EC200X_PWREN_PIN, PIN_LOW);
    rt_pin_mode(EC200X_PWREN_PIN, PIN_MODE_OUTPUT);
    rt_pin_write(EC200X_PWRKEY_PIN, PIN_HIGH);
    rt_pin_mode(EC200X_PWRKEY_PIN, PIN_MODE_OUTPUT);
    if(is_on){
        rt_pin_write(EC200X_PWREN_PIN, PIN_LOW);
        rt_thread_mdelay(200);
        rt_pin_write(EC200X_PWREN_PIN, PIN_HIGH);
        rt_thread_mdelay(2000);
    }
}

static int ec200x_device_register(void)
{
    struct at_device_ec200x *ec200x = &_dev;

    return at_device_register(&(ec200x->device),
                              ec200x->device_name,
                              ec200x->client_name,
                              AT_DEVICE_CLASS_EC200X,
                              (void *) ec200x);
}
INIT_APP_EXPORT(ec200x_device_register);

int ec200x_get_rssi(void)
{
    struct at_device_ec200x *ec200x = &_dev;
    return(ec200x->rssi);
}

