#ifndef PINS_FABSCAN_SHIELD_H
#define PINS_FABSCAN_SHIELD_H

#ifndef BOARD_NAME
  #define BOARD_NAME "FabScan Shield V1.1"
#endif

/*
 * Rotary Encoder 
 */
#define CLK 8
#define DT 10
#define SW 9

#define OK_BUTTON_PIN 12
#define UP_BUTTON_PIN 13
#define DOWN_BUTTON_PIN 11

#define MICROSTEP   A5

#define ENABLE_PIN_TURNTABLE 2
#define STEP_PIN_TURNTABLE 3
#define DIR_PIN_TURNTABLE 4

#define ENABLE_PIN_ROTOR 5
#define STEP_PIN_ROTOR 6
#define DIR_PIN_ROTOR 7

#endif
