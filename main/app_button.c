#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "esp_log.h"
#include "iot_button.h"

static const char *TAG = "APP_BUTTON";

static void button_a_single_click_cb(void *arg);
static void button_b_single_click_cb(void *arg);
static void button_c_single_click_cb(void *arg);
static void button_d_single_click_cb(void *arg);

void app_button_test(void *pvParam)
{
    button_config_t btn_a_cfg = {
        .type = BUTTON_TYPE_GPIO,
        .gpio_button_config = {
            .gpio_num = 0,
            .active_level = 0,
        },
    };
    button_handle_t btn_a = iot_button_create(&btn_a_cfg);
    if (NULL == btn_a)
    {
        ESP_LOGE(TAG, "Button A create failed");
    }
    iot_button_register_cb(btn_a, BUTTON_SINGLE_CLICK, button_a_single_click_cb);

    button_config_t btn_b_cfg = {
        .type = BUTTON_TYPE_GPIO,
        .gpio_button_config = {
            .gpio_num = 1,
            .active_level = 0,
        },
    };
    button_handle_t btn_b = iot_button_create(&btn_b_cfg);
    if (NULL == btn_b)
    {
        ESP_LOGE(TAG, "Button B create failed");
    }
    iot_button_register_cb(btn_b, BUTTON_SINGLE_CLICK, button_b_single_click_cb);

    button_config_t btn_c_cfg = {
        .type = BUTTON_TYPE_GPIO,
        .gpio_button_config = {
            .gpio_num = 21,
            .active_level = 0,
        },
    };
    button_handle_t btn_c = iot_button_create(&btn_c_cfg);
    if (NULL == btn_c)
    {
        ESP_LOGE(TAG, "Button C create failed");
    }
    iot_button_register_cb(btn_c, BUTTON_SINGLE_CLICK, button_c_single_click_cb);

    button_config_t btn_d_cfg = {
        .type = BUTTON_TYPE_GPIO,
        .gpio_button_config = {
            .gpio_num = 20,
            .active_level = 0,
        },
    };
    button_handle_t btn_d = iot_button_create(&btn_d_cfg);
    if (NULL == btn_d)
    {
        ESP_LOGE(TAG, "Button D create failed");
    }
    iot_button_register_cb(btn_d, BUTTON_SINGLE_CLICK, button_d_single_click_cb);
    ESP_LOGI(TAG, "Button init is done.");

    //while (true)
    //{
    //    vTaskDelay(pdMS_TO_TICKS(1000));
    //}

    vTaskDelete(NULL);
}

static void button_a_single_click_cb(void *arg)
{
    ESP_LOGI(TAG, "BUTTON_A_SINGLE_CLICK");
}

static void button_b_single_click_cb(void *arg)
{
    ESP_LOGI(TAG, "BUTTON_B_SINGLE_CLICK");
}

static void button_c_single_click_cb(void *arg)
{
    ESP_LOGI(TAG, "BUTTON_C_SINGLE_CLICK");
}

static void button_d_single_click_cb(void *arg)
{
    ESP_LOGI(TAG, "BUTTON_D_SINGLE_CLICK");
}