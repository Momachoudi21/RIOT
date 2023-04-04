/*
 * Copyright (C) 2017 OTA keys S.A.
 *
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License v2.1. See the file LICENSE in the top level
 * directory for more details.
 *
 */

/**
 * @ingroup     drivers_lSM9ds1
 * @{
 *
 * @file
 * @brief       Default configuration for LSM9DS1 devices
 *
 * @author      Vincent Dupont <vincent@otakeys.com>
 *
 */

#ifndef LSM9DS1_PARAMS_H
#define LSM9DS1_PARAMS_H

#include "board.h"
#include "lsm9ds1.h"
#include "saul_reg.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @name    Set default configuration parameters
 * @{
 */
#ifndef LSM9DS1_PARAM_I2C
#define LSM9DS1_PARAM_I2C            I2C_DEV(0)
#endif
#ifndef LSM9DS1_PARAM_ADDR
#define LSM9DS1_PARAM_ADDR           (0x6B) /* (0x6A) */
#endif
#ifndef LSM9DS1_PARAM_ACC_ODR
#define LSM9DS1_PARAM_ACC_ODR        (LSM9DS1_DATA_RATE_52HZ)
#endif
#ifndef LSM9DS1_PARAM_GYRO_ODR
#define LSM9DS1_PARAM_GYRO_ODR       (LSM9DS1_DATA_RATE_52HZ)
#endif
#ifndef LSM9DS1_PARAM_ACC_FS
#define LSM9DS1_PARAM_ACC_FS         (LSM9DS1_ACC_FS_2G)
#endif
#ifndef LSM9DS1_PARAM_GYRO_FS
#define LSM9DS1_PARAM_GYRO_FS        (LSM9DS1_GYRO_FS_245DPS)
#endif
#ifndef LSM9DS1_PARAM_ACC_FIFO_DEC
#define LSM9DS1_PARAM_ACC_FIFO_DEC   (LSM9DS1_DECIMATION_NO)
#endif
#ifndef LSM9DS1_PARAM_GYRO_FIFO_DEC
#define LSM9DS1_PARAM_GYRO_FIFO_DEC  (LSM9DS1_DECIMATION_NO)
#endif

#ifndef LSM9DS1_PARAM_MAGNE
#define LSM9DS1_PARAM_MAGNE          (LSM9DS1_MAGNE_ENABLE)
#endif
#ifndef LSM9DS1_PARAM_MAGNE_ODR
#define LSM9DS1_PARAM_MAGNE_ODR      (LSM9DS1_DATA_RATE_52HZ)
#endif
#ifndef LSM9DS1_PARAM_MAGNE_FS
#define LSM9DS1_PARAM_MAGNE_FS       (LSM9DS1_MAGNE_FS_4GAUSS)
#endif
#ifndef LSM9DS1_PARAM_MAGNE_FIFO_DEC
#define LSM9DS1_PARAM_MAGNE_FIFO_DEC (LSM9DS1_DECIMATION_NO)
#endif

#ifndef LSM9DS1_PARAMS
#define LSM9DS1_PARAMS               { .i2c             = LSM9DS1_PARAM_I2C,          \
                                       .addr            = LSM9DS1_PARAM_ADDR,         \
                                       .acc_odr         = LSM9DS1_PARAM_ACC_ODR,      \
                                       .gyro_odr        = LSM9DS1_PARAM_GYRO_ODR,     \
                                       .acc_fs          = LSM9DS1_PARAM_ACC_FS,       \
                                       .gyro_fs         = LSM9DS1_PARAM_GYRO_FS,      \
                                       .acc_decimation  = LSM9DS1_PARAM_ACC_FIFO_DEC, \
                                       .mag_odr         = LSM9DS1_PARAM_MAGNE_ODR,    \}
#endif
#ifndef LSM9DS1_SAUL_INFO
#define LSM9DS1_SAUL_INFO            { .name = "lsm9ds1" }
#endif
/** @} */

/**
 * @brief   Allocate some memory to store the actual configuration
 */
static const lSM9DS1_params_t lsm9ds1_params[] = 
{
    LSM9DS1_PARAMS
};

/**
 * @brief   Additional meta information to keep in the SAUL registry
 */
static const saul_reg_info_t lSM9ds1_saul_info[] =
{
    LSM9DS1_SAUL_INFO
};

#ifdef __cplusplus
}
#endif

#endif /* LSM9DS1_PARAMS_H */
/** @} */
