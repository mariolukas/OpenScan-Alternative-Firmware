#include "ScannerConfig.h"
#include "lcd_control.h"
#include "input_controls.h"
#include "program_manager.h"
#include "motor_controls.h"

LiquidCrystal_I2C lcd(LCD_ADRESS,LCD_CHARACTERS,LCD_MAXLINES);
const int arraySize = 20;

int selected; // currently selected menu item
uint8_t current_value = 1;
uint8_t max_value;
uint8_t min_value;
uint8_t eeprom_value_offset = 0;

/**
 * General used Variables
 */
char* current_menu[arraySize] = {0};
char* line_buffer[] = {};
uint8_t current_menu_index = 0; // current position in the array
uint8_t current_menu_size;
uint8_t current_menu_type = SCREEN_TYPE_NAVIGATION;
bool page_change = false;
uint8_t menu_top = 0; // top space between title and items

/**
 * Function pointers for Menu actions
 */
typedef void (* CurrentFuncPtr) (); // Function pointer for current menu
typedef void (* MenuFuncPtr) (); // Function pointer for Main Menu
typedef void (* SettingsMenuFuncPtr) (); // Function pointer for Test Menu 1
typedef void (* ProgramFuncPtr) (); // Function pointer for Test Menu 2
typedef void (* ProgramViewFuncPtr) (); // Function pointer for Test Menu 2
typedef void (* ProgramEditFuncPtr) ();
typedef void (* ProgramModifyFuncPtr) ();
typedef void (* ConfirmViewFuncPtr) ();
typedef void (* ProgramCancelFuncPrt) ();


/**
 * Render Menu FUnction 
 */
void setMenu(char** menu, CurrentFuncPtr* funcs, uint8_t size);
void showSettingsMenu(void);
void showProgramMenu(void);
void loadProgamMenu(void);
void returnMainMenu(void);
void showEditValueMenu(void);
void showConfirmMenu(void);
void startLastProgram(void);
void stopRunningProgram(void);


CurrentFuncPtr* current_func = NULL;


/**
 * Defines the Main Menu and it callback funcitons
 */
char* mainMenu[2] = {
                     MAIN_MENU_START_PROGRAM,
                     MAIN_MENU_SETTINGS
                    };


/**
 * Defines a SubMenu of the Main Menu Settings.
 */
char* settingsMenu[4] = {
                          SETTINGS_MENU_MODIFY_PROGRAM,
                          SETTINGS_MENU_TIME_PER_PHOTO,
                          SETTINGS_MENU_MIN_VERT_ANGLE,
                          BACK_LINE
                        };

/**                        
 * Defines a SubMenu of Main Menu                       
 */
char* programMenu[3] = {
                        PROGRAM_MENU_RUN_LAST,
                        PROGRAM_MENU_LOAD_PROGRAM,
                        BACK_LINE
                       };


/***                   
 *  Defines a Program Menu Entry, used for showing
 *  current Program Values.
 */
char* programView[4] = {
                        PROGRAM_VALUE_MENU_HEADER,
                        PROGRAM_VALUE_MENU_PHOTOS,
                        PROGRAM_VALUE_MENU_ANGLE,
                        PROGRAM_VALUE_MENU_POSITIONS
                       };

/***                                    
 *  Confirmation Menu. Used for User Confirmations.                                  
 */
char *confirmMenu[3] = {
             CONFIRM_MENU_HEADER,
             CONFIRM_MENU_YES,
             CONFIRM_MENU_NO
};

char *progressMenu[2] = {};

/***
 * Callback Functions for Menues
 */
MenuFuncPtr menu_func[3] = {
                            showProgramMenu,
                            showSettingsMenu
                           };

SettingsMenuFuncPtr settings_menu_func[5] = {
                                                loadProgamMenu,
                                             0,
                                            0,
                                             returnMainMenu
                                            };

ProgramFuncPtr program_menu_func[4] = {
                                         startLastProgram,
                                         loadProgamMenu,
                                         returnMainMenu
                                       };


/**
 * Defines the Program value menu and its callback functions
 */


ConfirmViewFuncPtr confirm_view_func[4] = {
                                            0,
                                            returnMainMenu,
                                            returnMainMenu,
                                          };

ProgramViewFuncPtr program_view_func[5] = {
                                            showProgramMenu,
                                            0,
                                            0,
                                             returnMainMenu
                                           };

                                         
ProgramModifyFuncPtr program_modidy_func[5] = {
                                            showEditValueMenu,
                                            showEditValueMenu,
                                            0,
                                             0,
                                           };

ProgramEditFuncPtr program_edit_func[5] = {
                                            showConfirmMenu,
                                            showConfirmMenu,
                                            0,
                                            0,
                                           };

ProgramCancelFuncPrt program_cancel_func[2] = {
                                            stopRunningProgram
                                            };
/**
 * Initializing of the LCD Display. 
 */
void initialize_lcd(){

  Wire.begin(); 
  for(byte add = 1; add < 127; add++ ) {
    Wire.beginTransmission(add);
    byte error = Wire.endTransmission();
 
    if (error == 0) { 
      int I2C=add;
      add=128;
    }
  }
  
  lcd.init();
  lcd.backlight();
  lcd.home ();

  lcd.clear();
  lcd.setCursor(5,0);
  lcd.print(F("3D Scanner"));
  lcd.setCursor(2,1);
  lcd.print(F("Firmware Version"));
  lcd.setCursor(2,2);
  lcd.print(F(BUILD_VERSION));
  delay(1000);
  
  lcd.clear();

  setMenu(mainMenu, menu_func, sizeof(mainMenu)/sizeof(char *)-1);
  displayMenu();

}

/***
 * Helper Funciton to define current used menu and 
 * setting the callbak funciton array.
 */
void setMenu(char** menu, CurrentFuncPtr* funcs, uint8_t size) {
  memset(current_menu, 0, arraySize);

  current_func = funcs;
  int i;
  for(i=0; i<=size; i++) {
    current_menu[i] = menu[i];
  }
  selected = 0;
  current_menu_size = i-2;
}


/**
 * Thit function is used for showing the current 
 * Program stae if the motor is running.
 */

void updateRunningState(){
    lcd.setCursor(2, 1);
    lcd.print("Photo ");
    lcd.print(current_progress);
    lcd.print(" of ");
    lcd.print(total_photos);
    
    lcd.setCursor(3,3);
    lcd.print("Abbrechen [OK]");    
}

/***
 * Update Funciton for Program Menus
 * is used for changing program values and 
 * rendering Program Views.
 */
void updateMenuProgram(uint8_t index){
  
  byte value_position = 0;
  
  switch(current_menu_type){
    
    case SCREEN_TYPE_SHOW_PROGRAM:

      value_position = strlen(current_menu[index])+1;
    
      lcd.setCursor(value_position,index);
      lcd.print(current_value);
      lcd.setCursor(value_position+2, index);
      lcd.print("/");
      lcd.setCursor(value_position+3, index);
      lcd.print(max_value);
      
      load_program(current_value);
      
      for(uint8_t i=0; i<=2; i++){
          value_position = strlen(current_menu[i+1])+1;
          lcd.setCursor(value_position,i+1);
          lcd.print(loaded_program_values[i].value);
      }
      
    break;

    /**
     * This menu type is generic and is build during runtime. 
     * There is no pedefined Menu Array. The Menu Text results
     * from the previous menu screen.
     * TODO: If there is eno
     */
    case SCREEN_TYPE_EDIT_VALUE:
    
        lcd.clear();
        lcd.setCursor(0,1);
        lcd.print(current_menu[eeprom_value_offset]);
        value_position = strlen(current_menu[eeprom_value_offset])+4;

        lcd.setCursor(value_position,1);
        lcd.print(current_value);
    
    break;
    
  }
}

/****
 * Sets the Cursor Position in Navigation Menus 
 * (e.g. Main Menu, Settings Menu, Confirmation...)
 */
void menuSetNavigationCursor(uint8_t index) {
  if (page_change == false) {
      lcd.setCursor(0, (selected - current_menu_index));
      lcd.print(current_menu[selected]);
  }
  lcd.setCursor(0, (index - current_menu_index)+menu_top );
  lcd.print("->");
  selected = index+menu_top;
  page_change = false;
}

/***
 * General Menu Render Funciton. Shows a Menu
 * and is used for triggering the update Program Menu
 */
void displayMenu() {
  uint8_t i;
  lcd.clear();
  lcd.setCursor(0, 0);

  for(i = current_menu_index; i <= (current_menu_index+4); i++) {
      lcd.setCursor(0, (i - current_menu_index));
      lcd.print(current_menu[i]);
  }

  switch(current_menu_type){
      case SCREEN_TYPE_NAVIGATION:
        menuSetNavigationCursor(selected);
      break;

      case SCREEN_TYPE_EDIT_VALUE:
      case SCREEN_TYPE_SHOW_PROGRAM:
        updateMenuProgram(selected);
      break;
      
  }

}

/**
 * Edit Values Function. This Function does not work 
 * like all other Menu Funnctions. Here the function 
 * pointers are set manually, deinded by the current
 * value position which should be changed.
 */
void showEditValueMenu(void){

  if (eeprom_value_offset == 3) {
      showConfirmMenu();
  
  } else {
      current_menu_type = SCREEN_TYPE_EDIT_VALUE;
    
      current_value = loaded_program_values[eeprom_value_offset].value;
      max_value = loaded_program_values[eeprom_value_offset].maximum;
      min_value = loaded_program_values[eeprom_value_offset].minimum;
      
      if (eeprom_value_offset <= 2){
         current_func = program_modidy_func;  
         eeprom_value_offset++;   
      } else {
         current_func = program_edit_func;
         eeprom_value_offset = 0;
      }
    
      selected = 0;
      updateMenuProgram(selected);
  }

}

/**
 * Stop Running Program 
 */

void stopRunningProgram(void){
  stop_program = true;
  returnMainMenu();
}

/***
 * Start Last Program 
 */
void startLastProgram(void){
  selected = 0;
  current_func = program_cancel_func;
  lcd.clear();
  updateRunningState();
  start_motor_program(1);
  
}


/***
 * Load Program Menu, Used for Program Menu Selection
 * and modifing a Program.
 */
void loadProgamMenu(void){
    
  current_value = 1;
  max_value = 12;
  min_value = 1;

  current_menu_type = SCREEN_TYPE_SHOW_PROGRAM;

  // Previous Menu was Settings Menu
  if(current_func == settings_menu_func){
     setMenu(programView, program_modidy_func, sizeof(programView)/sizeof(char *)-1);
     selected = 0;
  };

  // Previous Menu was Program Menu
  if(current_func == program_menu_func){
     setMenu(programView, program_view_func, sizeof(programView)/sizeof(char *)-1);
     selected = 0;
  }

  displayMenu();  
}

/***
 * Confirmation Menu. Used to confirm yes/no an action
 */
void showConfirmMenu(void){
  eeprom_value_offset = 0;
  menu_top =1;
  current_menu_type = SCREEN_TYPE_NAVIGATION;
  setMenu(confirmMenu, confirm_view_func, sizeof(confirmMenu)/sizeof(char *)-1);
  displayMenu();
}

/**
 * Show Program Menu - Used for first Entry in Main Menu
 */
void showProgramMenu(void) {
  current_menu_type = SCREEN_TYPE_NAVIGATION;
  setMenu(programMenu, program_menu_func, sizeof(programMenu)/sizeof(char *)-1);
  displayMenu();
}

/**
 * Show Settings Menu - Uesed for seconf Entry in Main Menu
 */
void showSettingsMenu(void) {
  current_menu_type = SCREEN_TYPE_NAVIGATION;
  setMenu(settingsMenu, settings_menu_func, sizeof(settingsMenu)/sizeof(char *)-1);
  displayMenu();
}


/***
 * Jump Back Function for returning to a previous Menu.
 */
void returnMainMenu(void) {
  menu_top = 0;
  current_menu_type = SCREEN_TYPE_NAVIGATION;
  setMenu(mainMenu, menu_func, sizeof(mainMenu)/sizeof(char *)-1);
  displayMenu();
}


/***
 * Button Event Functions.
 * This is called by the buton controller and defines the display
 * actions when UP/DOWN/OK Button was triggered.
 */

void lcd_action(uint8_t action) {
  switch (action) {
      case LCD_UP: { // up

        switch(current_menu_type){
          
          case SCREEN_TYPE_NAVIGATION:
          
            if (selected <= (current_menu_index + 4) && (selected - menu_top > current_menu_index)) {
                menuSetNavigationCursor(selected - 1 - menu_top);
            }
            else if ((current_menu_index > 1) && (selected <= current_menu_index)) {
                current_menu_index = (current_menu_index - 1 );
                selected = selected - 1;
                page_change = true;
                displayMenu();
            }
            
          break;

          case SCREEN_TYPE_EDIT_VALUE:
          current_value++;
          updateMenuProgram(selected);
          break;
          case SCREEN_TYPE_SHOW_PROGRAM:
            current_value++;
            if (current_value > max_value){
              current_value = min_value;
            }
            updateMenuProgram(selected);
          break;
        }    
      }
      break;
      
      case LCD_DOWN: { // down

        switch(current_menu_type){
          
          case SCREEN_TYPE_NAVIGATION:
            
            if (selected >= (current_menu_index + 4) &&
                (current_menu_size > 4) && (selected <= current_menu_size)) {
                current_menu_index = (current_menu_index + 1);
                selected = selected + 1;
                page_change = true;
                displayMenu();
            }
            else if ((selected < (current_menu_index + 4)) &&
                    (selected <= current_menu_size)) {
                menuSetNavigationCursor(selected + 1 - menu_top);
            }
            
          break;

          case SCREEN_TYPE_EDIT_VALUE:
              current_value--;
              updateMenuProgram(selected);
          break;
          case SCREEN_TYPE_SHOW_PROGRAM:
            current_value--;
            if (current_value < min_value){
              current_value = max_value; 
            }
            updateMenuProgram(selected);
          break;

        }
      }
      break;
      
      case LCD_SELECT: // select
          current_func[selected]();//
      break;

      case LCD_MOTOR_EVENT:
          updateRunningState();
      break;
  }
}
