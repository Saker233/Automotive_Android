#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>



int main()
{

    int fd = 0;


    fd = open("/sys/class/leds/input2::capslock/brightness", O_RDWR);

    printf("File Descriptor: %d\n",fd);
  
}