#include "ScannerConfig.h"
#include "motor_controls.h"
#include "program_manager.h"
#include "lcd_control.h"
#include "input_controls.h"

bool stop_program = false;
int current_progress = 0;
byte start_angle = load_value(START_ANGLE); 
byte positions = load_value(POSITIONS);
byte fotos_per_rotation = load_value(PHOTOS_PER_ROTATION);
byte min_vertical_angle = load_value(MIN_VERTICAL_ANGLE);
int total_photos = 0;

AccelStepper Turntable(1, STEP_PIN_TURNTABLE, DIR_PIN_TURNTABLE);
AccelStepper Rotor(1, STEP_PIN_ROTOR, DIR_PIN_ROTOR);

void initialize_motors(){

  Turntable.setMaxSpeed(TURNTABLE_MAX_SPEED);
  Turntable.setAcceleration(TURNTABLE_ACCELERATION);
  Turntable.setCurrentPosition(0);
  
  Rotor.setMaxSpeed(ROTOR_MAX_SPEED);
  Rotor.setAcceleration(ROTOR_ACCELERATION);
  Rotor.setCurrentPosition(0);

}

bool take_picture(){
    handle_inputs();
    current_progress += 1;
    lcd_action(LCD_MOTOR_EVENT);

    if !stop_program
      return true
    else
      return false
    /*
      digitalWrite(photopin1, HIGH);
      delay(releasetime);
      delay(100);
      digitalWrite(photopin1, LOW);
      delay(TpF);
    */
}


void start_motor_program(byte program) {
    load_program(LAST_USED_PROGRAM);
    
    Turntable.setCurrentPosition(0);
    Rotor.setCurrentPosition(0);
    
    current_progress = 0;
    Rotor.runToNewPosition(-start_angle); // COUNT PHOTOS ///////////////////////////////////////////////////////////////
      for (int j = 0; j < positions; j = j + 1) {
      if((j!=0) && (positions!=1)){
        int i = 1;
        while(-start_angle+2*start_angle/(positions-1)*(j-1)+i*min_vertical_angle<=-start_angle+2*start_angle/(positions-1)*j){
          handle_inputs();
          total_photos += 1;
          i= i+1;
        }
        };

      for (int i = 0; i < fotos_per_rotation; i = i + 1) {
        total_photos += 1;

      }
    }
    stop_program=false;
      for (int j = 0; j < positions && !stop_program; j = j + 1) {
      handle_inputs();
      if((j!=0) && (positions!=1)){
        int i = 1;
        while(-start_angle+2*start_angle/(positions-1)*(j-1)+i*min_vertical_angle<=-start_angle+2*start_angle/(positions-1)*j && !stop_program){
          Rotor.runToNewPosition(-start_angle+2*start_angle/(positions-1)*(j-1)+i*min_vertical_angle);
          if !take_picture() break;
          i= i+1;
        }
        if(!stop_program){
          Rotor.runToNewPosition(-start_angle+2*start_angle/(positions-1)*j);
        }
        };

      for (int i = 0; i < fotos_per_rotation&& !stop_program; i = i + 1) {
        handle_inputs();
        Turntable.runToNewPosition(TURNTABLE_STEPS_PER_FULL_TURN/fotos_per_rotation*i);

        if !take_picture() break;

      }
      if(!stop_program){
        Turntable.runToNewPosition(TURNTABLE_STEPS_PER_FULL_TURN);
      }
      Turntable.setCurrentPosition(0);
    }

    Turntable.setCurrentPosition(0);
    Turntable.runToNewPosition(0);
    
}
