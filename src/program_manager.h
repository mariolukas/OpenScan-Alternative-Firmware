#ifndef PROGRAM_MANAGER_H
#define PROGRAM_MANAGER_H

#include <EEPROM.h>

#if ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

/**
 * holds currently loaded progam
 * values.
 */

typedef struct{
  byte value;
  byte maximum;
  byte minimum;
} pgrvalue;

extern pgrvalue loaded_program_values[3];
extern byte current_loaded_program;
extern byte current_program_angle;
extern byte current_program_photos;
extern byte current_program_positions;

byte load_value(byte value);

void save_value(byte pos, byte value);

/**
 * load a program by number
 */
void load_program(byte program_number);

/**
 * save a program by number
 */
void save_program(byte program_number);

#define DEFAULTS_ARE_SET 42

#define DEFAULT_PROGRAMS 0
#define TIME_PER_PHOTO 4
#define MIN_VERTICAL_ANGLE 7

#define PHOTOS_PER_ROTATION 100
#define START_ANGLE 101
#define POSITIONS 102

#define FIRST_PORGAM_POSITION 8

// one c
#define NUMBER_OF_PROGRAMS 12

#define LAST_USED_PROGRAM 103
/**
 * Program slots in memory
 */
#define PROGRAM_1_PHOTOS 8
#define PROGRAM_1_ANGLE 9
#define PROGRAM_1_POSITIONS 10

#define PROGRAM_2_PHOTOS 11
#define PROGRAM_2_ANGLE 12
#define PROGRAM_2_POSITIONS 13

#define PROGRAM_3_PHOTOS 14
#define PROGRAM_3_ANGLE 15
#define PROGRAM_3_POSITIONS 16

#define PROGRAM_4_PHOTOS 17
#define PROGRAM_4_ANGLE 18
#define PROGRAM_4_POSITIONS 19

#define PROGRAM_5_PHOTOS 20
#define PROGRAM_5_ANGLE 21
#define PROGRAM_5_POSITIONS 22

#define PROGRAM_6_PHOTOS 23
#define PROGRAM_6_ANGLE 24
#define PROGRAM_6_POSITIONS 25

#define PROGRAM_7_PHOTOS 26
#define PROGRAM_7_ANGLE 27
#define PROGRAM_7_POSITIONS 28

#define PROGRAM_8_PHOTOS 29
#define PROGRAM_8_ANGLE 30
#define PROGRAM_8_POSITIONS 31

#define PROGRAM_9_PHOTOS 32
#define PROGRAM_9_ANGLE 33
#define PROGRAM_9_POSITIONS 34

#define PROGRAM_10_PHOTOS 35
#define PROGRAM_10_ANGLE 36
#define PROGRAM_10_POSITIONS 37

#define PROGRAM_11_PHOTOS 38
#define PROGRAM_11_ANGLE 39
#define PROGRAM_11_POSITIONS 40

#define PROGRAM_12_PHOTOS 41
#define PROGRAM_12_ANGLE 42
#define PROGRAM_12_POSITIONS 43

#endif
