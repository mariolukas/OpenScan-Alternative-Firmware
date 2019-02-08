#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#define DEBUG 1
/*
 * The following define selects which electronics board you have.
 * Please choose the name from boards.h that matches your setup.
 * Some possible Values are:
 * 
 * BOARD_DEFAULT       - Default Board made by Thomas.
 * BOARD_FABSCAN_SHIELD   - FabScan Arduino Shield with up to 3 Motor Drivers
 * 
 */

 
#ifndef MOTHERBOARD
  #define MOTHERBOARD BOARD_FABSCAN_SHIELD
#endif

/*
 * LCD 
 */
#ifndef LANGUAGE
  #define LANG_DE
#endif

#define LCD_ADRESS 0x27
#define LCD_MAXLINES 4    // defines the number of display lines
#define LCD_CHARACTERS 20


/**
 * Stepper Motor Setup
 */
#define ROTOR_MAX_SPEED 5000
#define ROTOR_ACCELERATION 1000
#define ROTOR_STEPS_PER_FULL_TURN 3200

#define TURNTABLE_MAX_SPEED 1000
#define TURNTABLE_ACCELERATION 200
#define TURNTABLE_STEPS_PER_FULL_TURN 3200

/**
 * INPUT CONFIG
 */
#define USE_BUTTONS 1
#define DEBOUNCE_DELAY 10000
//#define USE_ROTARY_ENCODER 1


#define TURN_BLOCKING 1
#define TURN_NON_BLOCKING 0

#define MAX_FEEDRATE         (2000)
#define MIN_FEEDRATE         (1000)

#define MAX_BUF        64

#endif
