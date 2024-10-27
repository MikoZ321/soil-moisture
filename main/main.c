#include <stdio.h>
#include <stdlib.h>

#include "driver/adc.h"
#include "esp_adc_cal.h"
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#define LOG "LOG"


static esp_adc_cal_characteristics_t adc1_chars;

void app_main(void)
{

    esp_adc_cal_characterize(ADC_UNIT_1, ADC_ATTEN_DB_12, ADC_WIDTH_BIT_DEFAULT, 0, &adc1_chars);

    adc1_config_width(ADC_WIDTH_BIT_DEFAULT);
    adc1_config_channel_atten(ADC1_CHANNEL_0, ADC_ATTEN_DB_12);
    adc1_config_channel_atten(ADC1_CHANNEL_3, ADC_ATTEN_DB_12);

    while (1) 
    {
        int adc_value1 = adc1_get_raw(ADC1_CHANNEL_0);
        int adc_value2 = adc1_get_raw(ADC1_CHANNEL_3);
        float soil_moisture_percentage1 = adc_value1 / 4095.0 * 100.0;
        float soil_moisture_percentage2 = adc_value2 / 4095.0 * 100.0;
        printf("Soil moisture level: %.2f%%, %.2f%%\n", soil_moisture_percentage1, soil_moisture_percentage2);
        vTaskDelay(500/ portTICK_PERIOD_MS);
    }
}