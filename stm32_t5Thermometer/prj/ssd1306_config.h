/*
rename to ssd_1306_config.h and put in the project, to make ssd1306 lib configurable
*/

#ifndef _SSD1306_CONFIG_H
#define _SSD1306_CONFIG_H

#include "stdint.h"

// define the needed HAL include:
#include "stm32f0xx_hal.h"

// define the default brightness of the display from 0 to 255:

#define SSD1306_DEFAULT_BRIGHTNESS 0x80


#endif