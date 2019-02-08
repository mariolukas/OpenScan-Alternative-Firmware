# Alternative Firmware for OpenScan Photogrammetry 3D Scanner (openscan.eu)

This project is work in progress. I am looking for help.
I started this project because i wanted to help making the firmware 
more flexible and modular by using a minimal amount of memory. 
The trade off is that the menu structure changed a lot, compared
to the original project. I tried to keep as much of the origanl 
code as possible. 

## Requirements
Install the following libraries for Arduino IDE. Go to Sketch -> Include Library -> Manage Libraries
The Library Manger opens. Select the Library and press install.

- LiquidCrystal I2C ( Display Library )
- AccelStepper ( Stepper Driver Library )
- JC_Button ( Button Debounce Library )

## Configuration
The configuration of the firmware is done in the file `configuration.h`. 
There are several self explanatory configuration variables/defines. Most
of them are commented. The most importent ones are the MOTHERBOARD and 
LANGUAGE. 

Possible Values for the Baords are: 

 * BOARD_DEFAULT       - Default Board made by Thomas.
 * BOARD_FABSCAN_SHIELD   - FabScan Arduino Shield with up to 3 Motor Drivers

 Posssible Values for the Languages are :

 * LANG_DE - german. 

## Build Sketch
Click on the build icon for compiling. Upload the Sketch to your Board. 

## Menue Translation
This sketch contains multilinugal support. The differen Languages
are defined in language header files. The files do follow the file
name pattern `lcd_lang_<lang_short>.h`. E.g. For english languge lcd_lang_en.h

You can define new language files by adding those files for your 
language. The best entry will be to copy one of the existing language files.
Change the content and rename it to your language. Afterwars open the file
`lcd_language.h` file and add the selection for your language file to the
macro. 

Choose your language in `configuration.h` and you are done. 

## Add custom boards
This sketch is made to support custom board configurations. There are 
different pin definition files for each supported board. Those files 
are defined by the following convention `pins_YOUR_BOARD_NAME_HERE.h`.
Best staring point is to copy one of the existing board files and change
the pin numbers in the file. Save it like described above. Add your new
board definition file to the pin.h board selection macro and you are done.

## Menu Structure. 
* TODO.

## TODO:
see https://github.com/mariolukas/OpenScan-Alternative-Firmware/issues



