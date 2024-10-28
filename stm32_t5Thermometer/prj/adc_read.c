#include "adc_read.h"
#include "adc.h"
#include "math.h"

const float NTC_UP_R = 10000.0;

/* constants of Steinhart-Hart equation */
const float A = 0.0008736528f;
const float B = 0.000253893f;
const float  C = 0.0000001816f;
const int MASK_12Bit = 0xFFF;

uint32_t AD_RES_BUF[ADC_BUF_SIZE];
adc_read_t _data = {0,0};

int calc_temp(int adc) {
    if (adc == 0) {
        return 0;
    }
    float Ntc_R = ((NTC_UP_R)/((4095.0/adc) - 1));
	float Ntc_Ln = log(Ntc_R);
	return (1.0/(A + B*Ntc_Ln + C*Ntc_Ln*Ntc_Ln*Ntc_Ln)) - 273.15;
}

HAL_StatusTypeDef start_adc() {
    return HAL_ADC_Start_DMA(&hadc, AD_RES_BUF, ADC_BUF_SIZE);
}

void stop_adc() {
    HAL_ADC_Stop_DMA(&hadc);
}

void init_adc() {
    HAL_ADCEx_Calibration_Start(&hadc);
}


void read_adc_values(adc_read_t *data) {
    data->in_temp = calc_temp(_data.in_temp);
    data->out_temp = calc_temp(_data.out_temp);
    stop_adc();
    start_adc();
}


void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc) {
    _data.in_temp =  AD_RES_BUF[0]&MASK_12Bit;
    _data.out_temp =  AD_RES_BUF[1]&MASK_12Bit;
}
