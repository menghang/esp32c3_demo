#ifndef __APP_LIST_H__
#define __APP_LIST_H__

void app_spiffs_test(void *pvParam);
void app_lvgl_benchmark(void *pvParam);
void app_button_init(void *pvParam);
void app_ina226_test(void *pvParam);
void app_buzzer_init(void *pvParam);
void buzzer_beep(const uint32_t * period);

void ui_power_meter_update(float vol, float cur, float pwr);

#endif