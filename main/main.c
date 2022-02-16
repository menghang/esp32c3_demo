/* Hello World Example

   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "esp_log.h"
#include "app_list.h"

static const char *TAG = "MAIN";

void app_main(void)
{
    /* Print chip information */
    esp_chip_info_t chip_info;
    esp_chip_info(&chip_info);
    ESP_LOGI(TAG, "This is %s chip with %d CPU core(s), WiFi%s%s, silicon revision %d, %s flash.",
             CONFIG_IDF_TARGET,
             chip_info.cores,
             (chip_info.features & CHIP_FEATURE_BT) ? "/BT" : "",
             (chip_info.features & CHIP_FEATURE_BLE) ? "/BLE" : "",
             chip_info.revision,
             (chip_info.features & CHIP_FEATURE_EMB_FLASH) ? "embedded" : "external");

    // TaskHandle_t pxTaskSpiffsTest = NULL;
    TaskHandle_t pxTaskLvglBenchmark = NULL;

    // xTaskCreate(app_spiffs_test, "spiffs_test", 1024 * 4, NULL, 1, &pxTaskSpiffsTest);
    xTaskCreate(app_lvgl_benchmark, "lvgl_benchmark", 1024 * 8, NULL, 2, &pxTaskLvglBenchmark);

    while (true)
    {
        // ESP_LOGI(TAG, "spiffs_test Task Stack: %d.",
        //          uxTaskGetStackHighWaterMark(pxTaskSpiffsTest));
        ESP_LOGI(TAG, "lvgl_benchmark Task Stack: %d.",
                 uxTaskGetStackHighWaterMark(pxTaskLvglBenchmark));

        vTaskDelay(pdMS_TO_TICKS(2000));
    }
}
