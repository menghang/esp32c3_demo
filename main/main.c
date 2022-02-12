/* Hello World Example

   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/
#include <stdio.h>
#include <string.h>
#include <sys/unistd.h>
#include <sys/stat.h>
#include "sdkconfig.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "esp_spi_flash.h"
#include "esp_err.h"
#include "esp_log.h"
#include "esp_spiffs.h"

static const char *TAG = "MAIN";
static const char *TAG_SPIFFS ="SPIFFS";

void app_spiffs_test(void *vParam)
{
    ESP_LOGI(TAG_SPIFFS, "Initializing SPIFFS");

    esp_vfs_spiffs_conf_t conf = {
        .base_path = "/spiffs",
        .partition_label = NULL,
        .max_files = 10,
        .format_if_mount_failed = true};

    // Use settings defined above to initialize and mount SPIFFS filesystem.
    // Note: esp_vfs_spiffs_register is an all-in-one convenience function.
    esp_err_t ret = esp_vfs_spiffs_register(&conf);

    if (ret != ESP_OK)
    {
        if (ret == ESP_FAIL)
        {
            ESP_LOGE(TAG_SPIFFS, "Failed to mount or format filesystem");
        }
        else if (ret == ESP_ERR_NOT_FOUND)
        {
            ESP_LOGE(TAG_SPIFFS, "Failed to find SPIFFS partition");
        }
        else
        {
            ESP_LOGE(TAG_SPIFFS, "Failed to initialize SPIFFS (%s)", esp_err_to_name(ret));
        }
        return;
    }

    size_t total = 0, used = 0;
    ret = esp_spiffs_info(conf.partition_label, &total, &used);
    if (ret != ESP_OK)
    {
        ESP_LOGE(TAG_SPIFFS, "Failed to get SPIFFS partition information (%s)", esp_err_to_name(ret));
    }
    else
    {
        ESP_LOGI(TAG_SPIFFS, "Partition size: total: %d, used: %d", total, used);
    }

    // Use POSIX and C standard library functions to work with files.
    // First create a file.
    ESP_LOGI(TAG, "Opening file");
    FILE *f = fopen("/spiffs/hello.txt", "w");
    if (f == NULL)
    {
        ESP_LOGE(TAG_SPIFFS, "Failed to open file for writing");
        return;
    }
    fprintf(f, "Hello World!\n");
    fclose(f);
    ESP_LOGI(TAG_SPIFFS, "File written");

    // Check if destination file exists before renaming
    struct stat st;
    if (stat("/spiffs/foo.txt", &st) == 0)
    {
        // Delete it if it exists
        unlink("/spiffs/foo.txt");
    }

    // Rename original file
    ESP_LOGI(TAG_SPIFFS, "Renaming file");
    if (rename("/spiffs/hello.txt", "/spiffs/foo.txt") != 0)
    {
        ESP_LOGE(TAG_SPIFFS, "Rename failed");
        return;
    }

    // Open renamed file for reading
    ESP_LOGI(TAG_SPIFFS, "Reading file");
    f = fopen("/spiffs/foo.txt", "r");
    if (f == NULL)
    {
        ESP_LOGE(TAG_SPIFFS, "Failed to open file for reading");
        return;
    }
    char line[64];
    fgets(line, sizeof(line), f);
    fclose(f);
    // strip newline
    char *pos = strchr(line, '\n');
    if (pos)
    {
        *pos = '\0';
    }
    ESP_LOGI(TAG_SPIFFS, "Read from file: '%s'", line);

    // Format partition
    ret = esp_spiffs_format(conf.partition_label);

    if (ESP_OK != ret)
    {
        ESP_LOGE(TAG_SPIFFS, "Fail to format partition.");
        return;
    }
    else
    {
        ESP_LOGI(TAG_SPIFFS, "Formatting partition is done.");
    }

    // All done, unmount partition and disable SPIFFS
    esp_vfs_spiffs_unregister(conf.partition_label);
    ESP_LOGI(TAG_SPIFFS, "SPIFFS unmounted");

    while (true)
    {
        vTaskDelay(5000 / portTICK_PERIOD_MS);
    }
}

void app_main(void)
{
    /* Print chip information */
    esp_chip_info_t chip_info;
    esp_chip_info(&chip_info);
    ESP_LOGI(TAG, "This is %s chip with %d CPU core(s), WiFi%s%s, silicon revision %d, %dMB %s flash.",
             CONFIG_IDF_TARGET,
             chip_info.cores,
             (chip_info.features & CHIP_FEATURE_BT) ? "/BT" : "",
             (chip_info.features & CHIP_FEATURE_BLE) ? "/BLE" : "",
             chip_info.revision,
             spi_flash_get_chip_size() / (1024 * 1024),
             (chip_info.features & CHIP_FEATURE_EMB_FLASH) ? "embedded" : "external");

    TaskHandle_t pxTaskSpiffsTest = NULL;

    xTaskCreate(app_spiffs_test, "spiffs_test", 4096, NULL, 1, &pxTaskSpiffsTest);

    while (true)
    {
        ESP_LOGI(TAG, "spiffs_test Task Stack High Water Mark: %d.",
                 uxTaskGetStackHighWaterMark(pxTaskSpiffsTest));
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}
