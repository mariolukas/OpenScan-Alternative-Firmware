#ifndef LCD_CONTROL_H
#define LCD_CONTROL_H

#if ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif


const static PROGMEM byte uplevel[8] = {
  B00100,
  B01110,
  B11111,
  B00100,
  B11100,
  B00000,
  B00000,
  B00000
};

#include <LiquidCrystal_I2C.h>
#include <Wire.h>

/**
 * Display Action Types
 */
#define LCD_DOWN 1
#define LCD_UP 2
#define LCD_SELECT 3
#define LCD_MOTOR_EVENT 4

/**
 * Menu Screen Types
 */
#define SCREEN_TYPE_NAVIGATION 0
#define SCREEN_TYPE_SHOW_PROGRAM 1
#define SCREEN_TYPE_EDIT_VALUE 2


void displayMenu();
void initialize_lcd();
void lcd_action(uint8_t action);

#if !defined(MENU_SIZE)
    #define MENU_SIZE(x) (sizeof((x)) / sizeof((x)[0]))
#endif

extern uint8_t current_menu_type;

void initialize_lcd();

void print_menue(char **menue, byte cursor_type);

void lcd_move_down();
void lcd_move_up();
void lcd_selection();


#endif
