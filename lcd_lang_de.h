#ifndef __LCD_LANG_DE_H__
#define __LCD_LANG_DE_H__

/***
 * HINT: Navigation Menues need an amount of spaces in front of the 
 * Menu Entry, for showing the slector icon. 
 */

#include <avr/pgmspace.h>

#ifndef LANGUAGE
  #define LANGUAGE "Deutsch"
#endif

// Main Menu 
#define MAIN_MENU_HEADER " -- Haupt Menue --"
#define MAIN_MENU_START_PROGRAM  "   Programm starten"
#define MAIN_MENU_SETTINGS "   Einstellungen"

// Program Menu
#define PROGAM_MENU_HEADER "-- Programm Menue --"
#define PROGRAM_MENU_RUN_LAST "   Letztes Programm"
#define PROGRAM_MENU_LOAD_PROGRAM "   Programm laden"

// Settings Menu
#define SETTINGS_MENU_HEADER " -- Einstellungen --"
#define SETTINGS_MENU_TIME_PER_PHOTO "   Zeit pro Bild"
#define SETTINGS_MENU_MODIFY_PROGRAM "   Proramm aendern"
#define SETTINGS_MENU_MIN_VERT_ANGLE "   Min. vert. Winkel"

// Program value menu
#define PROGRAM_VALUE_MENU_HEADER "Programm"
#define PROGRAM_VALUE_MENU_PHOTOS "Bilder:"
#define PROGRAM_VALUE_MENU_ANGLE "Winkel:"
#define PROGRAM_VALUE_MENU_POSITIONS "Positionen:"

// Edit Menu
#define EDIT_MENU_HEADER_TIME_PER_PHOTO "Zeit pro Bild"
#define EDIT_MENU_HEADER_PHOTOS "Anzahl Bilder"
#define EDIT_MENU_HEADER_ANGLE "Winkel Einstellen"
#define EDIT_MENU_HEADER_
#define EDIT_MENU_HEADER "Wert editieren"
#define EDIT_MENU_NEW_VALUE "Neuer Wert:"
#define EDIT_CURRENT_VALUE "Aktueller Wert:"
#define EDIT_MAX_MIN_VALUE "Min.     Max. "

// Confirmation Menu
#define CONFIRM_MENU_HEADER "Speichern?"
#define CONFIRM_MENU_YES "   Ja"
#define CONFIRM_MENU_NO "   Nein"

#define BACK_LINE "   Zurueck"

#endif
