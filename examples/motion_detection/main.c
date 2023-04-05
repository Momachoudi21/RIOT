/*
 * Copyright (C) 2023 Orange
 *
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License v2.1. See the file LICENSE in the top level
 * directory for more details.
 */

/**
 * @ingroup     examples
 * @{
 *
 * @file
 * @brief       Application to test the motion detection library
 *
 * @author      Mohamed El Machoudi <momachoudi8@gmail.com>
 *
 * @}
 */

#include <stdio.h>
#include "motion_detection.h"
#include "metrics.h"

static metrics_t metrics;

// 

static void motion_detection_callback(motion_detection_event_t *event)
{
  printf("Motion event detected: type=%d\n", event->type);

  metrics_update(&metrics, event);
}

int main(void)
{
  motion_detection_config_t config = {
    .threshold = 0.1,
    .debounce_count = 5
  };

  motion_detection_init(config);
  motion_detection_register_callback(motion_detection_callback);
  motion_detection_start();

  while (1) {
    // Print metrics every second
    printf("Metrics:\n");
    printf("  Up to down: count=%d, distance=%.2f, frequency=%.2f, speed=%.2f\n",
           metrics.up_to_down.count, metrics.up_to_down.distance,
           metrics.up_to_down.frequency, metrics.up_to_down.speed);
    printf("  Down to up: count=%d, distance=%.2f, frequency=%.2f, speed=%.2f\n",
           metrics.down_to_up.count, metrics.down_to_up.distance,
           metrics.down_to_up.frequency, metrics.down_to_up.speed);
    printf("  Right to left: count=%d, distance=%.2f, frequency=%.2f, speed=%.2f\n",
           metrics.right_to_left.count, metrics.right_to_left.distance,
           metrics.right_to_left.frequency, metrics.right_to_left.speed);
    printf("  Left to right: count=%d, distance=%.2f, frequency=%.2f, speed=%.2f\n",
           metrics.left_to_right.count, metrics.left_to_right.distance,
           metrics.left_to_right.frequency, metrics.left_to_right.speed);
    printf("  Loop: count=%d, distance=%.2f, frequency=%.2f, speed=%.2f\n",
           metrics.loop.count, metrics.loop.distance,
           metrics.loop.frequency, metrics.loop.speed);

    xtimer_sleep(1);
  }

  return 0;
}
