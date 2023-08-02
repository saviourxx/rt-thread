/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-11-5      SummerGift   first version
 */

#include <rtthread.h>
#include <rtdevice.h>
#include <board.h>

#define DBG_TAG "main"
#define DBG_LVL DBG_LOG
#include <rtdbg.h>

#include "fal.h"
#include "easyflash.h"
#include "usr_ef.h"

#define APP_VERSION "2.0.0"

/* defined the LED0 pin: PF7 */
#define LED0_PIN    GET_PIN(C, 13)

int main(void)
{
    fal_init();
    // easyflash_init();
    user_easy_flash();

    LOG_D("The current version of App fireware: %s",APP_VERSION);

    uint8_t data[3] ={1,2,3};
    LOG_E("error");
    LOG_W("waring");
    LOG_I("info");
    LOG_D("debug");
    LOG_RAW("unformatted\n");
    ulog_hexdump("main", 8, data, sizeof(data)); //m
    /* set LED0 pin mode to output */
    rt_pin_mode(LED0_PIN, PIN_MODE_OUTPUT);

    while (1)
    {
        rt_pin_write(LED0_PIN, PIN_HIGH);
        rt_thread_mdelay(500);
        rt_pin_write(LED0_PIN, PIN_LOW);
        rt_thread_mdelay(500);
    }
}
