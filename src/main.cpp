#include <Arduino.h>
#include <LiquidCrystal.h>

/*
/ 
/ A breaksdown of the pins:
/ 
/ - VDD (positive power supply connection)                         -> VDD (5V)
/ - VSS (GND connection)                                           -> VSS (GND)
/ - A (anode; positive power supply connection for LED backlight)  -> A (5V)
/ - K (kathode; ground connection for the LED backlight)           -> K (GND)
/ - RW (read/write)
/ - RS (register select)
/ - EN (enable)
/ - D0-D1 (data pins or data lines).
/ 
/ The VDD and VSS pins relate to the power supply for the logic and internal 
/ circuitry of the LCD, and not specifically the backlight. The A and K pins 
/ relate to the power supply of the LED backlight. Applying a voltage over the 
/ A and K pins supplies power to the LED backlight.
/ 
/ The RW pin sets the mode for the LCD. When set to read (R) mode, then the 
/ microcontroller can read data from the LCD. This is not very common in 
/ typical applications. More common is the write (W) mode, in which the 
/ microcontroller writes data to the LCD.
/ 
/ The RS pin determines if the data sent by the microcontroller to the LCD 
/ modules must be treated as a command or as characters to be displayed. If  
/ set to LOW (0), then the data sent to the LCD module is treated as a 
/ command, controlling the behavior of the LCD. If set to HIGH (1), then the 
/ data sent to the LCD is treated as characters to be displayed.
/ 
/ The E pin enables the LCD command to read data from the data pins. If the 
/ state of the pin goes from HIGH to LOW, then the LCD modules reads the data 
/ from the data lines (data pins), whether it is data or characters to be 
/ displayed.
/ 
*/

int RS = 7;
int EN = 8;
int D4 = 9;
int D5 = 10;
int D6 = 11;
int D7 = 12;

LiquidCrystal lcd(RS, EN, D4, D5, D6, D7);

const int screenTime = 2000;

void setup() {

    lcd.begin(16, 2); // initialize an interface to the LCD (16 cols; 2 rows)

}

void loop() {

    lcd.clear();
    lcd.print("Hello World!");
    delay(screenTime);
    lcd.clear();
    lcd.print("My name is Fre");
    delay(screenTime);

}