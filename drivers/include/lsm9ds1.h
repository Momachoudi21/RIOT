/*
 * Copyright (C) 2017 OTA keys S.A.
 *
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License v2.1. See the file LICENSE in the top level
 * directory for more details.
 *
 */

/**
 * @defgroup    drivers_lSM9DS1 LSM9DS1 3D accelerometer/gyroscope/magnetometer
 * @ingroup     drivers_sensors
 * @ingroup     drivers_saul
 * @brief       Device driver for the LSM9DS1 3D accelerometer/gyroscope
 *
 * This driver provides @ref drivers_saul capabilities.
 * @{
 *
 * @file
 * @brief       Device driver interface for the LSM9DS1 3D accelerometer/gyroscope/magnetometer.
 *
 * @author      Vincent Dupont <vincent@otakeys.com>
 * @author      Sebastian Meiling <s@mlng.net>
 *
 */

#ifndef LSM9DS1_H
#define LSM9DS1_H

#ifdef __cplusplus
extern "C" {
#endif

#include "periph/i2c.h"

/**
 * @brief   Data rate settings
 */
enum {
    LSM9DS1_DATA_RATE_POWER_DOWN = 0x0,
    LSM9DS1_DATA_RATE_1_6HZ      = 0xB,
    LSM9DS1_DATA_RATE_12_5HZ     = 0x1,
    LSM9DS1_DATA_RATE_26HZ       = 0x2,
    LSM9DS1_DATA_RATE_52HZ       = 0x3,
    LSM9DS1_DATA_RATE_104HZ      = 0x4,
    LSM9DS1_DATA_RATE_208HZ      = 0x5,
    LSM9DS1_DATA_RATE_416HZ      = 0x6,
    LSM9DS1_DATA_RATE_833HZ      = 0x7,
    LSM9DS1_DATA_RATE_1_66KHZ    = 0x8,
    LSM9DS1_DATA_RATE_3_33KHZ    = 0x9,
    LSM9DS1_DATA_RATE_6_66KHZ    = 0xa,
};

/**
 * @brief   Decimation settings
 */
enum {
    LSM9DS1_DECIMATION_NOT_IN_FIFO = 0,
    LSM9DS1_DECIMATION_NO,
    LSM9DS1_DECIMATION_2,
    LSM9DS1_DECIMATION_3,
    LSM9DS1_DECIMATION_4,
    LSM9DS1_DECIMATION_8,
    LSM9DS1_DECIMATION_16,
    LSM9DS1_DECIMATION_32,
    LSM9DS1_DECIMATION_MAX,
};

/**
 * @brief   Accelerometer full scale
 */
enum {
    LSM9DS1_ACC_FS_2G  = 0,
    LSM9DS1_ACC_FS_16G,
    LSM9DS1_ACC_FS_4G,
    LSM9DS1_ACC_FS_8G,
    LSM9DS1_ACC_FS_MAX,
};

/**
 * @brief   Gyroscope full scale
 */
enum {
    LSM9DS1_GYRO_FS_245DPS    = 0,
    LSM9DS1_GYRO_FS_500DPS,
    LSM9DS1_GYRO_FS_1000DPS,
    LSM9DS1_GYRO_FS_2000DPS,
    LSM9DS1_GYRO_FS_MAX,
};

/**
*   @brief  Magnetometer full scale
*/
enum {
    LSM9DS1_MAG_FS_4GAUSS = 0,
    LSM9DS1_MAG_FS_8GAUSS,
    LSM9DS1_MAG_FS_12GAUSS,
    LSM9DS1_MAG_FS_16GAUSS,
    LSM9DS1_MAG_FS_MAX,
};

/**
 * @brief   LSM9DS1 driver parameters
 */
typedef struct {
    i2c_t i2c;                  /**< i2c bus */
    uint8_t addr;               /**< i2c address */
    uint8_t acc_odr;            /**< accelerometer output data rate */
    uint8_t gyro_odr;           /**< gyroscope output data rate */
    uint8_t acc_fs;             /**< accelerometer full scale */
    uint8_t gyro_fs;            /**< gyroscope full scale */
    uint8_t acc_decimation;     /**< accelerometer decimation */
    uint8_t mag_fs;             /**< magnetometer full scale */
    uint8_t mag_odr;            /**< magnetometer output data rate */
} lSM9DS1_params_t;

/**
 * @brief   LSM9DS1 device descriptor
 */
typedef struct {
    lSM9DS1_params_t params; /**< driver parameters */
} lSM9DS1_t;

/**
 * @brief   3D output data
 */
typedef struct {
    int16_t x;  /**< X axis */
    int16_t y;  /**< Y axis */
    int16_t z;  /**< Z axis */
} lsm9ds1_3d_data_t;

/**
 * @brief   Named return values
 */
enum {
    LSM9DS1_OK = 0,             /**< all good */
    LSM9DS1_ERROR_BUS,          /**< I2C bus error */
    LSM9DS1_ERROR_CNF,          /**< Config error */
    LSM9DS1_ERROR_DEV,          /**< device error */
    LSM9DS1_ERROR_NO_DATA,      /**< no data available */
};

/**
 * @brief   Initialize a LSM9DS1 device
 *
 * @param[out] dev     device to initialize
 * @param[in] params  driver parameters
 *
 * @return LSM9DS1_OK on success
 * @return < 0 on error
 */
int lsm9ds1_init(lSM9DS1_t *dev, const lSM9DS1_params_t *params);

/**
 * @brief   Read accelerometer data
 *
 * @param[in] dev    device to read
 * @param[out] data  accelerometer values
 *
 * @return LSM9DS1_OK on success
 * @return < 0 on error
 */
int lsm9ds1_read_acc(const lSM9DS1_t *dev, lsm9ds1_3d_data_t *data);

/**
 * @brief   Read gyroscope data
 *
 * @param[in] dev    device to read
 * @param[out] data  gyroscope values
 *
 * @return LSM9DS1_OK on success
 * @return < 0 on error
 */
int lsm9ds1_read_gyro(const lSM9DS1_t *dev, lsm9ds1_3d_data_t *data);


/**
 * @brief   Read magnetometer data
 *
 * @param[in] dev    device to read
 * @param[out] data  magnetometer values
 *
 * @return LSM9DS1_OK on success
 * @return < 0 on error
 */

int lsm9ds1_read_mag(const lSM9DS1_t *dev, lsm9ds1_3d_data_t *data);

/**
 * @brief   Read temperature data
 *
 * @note To avoid floating point data types but still provide high resolution
 *       for temperature readings, resulting values are scale by factor 100.
 *
 *
 * @param[in] dev    device to read
 * @param[out] data  temperature value, in °C x 100
 *
 * @return LSM9DS1_OK on success
 * @return < 0 on error
 */
int lsm9ds1_read_temp(const lSM9DS1_t *dev, int16_t *data);

/**
 * @brief   Power down accelerometer
 *
 * @param[in] dev    device to power down
 *
 * @return LSM9DS1_OK on success
 * @return < 0 on error
 */
int lsm9ds1_acc_power_down(const lSM9DS1_t *dev);

/**
 * @brief   Power down gyroscope
 *
 * @param[in] dev    device to power down
 *
 * @return LSM9DS1_OK on success
 * @return < 0 on error
 */
int lsm9ds1_gyro_power_down(const lSM9DS1_t *dev);

/**
 * @brief   Power down magnetometer
 *
 * @param[in] dev    device to power down
 *
 * @return LSM9DS1_OK on success
 * @return < 0 on error
 */
int lsm9ds1_mag_power_down(const lSM9DS1_t *dev);


/**
 * @brief   Power up accelerometer
 *
 * @param[in] dev    device to power up
 *
 * @return LSM9DS1_OK on success
 * @return < 0 on error
 */
int lsm9ds1_acc_power_up(const lSM9DS1_t *dev);

/**
 * @brief   Power up gyroscope
 *
 * @param[in] dev    device to power up
 *
 * @return LSM9DS1_OK on success
 * @return < 0 on error
 */
int lsm9ds1_gyro_power_up(const lSM9DS1_t *dev);

/**
 * @brief   Power up magnetometer
 *
 * @param[in] dev    device to power up
 *
 * @return LSM9DS1_OK on success
 * @return < 0 on error
 */
int lsm9ds1_mag_power_up(const lSM9DS1_t *dev);

#ifdef __cplusplus
}
#endif

#endif /* LSM9DS1_H */
/** @} */
