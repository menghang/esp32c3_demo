#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "esp_log.h"
#include "iot_button.h"
#include "app_list.h"
#include "lvgl.h"

extern lv_key_t key_event;

static const char *TAG = "APP_KEY";
static const uint8_t gpio_num_left = 1;
static const uint8_t gpio_num_right = 21;
static const uint8_t gpio_num_enter = 20;
static const uint8_t gpio_num_esc = 0;
static const uint32_t button_beep_period = 50;

static void button_left_press_right_cb(void *arg);
static void button_right_press_right_cb(void *arg);
static void button_enter_press_right_cb(void *arg);
static void button_esc_press_right_cb(void *arg);

esp_err_t dev_key_init(void)
{
    button_config_t btn_left_cfg = {
        .type = BUTTON_TYPE_GPIO,
        .gpio_button_config = {
            .gpio_num = gpio_num_left,
            .active_level = 0,
        },
    };
    button_handle_t btn_left_handler = iot_button_create(&btn_left_cfg);
    if (NULL == btn_left_handler)
    {
        ESP_LOGE(TAG, "Button LEFT create failed");
        return ESP_FAIL;
    }
    iot_button_register_cb(btn_left_handler, BUTTON_PRESS_DOWN, button_left_press_right_cb);

    button_config_t btn_right_cfg = {
        .type = BUTTON_TYPE_GPIO,
        .gpio_button_config = {
            .gpio_num = gpio_num_right,
            .active_level = 0,
        },
    };
    button_handle_t btn_right_handler = iot_button_create(&btn_right_cfg);
    if (NULL == btn_right_handler)
    {
        ESP_LOGE(TAG, "Button RIGHT create failed");
        return ESP_FAIL;
    }
    iot_button_register_cb(btn_right_handler, BUTTON_PRESS_DOWN, button_right_press_right_cb);

    button_config_t btn_enter_cfg = {
        .type = BUTTON_TYPE_GPIO,
        .gpio_button_config = {
            .gpio_num = gpio_num_enter,
            .active_level = 0,
        },
    };
    button_handle_t btn_enter_handler = iot_button_create(&btn_enter_cfg);
    if (NULL == btn_enter_handler)
    {
        ESP_LOGE(TAG, "Button ENTER create failed");
        return ESP_FAIL;
    }
    iot_button_register_cb(btn_enter_handler, BUTTON_PRESS_DOWN, button_enter_press_right_cb);

    button_config_t btn_esc_cfg = {
        .type = BUTTON_TYPE_GPIO,
        .gpio_button_config = {
            .gpio_num = gpio_num_esc,
            .active_level = 0,
        },
    };
    button_handle_t btn_esc_handler = iot_button_create(&btn_esc_cfg);
    if (NULL == btn_esc_handler)
    {
        ESP_LOGE(TAG, "Button ESC create failed");
        return ESP_FAIL;
    }
    iot_button_register_cb(btn_esc_handler, BUTTON_PRESS_DOWN, button_esc_press_right_cb);
    ESP_LOGI(TAG, "Key init is done.");
    return ESP_OK;
}

static void button_left_press_right_cb(void *arg)
{
    ESP_LOGD(TAG, "Key RIGHT press down.");
    buzzer_beep(&button_beep_period);
    key_event = LV_KEY_PREV;
}

static void button_right_press_right_cb(void *arg)
{
    ESP_LOGD(TAG, "Key LEFT press down.");
    buzzer_beep(&button_beep_period);
    key_event = LV_KEY_NEXT;
}

static void button_enter_press_right_cb(void *arg)
{
    ESP_LOGD(TAG, "Key ENTER press down.");
    buzzer_beep(&button_beep_period);
    key_event = LV_KEY_ENTER;
}

static void button_esc_press_right_cb(void *arg)
{
    ESP_LOGD(TAG, "Key ESC press down.");
    buzzer_beep(&button_beep_period);
    key_event = LV_KEY_ESC;
}
