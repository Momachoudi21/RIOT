motion_detection
================

Application to test the motion detection library

Usage
=====

This is a simple application designed to demonstrate the use of the motion detection library. The main function initializes the motion detection system with a configuration containing a minimum threshold value for motion detection and the number of readings required to confirm the detection of motion. It then registers a callback function that is called whenever motion is detected. The application continuously runs a loop that prints the metrics calculated by the motion detection library.

The metrics include the number of times a particular type of motion was detected, the total distance covered by the motion, the frequency of the motion events, and the average speed of the motion events.

The application uses the xtimer_sleep function to delay the execution of the loop for one second. This delay ensures that the metrics are printed every second, providing real-time information on the detected motion.
