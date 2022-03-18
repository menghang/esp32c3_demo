#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "esp_log.h"
#include "driver/ledc.h"

static const char *TAG = "APP_BUZER";

#define BUZZER_TIMER LEDC_TIMER_0
#define BUZZER_MODE LEDC_LOW_SPEED_MODE
#define BUZZER_OUTPUT_IO (10)
#define BUZZER_CHANNEL LEDC_CHANNEL_0
#define BUZZER_DUTY_RES LEDC_TIMER_8_BIT
#define BUZZER_DUTY (127)
#define BUZZER_FREQUENCY (5000)

static void app_buzzer_beep(void *pvParam);

void app_buzzer_init(void *pvParam)
{
    ledc_timer_config_t buzzer_timer = {
        .speed_mode = BUZZER_MODE,
        .timer_num = BUZZER_TIMER,
        .duty_resolution = BUZZER_DUTY_RES,
        .freq_hz = BUZZER_FREQUENCY,
        .clk_cfg = LEDC_AUTO_CLK};
    ESP_ERROR_CHECK(ledc_timer_config(&buzzer_timer));

    ledc_channel_config_t buzzer_channel = {
        .speed_mode = BUZZER_MODE,
        .channel = BUZZER_CHANNEL,
        .timer_sel = BUZZER_TIMER,
        .intr_type = LEDC_INTR_DISABLE,
        .gpio_num = BUZZER_OUTPUT_IO,
        .duty = BUZZER_DUTY,
        .hpoint = 0};
    ESP_ERROR_CHECK(ledc_channel_config(&buzzer_channel));
    ESP_ERROR_CHECK(ledc_timer_pause(BUZZER_MODE, BUZZER_TIMER));

    ESP_LOGI(TAG, "Buzzer init is done.");

    vTaskDelete(NULL);
}

void buzzer_beep(const uint32_t *period)
{
    xTaskCreate(app_buzzer_beep, "app_buzzer_beep", 1024 * 4, (void * const)period, 1, NULL);
}

static void app_buzzer_beep(void *pvParam)
{
    uint32_t period = *((uint32_t *)pvParam);
    ESP_ERROR_CHECK(ledc_timer_resume(BUZZER_MODE, BUZZER_TIMER));
    vTaskDelay(pdMS_TO_TICKS(period));
    ESP_ERROR_CHECK(ledc_timer_pause(BUZZER_MODE, BUZZER_TIMER));
    vTaskDelete(NULL);
}
