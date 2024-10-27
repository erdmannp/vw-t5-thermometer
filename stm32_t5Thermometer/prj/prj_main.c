#include "prj_main.h"
#include "stm32f0xx_hal.h"

#include "stdio.h"
#include "ssd1306.h"
#include "i2c.h"
#include "gpio.h"

#include "font_freemono_11x16.h"
#include "font_opensymbol_14x20.h"

const char SNOWFLAKE[] = " ";
const char ESZETT[] = "{";
const char GRAD[] = "}";
#define BUFSIZE 11

typedef struct {
    int16_t in_temp;
    int16_t out_temp;
} adc_read_t;




void prj_main() {
    adc_read_t temps = {-10, -24};
    char buf1[BUFSIZE+1];
    char buf2[BUFSIZE+1];    

    //init_adc();
    ssd1306_Init(&hi2c1);

    while (1) {
        //read_adc_values(&temps);

//Font_11x18

        snprintf(buf1, BUFSIZE+1, "Innen Au%sen", ESZETT);

        ssd1306_Fill(Black);
        
        ssd1306_SetCursor(0, 0);
        ssd1306_WriteString(buf1, Font_FreeMono_11x16, White);

        ssd1306_SetCursor(0, 20);
        snprintf(buf2, BUFSIZE, "%d%sC", temps.in_temp, GRAD);
        ssd1306_WriteString(buf2, Font_FreeMono_11x16, White);

        ssd1306_SetCursor((6*BUFSIZE), 20);
        snprintf(buf2, BUFSIZE+1, "%d%sC", temps.out_temp, GRAD);
        ssd1306_WriteString(buf2, Font_FreeMono_11x16, White);

        if (temps.out_temp < 4) {
            ssd1306_SetCursor(28, 40);
            ssd1306_WriteString(SNOWFLAKE, Font_OpenSymbol_14x20, White);
        }

        if (temps.out_temp < 3) {
            ssd1306_SetCursor(28 * 2, 40);
            ssd1306_WriteString(SNOWFLAKE, Font_OpenSymbol_14x20, White);
        }

        if (temps.out_temp < 2) {
            ssd1306_SetCursor(28 * 3, 40);
            ssd1306_WriteString(SNOWFLAKE, Font_OpenSymbol_14x20, White);
        }

        ssd1306_UpdateScreen(&hi2c1);
        HAL_Delay(500);
    }
}