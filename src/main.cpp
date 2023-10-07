#include <Arduino.h>
#include <Keypad.h>


const byte ROWS = 4; // four rows
const byte COLS = 4; // four columns

// Map the buttons to an array for the Keymap instance
char keyChars[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

byte rowPins[ROWS] = {9, 8, 7, 6}; // Pins used for the rows of the keypad
byte colPins[COLS] = {5, 4, 3, 2}; // Pins used for the columns of the keypad

// Initialize a Keypad instance
Keypad keypad = Keypad(makeKeymap(keyChars), rowPins, colPins, ROWS, COLS);

char programMode = '1';

void setup() {

  Serial.begin(9600);

}

void loop() {

  // The following program modes are available:
  // - '0': waiting
  // - '1': main menu
  // - '2': setting new code
  // - '3': entering code
  if (programMode == '1') {
    programMode = '0';
    Serial.println("Select what you want to do:");
    Serial.println("- 1 : reprint main menu");
    Serial.println("- 2 : select new code");
    Serial.println("- 3 : enter code");
  }
  
  // Obtain any key presses. If the user does not press any key, wait until a 
  // key is pressed.
  char pressedKey = keypad.getKey();

  if (pressedKey == '1') {
    programMode = '1';
  } else if (pressedKey == '2') {
    Serial.println ("# Set new code #####");
    programMode = '1';
  } else if (pressedKey == '3') {
    Serial.println("# Enter code ########");
    programMode = '1';
  }

}
