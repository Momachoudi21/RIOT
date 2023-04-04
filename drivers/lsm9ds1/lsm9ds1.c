/*
 * Copyright (C) 2017 OTA keys S.A.
 *
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License v2.1. See the file LICENSE in the top level
 * directory for more details.
 *
 */

/**
 * @ingroup     drivers_lsm9ds1
 * @{
 *
 * @file
 * @brief       Device driver implementation for the LSM9DS1 3D accelerometer/gyroscope/magnetometer.
 *
 * @author      Mohamed El Machoudi <momachoudi8@gmail.com>
 *
 *
 * @}
 */

#include <assert.h>

#include "ztimer.h"
#include "macros/utils.h"

#include "lsm9ds1.h"
#include "lsm9ds1_internal.h"

#define ENABLE_DEBUG 0
#include "debug.h"

#define BUS (dev->params.i2c)
#define ADDR (dev->params.addr)

/**
 * order in array [0, 1, 2, 3] is
 * LSM9DS1_ACC_FS_2G, LSM9DS1_ACC_FS_16G, LSM9DS1_ACC_FS_4G, LSM9DS1_ACC_FS_8G
 */
static const int16_t range_acc[] = {2000, 16000, 4000, 8000};

/**
 * order in array [0, 1, 2, 3] is
 * LSM9DS1_GYRO_FS_245DPS, LSM9DS1_GYRO_FS_500DPS,
 * LSM9DS1_GYRO_FS_1000DPS, LSM9DS1_GYRO_FS_2000DPS
 */
static const int16_t range_gyro[] = {2450, 5000, 10000, 20000};

/**
 * order in array [] is
 * LSM9DS1_MAGNE_FS_4G, LSM9DS1_MAGNE_FS_8G, LSM9DS1_MAGNE_FS_12G, LSM9DS1_MAGNE_FS_16G
 */

static const int16_t range_mag[] = {4000, 8000, 12000, 16000};

/**
 * LSM9DS1 initialization
 */

int lsm9ds1_init(lSM9DS1_t *dev, const lSM9DS1_params_t *params)
{
    uint8_t tmp;
    int res;

    assert(dev && params);

    dev->params = *params;

    i2c_acquire(BUS);

    /* Reboot */

    i2c_write_reg(BUS, ADDR, LSM9DS1_REG_CTRL_REG8, LSM9DS1_REG_CTRL_REG8_BOOT, 0);

    /* Wait for reboot */

    ztimer_sleep(ZTIMER_MSEC, LSM9DS1_REBOOT_WAIT);

    /* Check WHO_AM_I */

    if (i2c_read_reg(BUS, ADDR, LSM9DS1_REG_WHO_AM_I, &tmp, 0) < 0)
    {
        i2c_release(BUS);
        DEBUG("[ERROR] lsm9ds1_init: i2c_read_reg LSM9DS1_REG_WHO_AM_I!\n");
        return -LSM9DS1_ERROR_BUS;
    }

    if (tmp != LSM9DS1_WHO_AM_I)
    {
        DEBUG("[ERROR] lsm9ds1_init: WHO_AM_I\n");
        return -LSM9DS1_ERROR_DEV;
    }

    /* Check WHO_AM_I_M */

    if (i2c_read_reg(BUS, ADDR, LSM9DS1_REG_WHO_AM_I_M, &tmp, 0) < 0)
    {
        i2c_release(BUS);
        DEBUG("[ERROR] lsm9ds1_init: i2c_read_reg LSM9DS1_REG_WHO_AM_I_M!\n");
        return -LSM9DS1_ERROR_BUS;
    }

    if (tmp != LSM9DS1_REG_WHO_AM_I_M)
    {
        DEBUG("[ERROR] lsm9ds1_init: WHO_AM_I\n");
        return -LSM9DS1_ERROR_DEV;
    }
    /* Set acc odr / full scale */
    tmp = (dev->params.acc_odr << LSM9DS1_CTRL_ODR_SHIFT) |
          (dev->params.acc_fs << LSM9DS1_CTRL_FS_SHIFT);
    res += i2c_write_reg(BUS, ADDR, LSM9DS1_REG_CTRL_REG6_XL, tmp, 0);
    /* Set gyro odr / full scale */
    tmp = (dev->params.gyro_odr << LSM9DS1_CTRL_ODR_SHIFT) |
          (dev->params.gyro_fs << LSM9DS1_CTRL_FS_SHIFT);
    res += i2c_write_reg(BUS, ADDR, LSM9DS1_REG_CTRL_REG1_G, tmp, 0);

    /* Set mag odr / full scale */
    tmp = (dev->params.mag_odr << LSM9DS1_CTRL_ODR_SHIFT) |
          (dev->params.mag_fs << LSM9DS1_CTRL_FS_SHIFT);
    res += i2c_write_reg(BUS, ADDR, LSM9DS1_REG_CTRL_REG2_M, tmp, 0);

    /* Set continuous mode */



    /* Set FIFO mode */

    tmp = LSM9DS1_REG_FIFO_CTRL;
    res += i2c_write_reg(BUS, ADDR, LSM9DS1_REG_FIFO_CTRL, tmp, 0);

    /* Set FIFO threshold */

    i2c_release(BUS);

    if (res < 0)
    {
        DEBUG("[ERROR] lsm9ds1_init: config\n");
        return -LSM9DS1_ERROR_CNF;
    }
    return LSM9DS1_OK;
}

int lsm9ds1_read_acc(const lSM9DS1_t *dev, lsm9ds1_3d_data_t *data)
{
    int res;
    uint8_t tmp;

    i2c_acquire(BUS);
    i2c_read_reg(BUS, ADDR, LSM9DS1_REG_STATUS_REG, &tmp, 0);
    DEBUG("lsm9ds1 status: %x\n", tmp);

    res = i2c_read_reg(BUS, ADDR, LSM9DS1_REG_OUT_X_L_XL, &tmp, 0);
    data->x = tmp;
    res += i2c_read_reg(BUS, ADDR, LSM9DS1_REG_OUT_X_H_XL, &tmp, 0);
    data->x |= tmp << 8;
    res += i2c_read_reg(BUS, ADDR, LSM9DS1_REG_OUT_Y_L_XL, &tmp, 0);
    data->y = tmp;
    res += i2c_read_reg(BUS, ADDR, LSM9DS1_REG_OUT_Y_H_XL, &tmp, 0);
    data->y |= tmp << 8;
    res += i2c_read_reg(BUS, ADDR, LSM9DS1_REG_OUT_Z_L_XL, &tmp, 0);
    data->z = tmp;
    res += i2c_read_reg(BUS, ADDR, LSM9DS1_REG_OUT_Z_H_XL, &tmp, 0);
    data->z |= tmp << 8;
    i2c_release(BUS);

    if (res < 0)
    {
        DEBUG("[ERROR] lsm9ds1_read_acc\n");
        return -LSM9DS1_ERROR_BUS;
    }

    assert(dev->params.acc_fs < LSM9DS1_ACC_FS_MAX);
    data->x = ((int32_t)data->x * range_acc[dev->params.acc_fs]) / INT16_MAX;
    data->y = ((int32_t)data->y * range_acc[dev->params.acc_fs]) / INT16_MAX;
    data->z = ((int32_t)data->z * range_acc[dev->params.acc_fs]) / INT16_MAX;

    return LSM9DS1_OK;
}

int lsm9ds1_read_gyro(const lSM9DS1_t *dev, lsm9ds1_3d_data_t *data)
{
    int res;
    uint8_t tmp;

    i2c_acquire(BUS);
    i2c_read_reg(BUS, ADDR, LSM9DS1_REG_STATUS_REG, &tmp, 0);
    DEBUG("lsm9ds1 status: %x\n", tmp);

    res = i2c_read_reg(BUS, ADDR, LSM9DS1_REG_OUT_X_L_G, &tmp, 0);
    data->x = tmp;
    res += i2c_read_reg(BUS, ADDR, LSM9DS1_REG_OUT_X_H_G, &tmp, 0);
    data->x |= tmp << 8;
    res += i2c_read_reg(BUS, ADDR, LSM9DS1_REG_OUT_Y_L_G, &tmp, 0);
    data->y = tmp;
    res += i2c_read_reg(BUS, ADDR, LSM9DS1_REG_OUT_Y_H_G, &tmp, 0);
    data->y |= tmp << 8;
    res += i2c_read_reg(BUS, ADDR, LSM9DS1_REG_OUT_Z_L_G, &tmp, 0);
    data->z = tmp;
    res += i2c_read_reg(BUS, ADDR, LSM9DS1_REG_OUT_Z_H_G, &tmp, 0);
    data->z |= tmp << 8;
    i2c_release(BUS);

    if (res < 0)
    {
        DEBUG("[ERROR] lsm9ds1_read_gyro\n");
        return -LSM9DS1_ERROR_BUS;
    }

    assert(dev->params.gyro_fs < LSM9DS1_GYRO_FS_MAX);
    data->x = ((int32_t)data->x * range_gyro[dev->params.gyro_fs]) / INT16_MAX;
    data->y = ((int32_t)data->y * range_gyro[dev->params.gyro_fs]) / INT16_MAX;
    data->z = ((int32_t)data->z * range_gyro[dev->params.gyro_fs]) / INT16_MAX;

    return LSM9DS1_OK;
}

int lsm9ds1_read_mag(const lSM9DS1_t *dev, lsm9ds1_3d_data_t *data)
{
    int res;
    uint8_t tmp;

    i2c_acquire(BUS);
    i2c_read_reg(BUS, ADDR, LSM9DS1_REG_STATUS_REG, &tmp, 0);
    DEBUG("lsm9ds1 status: %x\n", tmp);

    res = i2c_read_reg(BUS, ADDR, LSM9DS1_REG_OUT_X_L_M, &tmp, 0);
    data->x = tmp;
    res += i2c_read_reg(BUS, ADDR, LSM9DS1_REG_OUT_X_H_M, &tmp, 0);
    data->x |= tmp << 8;
    res += i2c_read_reg(BUS, ADDR, LSM9DS1_REG_OUT_Y_L_M, &tmp, 0);
    data->y = tmp;
    res += i2c_read_reg(BUS, ADDR, LSM9DS1_REG_OUT_Y_H_M, &tmp, 0);
    data->y |= tmp << 8;
    res += i2c_read_reg(BUS, ADDR, LSM9DS1_REG_OUT_Z_L_M, &tmp, 0);
    data->z = tmp;
    res += i2c_read_reg(BUS, ADDR, LSM9DS1_REG_OUT_Z_H_M, &tmp, 0);
    data->z |= tmp << 8;
    i2c_release(BUS);

    if (res < 0)
    {
        DEBUG("[ERROR] lsm9ds1_read_mag\n");
        return -LSM9DS1_ERROR_BUS;
    }

    assert(dev->params.mag_fs < LSM9DS1_MAG_FS_MAX);
    data->x = ((int32_t)data->x * range_mag[dev->params.mag_fs]) / INT16_MAX;
    data->y = ((int32_t)data->y * range_mag[dev->params.mag_fs]) / INT16_MAX;
    data->z = ((int32_t)data->z * range_mag[dev->params.mag_fs]) / INT16_MAX;

    return LSM9DS1_OK;
}

int lsm9ds1_read_temp(const lSM9DS1_t *dev, int16_t *data)
{
    uint8_t tmp;
    uint16_t traw;
    /* read raw temperature */
    i2c_acquire(BUS);
    if (i2c_read_reg(BUS, ADDR, LSM9DS1_REG_OUT_TEMP_L, &tmp, 0) < 0)
    {
        i2c_release(BUS);
        return -LSM9DS1_ERROR_BUS;
    }
    traw = tmp;
    if (i2c_read_reg(BUS, ADDR, LSM9DS1_REG_OUT_TEMP_H, &tmp, 0) < 0)
    {
        i2c_release(BUS);
        return -LSM9DS1_ERROR_BUS;
    }
    traw |= (uint16_t)tmp << 8;
    i2c_release(BUS);
    /* convert temperature to degC x 100 */
    traw += LSM9DS1_TEMP_OFFSET;
    *data = (int16_t)(((int32_t)traw * 100) / 256);

    return LSM9DS1_OK;
}

int lsm9ds1_acc_power_down(const lSM9DS1_t *dev)
{
    int res;
    uint8_t tmp;

    i2c_acquire(BUS);
    res = i2c_read_reg(BUS, ADDR, LSM9DS1_REG_CTRL_REG6_XL, &tmp, 0);
    if (res < 0)
    {
        i2c_release(BUS);
        DEBUG("[ERROR] lsm9ds1_acc_power_down\n");
        return -LSM9DS1_ERROR_BUS;
    }

    tmp &= ~(LSM9DS1_CTRL_ODR_MASK);
    res = i2c_write_reg(BUS, ADDR, LSM9DS1_REG_CTRL_REG6_XL, tmp, 0);

    i2c_release(BUS);

    if (res < 0)
    {
        DEBUG("[ERROR] lsm9ds1_acc_power_down\n");
        return -LSM9DS1_ERROR_BUS;
    }

    return LSM9DS1_OK;
}

int lsm9ds1_gyro_power_down(const lSM9DS1_t *dev)
{
    int res;
    uint8_t tmp;

    i2c_acquire(BUS);
    res = i2c_read_reg(BUS, ADDR, LSM9DS1_REG_CTRL_REG1_G, &tmp, 0);
    if (res < 0)
    {
        i2c_release(BUS);
        DEBUG("[ERROR] lsm9ds1_gyro_power_down\n");
        return -LSM9DS1_ERROR_BUS;
    }

    tmp &= ~(LSM9DS1_CTRL_ODR_MASK);
    res = i2c_write_reg(BUS, ADDR, LSM9DS1_REG_CTRL_REG1_G, tmp, 0);

    i2c_release(BUS);

    if (res < 0)
    {
        DEBUG("[ERROR] lsm9ds1_gyro_power_down\n");
        return -LSM9DS1_ERROR_BUS;
    }

    return LSM9DS1_OK;
}

int lsm9ds1_mag_power_down(const lSM9DS1_t *dev)
{
    int res;
    uint8_t tmp;

    i2c_acquire(BUS);
    res = i2c_read_reg(BUS, ADDR, LSM9DS1_REG_CTRL_REG1_M, &tmp, 0);
    if (res < 0) {
        i2c_release(BUS);
        DEBUG("[ERROR] lsm9ds1_mag_power_down\n");
        return -LSM9DS1_ERROR_BUS;
    }

    tmp &= ~(LSM9DS1_CTRL_ODR_MASK);
    res = i2c_write_reg(BUS, ADDR, LSM9DS1_REG_CTRL_REG1_M, tmp, 0);

    i2c_release(BUS);

    if (res < 0) {
        DEBUG("[ERROR] lsm9ds1_mag_power_down\n");
        return -LSM9DS1_ERROR_BUS;
    }

    return LSM9DS1_OK;
}


int lsm9ds1_acc_power_up(const lSM9DS1_t *dev)
{
    int res;
    uint8_t tmp;

    i2c_acquire(BUS);
    res = i2c_read_reg(BUS, ADDR, LSM9DS1_REG_CTRL_REG6_XL, &tmp, 0);
    if (res < 0)
    {
        i2c_release(BUS);
        DEBUG("[ERROR] lsm9ds1_acc_power_up\n");
        return -LSM9DS1_ERROR_BUS;
    }

    tmp &= ~(LSM9DS1_CTRL_ODR_MASK);
    tmp |= dev->params.acc_odr << LSM9DS1_CTRL_ODR_SHIFT;
    res = i2c_write_reg(BUS, ADDR, LSM9DS1_REG_CTRL_REG6_XL, tmp, 0);

    i2c_release(BUS);

    if (res < 0)
    {
        DEBUG("[ERROR] lsm9ds1_acc_power_up\n");
        return -LSM9DS1_ERROR_BUS;
    }

    return LSM9DS1_OK;
}

int lsm9ds1_gyro_power_up(const lSM9DS1_t *dev)
{
    int res;
    uint8_t tmp;

    i2c_acquire(BUS);
    res = i2c_read_reg(BUS, ADDR, LSM9DS1_REG_CTRL_REG1_G, &tmp, 0);
    if (res < 0)
    {
        i2c_release(BUS);
        DEBUG("[ERROR] lsm9ds1_gyro_power_up\n");
        return -LSM9DS1_ERROR_BUS;
    }

    tmp &= ~(LSM9DS1_CTRL_ODR_MASK);
    tmp |= dev->params.gyro_odr << LSM9DS1_CTRL_ODR_SHIFT;
    res = i2c_write_reg(BUS, ADDR, LSM9DS1_REG_CTRL_REG1_G, tmp, 0);

    i2c_release(BUS);

    if (res < 0)
    {
        DEBUG("[ERROR] lsm9ds1_gyro_power_up\n");
        return -LSM9DS1_ERROR_BUS;
    }

    return LSM9DS1_OK;

}

int lsm9ds1_mag_power_up(const lSM9DS1_t *dev){
    int res;
    uint8_t tmp;

    i2c_acquire(BUS);
    res = i2c_read_reg(BUS, ADDR, LSM9DS1_REG_CTRL_REG1_M, &tmp, 0);
    if (res < 0) {
        i2c_release(BUS);
        DEBUG("[ERROR] lsm9ds1_mag_power_up\n");
        return -LSM9DS1_ERROR_BUS;
    }

    tmp &= ~(LSM9DS1_CTRL_ODR_MASK);
    tmp |= dev->params.mag_odr << LSM9DS1_CTRL_ODR_SHIFT;
    res = i2c_write_reg(BUS, ADDR, LSM9DS1_REG_CTRL_REG1_M, tmp, 0);

    i2c_release(BUS);

    if (res < 0) {
        DEBUG("[ERROR] lsm9ds1_mag_power_up\n");
        return -LSM9DS1_ERROR_BUS;
    }

    return LSM9DS1_OK;
}



