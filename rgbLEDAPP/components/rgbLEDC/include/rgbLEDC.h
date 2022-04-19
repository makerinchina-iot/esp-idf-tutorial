#pragma once

#include "driver/ledc.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

void rgbLED_init();
void rgbLED_on(uint8_t r, uint8_t g, uint8_t b);
void rgbLED_off();
void rgbLED_fade(uint8_t r, uint8_t g, uint8_t b, bool up, int time);
