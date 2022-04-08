#ifndef __APP_LIST_H__
#define __APP_LIST_H__

void dev_button_init(void);
void dev_buzzer_init(void);
void dev_ina226_init(void);
void dev_lvgl_init(void);
void dev_spiffs_init(void);

void buzzer_beep(const uint32_t *period);
void ui_power_meter_update(float vol, float cur, float pwr);

void app_ina226_meas(void *pvParam);
void app_lvgl(void *vParam);
void app_spiffs_test(void *pvParam);

#endif
