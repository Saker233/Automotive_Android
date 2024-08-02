#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>



int main()
{
    char* value0 = "0";
    char* value1 = "1";

    char read = 0;

    int fd = 0;

    FILE *file = fopen("/sys/class/leds/input2::capslock/brightness", "r");

    fscanf(file, " %c", &read);

    printf("%c\n", read);

    fd = open("/sys/class/leds/input2::capslock/brightness", O_RDWR);

    if(read == *value0)
    {
        write(fd, value1, 1);
    }
    else
    {
        write(fd, value0, 1);
    }

}