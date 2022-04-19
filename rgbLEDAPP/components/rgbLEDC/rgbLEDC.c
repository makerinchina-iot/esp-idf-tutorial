#include <stdio.h>
#include "rgbLEDC.h"
#include "sdkconfig.h"

#define LED_RED_CH      LEDC_CHANNEL_0
#define LED_GREEN_CH    LEDC_CHANNEL_1
#define LED_BLUE_CH     LEDC_CHANNEL_2

#define LED_RED_PIN     CONFIG_LED_RED_PIN
#define LED_GREEN_PIN   CONFIG_LED_GREEN_PIN
#define LED_BLUE_PIN    CONFIG_LED_BLUE_PIN

void rgbLED_init()
{
    ledc_timer_config_t ledc_timer = {
        .speed_mode = LEDC_LOW_SPEED_MODE,
        .timer_num = LEDC_TIMER_0,
        .duty_resolution = LEDC_TIMER_13_BIT,
        .freq_hz = 5000,
        .clk_cfg = LEDC_AUTO_CLK
    };
    ESP_ERROR_CHECK(ledc_timer_config(&ledc_timer));

    ledc_channel_config_t led_red_chan = {
        .speed_mode = LEDC_LOW_SPEED_MODE,
        .channel = LED_RED_CH,
        .timer_sel = LEDC_TIMER_0,
        .intr_type = LEDC_INTR_DISABLE,
        .gpio_num = LED_RED_PIN,
        .duty = 0,
        .hpoint = 0
    };
    ESP_ERROR_CHECK(ledc_channel_config(&led_red_chan));

    ledc_channel_config_t led_green_chan = {
        .speed_mode = LEDC_LOW_SPEED_MODE,
        .channel = LED_GREEN_CH,
        .timer_sel = LEDC_TIMER_0,
        .intr_type = LEDC_INTR_DISABLE,
        .gpio_num = LED_GREEN_PIN,
        .duty = 0,
        .hpoint = 0
    };
    ESP_ERROR_CHECK(ledc_channel_config(&led_green_chan));

    ledc_channel_config_t led_blue_chan = {
        .speed_mode = LEDC_LOW_SPEED_MODE,
        .channel = LED_BLUE_CH,
        .timer_sel = LEDC_TIMER_0,
        .intr_type = LEDC_INTR_DISABLE,
        .gpio_num = LED_BLUE_PIN,
        .duty = 0,
        .hpoint = 0
    };
    ESP_ERROR_CHECK(ledc_channel_config(&led_blue_chan));

    ledc_fade_func_install(0);
}

void rgbLED_on(uint8_t r, uint8_t g, uint8_t b)
{
    uint32_t r_duty = r<<5; //255 -> 2^13
    uint32_t g_duty = g<<5;
    uint32_t b_duty = b<<5;

    ledc_set_duty_and_update(LEDC_LOW_SPEED_MODE,LED_RED_CH,r_duty,0);
    ledc_set_duty_and_update(LEDC_LOW_SPEED_MODE,LED_GREEN_CH,g_duty,0);
    ledc_set_duty_and_update(LEDC_LOW_SPEED_MODE,LED_BLUE_CH,b_duty,0);
}

void rgbLED_off()
{
    ledc_stop(LEDC_LOW_SPEED_MODE,LED_RED_CH,0);
    ledc_stop(LEDC_LOW_SPEED_MODE,LED_GREEN_CH,0);
    ledc_stop(LEDC_LOW_SPEED_MODE,LED_BLUE_CH,0);
}

void rgbLED_fade(uint8_t r, uint8_t g, uint8_t b, bool up, int time)
{
    uint32_t r_duty = r<<5; //255 -> 2^13
    uint32_t g_duty = g<<5;
    uint32_t b_duty = b<<5;

    //fade: 0->100%
    if(up){
        //init state, min
        ledc_set_duty_and_update(LEDC_LOW_SPEED_MODE,LED_RED_CH,0,0);
        ledc_set_duty_and_update(LEDC_LOW_SPEED_MODE,LED_GREEN_CH,0,0);
        ledc_set_duty_and_update(LEDC_LOW_SPEED_MODE,LED_BLUE_CH,0,0);
    }else{ //fade: 100% -> 0
        //init state, max
        ledc_set_duty_and_update(LEDC_LOW_SPEED_MODE,LED_RED_CH,r_duty,0);
        ledc_set_duty_and_update(LEDC_LOW_SPEED_MODE,LED_GREEN_CH,g_duty,0);
        ledc_set_duty_and_update(LEDC_LOW_SPEED_MODE,LED_BLUE_CH,b_duty,0);

        //target dudy, 0
        r_duty = 0;
        g_duty = 0;
        b_duty = 0;
    }

    ledc_set_fade_time_and_start(LEDC_LOW_SPEED_MODE,LED_RED_CH,r_duty,time,LEDC_FADE_WAIT_DONE);
    ledc_set_fade_time_and_start(LEDC_LOW_SPEED_MODE,LED_GREEN_CH,g_duty,time,LEDC_FADE_WAIT_DONE);
    ledc_set_fade_time_and_start(LEDC_LOW_SPEED_MODE,LED_BLUE_CH,b_duty,time,LEDC_FADE_WAIT_DONE);
}
