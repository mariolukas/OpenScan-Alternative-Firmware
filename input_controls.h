#ifndef INPUT_CONTROLS_H
#define INPUT_CONTROLS_H

#if ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

void handle_inputs();

// rotary encoder
void initialize_encoder();


extern boolean up;
extern boolean turned;

extern bool current_ok_button_state;
extern bool current_down_button_state;
extern bool current_up_button_state;


#endif
