

#define DBG_TAG "usr_init"
#define DBG_LVL DBG_LOG
#include <rtdbg.h>

#include <rtthread.h>
#include <rtdevice.h>
#include <board.h>
#include <stdio.h>
#include <fal.h>
#include <dfs_fs.h>
#include <easyflash.h>

#include "usr_led.h"

static void test_env(void)
{
    uint32_t i_boot_times = 0;
    char *c_old_boot_times, c_new_boot_times[11] = {0};

    c_old_boot_times = ef_get_env("boot_times");
    if (c_old_boot_times == RT_NULL)
    {
        rt_kprintf(c_new_boot_times, "%d", i_boot_times);
    }

    i_boot_times = atol(c_old_boot_times);
    i_boot_times++;
    LOG_D("===============================================");
    LOG_D("The system now boot %d times", i_boot_times);
    LOG_D("===============================================");
    sprintf(c_new_boot_times, "%d", i_boot_times);
    ef_set_env("boot_times", c_new_boot_times);
    ef_save_env();
}

void test_ulog(void)
{
    uint8_t data[3] ={1,2,3};

    LOG_E("error");
    LOG_W("waring");
    LOG_I("info");
    LOG_D("debug");
    LOG_RAW("unformatted\n");
    ulog_hexdump("main", 8, data, sizeof(data)); //m
}

void usr_mnt_init(void)
{
    struct rt_device *rootfs = RT_NULL;

    /* 使用 filesystem 分区创建块设备，块设备名称为 filesystem */
    rootfs = fal_blk_device_create("filesystem");
    if(rootfs == RT_NULL)
        return;

	/* 将 elm fat 文件系统挂载 W25Q128 的 filesystem 分区 */
    if (dfs_mount("filesystem", "/", "elm", 0, 0) == 0)
    {
        rt_kprintf("file system initialization done!\n");
    }
    else
    {
        if(dfs_mkfs("elm", "filesystem") == 0)
        {
            if (dfs_mount("filesystem", "/", "elm", 0, 0) == 0)
            {
                rt_kprintf("file system initialization done!\n");
            }
            else
            {
                rt_kprintf("file system initialization failed!\n");
            }
        }
    }

}

void usr_init(void)
{
    usr_led_init();
    fal_init();
    usr_mnt_init();
    easyflash_init();
    test_env();
    test_ulog();
}

// INIT_APP_EXPORT(user_easy_flash);
