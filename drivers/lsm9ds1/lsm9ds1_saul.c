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
 * @brief       SAUL implementation for the LSM9DS1 3D accelerometer/gyroscope/magnetometer.
 *
 * @author      Mohamed El Machoudi <momachoudi8@gmail.com>
 *
 * @}
 */

#include "lsm9ds1.h"
#include "saul.h"

static int read_acc(const void *dev, phydat_t *res)
{
    int ret = lsm9ds1_read_acc((const lSM9DS1_t *)dev, (lsm9ds1_3d_data_t *)res->val);
    if (ret < 0) {
        return -ECANCELED;
    }

    res->scale = -3;
    res->unit = UNIT_G;

    return 3;
}

static int read_gyro(const void *dev, phydat_t *res)
{
    int ret = lsm9ds1_read_gyro((const lSM9DS1_t *)dev, (lsm9ds1_3d_data_t *)res->val);
    if (ret < 0) {
        return -ECANCELED;
    }

    res->scale = -1;
    res->unit = UNIT_DPS;

    return 3;
}

static int read_mag(const void *dev, phydat_t *res)
{
    int ret = lsm9ds1_read_mag((const lSM9DS1_t *)dev, (lsm9ds1_3d_data_t *)res->val);
    if (ret < 0) {
        return -ECANCELED;
    }

    res->scale = -1;
    res->unit = UNIT_GS;

    return 3;
}

static int read_temp(const void *dev, phydat_t *res)
{
    if (lsm9ds1_read_temp((const lSM9DS1_t *)dev, &res->val[0]) < 0) {
        return -ECANCELED;
    }
    res->scale = -2;
    res->unit = UNIT_TEMP_C;

    return 1;
}

const saul_driver_t lsm9ds1_saul_acc_driver = {
    .read = read_acc,
    .write = saul_write_notsup,
    .type = SAUL_SENSE_ACCEL,
};

const saul_driver_t lsm9ds1_saul_gyro_driver = {
    .read = read_gyro,
    .write = saul_write_notsup,
    .type = SAUL_SENSE_GYRO,
};

const saul_driver_t lsm9ds1_saul_magne_driver = {
    .read = read_mag,
    .write = saul_write_notsup,
    .type = SAUL_SENSE_MAG,
};

const saul_driver_t lsm9ds1_saul_temp_driver = {
    .read = read_temp,
    .write = saul_write_notsup,
    .type = SAUL_SENSE_TEMP,
};
