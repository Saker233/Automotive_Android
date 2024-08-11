#include "file_operations.h"

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Saker");
MODULE_DESCRIPTION("Hello from the driver");

struct platform_device new_device = {
    .name = "LED_GREEN",
    .id = 1,
};

static int __init device_init(void)
{
    printk("LED_GREEN has been successfully registered\n");
    platform_device_register(&new_device);
    return 0;
}

static void __exit device_exit(void)
{
    printk("LED_GREEN has been successfully unregistered\n");
    platform_device_unregister(&new_device);
}

module_init(device_init);
module_exit(device_exit);
