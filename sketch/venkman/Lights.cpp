#include <Arduino_FreeRTOS.h>
#include "venkman.h"
#include "Lights.h"

// This just takes the current state of the lights and dumps it out to the pins
int cyclotronPin1 = 7;
bool lightMask[4];

Lights::Lights() {
  for (int i = 0; i < 4; i ++) {
    pinMode(cyclotronPin1 - i, OUTPUT);
  }
}


void writeToLights() {
  // TODO replace with shift register
  for (int i = 0; i < 4; i ++) {
    digitalWrite(cyclotronPin1 - i, lightMask[i]);
  }
}

void Lights::setCyclotronMask(byte mask) {
  lightMask[0] = mask & 0x08;
  lightMask[1] = mask & 0x04;
  lightMask[2] = mask & 0x02;
  lightMask[3] = mask & 0x01;

  writeToLights();
}

