/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-11-06     balanceTWK   first version
 */

#ifndef __USR_LED_H__
#define __USR_LED_H__

#include <rtthread.h>
#include "drv_common.h"
#include "drv_gpio.h"

typedef struct{
  int num;
  char on;
}LED_OPT_T;

typedef enum{
  LEDTB_PIN_NUM=0,
  LEDM1_PIN_NUM,            // pwr
  LEDM2_PIN_NUM,            // netsta
  LEDM3_PIN_NUM,            // mainsta
  LED_PIN_NUM_MAX,
}LED_PIN_NUM_E;

#ifdef __cplusplus
extern "C" {
#endif

extern void usr_led_init();

#ifdef __cplusplus
}
#endif

#endif /* __USR_LED_H__ */
