/*
 * Copyright (c) 2019 Ruslan V. Uss <unclerus@gmail.com>
 * Copyright (c) 2022 Hang Meng <chocolate.menghang@gmail.com>
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 * 3. Neither the name of the copyright holder nor the names of itscontributors
 *    may be used to endorse or promote products derived from this software without
 *    specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/**
 * @file ina226.c
 *
 * ESP-IDF driver for INA226 Zerø-Drift, Bidirectional
 * Current / Power Monitor
 *
 * Copyright (c) 2019 Ruslan V. Uss <unclerus@gmail.com>
 * Copyright (c) 2022 Hang Meng <chocolate.menghang@gmail.com>
 *
 * BSD Licensed as described in the file LICENSE
 */
#include <esp_log.h>
#include <math.h>
#include <esp_idf_lib_helpers.h>
#include "ina226.h"

#define I2C_FREQ_HZ 1000000 // Max 1 MHz for esp-idf, but supports up to 2.94 MHz

static const char *TAG = "ina226";

#define REG_CONFIG 0x00
#define REG_SHUNT_U 0x01
#define REG_BUS_U 0x02
#define REG_POWER 0x03
#define REG_CURRENT 0x04
#define REG_CALIBRATION 0x05
#define REG_MASK 0x06
#define REG_ALERT 0x07
#define REG_MFR_ID 0xFE
#define REG_DIE_ID 0xFF

#define BIT_RST 15
#define BIT_AVG 9
#define BIT_VBUSCT 6
#define BIT_VSHCT 3
#define BIT_MODE 0

#define MASK_AVG (0x0 << BIT_AVG)
#define MASK_VBUSCT (0x4 << BIT_VBUSCT)
#define MASK_VSHCT (0x4 << BIT_VSHCT)
#define MASK_MODE (0x7 << BIT_MODE)

#define DEF_CONFIG 0x4127
#define DEF_MFR_ID 0x5449
#define DEF_DIE_ID 0x2260

#define CHECK(x)                \
    do                          \
    {                           \
        esp_err_t __;           \
        if ((__ = x) != ESP_OK) \
            return __;          \
    } while (0)
#define CHECK_ARG(VAL)                  \
    do                                  \
    {                                   \
        if (!(VAL))                     \
            return ESP_ERR_INVALID_ARG; \
    } while (0)

static esp_err_t read_reg_16(ina226_t *dev, uint8_t reg, uint16_t *val)
{
    CHECK_ARG(val);

    I2C_DEV_TAKE_MUTEX(&dev->i2c_dev);
    I2C_DEV_CHECK(&dev->i2c_dev, i2c_dev_read_reg(&dev->i2c_dev, reg, val, 2));
    I2C_DEV_GIVE_MUTEX(&dev->i2c_dev);

    *val = (*val >> 8) | (*val << 8);

    return ESP_OK;
}

static esp_err_t write_reg_16(ina226_t *dev, uint8_t reg, uint16_t val)
{
    uint16_t v = (val >> 8) | (val << 8);

    I2C_DEV_TAKE_MUTEX(&dev->i2c_dev);
    I2C_DEV_CHECK(&dev->i2c_dev, i2c_dev_write_reg(&dev->i2c_dev, reg, &v, 2));
    I2C_DEV_GIVE_MUTEX(&dev->i2c_dev);

    return ESP_OK;
}

static esp_err_t read_conf_bits(ina226_t *dev, uint16_t mask, uint8_t bit, uint16_t *res)
{
    uint16_t raw;
    CHECK(read_reg_16(dev, REG_CONFIG, &raw));

    *res = (raw & mask) >> bit;

    return ESP_OK;
}

///////////////////////////////////////////////////////////////////////////////

esp_err_t ina226_init_desc(ina226_t *dev, uint8_t addr, i2c_port_t port, gpio_num_t sda_gpio, gpio_num_t scl_gpio)
{
    CHECK_ARG(dev);

    if (addr < INA226_ADDR_GND_GND || addr > INA226_ADDR_SCL_SCL)
    {
        ESP_LOGE(TAG, "Invalid I2C address");
        return ESP_ERR_INVALID_ARG;
    }

    dev->i2c_dev.port = port;
    dev->i2c_dev.addr = addr;
    dev->i2c_dev.cfg.sda_io_num = sda_gpio;
    dev->i2c_dev.cfg.scl_io_num = scl_gpio;
#if HELPER_TARGET_IS_ESP32
    dev->i2c_dev.cfg.master.clk_speed = I2C_FREQ_HZ;
#endif

    return i2c_dev_create_mutex(&dev->i2c_dev);
}

esp_err_t ina226_free_desc(ina226_t *dev)
{
    CHECK_ARG(dev);

    return i2c_dev_delete_mutex(&dev->i2c_dev);
}

esp_err_t ina226_init(ina226_t *dev)
{
    CHECK_ARG(dev);

    CHECK(read_reg_16(dev, REG_CONFIG, &dev->config));
    CHECK(read_reg_16(dev, REG_MFR_ID, &dev->mfr_id));
    CHECK(read_reg_16(dev, REG_DIE_ID, &dev->die_id));

    ESP_LOGD(TAG, "Initialize, config: 0x%04x, mfr_id: 0x%04x, die_id: 0x%04x.",
             dev->config, dev->mfr_id, dev->die_id);

    return ESP_OK;
}

esp_err_t ina226_reset(ina226_t *dev)
{
    CHECK_ARG(dev);
    CHECK(write_reg_16(dev, REG_CONFIG, 1 << BIT_RST));

    dev->config = DEF_CONFIG;

    ESP_LOGD(TAG, "Device reset");

    return ESP_OK;
}

esp_err_t ina226_configure(ina226_t *dev, ina226_config_avg_t avg_mode,
                           ina226_config_vbusct_t vbus_ct, ina226_config_vshct_t vsh_ct,
                           ina226_config_mode_t op_mode)
{
    CHECK_ARG(dev);
    CHECK_ARG(avg_mode <= INA226_CONFIG_AVG_1024);
    CHECK_ARG(vbus_ct <= INA226_CONFIG_VBUSCT_8_244m);
    CHECK_ARG(vsh_ct <= INA226_CONFIG_VSHCT_8_244m);
    CHECK_ARG(op_mode <= INA226_CONFIG_MODE_CONT_SHUNT_BUS);

    dev->config = (avg_mode << BIT_AVG) |
                  (vbus_ct << BIT_VBUSCT) |
                  (vsh_ct << BIT_VSHCT) |
                  (op_mode << BIT_MODE);

    ESP_LOGD(TAG, "Config: 0x%04x", dev->config);

    return write_reg_16(dev, REG_CONFIG, dev->config);
}

esp_err_t ina226_get_avg_mode(ina226_t *dev, ina226_config_avg_t *avg_mode)
{
    CHECK_ARG(dev && avg_mode);
    *avg_mode = 0;
    return read_conf_bits(dev, MASK_AVG, BIT_AVG, (uint16_t *)avg_mode);
}

esp_err_t ina226_get_vbus_conv_time(ina226_t *dev, ina226_config_vbusct_t *vbus_ct)
{
    CHECK_ARG(dev && vbus_ct);
    *vbus_ct = 0;
    return read_conf_bits(dev, MASK_VBUSCT, BIT_VBUSCT, (uint16_t *)vbus_ct);
}

esp_err_t ina226_get_shunt_conv_time(ina226_t *dev, ina226_config_vshct_t *vsh_ct)
{
    CHECK_ARG(dev && vsh_ct);
    *vsh_ct = 0;
    return read_conf_bits(dev, MASK_VSHCT, BIT_VSHCT, (uint16_t *)vsh_ct);
}

esp_err_t ina226_get_mode(ina226_t *dev, ina226_config_mode_t *op_mode)
{
    CHECK_ARG(dev && op_mode);
    *op_mode = 0;
    return read_conf_bits(dev, MASK_MODE, BIT_MODE, (uint16_t *)op_mode);
}

esp_err_t ina226_calibrate(ina226_t *dev, float i_lsb, float r_shunt)
{
    CHECK_ARG(dev);

    dev->i_lsb = i_lsb;
    dev->p_lsb = dev->i_lsb * 25 / 1000;

    uint16_t cal = (uint16_t)((5120) / (dev->i_lsb * r_shunt));
    float i_expected_max = dev->i_lsb * 32768 / 1000;

    ESP_LOGI(TAG, "Max current: %.4f A, shunt resister: %.4f mOhm, cali regisiter: 0x%04x",
             i_expected_max, r_shunt, cal);

    return write_reg_16(dev, REG_CALIBRATION, cal);
}

esp_err_t ina226_trigger(ina226_t *dev)
{
    CHECK_ARG(dev);

    uint16_t mode = (dev->config & MASK_MODE) >> BIT_MODE;
    if (mode < INA226_CONFIG_MODE_TRIG_SHUNT || mode > INA226_CONFIG_MODE_TRIG_SHUNT_BUS)
    {
        ESP_LOGE(TAG, "Could not trigger conversion in this mode: %d", mode);
        return ESP_ERR_INVALID_STATE;
    }

    return write_reg_16(dev, REG_CONFIG, dev->config);
}

esp_err_t ina226_get_bus_voltage(ina226_t *dev, float *voltage)
{
    CHECK_ARG(dev && voltage);

    int16_t raw;
    CHECK(read_reg_16(dev, REG_BUS_U, (uint16_t *)&raw));

    *voltage = raw * 1.25;

    return ESP_OK;
}

esp_err_t ina226_get_shunt_voltage(ina226_t *dev, float *voltage)
{
    CHECK_ARG(dev && voltage);

    int16_t raw;
    CHECK(read_reg_16(dev, REG_SHUNT_U, (uint16_t *)&raw));

    *voltage = raw * 2.5;

    return ESP_OK;
}

esp_err_t ina226_get_current(ina226_t *dev, float *current)
{
    CHECK_ARG(dev && current);

    int16_t raw;
    CHECK(read_reg_16(dev, REG_CURRENT, (uint16_t *)&raw));

    *current = raw * dev->i_lsb;

    return ESP_OK;
}

esp_err_t ina226_get_power(ina226_t *dev, float *power)
{
    CHECK_ARG(dev && power);

    int16_t raw;
    CHECK(read_reg_16(dev, REG_POWER, (uint16_t *)&raw));

    *power = raw * dev->p_lsb;

    return ESP_OK;
}
