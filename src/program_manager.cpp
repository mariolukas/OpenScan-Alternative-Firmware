#include "ScannerConfig.h"
#include "program_manager.h"

/*
byte time_per_photo;
unsigned byte min_vertical_angle;
byte photos_per_rotation;
byte start_angle;
*/
byte current_loaded_program;
byte current_program_angle;
byte current_program_photos;
byte current_program_positions;


pgrvalue loaded_program_values[3];

/**
 * Initialize EEPROM Values - most needed at the very first start
 */
void initialize_eeprom() {
  
  if (EEPROM.read(DEFAULT_PROGRAMS) != DEFAULTS_ARE_SET ) {

    // Not found/used in original code
    //EEPROM.write(5, 4);
    //EEPROM.write(6, 4);
    
    EEPROM.write(TIME_PER_PHOTO, 25);
    EEPROM.write(MIN_VERTICAL_ANGLE, 10);
    EEPROM.write(LAST_USED_PROGRAM, 1);
    
    EEPROM.write(PHOTOS_PER_ROTATION, 1);
    EEPROM.write(START_ANGLE, 16);
    EEPROM.write(POSITIONS, 0);

    // Number of Photos                 Angle to turn                     Motor Positions
    EEPROM.write(PROGRAM_1_PHOTOS, 16); EEPROM.write(PROGRAM_1_ANGLE, 0); EEPROM.write(PROGRAM_1_POSITIONS, 1);
    EEPROM.write(PROGRAM_2_PHOTOS, 32); EEPROM.write(PROGRAM_2_ANGLE, 0); EEPROM.write(PROGRAM_2_POSITIONS, 1);
    EEPROM.write(PROGRAM_3_PHOTOS, 64); EEPROM.write(PROGRAM_3_ANGLE, 0); EEPROM.write(PROGRAM_3_POSITIONS, 1);
    EEPROM.write(PROGRAM_4_PHOTOS, 16); EEPROM.write(PROGRAM_4_ANGLE, 25); EEPROM.write(PROGRAM_4_POSITIONS, 3);
    EEPROM.write(PROGRAM_5_PHOTOS, 16); EEPROM.write(PROGRAM_5_ANGLE, 50); EEPROM.write(PROGRAM_5_POSITIONS, 3);
    EEPROM.write(PROGRAM_6_PHOTOS, 16); EEPROM.write(PROGRAM_6_ANGLE, 75); EEPROM.write(PROGRAM_6_POSITIONS, 3);
    EEPROM.write(PROGRAM_7_PHOTOS, 16); EEPROM.write(PROGRAM_7_ANGLE, 25); EEPROM.write(PROGRAM_7_POSITIONS, 5);
    EEPROM.write(PROGRAM_8_PHOTOS, 16); EEPROM.write(PROGRAM_8_ANGLE, 50); EEPROM.write(PROGRAM_8_POSITIONS, 5);
    EEPROM.write(PROGRAM_9_PHOTOS, 16); EEPROM.write(PROGRAM_9_ANGLE, 75); EEPROM.write(PROGRAM_9_POSITIONS, 5);
    EEPROM.write(PROGRAM_10_PHOTOS, 32); EEPROM.write(PROGRAM_10_ANGLE, 25); EEPROM.write(PROGRAM_10_POSITIONS, 3);
    EEPROM.write(PROGRAM_11_PHOTOS, 32); EEPROM.write(PROGRAM_11_ANGLE, 50); EEPROM.write(PROGRAM_11_POSITIONS, 5);
    EEPROM.write(PROGRAM_12_PHOTOS, 32); EEPROM.write(PROGRAM_12_ANGLE, 75); EEPROM.write(PROGRAM_12_POSITIONS, 5);

    // we need to know that the program is already initialized 
    // for the first time.
    EEPROM.write(DEFAULT_PROGRAMS, DEFAULTS_ARE_SET);
  }
   
}

/**
 * Save a program by number
 */
void set_program(byte program_number){
  EEPROM.write((program_number-1) *3 + FIRST_PORGAM_POSITION, current_program_photos);
  EEPROM.write((program_number-1) *3 + FIRST_PORGAM_POSITION + 1, current_program_angle);
  EEPROM.write((program_number-1) *3 + FIRST_PORGAM_POSITION + 2, current_program_positions);
}

/**
 * Load a Pogram by number
 */
void load_program(byte program_number){

   // Number of Photos
   loaded_program_values[0] = { EEPROM.read((program_number-1) *3 + FIRST_PORGAM_POSITION), 0, 100 };
   // Angle
   loaded_program_values[1] = { EEPROM.read((program_number-1) *3 + FIRST_PORGAM_POSITION + 1 ), 0, 100 };
   // Positions
   loaded_program_values[2] = { EEPROM.read((program_number-1) *3 + FIRST_PORGAM_POSITION + 2 ), 0, 100 };
   
   current_loaded_program = program_number;
}

/**
 * Load single Value from EEPROM
 */
byte load_value(byte value){
  return EEPROM.read(value);
}

/**
 * Save single Value to EEPROM
 */
void save_value(byte pos, byte value){
  EEPROM.write(pos, value);  
}

/**
 * Load Default settings
 */
void restore_default_settings(){
     EEPROM.write(DEFAULT_PROGRAMS, 0);
     initialize_eeprom();
}
