#include <Arduino.h>

#include "Joystick.h"

const byte SWITCH_PINS_COUNT = 11;

int switchPins[SWITCH_PINS_COUNT] = {2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};

Joystick_ Joystick;

void readSwitches() {
  for (size_t i = 0; i < SWITCH_PINS_COUNT; i++) {
    Joystick.setButton(i, !digitalRead(switchPins[i]));
    Joystick.setButton(i + SWITCH_PINS_COUNT + 1, digitalRead(switchPins[i]));
  }
}

void setup() {
  Serial.begin(9600);
  Joystick.begin();

  for (size_t i = 0; i < SWITCH_PINS_COUNT; i++) {
    pinMode(switchPins[i], INPUT_PULLUP);
  }
}

void loop() {
  readSwitches();
}