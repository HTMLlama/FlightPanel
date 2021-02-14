#include <Arduino.h>

#include "Adafruit_Keypad.h"
#include "HID-Project.h"
#include "Joystick.h"

const byte ROWS = 4; // rows
const byte COLS = 3; // columns
const byte KEY_PINS = 5;
//define the symbols on the buttons of the keypads
char keypadKeys[ROWS][COLS] = {
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'*','0','#'}
};
byte rowPins[ROWS] = {7, 12, 11, 9}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {8, 6, 10}; //connect to the column pinouts of the keypad

Adafruit_Keypad customKeypad = Adafruit_Keypad( makeKeymap(keypadKeys), rowPins, colPins, ROWS, COLS);

Joystick_ Joystick;

int keyPins[KEY_PINS] = {1, 2, 3, 4, 5};

void readKeypad() {
  keypadEvent e = customKeypad.read();
  if(e.bit.EVENT == KEY_JUST_PRESSED) {
    BootKeyboard.press(e.bit.KEY);
    // Serial.println(e.bit.KEY);
    BootKeyboard.releaseAll();
  } 
}

void readKey() {
  for (size_t i = 0; i < KEY_PINS; i++) {
    Joystick.setButton(i, !digitalRead(keyPins[i]));
  }
}

void setup() {
  Serial.begin(9600);
  customKeypad.begin();
  BootKeyboard.begin();
  Joystick.begin();

  for (size_t i = 0; i < KEY_PINS; i++) {
    pinMode(keyPins[i], INPUT_PULLUP);
  }
  
}

void loop() {
  customKeypad.tick();
  readKeypad();
  readKey();
  delay(5);
}