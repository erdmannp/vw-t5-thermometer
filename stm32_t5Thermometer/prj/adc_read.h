#pragma once

#include "main.h"
#include "adc.h"
#include "stdint.h"


#define ADC_BUF_SIZE 4


typedef struct {
    int16_t in_temp;
    int16_t out_temp;
} adc_read_t;



HAL_StatusTypeDef start_adc();
void init_adc();
void read_adc_values(adc_read_t *data);
void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc);
