#ifndef __APP_LIST_H__
#define __APP_LIST_H__

esp_err_t dev_key_init(void);
esp_err_t dev_buzzer_init(void);
esp_err_t dev_lvgl_init(void);
esp_err_t dev_spiffs_init(void);

void buzzer_beep(const uint32_t *period);
void ui_power_meter_update(float vol, float cur, float pwr);
esp_err_t start_ina226_service(void);
esp_err_t terminate_ina226_service(void);

void app_lvgl(void *vParam);
void app_spiffs_test(void *pvParam);

#endif
