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
 * @file ina226.h
 * @defgroup ina226 ina226
 * @{
 *
 * ESP-IDF driver for INA226 Zerø-Drift, Bidirectional
 * Current / Power Monitor
 *
 * Copyright (c) 2019 Ruslan V. Uss <unclerus@gmail.com>
 * Copyright (c) 2022 Hang Meng <chocolate.menghang@gmail.com>
 *
 * BSD Licensed as described in the file LICENSE
 */
#ifndef __INA226_H__
#define __INA226_H__

#include <i2cdev.h>
#include <esp_err.h>

#ifdef __cplusplus
extern "C"
{
#endif

#define INA226_ADDR_GND_GND 0x40 //!< I2C address, A1 pin - GND, A0 pin - GND
#define INA226_ADDR_GND_VS 0x41  //!< I2C address, A1 pin - GND, A0 pin - VS+
#define INA226_ADDR_GND_SDA 0x42 //!< I2C address, A1 pin - GND, A0 pin - SDA
#define INA226_ADDR_GND_SCL 0x43 //!< I2C address, A1 pin - GND, A0 pin - SCL
#define INA226_ADDR_VS_GND 0x44  //!< I2C address, A1 pin - VS+, A0 pin - GND
#define INA226_ADDR_VS_VS 0x45   //!< I2C address, A1 pin - VS+, A0 pin - VS+
#define INA226_ADDR_VS_SDA 0x46  //!< I2C address, A1 pin - VS+, A0 pin - SDA
#define INA226_ADDR_VS_SCL 0x47  //!< I2C address, A1 pin - VS+, A0 pin - SCL
#define INA226_ADDR_SDA_GND 0x48 //!< I2C address, A1 pin - SDA, A0 pin - GND
#define INA226_ADDR_SDA_VS 0x49  //!< I2C address, A1 pin - SDA, A0 pin - VS+
#define INA226_ADDR_SDA_SDA 0x4a //!< I2C address, A1 pin - SDA, A0 pin - SDA
#define INA226_ADDR_SDA_SCL 0x4b //!< I2C address, A1 pin - SDA, A0 pin - SCL
#define INA226_ADDR_SCL_GND 0x4c //!< I2C address, A1 pin - SCL, A0 pin - GND
#define INA226_ADDR_SCL_VS 0x4d  //!< I2C address, A1 pin - SCL, A0 pin - VS+
#define INA226_ADDR_SCL_SDA 0x4e //!< I2C address, A1 pin - SCL, A0 pin - SDA
#define INA226_ADDR_SCL_SCL 0x4f //!< I2C address, A1 pin - SCL, A0 pin - SCL

/**
 * Averaging Mode
 */
typedef enum
{
    INA226_CONFIG_AVG_1 = 0, // Default
    INA226_CONFIG_AVG_4 = 1,
    INA226_CONFIG_AVG_16 = 2,
    INA226_CONFIG_AVG_64 = 3,
    INA226_CONFIG_AVG_128 = 4,
    INA226_CONFIG_AVG_256 = 5,
    INA226_CONFIG_AVG_512 = 6,
    INA226_CONFIG_AVG_1024 = 7
} ina226_config_avg_t;

/**
 * Bus Voltage Conversion Time
 */
typedef enum
{
    INA226_CONFIG_VBUSCT_140u = 0,
    INA226_CONFIG_VBUSCT_204u = 1,
    INA226_CONFIG_VBUSCT_332u = 2,
    INA226_CONFIG_VBUSCT_588u = 3,
    INA226_CONFIG_VBUSCT_1_1m = 4, // Default
    INA226_CONFIG_VBUSCT_2_116m = 5,
    INA226_CONFIG_VBUSCT_4_156m = 6,
    INA226_CONFIG_VBUSCT_8_244m = 7,
} ina226_config_vbusct_t;

/**
 * Shunt Voltage Conversion Time
 */
typedef enum
{
    INA226_CONFIG_VSHCT_140u = 0,
    INA226_CONFIG_VSHCT_204u = 1,
    INA226_CONFIG_VSHCT_332u = 2,
    INA226_CONFIG_VSHCT_588u = 3,
    INA226_CONFIG_VSHCT_1_1m = 4, // Default
    INA226_CONFIG_VSHCT_2_116m = 5,
    INA226_CONFIG_VSHCT_4_156m = 6,
    INA226_CONFIG_VSHCT_8_244m = 7,
} ina226_config_vshct_t;

/**
 * Operating mode
 */
typedef enum
{
    INA226_CONFIG_MODE_POWER_DOWN = 0,     //!< Power-done
    INA226_CONFIG_MODE_TRIG_SHUNT = 1,     //!< Shunt voltage, triggered
    INA226_CONFIG_MODE_TRIG_BUS = 2,       //!< Bus voltage, triggered
    INA226_CONFIG_MODE_TRIG_SHUNT_BUS = 3, //!< Shunt and bus, triggered
    INA226_CONFIG_MODE_DISABLED = 4,       //!< ADC off (disabled)
    INA226_CONFIG_MODE_CONT_SHUNT = 5,     //!< Shunt voltage, continuous
    INA226_CONFIG_MODE_CONT_BUS = 6,       //!< Bus voltage, continuous
    INA226_CONFIG_MODE_CONT_SHUNT_BUS = 7  //!< Shunt and bus, continuous (default)
} ina226_config_mode_t;

/**
 * Device descriptor
 */
typedef struct
{
    i2c_dev_t i2c_dev;

    uint16_t config;
    float i_lsb, p_lsb;
    uint16_t mfr_id, die_id;
} ina226_t;

/**
 * @brief Initialize device descriptor
 *
 * @param dev Device descriptor
 * @param addr Device I2C address
 * @param port I2C port
 * @param sda_gpio SDA GPIO
 * @param scl_gpio SCL GPIO
 * @return `ESP_OK` on success
 */
esp_err_t ina226_init_desc(ina226_t *dev, uint8_t addr,
                           i2c_port_t port, gpio_num_t sda_gpio, gpio_num_t scl_gpio);

/**
 * @brief Free device descriptor
 *
 * @param dev Device descriptor
 * @return `ESP_OK` on success
 */
esp_err_t ina226_free_desc(ina226_t *dev);

/**
 * @brief Init device
 *
 * Read current device configuration into `dev->config`
 *
 * @param dev Device descriptor
 * @return `ESP_OK` on success
 */
esp_err_t ina226_init(ina226_t *dev);

/**
 * @brief Reset device
 *
 * Same as power-on reset. Resets all registers to default values.
 * You still need to calibrate device to read current, otherwise
 * only shunt voltage readings will be valid.
 *
 * @param dev Device descriptor
 * @return `ESP_OK` on success
 */
esp_err_t ina226_reset(ina226_t *dev);

/**
 * @brief Set device configuration
 *
 * @param dev Device descriptor
 * @param avg_mode Averaging mode
 * @param vbus_ct Bus voltage conversion time
 * @param vsh_ct Shunt voltage conversion time
 * @param op_mode Operating mode
 * @return `ESP_OK` on success
 */
esp_err_t ina226_configure(ina226_t *dev, ina226_config_avg_t avg_mode,
                           ina226_config_vbusct_t vbus_ct, ina226_config_vshct_t vsh_ct,
                           ina226_config_mode_t op_mode);

/**
 * @brief Get averaging mode
 *
 * @param dev Device descriptor
 * @param[out] avg_mode Averaging mode
 * @return `ESP_OK` on success
 */
esp_err_t ina226_get_avg_mode(ina226_t *dev, ina226_config_avg_t *avg_mode);

/**
 * @brief Get bus voltage conversion time
 *
 * @param dev Device descriptor
 * @param[out] vbus_ct Bus voltage conversion time
 * @return `ESP_OK` on success
 */
esp_err_t ina226_get_vbus_conv_time(ina226_t *dev, ina226_config_vbusct_t *vbus_ct);

/**
 * @brief Get shunt voltage conversion time
 *
 * @param dev Device descriptor
 * @param[out] vsh_ct Shunt voltage conversion time
 * @return `ESP_OK` on success
 */
esp_err_t ina226_get_shunt_conv_time(ina226_t *dev, ina226_config_vshct_t *vsh_ct);

/**
 * @brief Get operating mode
 *
 * @param dev Device descriptor
 * @param[out] op_mode Operating mode
 * @return `ESP_OK` on success
 */
esp_err_t ina226_get_mode(ina226_t *dev, ina226_config_mode_t *op_mode);

/**
 * @brief Perform calibration
 *
 * Current readings will be valid only after calibration
 *
 * @param dev Device descriptor
 * @param i_lsb LSB of current register, mA
 * @param r_shunt Shunt resistance, mOhm
 * @return `ESP_OK` on success
 */
esp_err_t ina226_calibrate(ina226_t *dev, float i_lsb, float r_shunt);

/**
 * @brief Trigger single conversion
 *
 * Function will return an error if current operating
 * mode is not `INA226_MODE_TRIG_SHUNT`/`INA226_MODE_TRIG_BUS`/`INA226_MODE_TRIG_SHUNT_BUS`
 *
 * @param dev Device descriptor
 * @return `ESP_OK` on success
 */
esp_err_t ina226_trigger(ina226_t *dev);

/**
 * @brief Read bus voltage
 *
 * @param dev Device descriptor
 * @param[out] voltage Bus voltage, mV
 * @return `ESP_OK` on success
 */
esp_err_t ina226_get_bus_voltage(ina226_t *dev, float *voltage);

/**
 * @brief Read shunt voltage
 *
 * @param dev Device descriptor
 * @param[out] voltage Shunt voltage, uV
 * @return `ESP_OK` on success
 */
esp_err_t ina226_get_shunt_voltage(ina226_t *dev, float *voltage);

/**
 * @brief Read current
 *
 * This function works properly only after calibration.
 *
 * @param dev Device descriptor
 * @param[out] current Current, mA
 * @return `ESP_OK` on success
 */
esp_err_t ina226_get_current(ina226_t *dev, float *current);

/**
 * @brief Read power
 *
 * This function works properly only after calibration.
 *
 * @param dev Device descriptor
 * @param[out] power Power, W
 * @return `ESP_OK` on success
 */
esp_err_t ina226_get_power(ina226_t *dev, float *power);

#ifdef __cplusplus
}
#endif

/**@}*/

#endif /* __INA226_H__ */
