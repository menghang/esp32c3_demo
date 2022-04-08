#include <stdio.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "esp_log.h"
#include "ina226.h"
#include "app_list.h"

static const char *TAG = "APP_INA226";

#define I2C_INA226_PORT 0
#define I2C_INA226_ADDR INA226_ADDR_GND_GND
#define I2C_INA226_SDA_GPIO 2
#define I2C_INA226_SCL_GPIO 3

#define MEAS_BUF_SIZE 10

static float buf_vol[MEAS_BUF_SIZE];
static float buf_cur[MEAS_BUF_SIZE];
static float buf_pwr[MEAS_BUF_SIZE];

static float calc_avg_val(float *buf, uint8_t length);
static ina226_t dev;

void dev_ina226_init(void)
{
    ESP_ERROR_CHECK(i2cdev_init());

    memset(&dev, 0, sizeof(ina226_t));

    ESP_ERROR_CHECK(ina226_init_desc(&dev, I2C_INA226_ADDR, I2C_INA226_PORT,
                                     I2C_INA226_SDA_GPIO, I2C_INA226_SCL_GPIO));
    ESP_LOGI(TAG, "Initializing INA226");
    ESP_ERROR_CHECK(ina226_init(&dev));

    ESP_LOGI(TAG, "Configuring INA226");
    ESP_ERROR_CHECK(ina226_configure(&dev, INA226_CONFIG_AVG_16,
                                     INA226_CONFIG_VBUSCT_1_1m,
                                     INA226_CONFIG_VSHCT_1_1m,
                                     INA226_CONFIG_MODE_CONT_SHUNT_BUS));

    ESP_LOGI(TAG, "Calibrating INA226");
    ESP_ERROR_CHECK(ina226_calibrate(&dev, 0.125, 9.8579));
}

void app_ina226_meas(void *pvParam)
{
    float vol, cur, pwr;

    ESP_LOGI(TAG, "Starting the loop");
    while (1)
    {
        for (uint8_t ii = 0; ii < MEAS_BUF_SIZE; ii++)
        {
            ESP_ERROR_CHECK(ina226_get_bus_voltage(&dev, buf_vol + ii));
            ESP_ERROR_CHECK(ina226_get_current(&dev, buf_cur + ii));
            ESP_ERROR_CHECK(ina226_get_power(&dev, buf_pwr + ii));

            vol = calc_avg_val(buf_vol, MEAS_BUF_SIZE);
            cur = calc_avg_val(buf_cur, MEAS_BUF_SIZE);
            pwr = calc_avg_val(buf_pwr, MEAS_BUF_SIZE);

            vTaskDelay(pdMS_TO_TICKS(100));
        }
        ESP_LOGI(TAG, "VBUS: %.02fmV, IBUS: %.02fmA, PBUS: %.04fW",
                 vol, cur, pwr);
        ui_power_meter_update(vol / 1000, cur / 1000, pwr);
    }
}

static float calc_avg_val(float *buf, uint8_t length)
{
    float sum = 0;
    for (uint8_t ii = 0; ii < length; ii++)
    {
        sum += *(buf + ii);
    }
    return sum / length;
}
