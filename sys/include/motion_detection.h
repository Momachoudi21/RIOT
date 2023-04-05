/*
 * Copyright (C) 2023 Polytech Orleans
 *
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License v2.1. See the file LICENSE in the top level
 * directory for more details.
 */

/**
 * @defgroup    sys_motion_detection motion_detection
 * @ingroup     sys
 * @brief       motion detection library
 *
 * @{
 *
 * @file motion_detection.h
 * @brief Header file for motion detection system.
 *
 * @author      Mohamed El Machoudi <momachoudi8@gmail.com>
 */


#ifndef MOTION_DETECTION_H
#define MOTION_DETECTION_H

#include "lsm9ds1.h"
#include <assert.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Enumeration of different types of motion.
 */
typedef enum {
  MOTION_UP_TO_DOWN, /**< Motion from up to down. */
  MOTION_DOWN_TO_UP, /**< Motion from down to up. */
  MOTION_RIGHT_TO_LEFT, /**< Motion from right to left. */
  MOTION_LEFT_TO_RIGHT, /**< Motion from left to right. */
  MOTION_LOOP /**< Looping motion. */
} motion_type_t;

/**
 * @brief Structure for 3D float data.
 */
typedef struct {
  float x; /**< X coordinate. */
  float y; /**< Y coordinate. */
  float z; /**< Z coordinate. */
} lsm9ds1_3d_float_data_t;

/**
 * @brief Structure for motion data from LSM9DS1 sensor.
 */
typedef struct {
  lsm9ds1_3d_float_data_t acc; /**< Accelerometer data. */
  lsm9ds1_3d_float_data_t gyro; /**< Gyroscope data. */
  lsm9ds1_3d_float_data_t mag; /**< Magnetometer data. */
} lsm9ds1_motion_data_t;

/**
 * @brief Structure for motion detection configuration parameters.
 */
typedef struct {
  float threshold; /**< Minimum motion value for detection. */
  int nbr_sample; /**< Number of readings required for detection. */
} motion_detection_config_t;

/**
 * @brief Structure for motion detection events.
 */
typedef struct {
  motion_type_t type; /**< Type of motion detected. */
  lsm9ds1_motion_data_t start_data; /**< Motion data at start of event. */
  lsm9ds1_motion_data_t end_data; /**< Motion data at end of event. */
} motion_detection_event_t;

/**
 * @brief Function pointer type for motion detection callback functions.
 *
 * @param event Pointer to the motion detection event.
 */
typedef void (*motion_detection_callback_t)(motion_detection_event_t *event);

/**
 * @brief Initializes the motion detection system with the specified configuration.
 *
 * @param config Configuration parameters for motion detection.
 */
void motion_detection_init(motion_detection_config_t config);

/**
 * @brief Registers a callback function to be called when motion is detected.
 *
 * @param callback Callback function to register.
 */
void motion_detection_register_callback(motion_detection_callback_t callback);

/**
 * @brief Starts the motion detection system.
 */
void motion_detection_start(void);

/**
 * @brief Stops the motion detection system.
 */
void motion_detection_stop(void);

#endif

#ifdef __cplusplus
}

#endif /* MOTION_DETECTION_H */
/** @} */













/
