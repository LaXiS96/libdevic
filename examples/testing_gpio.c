#include <stdio.h>
#include <libdevic/port/testing.h>

int main(void)
{
    devic_gpio_set(NULL, 1, true);

    return 0;
}
