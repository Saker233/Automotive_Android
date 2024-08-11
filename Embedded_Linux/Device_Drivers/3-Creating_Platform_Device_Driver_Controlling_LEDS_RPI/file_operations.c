#include <linux/init.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/uaccess.h>
#include <linux/device.h>
#include <linux/platform_device.h>
#include <linux/mod_devicetable.h>
#include <linux/gpio.h>
#include <linux/string.h>

enum device_names
{
    LED_RED,
    LED_GREEN
};

static char red_val[3] = {0};
static char green_val[3] = {0};

int minor_num;

enum device_status
{
    RED_DEVICE = 0,
    GREEN_DEVICE
} current_status;

int device_open(struct inode *inode, struct file *file)
{
    dev_t dev_id = inode->i_rdev;
    int major_num = MAJOR(dev_id);
    int minor = MINOR(dev_id);

    minor_num = minor;
    file->private_data = &minor_num;

    printk("Device opened with major %d, minor %d\n", major_num, minor);
    return 0;
}

int device_close(struct inode *inode, struct file *file)
{
    printk("Device closed\n");
    return 0;
}

ssize_t device_write(struct file *file, const char *buf, size_t len, loff_t *off)
{
    char(*device_val)[3] = NULL;
    int uncopied_bytes;

    if (*(int *)file->private_data == 0)
    {
        device_val = &red_val;
        current_status = RED_DEVICE;
    }
    else if (*(int *)file->private_data == 1)
    {
        device_val = &green_val;
        current_status = GREEN_DEVICE;
    }

    uncopied_bytes = copy_from_user(device_val, buf, sizeof(red_val));

    switch ((*device_val)[0])
    {
    case '0':
        gpio_set_value(current_status, 0);
        printk("GPIO cleared\n");
        break;
    case '1':
        gpio_set_value(current_status, 1);
        printk("GPIO set\n");
        break;
    default:
        printk("Invalid GPIO input\n");
        break;
    }

    return len - uncopied_bytes;
}

ssize_t device_read(struct file *file, char *buf, size_t len, loff_t *off)
{
    printk("Read operation is not supported on this device\n");
    return -ENOSYS;
}
