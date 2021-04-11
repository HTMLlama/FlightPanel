#include <Arduino.h>

#include "Adafruit_Keypad.h"
#include "HID-Project.h"
#include "Joystick.h"

#define IGNITION_PIN 13

const byte ROWS = 4; // rows
const byte COLS = 3; // columns
const byte KEY_PINS_COUNT = 4;
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

int keyPins[KEY_PINS_COUNT] = {2, 3, 4, 5};

void readKeypad() {
  keypadEvent e = customKeypad.read();
  if(e.bit.EVENT == KEY_JUST_PRESSED) {
    int key = e.bit.KEY;
    if (key == '*') {
      Joystick.setButton(KEY_PINS_COUNT + 1, HIGH);
      delay(50);
      Joystick.setButton(KEY_PINS_COUNT + 1, LOW);
    } else if (key == '#') {
      Joystick.setButton(KEY_PINS_COUNT + 2, HIGH);
      delay(50);
      Joystick.setButton(KEY_PINS_COUNT + 2, LOW);
    }else {
      BootKeyboard.press(e.bit.KEY);
      delay(50);
      BootKeyboard.releaseAll();
    }
  } 
}

void readKeySwitch() {
  for (size_t i = 0; i < KEY_PINS_COUNT; i++) {
    if (!digitalRead(IGNITION_PIN)) {
      Joystick.setButton(i, LOW);
      Joystick.setButton(KEY_PINS_COUNT, HIGH);
    } else {
      Joystick.setButton(i, !digitalRead(keyPins[i]));
      Joystick.setButton(KEY_PINS_COUNT, LOW);
    }
  }
}

void setup() {
  Serial.begin(9600);
  customKeypad.begin();
  BootKeyboard.begin();
  Joystick.begin();

  for (size_t i = 0; i < KEY_PINS_COUNT; i++) {
    pinMode(keyPins[i], INPUT_PULLUP);
  }

  pinMode(IGNITION_PIN, INPUT_PULLUP);
}

void loop() {
  customKeypad.tick();
  readKeypad();
  readKeySwitch();
}