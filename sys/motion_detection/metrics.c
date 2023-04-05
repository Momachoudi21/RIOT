#include "metrics.h"
#include "motion_detection.h"
#include <math.h>

#define SAMPLE_RATE 100 // in Hz

static float lsm9ds1_3d_float_data_distance(lsm9ds1_3d_float_data_t *data1, lsm9ds1_3d_float_data_t *data2)
{
  float x_diff = data1->x - data2->x;
  float y_diff = data1->y - data2->y;
  float z_diff = data1->z - data2->z;

  return sqrt(x_diff * x_diff + y_diff * y_diff + z_diff * z_diff);
}

static float motion_duration(motion_detection_event_t *event)
{
  lsm9ds1_3d_float_data_t *start_acc = &(event->start_data.acc);
  lsm9ds1_3d_float_data_t *end_acc = &(event->end_data.acc);

  return lsm9ds1_3d_float_data_distance(start_acc, end_acc) / SAMPLE_RATE;
}

static float motion_distance(motion_detection_event_t *event)
{
  lsm9ds1_3d_float_data_t *start_acc = &(event->start_data.acc);
  lsm9ds1_3d_float_data_t *end_acc = &(event->end_data.acc);

  return lsm9ds1_3d_float_data_distance(start_acc, end_acc);
}

static void motion_metrics_update(motion_metrics_t *metrics, motion_detection_event_t *event)
{
  metrics->count++;
  metrics->distance += motion_distance(event);
  metrics->frequency = metrics->count / motion_duration(event);
  metrics->speed = metrics->distance / motion_duration(event);
}

void metrics_reset(metrics_t *metrics)
{
  memset(metrics, 0, sizeof(metrics_t));
}

void metrics_update(metrics_t *metrics, motion_detection_event_t *event)
{
  switch (event->type) {
    case MOTION_UP_TO_DOWN:
      motion_metrics_update(&(metrics->up_to_down), event);
      break;
    case MOTION_DOWN_TO_UP:
      motion_metrics_update(&(metrics->down_to_up), event);
      break;
    case MOTION_RIGHT_TO_LEFT:
      motion_metrics_update(&(metrics->right_to_left), event);
      break;
    case MOTION_LEFT_TO_RIGHT:
      motion_metrics_update(&(metrics->left_to_right), event);
      break;
    case MOTION_LOOP:
      motion_metrics_update(&(metrics->loop), event);
      break;
    default:
      break;
  }
}
