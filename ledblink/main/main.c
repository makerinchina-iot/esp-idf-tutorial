#include <stdio.h>

#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

void app_main(void)
{
    gpio_reset_pin(12);
    gpio_set_direction(12,GPIO_MODE_OUTPUT);

    while (1)
    {
        printf("led on\r\n");
        gpio_set_level(12,1);

        //delay
        vTaskDelay(1000/portTICK_PERIOD_MS);

        printf("led off\r\n");
        gpio_set_level(12,0);

        vTaskDelay(1000/portTICK_PERIOD_MS);
    }
    
}
