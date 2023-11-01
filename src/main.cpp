#include <Arduino.h>
#include <LiquidCrystal.h>
#include <Keypad.h>

/*
/ 
/ A breaksdown of the pins:
/ 
/ - VDD (positive power supply connection)                         -> VDD (5V)
/ - VSS (ground connection)                                        -> VSS (GND)
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
/ The E pin enables the LCD module to read data from the data pins. If the 
/ state of the pin goes from HIGH to LOW, then the LCD modules reads the data 
/ from the data lines (data pins), whether it is a command or characters to be 
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

const int LONG_SCREEN_TIME = 2500;
const int SHORT_SCREEN_TIME = 1000;

// Initialize variables to control the program
char programMode = '1';
const byte CODE_LENGTH = 5;
byte currentCodeLength;
String userCode = "";
String enteredCode = "";

// Map the buttons to an array for the Keymap instance
const byte ROWS = 4;
const byte COLS = 4;

char keyChars[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

byte rowPins[ROWS] = {13, 6, 5, 4}; // Pins used for the rows of the keypad
byte colPins[COLS] = {3, 2, A1, A2}; // Pins used for the columns of the keypad

// Initialize a Keypad instance
Keypad keypad = Keypad(makeKeymap(keyChars), rowPins, colPins, ROWS, COLS);

void setup() {

    Serial.begin(9600);
    lcd.begin(16, 2); // initialize an interface to the LCD (16 cols; 2 rows)

}

void loop() {

    // The following program modes are available:
    // - '0': waiting for user input
    // - '1': showing main menu
    // - '2': setting new code
    // - '3': entering code
    if (programMode == '1') {
        
        programMode = '0';

        lcd.clear();
        lcd.print("Select what you");
        lcd.setCursor(0, 1);
        lcd.print("want to do:");
        delay(LONG_SCREEN_TIME);

        lcd.clear();
        lcd.print("1: show main");
        lcd.setCursor(0, 1);
        lcd.print("   menu");
        delay(LONG_SCREEN_TIME);

        lcd.clear();
        lcd.print("2: set new code");
        delay(LONG_SCREEN_TIME);

        lcd.clear();
        lcd.print("3: enter code");
        delay(LONG_SCREEN_TIME);

        lcd.clear();
        lcd.print("Enter option:");
        lcd.setCursor(0, 1);
        lcd.blink();

    }

    // Obtain any key presses. If the user does not press any key, wait until 
    // a key is pressed.
    char pressedKey = keypad.getKey();

    if (pressedKey) {
        lcd.print(pressedKey);
        delay(SHORT_SCREEN_TIME);
        lcd.noBlink();
    }

    if (pressedKey == '1') {

        programMode = '1';

    } else if (pressedKey == '2' or programMode == '2') {

        lcd.clear();
        lcd.print("Set new code:");
        lcd.setCursor(0, 1);
        lcd.blink();

        currentCodeLength = 0;
        userCode = "";

        while (currentCodeLength < CODE_LENGTH) {
            pressedKey = keypad.getKey();
            if (pressedKey) {
                lcd.print('*');
                userCode += pressedKey;
                currentCodeLength += 1;
            }
        }
        delay(SHORT_SCREEN_TIME);

        lcd.noBlink();
        lcd.clear();
        lcd.print("Re-enter code:");
        lcd.setCursor(0, 1);
        lcd.blink();

        currentCodeLength = 0;
        enteredCode = "";

        while (currentCodeLength < CODE_LENGTH) {
            pressedKey = keypad.getKey();
            if (pressedKey) {
                lcd.print('*');
                enteredCode += pressedKey;
                currentCodeLength += 1;
            }
        }
        delay(SHORT_SCREEN_TIME);
        lcd.clear();

        if (enteredCode == userCode) {
            lcd.print("Entries match");
            programMode = '1';
        } else {
            lcd.print("No match");
            programMode = '2';
        }
        lcd.noBlink();
        delay(LONG_SCREEN_TIME);

    } else if (pressedKey == '3') {

        lcd.clear();
        lcd.print("Enter code:");
        lcd.setCursor(0, 1);
        lcd.blink();

        currentCodeLength = 0;
        enteredCode = "";

        // Obtain the user code from the user. Do not print out the pressed keys 
        // for security reasons.
        while (currentCodeLength < CODE_LENGTH) {

            pressedKey = keypad.getKey();
            if (pressedKey) {
                lcd.print('*');
                enteredCode += pressedKey;
                currentCodeLength += 1;
            }

        }

        lcd.noBlink();
        lcd.clear();

        // Evaluate the entered code and warn the user of the outcome.
        if (enteredCode == userCode) {
            lcd.print("Valid code");
        } else {
            lcd.print("Invalid code");
        }

        delay(LONG_SCREEN_TIME);
        programMode = '1';

    }

}