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
 * @file  metrics.h
 * @brief Header file for motion metrics.
 *
 *
 * @author      Mohamed El Machoudi <momachoudi8@gmail.com>
 */

/**
 * 
 */

#ifndef METRICS_H
#define METRICS_H

#include "motion_detection.h"
#include <assert.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Structure for motion metrics.
 */
typedef struct {
  int count; /**< Number of times motion was detected. */
  float distance; /**< Total distance moved during motion. */
  float frequency; /**< Frequency of motion (in Hz). */
  float speed; /**< Average speed of motion (in m/s). */
} motion_metrics_t;

/**
 * @brief Structure for metrics for different types of motion.
 */
typedef struct {
  motion_metrics_t up_to_down; /**< Metrics for up-to-down motion. */
  motion_metrics_t down_to_up; /**< Metrics for down-to-up motion. */
  motion_metrics_t right_to_left; /**< Metrics for right-to-left motion. */
  motion_metrics_t left_to_right; /**< Metrics for left-to-right motion. */
  motion_metrics_t loop; /**< Metrics for looping motion. */
} metrics_t;

/**
 * @brief Resets the motion metrics.
 *
 * @param metrics Pointer to the motion metrics to reset.
 */
void metrics_reset(metrics_t *metrics);

/**
 * @brief Updates the motion metrics based on the specified event.
 *
 * @param metrics Pointer to the motion metrics to update.
 * @param event Pointer to the motion detection event.
 */
void metrics_update(metrics_t *metrics, motion_detection_event_t *event);

#endif

#ifdef __cplusplus
}
#endif






