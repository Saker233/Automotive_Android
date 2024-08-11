obj-m += gpio_driver.o led_device.o led_device2.o
gpio_driver-y := platform_driver.o file_operations.o
led_device-y := platform_device.o
led_device2-y := platform_device2.o

all:
	make -C /usr/src/linux-headers-6.1.21-v7+ M=$(shell pwd) modules

clean:
	make -C /usr/src/linux-headers-6.1.21-v7+ M=$(shell pwd) clean
