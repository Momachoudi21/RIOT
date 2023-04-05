/*
 * Copyright (C) 2023 Polytech Orleans
 *
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License v2.1. See the file LICENSE in the top level
 * directory for more details.
 */

/**
 * @ingroup     module_motion_detection
 * @{
 *
 * @file
 * @brief       motion_detection implementation
 *
 * @author      Mohamed El Machoudi <momachoudi8@gmail.com>
 *
 * @}
 */


#include "motion_detection.h"
#include "lsm9ds1.h"
#include "lsm9ds1_params.h"
#include "xtimer.h"

#define ACCELEROMETER_THRESHOLD 0.1
#define GYROSCOPE_THRESHOLD 1.0

#define NBR_SAMPLE 5

static motion_detection_config_t config;
static motion_detection_callback_t callback;

static void motion_detection_task(void *arg ) {

  lSM9DS1_t dev;
  lSM9DS1_params_t params;
  lsm9ds1_init(&dev, &params);
  lsm9ds1_motion_data_t prev_data = {0};
  int debounce_counter = 0;

  while (1) {
    lsm9ds1_motion_data_t data = {0};
    lsm9ds1_read_acc(&dev, &data.acc);
    lsm9ds1_read_gyro(&dev, &data.gyro);
    lsm9ds1_read_mag(&dev, &data.mag);

    if (config.threshold > 0) {
      // Check for vertical movement
      if (data.acc.y - prev_data.acc.y > config.threshold) {
        if (callback && debounce_counter == 0) {
          motion_detection_event_t event = {
            .type = MOTION_UP_TO_DOWN,
            .start_data = prev_data,
            .end_data = data
          };
          callback(&event);
          debounce_counter = config.nbr_sample;
        }
      } else if (prev_data.acc.y - data.acc.y > config.threshold) {
        if (callback && debounce_counter == 0) {
          motion_detection_event_t event = {
            .type = MOTION_DOWN_TO_UP,
            .start_data = prev_data,
            .end_data = data
          };
          callback(&event);
          debounce_counter = config.nbr_sample;
        }
      }

      // Check for horizontal movement
      if (data.gyro.z - prev_data.gyro.z > GYROSCOPE_THRESHOLD) {
        if (callback && debounce_counter == 0) {
          motion_detection_event_t event = {
            .type = MOTION_RIGHT_TO_LEFT,
            .start_data = prev_data,
            .end_data = data
          };
          callback(&event);
          debounce_counter = config.nbr_sample;
        }
      } else if (prev_data.gyro.z - data.gyro.z > GYROSCOPE_THRESHOLD) {
        if (callback && debounce_counter ==0){

            motion_detection_event_t event = {
                .type = MOTION_LEFT_TO_RIGHT,
                .start_data = prev_data,
                .end_data = data
            };
            callback(&event);
            debounce_counter = config.nbr_sample;

        }

      // Check for circular movement
      if ((prev_data.acc.x - data.acc.x) * (prev_data.acc.x - data.acc.x) +
          (prev_data.acc.y - data.acc.y) * (prev_data.acc.y - data.acc.y) +
          (prev_data.acc.z - data.acc.z) * (prev_data.acc.z - data.acc.z) >
          ACCELEROMETER_THRESHOLD * ACCELEROMETER_THRESHOLD &&
          (prev_data.gyro.x - data.gyro.x) * (prev_data.gyro.x - data.gyro.x) +
          (prev_data.gyro.y - data.gyro.y) * (prev_data.gyro.y - data.gyro.y) +
          (prev_data.gyro.z - data.gyro.z) * (prev_data.gyro.z - data.gyro.z) >
          GYROSCOPE_THRESHOLD * GYROSCOPE_THRESHOLD) {
        if (callback && debounce_counter == 0) {
          motion_detection_event_t event = {
            .type = MOTION_LOOP,
            .start_data = prev_data,
            .end_data = data
          };
          callback(&event);
          debounce_counter = config.nbr_sample;
        }
      }
    }

    prev_data = data;

    if (debounce_counter > 0) {
      debounce_counter--;
    }

    // Sleep for 10 milliseconds
    xtimer_usleep(10000);
  }
}


static kernel_pid_t motion_detection_task_pid;

void motion_detection_init(motion_detection_config_t config)
{
  motion_detection_stop();

  motion_detection_task_pid = thread_create_stacksize("motion_detection", motion_detection_task,
                                                       NULL, THREAD_STACKSIZE_DEFAULT, THREAD_PRIORITY_MAIN - 1);
  if (motion_detection_task_pid <= KERNEL_PID_UNDEF) {
    return;
  }

  motion_detection_start();
}


void motion_detection_register_callback(motion_detection_callback_t callback)
{
  motion_detection_stop();

  callback = callback;

  motion_detection_start();
}

void motion_detection_start(void)
{
  if (motion_detection_task_pid > KERNEL_PID_UNDEF) {
    thread_wakeup(motion_detection_task_pid);
  }
}

void motion_detection_stop(void)
{
  if (motion_detection_task_pid > KERNEL_PID_UNDEF) {
    thread_sleep(motion_detection_task_pid);
  }
}
