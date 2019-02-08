#include "ScannerConfig.h"
#include "lcd_control.h"
#include "input_controls.h"
#include "motor_controls.h"

/**
 * This sketch needs the following libraries to be
 * installed.
 * 
 *  - LiquidCrystal_I2C
 *  - LiquidMenu
 *  - AccelStepper
 *  - Wire ( included in Arduino Core )
 *  - JC_Button ( for a better button debouncing )
 * 
 */

void setup() {

 Serial.begin (19200);
 initialize_encoder();
 initialize_motors();
 initialize_lcd();

}

void loop() {
  handle_inputs();
}
