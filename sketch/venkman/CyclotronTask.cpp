#include <Arduino_FreeRTOS.h>
#include "venkman.h"
#include "CyclotronTask.h"

byte cyclotronSequence[4];
int cyclotronDelay = 500;
int cyclotronStep = -1;
byte invalidStateCyclotronSequence[4];
byte defaultCyclotronSequence[4];

CyclotronTask::CyclotronTask(Lights* lights) {
  lights = lights;

  invalidStateCyclotronSequence[0] = 0b00001111;
  invalidStateCyclotronSequence[1] = 0b00000000;
  invalidStateCyclotronSequence[2] = 0b00001111;
  invalidStateCyclotronSequence[3] = 0b00000000;

  defaultCyclotronSequence[0] = 0b00000001;
  defaultCyclotronSequence[1] = 0b00000010;
  defaultCyclotronSequence[2] = 0b00000100;
  defaultCyclotronSequence[3] = 0b00001000;

  onStateChanged(poweredOn);
}

void CyclotronTask::start() {
  for (;;) loop();
}

void CyclotronTask::loop() {
  cyclotronStep ++;
  if (cyclotronStep == 4) {
    cyclotronStep = 0;
  }

  lights->setCyclotronMask(cyclotronSequence[cyclotronStep]);  
  vTaskDelay(cyclotronDelay / portTICK_PERIOD_MS);
}

void CyclotronTask::onStateChanged(PackState newState) {
  if (newState == initial || newState == poweredOn || newState == shutDown) {
    setCyclotronSequence(defaultCyclotronSequence);
    cyclotronDelay = 700;
  } else if (newState == generatorOn || newState == arming || newState == armed || newState == firing || newState == endingFiring) {
    setCyclotronSequence(defaultCyclotronSequence);
    cyclotronDelay = 300;
  } else {
    setCyclotronSequence(invalidStateCyclotronSequence);
    cyclotronDelay = 750;
  }
}

void CyclotronTask::setCyclotronSequence(byte newSequence[]) {
  for (int i = 0; i < 4; i ++) {
    cyclotronSequence[i] = newSequence[i];
  }
}


