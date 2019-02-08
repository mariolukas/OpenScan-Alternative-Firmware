#include "ScannerConfig.h"
#include "input_controls.h"
#include "lcd_control.h"
//#include "Button.h"
#include <JC_Button.h> 

boolean up = false;
boolean turned = false;

#ifdef USE_BUTTONS

/*
const bool pullup = true;
Button up_button(UP_BUTTON_PIN, pullup);
Button down_button(DOWN_BUTTON_PIN, pullup);
Button ok_button(OK_BUTTON_PIN, pullup);
*/


Button up_button(UP_BUTTON_PIN, 50);
Button down_button(DOWN_BUTTON_PIN,50);
Button ok_button(OK_BUTTON_PIN, 50);
 
#endif


void initialize_encoder(){
  Serial.println("Encoder Pins initialized");

  ok_button.begin();
  down_button.begin();
  up_button.begin();
  
  #ifdef USE_ROTARY_ENCODER
    // Encoder
    pinMode(CLK, INPUT);
    pinMode(DT, INPUT);
    pinMode(SW, INPUT_PULLUP);
  #endif


}

/**
 * Rotary Encoder 
 */
void read_encoder() {
  static bool block;
 
  bool M_CLK = digitalRead(CLK);
  bool M_DT = digitalRead(DT);
  bool M_SW = !digitalRead(SW);
  
  if(M_SW && !block) //Taster
  {
    block = true;

    Serial.print(F("RESET "));

  }
  else if(!M_SW && block)
  {
    block = false;
  }
  
  if (!M_CLK && !turned) //rechts
  {
    turned = true;
    up = false;
  }
  else if (!M_DT && !turned) //links
  {
    turned = true;
    up = true;
  }
  
  if (M_CLK && M_DT && turned) //Grunstellung
  {
    turned = false;
  }
}

void handle_inputs(){

  #ifdef USE_BUTTONS
    ok_button.read();
    up_button.read();
    down_button.read();
    
    if (ok_button.wasReleased()) {
       lcd_action(LCD_SELECT);
    }
    
    if (up_button.wasReleased()) {
        lcd_action(LCD_UP);
    }

    if (down_button.wasReleased()) {
       lcd_action(LCD_DOWN);
    }

  #endif

  #ifdef USE_ROTARY_ENCODER
    read_encoder();
  #endif
}
  
