#include "file_operations.h"

#define DRIVER_NAME "newDriver"
#define DRIVER_CLASS "new_class"

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Author Name");
MODULE_DESCRIPTION("Hello from the new driver");

struct device_data
{
    dev_t dev_number;
    struct cdev cdev_obj;
    struct file_operations file_ops;
    struct class *dev_class;
} device_data_st = {
    .file_ops = {
        .owner = THIS_MODULE,
        .open = device_open,
        .release = device_close,
        .read = device_read,
        .write = device_write}};

static struct platform_device_id supported_devices[] = {
    [LED_RED] = {.name = "RED_LED"},
    [LED_RED_2] = {.name = "RED_LED_2"},
};

int probe_function(struct platform_device *pdev)
{
    printk("%s detected", pdev->name);

    if (strcmp(pdev->name, "RED_LED") == 0)
    {
        if (gpio_request(2, "RED_LED_PIN"))
        {
            printk("GPIO 2 allocation failed\n");
        }
        else
        {
            printk("GPIO 2 allocated\n");
        }

        if (gpio_direction_output(2, 0))
        {
            printk("Failed to set GPIO 2 as output\n");
            gpio_free(2);
        }
        else
        {
            printk("GPIO 2 set as output\n");
        }
    }
    else if (strcmp(pdev->name, "RED_LED_2") == 0)
    {
        if (gpio_request(3, "RED_LED_2_PIN"))
        {
            printk("GPIO 3 allocation failed\n");
        }

        if (gpio_direction_output(3, 0))
        {
            printk("Failed to set GPIO 3 as output\n");
            gpio_free(3);
        }
    }
    else if (strcmp(pdev->name, "GREEN_LED") == 0)
    {
        if (gpio_request(4, "GREEN_LED_PIN"))
        {
            printk("GPIO 4 allocation failed\n");
        }

        if (gpio_direction_output(4, 0))
        {
            printk("Failed to set GPIO 4 as output\n");
            gpio_free(4);
        }
    }

    if (device_create(device_data_st.dev_class, NULL, device_data_st.dev_number + (pdev->id), NULL, pdev->name) == NULL)
    {
        printk("Device file creation failed\n");
    }
    else
    {
        printk("Device file created\n");
    }

    return 0;
}

int remove_function(struct platform_device *pdev)
{
    if (strcmp(pdev->name, "RED_LED") == 0)
    {
        gpio_set_value(2, 0);
        gpio_free(2);
    }
    else if (strcmp(pdev->name, "RED_LED_2") == 0)
    {
        gpio_set_value(3, 0);
        gpio_free(3);
    }
    else if (strcmp(pdev->name, "GREEN_LED") == 0)
    {
        gpio_set_value(4, 0);
        gpio_free(4);
    }

    device_destroy(device_data_st.dev_class, device_data_st.dev_number + (pdev->id));
    printk("Device removed\n");

    return 0;
}

struct platform_driver platform_drv_data = {
    .probe = probe_function,
    .remove = remove_function,
    .id_table = supported_devices,
    .driver = {
        .name = "new_driver"}};

static int __init driver_init(void)
{
    printk("Platform driver loaded\n");

    if (alloc_chrdev_region(&device_data_st.dev_number, 0, 3, DRIVER_NAME) < 0)
    {
        printk("Device number allocation failed\n");
        return -1;
    }

    cdev_init(&device_data_st.cdev_obj, &device_data_st.file_ops);

    if (cdev_add(&device_data_st.cdev_obj, device_data_st.dev_number, 3) == -1)
    {
        printk("Adding device to kernel failed\n");
    }

    if ((device_data_st.dev_class = class_create(THIS_MODULE, DRIVER_CLASS)) == NULL)
    {
        printk("Class creation failed\n");
        goto class_error;
    }

    platform_driver_register(&platform_drv_data);
    return 0;

class_error:
    unregister_chrdev_region(device_data_st.dev_number, 1);
    return -1;
}

static void __exit driver_exit(void)
{
    platform_driver_unregister(&platform_drv_data);
    class_destroy(device_data_st.dev_class);
    cdev_del(&device_data_st.cdev_obj);
    unregister_chrdev_region(device_data_st.dev_number, 1);
    printk("Goodbye from new driver\n");
}

module_init(driver_init);
module_exit(driver_exit);
