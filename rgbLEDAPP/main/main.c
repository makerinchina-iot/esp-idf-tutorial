#include <stdio.h>

#include "rgbledc.h"

void app_main(void)
{
    //init
    rgbLED_init();

    while(1){
        //blink red
        for(int i=0; i<3; i++){
            rgbLED_on(255,0,0);//red color: (255,0,0)
            vTaskDelay(400/portTICK_PERIOD_MS);
            rgbLED_off();
            vTaskDelay(400/portTICK_PERIOD_MS);
        }

        //fade up then down, color:green (0,255,0)
        rgbLED_fade(0,255,0,true,4000);
        rgbLED_fade(0,255,0,false,4000);

        //yellow color set
        rgbLED_on(100,100,0);
        vTaskDelay(1000/portTICK_PERIOD_MS);
    }
}
