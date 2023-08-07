
#define DBG_TAG "usr_led"
#define DBG_LVL DBG_LOG
#include <rtdbg.h>

#include <rtthread.h>
#include <rtdevice.h>
#include <board.h>

#include "usr_led.h"

LED_OPT_T led_opt[LED_PIN_NUM_MAX]={
    {GET_PIN(A, 1),1},
    {GET_PIN(C, 0),1},
    {GET_PIN(C, 1),1},
    {GET_PIN(C, 2),1},
};

int led_init();             //LED 灯初始化
int led_on(int);            //LED 灯亮
int led_off(int);           //LED 灯灭
int led_toggle(int);        //LED 灯亮灭状态翻转

int led_off(int pin)
{
    /* 调用 API 输出电平 */
    rt_pin_write(led_opt[pin].num, !led_opt[pin].on);
    return 0;
}

int led_on(int pin)
{
    /* 调用 API 输出电平 */
    rt_pin_write(led_opt[pin].num, led_opt[pin].on);
    return 0;
}

int led_toggle(int pin)
{
    /* 调用 API 读出当前电平 然后输出相反电平 */
    rt_pin_write(led_opt[pin].num, !rt_pin_read(led_opt[pin].num));
    return 0;
}

int led_init(void)
{
    /* 设定 LED 引脚为推挽输出模式 */
    led_on(LEDTB_PIN_NUM);
    rt_pin_mode(led_opt[LEDTB_PIN_NUM].num, PIN_MODE_OUTPUT);

    led_on(LEDM1_PIN_NUM);
    rt_pin_mode(led_opt[LEDM1_PIN_NUM].num, PIN_MODE_OUTPUT);
    led_off(LEDM2_PIN_NUM);
    rt_pin_mode(led_opt[LEDM2_PIN_NUM].num, PIN_MODE_OUTPUT);
    led_off(LEDM3_PIN_NUM);
    rt_pin_mode(led_opt[LEDM3_PIN_NUM].num, PIN_MODE_OUTPUT);

    return 0;
}

void usr_led_init(void)
{
    led_init();
}
