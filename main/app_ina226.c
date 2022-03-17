#include <stdio.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "esp_log.h"
#include "ina226.h"

static const char *TAG = "APP_INA226";

#define I2C_INA226_PORT 0
#define I2C_INA226_ADDR INA226_ADDR_GND_GND
#define I2C_INA226_SDA_GPIO 2
#define I2C_INA226_SCL_GPIO 3

void app_ina226_test(void *pvParam)
{
    ESP_ERROR_CHECK(i2cdev_init());

    ina226_t dev;
    memset(&dev, 0, sizeof(ina226_t));

    ESP_ERROR_CHECK(ina226_init_desc(&dev, I2C_INA226_ADDR, I2C_INA226_PORT,
                                     I2C_INA226_SDA_GPIO, I2C_INA226_SCL_GPIO));
    ESP_LOGI(TAG, "Initializing INA226");
    ESP_ERROR_CHECK(ina226_init(&dev));

    ESP_LOGI(TAG, "Configuring INA226");
    ESP_ERROR_CHECK(ina226_configure(&dev, INA226_CONFIG_AVG_1,
                                     INA226_CONFIG_VBUSCT_1_1m,
                                     INA226_CONFIG_VSHCT_1_1m,
                                     INA226_CONFIG_MODE_CONT_SHUNT_BUS));

    ESP_LOGI(TAG, "Calibrating INA226");
    ESP_ERROR_CHECK(ina226_calibrate(&dev, 0.125, 10));

    float bus_voltage, current, power;

    ESP_LOGI(TAG, "Starting the loop");
    while (1)
    {
        ESP_ERROR_CHECK(ina226_get_bus_voltage(&dev, &bus_voltage));
        ESP_ERROR_CHECK(ina226_get_current(&dev, &current));
        ESP_ERROR_CHECK(ina226_get_power(&dev, &power));

        ESP_LOGI(TAG, "VBUS: %.02fmV, IBUS: %.02fmA, PBUS: %.04fW",
                 bus_voltage, current, power);

        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}
