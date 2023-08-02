#include <rtthread.h>
#include <rtdevice.h>
#include <board.h>
#include <stdio.h>

#define DBG_TAG "user_env"
#define DBG_LVL DBG_LOG
#include <rtdbg.h>

#include <rtdevice.h>
#include <board.h>
#include <easyflash.h>

static void test_env(void)
{
    uint32_t i_boot_times = 0;
    char *c_old_boot_times, c_new_boot_times[11] = {0};

    /* 从环境变量中获取启动次数 */
    c_old_boot_times = ef_get_env("boot_times");
    /* 获取启动次数是否失败 */
    if (c_old_boot_times == RT_NULL)
    {
        // c_old_boot_times[0] = '0';
        rt_kprintf(c_new_boot_times, "%d", i_boot_times);
    }

    i_boot_times = atol(c_old_boot_times);
    /* 启动次数加 1 */
    i_boot_times++;
    LOG_D("===============================================");
    LOG_D("The system now boot %d times", i_boot_times);
    LOG_D("===============================================");
    /* 数字转字符串 */
    sprintf(c_new_boot_times, "%d", i_boot_times);
    /* 保存开机次数的值 */
    ef_set_env("boot_times", c_new_boot_times);
    ef_save_env();
}

int user_easy_flash(void)
{
   if (easyflash_init() == EF_NO_ERR)
   {
       /* 演示环境变量功能 */
       test_env();
   }
    return 0;
}

// INIT_APP_EXPORT(user_easy_flash);
