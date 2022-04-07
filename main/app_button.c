#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "esp_log.h"
#include "iot_button.h"
#include "app_list.h"

static const char *TAG = "APP_BUTTON";
static const uint8_t gpio_num_up = 1;
static const uint8_t gpio_num_down = 21;
static const uint8_t gpio_num_ok = 20;
static const uint8_t gpio_num_back = 0;
static const uint32_t button_beep_period = 50;

static void button_up_press_down_cb(void *arg);
static void button_down_press_down_cb(void *arg);
static void button_ok_press_down_cb(void *arg);
static void button_back_press_down_cb(void *arg);

void app_button_init(void *pvParam)
{
    button_config_t btn_up_cfg = {
        .type = BUTTON_TYPE_GPIO,
        .gpio_button_config = {
            .gpio_num = gpio_num_up,
            .active_level = 0,
        },
    };
    button_handle_t btn_up_handler = iot_button_create(&btn_up_cfg);
    if (NULL == btn_up_handler)
    {
        ESP_LOGE(TAG, "Button up create failed");
    }
    iot_button_register_cb(btn_up_handler, BUTTON_PRESS_DOWN, button_up_press_down_cb);

    button_config_t btn_down_cfg = {
        .type = BUTTON_TYPE_GPIO,
        .gpio_button_config = {
            .gpio_num = gpio_num_down,
            .active_level = 0,
        },
    };
    button_handle_t btn_down_handler = iot_button_create(&btn_down_cfg);
    if (NULL == btn_down_handler)
    {
        ESP_LOGE(TAG, "Button down create failed");
    }
    iot_button_register_cb(btn_down_handler, BUTTON_PRESS_DOWN, button_down_press_down_cb);

    button_config_t btn_ok_cfg = {
        .type = BUTTON_TYPE_GPIO,
        .gpio_button_config = {
            .gpio_num = gpio_num_ok,
            .active_level = 0,
        },
    };
    button_handle_t btn_ok_handler = iot_button_create(&btn_ok_cfg);
    if (NULL == btn_ok_handler)
    {
        ESP_LOGE(TAG, "Button ok create failed");
    }
    iot_button_register_cb(btn_ok_handler, BUTTON_PRESS_DOWN, button_ok_press_down_cb);

    button_config_t btn_back_cfg = {
        .type = BUTTON_TYPE_GPIO,
        .gpio_button_config = {
            .gpio_num = gpio_num_back,
            .active_level = 0,
        },
    };
    button_handle_t btn_back_handler = iot_button_create(&btn_back_cfg);
    if (NULL == btn_back_handler)
    {
        ESP_LOGE(TAG, "Button back create failed");
    }
    iot_button_register_cb(btn_back_handler, BUTTON_PRESS_DOWN, button_back_press_down_cb);
    ESP_LOGI(TAG, "Button init is done.");

    vTaskDelete(NULL);
}

static void button_up_press_down_cb(void *arg)
{
    ESP_LOGI(TAG, "Button up press down.");
    buzzer_beep(&button_beep_period);
}

static void button_down_press_down_cb(void *arg)
{
    ESP_LOGI(TAG, "Button down press down.");
    buzzer_beep(&button_beep_period);
}

static void button_ok_press_down_cb(void *arg)
{
    ESP_LOGI(TAG, "Button ok press down.");
    buzzer_beep(&button_beep_period);
}

static void button_back_press_down_cb(void *arg)
{
    ESP_LOGI(TAG, "Button back press down.");
    buzzer_beep(&button_beep_period);
}
