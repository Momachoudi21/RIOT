/*
 * Copyright (C) 2017 OTA keys S.A.
 *
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License v2.1. See the file LICENSE in the top level
 * directory for more details.
 *
 */

/**
 * @ingroup     drivers_lSM9DS1
 * @{
 *
 * @file
 * @brief       Internal configuration for LSM9DS1 devices
 *
 * @author      Vincent Dupont <vincent@otakeys.com>
 * @author      Sebastian Meiling <s@mlng.net>
 *
 */

#ifndef LSM9DS1_INTERNAL_H
#define LSM9DS1_INTERNAL_H

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @name    LSM9DS1 registers
 * @{
 */
#define LSM9DS1_REG_ACT_THS                 (0x04)
#define LSM9DS1_REG_ACT_DUR                 (0x05)
#define LSM9DS1_REG_INT_GEN_CFG_XL          (0x06)
#define LSM9DS1_REG_INT_GEN_THS_X_XL        (0x07)
#define LSM9DS1_REG_INT_GEN_THS_Y_XL        (0x08)
#define LSM9DS1_REG_INT_GEN_THS_Z_XL        (0x09)
#define LSM9DS1_REG_INT_GEN_DUR_XL          (0x0A)
#define LSM9DS1_REG_REFERENCE_G             (0x0B)
#define LSM9DS1_REG_INT1_CTRL               (0x0C)
#define LSM9DS1_REG_INT2_CTRL               (0x0D)
#define LSM9DS1_REG_WHO_AM_I                (0x0F)
#define LSM9DS1_REG_CTRL_REG1_G             (0x10)
#define LSM9DS1_REG_CTRL_REG2_G             (0x11)
#define LSM9DS1_REG_CTRL_REG3_G             (0x12)
#define LSM9DS1_REG_ORIENT_CFG_G            (0x13)
#define LSM9DS1_REG_INT_GEN_SRC_G           (0x14)
#define LSM9DS1_REG_OUT_TEMP_L              (0x15)
#define LSM9DS1_REG_OUT_TEMP_H              (0x16)
#define LSM9DS1_REG_STATUS_REG              (0x17)
#define LSM9DS1_REG_OUT_X_L_G               (0x18)
#define LSM9DS1_REG_OUT_X_H_G               (0x19)
#define LSM9DS1_REG_OUT_Y_L_G               (0x1A)
#define LSM9DS1_REG_OUT_Y_H_G               (0x1B)
#define LSM9DS1_REG_OUT_Z_L_G               (0x1C)
#define LSM9DS1_REG_OUT_Z_H_G               (0x1D)
#define LSM9DS1_REG_CTRL_REG4               (0x1E)
#define LSM9DS1_REG_CTRL_REG5_XL            (0x1F)
#define LSM9DS1_REG_CTRL_REG6_XL            (0x20)
#define LSM9DS1_REG_CTRL_REG7_XL            (0x21)
#define LSM9DS1_REG_CTRL_REG8               (0x22)
#define LSM9DS1_REG_CTRL_REG9               (0x23)
#define LSM9DS1_REG_CTRL_REG10              (0x24)
#define LSM9DS1_REG_INT_GEN_SRC_XL          (0x26)
#define LSM9DS1_REG_STATUS_REG_2            (0x27)
#define LSM9DS1_REG_OUT_X_L_XL              (0x28)
#define LSM9DS1_REG_OUT_X_H_XL              (0x29)
#define LSM9DS1_REG_OUT_Y_L_XL              (0x2A)
#define LSM9DS1_REG_OUT_Y_H_XL              (0x2B)
#define LSM9DS1_REG_OUT_Z_L_XL              (0x2C)
#define LSM9DS1_REG_OUT_Z_H_XL              (0x2D)
#define LSM9DS1_REG_FIFO_CTRL               (0x2E)
#define LSM9DS1_REG_FIFO_SRC                (0x2F)
#define LSM9DS1_REG_INT_GEN_CFG_G           (0x30)
#define LSM9DS1_REG_INT_GEN_THS_XH_G        (0x31)
#define LSM9DS1_REG_INT_GEN_THS_XL_G        (0x32)
#define LSM9DS1_REG_INT_GEN_THS_YH_G        (0x33)
#define LSM9DS1_REG_INT_GEN_THS_YL_G        (0x34)
#define LSM9DS1_REG_INT_GEN_THS_ZH_G        (0x35)
#define LSM9DS1_REG_INT_GEN_THS_ZL_G        (0x36)
#define LSM9DS1_REG_INT_GEN_DUR_G           (0x37)
#define LSM9DS1_REG_OFFSET_X_REG_L_M        (0x05)
#define LSM9DS1_REG_OFFSET_X_REG_H_M        (0x06)
#define LSM9DS1_REG_OFFSET_Y_REG_L_M        (0x07)
#define LSM9DS1_REG_OFFSET_Y_REG_H_M        (0x08)
#define LSM9DS1_REG_OFFSET_Z_REG_L_M        (0x09)
#define LSM9DS1_REG_OFFSET_Z_REG_H_M        (0x0A)
#define LSM9DS1_REG_WHO_AM_I_M              (0x0F)
#define LSM9DS1_REG_CTRL_REG1_M             (0x20)
#define LSM9DS1_REG_CTRL_REG2_M             (0x21)
#define LSM9DS1_REG_CTRL_REG3_M             (0x22)
#define LSM9DS1_REG_CTRL_REG4_M             (0x23)
#define LSM9DS1_REG_CTRL_REG5_M             (0x24)
#define LSM9DS1_REG_STATUS_REG_M            (0x27)
#define LSM9DS1_REG_OUT_X_L_M               (0x28)
#define LSM9DS1_REG_OUT_X_H_M               (0x29)
#define LSM9DS1_REG_OUT_Y_L_M               (0x2A)
#define LSM9DS1_REG_OUT_Y_H_M               (0x2B)
#define LSM9DS1_REG_OUT_Z_L_M               (0x2C)
#define LSM9DS1_REG_OUT_Z_H_M               (0x2D)
#define LSM9DS1_REG_INT_CFG_M               (0x30)
#define LSM9DS1_REG_INT_SRC_M               (0x31)  
#define LSM9DS1_REG_INT_THS_L_M             (0x32)
#define LSM9DS1_REG_INT_THS_H_M             (0x33)
/** @} */

/** WHO_AM_I value */
#define LSM9DS1_WHO_AM_I                    (0b01101010)


/**
 * @name    CTRL_x registers
 * @{
 */
#define LSM9DS1_CTRL_ODR_SHIFT              (4)
#define LSM9DS1_CTRL_ODR_MASK               (0xF0)
#define LSM9DS1_CTRL_FS_SHIFT               (2)
#define LSM9DS1_CTRL_FS_MASK                (0x0C)

#define LSM9DS1_CTRL_BDU                    (0x40)
#define LSM9DS1_CTRL_IF_INC                 (0x04)
#define LSM9DS1_CTRL_SIM                    (0x01)

#define LSM9DS1_CTRL_TEMP_EN                (0x80)
#define LSM9DS1_CTRL_FIFO_EN                (0x40)
#define LSM9DS1_CTRL_XL_EN                  (0x08)
#define LSM9DS1_CTRL_G_EN                   (0x04)
#define LSM9DS1_CTRL_M_EN                   (0x01)

#define LSM9DS1_CTRL_XL_ODR_SHIFT           (4)
#define LSM9DS1_CTRL_XL_ODR_MASK            (0xF0)
#define LSM9DS1_CTRL_XL_FS_SHIFT            (2)
#define LSM9DS1_CTRL_XL_FS_MASK             (0x0C)

#define LSM9DS1_CTRL_G_ODR_SHIFT            (4)
#define LSM9DS1_CTRL_G_ODR_MASK             (0xF0)
#define LSM9DS1_CTRL_G_FS_SHIFT             (2)
#define LSM9DS1_CTRL_G_FS_MASK              (0x0C)

#define LSM9DS1_CTRL_G_BW_SHIFT             (0)
#define LSM9DS1_CTRL_G_BW_MASK              (0x03)

#define LSM9DS1_CTRL_G_HPF_SHIFT            (0)
#define LSM9DS1_CTRL_G_HPF_MASK             (0x0F)

#define LSM9DS1_CTRL_G_HPF_EN               (0x10)

#define LSM9DS1_CTRL_G_HPF_MODE             (0x20)

#define LSM9DS1_CTRL_G_HPF_CUTOFF_SHIFT     (5)
#define LSM9DS1_CTRL_G_HPF_CUTOFF_MASK      (0xE0)

#define LSM9DS1_CTRL_M_ODR_SHIFT            (2)
#define LSM9DS1_CTRL_M_ODR_MASK             (0x1C)
#define LSM9DS1_CTRL_M_FS_SHIFT             (5)
#define LSM9DS1_CTRL_M_FS_MASK              (0xE0)

#define LSM9DS1_CTRL_M_MD_SHIFT             (0)
#define LSM9DS1_CTRL_M_MD_MASK              (0x03)

#define LSM9DS1_CTRL_M_MD_CONTINUOUS        (0x00)
#define LSM9DS1_CTRL_M_MD_SINGLE            (0x01)
#define LSM9DS1_CTRL_M_MD_POWER_DOWN        (0x03)

#define LSM9DS1_REG_CTRL_REG8_BOOT          (0x80)


/** @} */

/**
 * @name    FIFO_CTRL_x registers
 * @{
 */

#define LSM9DS1_FIFO_CTRL_FMODE_SHIFT       (5)
#define LSM9DS1_FIFO_CTRL_FMODE_MASK        (0xE0)
#define LSM9DS1_FIFO_CTRL_FTH_SHIFT         (0)
#define LSM9DS1_FIFO_CTRL_FTH_MASK          (0x1F)
/** @} */

/**
 * @brief   Offset for temperature calculation
 */
#define LSM9DS1_TEMP_OFFSET                 (25)
/**
 * @brief   Reboot wait interval in ms (15ms)
 */
#define LSM9DS1_REBOOT_WAIT                 (15)

#ifdef __cplusplus
}
#endif

#endif /* LSM9DS1_INTERNAL_H */
/** @} */
