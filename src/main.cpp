#include <Arduino.h>
#include <Keypad.h>


// Map the buttons to an array for the Keymap instance
const byte ROWS = 4;
const byte COLS = 4;

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

// Initialize variables to work with program
char programMode = '1';
const byte CODE_LENGTH = 5;
byte currentCodeLength;
String userCode = "";
String enteredCode = "";

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
    Serial.println("Select what you want to do:");
    Serial.println("- 1 : show main menu");
    Serial.println("- 2 : set new code");
    Serial.println("- 3 : enter code");
    programMode = '0';
  }
  
  // Obtain any key presses. If the user does not press any key, wait until a 
  // key is pressed.
  char pressedKey = keypad.getKey();

  if (pressedKey == '1') {

    programMode = '1';

  } else if (pressedKey == '2') {

    Serial.println ("# Set new code");
    currentCodeLength = 0;
    userCode = "";
    while (currentCodeLength < CODE_LENGTH) {
      pressedKey = keypad.getKey();
      if (pressedKey) {
        Serial.println(pressedKey);
        userCode += pressedKey;
        currentCodeLength += 1;
      }
    }
    Serial.println(userCode);
    programMode = '1';

  } else if (pressedKey == '3') {

    Serial.println("# Enter code");
    currentCodeLength = 0;
    enteredCode = "";

    // Obtain the user code from the user. Do not print out the pressed keys 
    // for security reasons.
    while (currentCodeLength < CODE_LENGTH) {

      pressedKey = keypad.getKey();
      if (pressedKey) {
        Serial.print('*');
        enteredCode += pressedKey;
        currentCodeLength += 1;
      }

    }
    Serial.println("");

    // Evaluate the entered code and warn the user of the outcome.
    if (enteredCode == userCode) {
      Serial.println("Congrats! You entered the correct code!");
    } else {
      Serial.println("Error: you entered an incorrect code!");
    }

    programMode = '1';

  }

}
