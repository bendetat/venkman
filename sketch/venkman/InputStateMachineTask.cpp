#include <Arduino.h>
#include <Arduino_FreeRTOS.h>
#include "venkman.h"
#include "InputStateMachineTask.h"

int generatorPin = 11;
int armPin = 10;
int firePin = 8;
bool isGeneratorEngaged = false;
bool isArmed = false;
bool isFiring = false;
PackState currentPackState = poweredOn;

InputStateMachineTask::InputStateMachineTask(CyclotronTask* cyclotronTask, Sounds* sounds) {
  cyclotronTask = cyclotronTask;
  sounds = sounds;
}

void InputStateMachineTask::start() {
  pinMode(generatorPin, INPUT);
  pinMode(armPin, INPUT);
  pinMode(firePin, INPUT);

  isGeneratorEngaged = digitalRead(generatorPin);
  isArmed = digitalRead(armPin);
  isFiring = digitalRead(firePin);

  if (isGeneratorEngaged || isArmed || isFiring) {
    transitionStateTo(invalidState);
  } else {
    transitionStateTo(poweredOn);
  }

  for(;;) loop();
}

void InputStateMachineTask::loop() {
  if (digitalRead(generatorPin)) {
    if (!isGeneratorEngaged) {
      isGeneratorEngaged = true;
      transitionStateTo(generatorOn);
    }
  } else if (isGeneratorEngaged) {
    isGeneratorEngaged = false;
    transitionStateTo(poweredOn);
  }

  if (digitalRead(armPin)) {
    if (!isArmed) {
      isArmed = true;
      transitionStateTo(arming);
    }
  } else if (isArmed) {
    isArmed = false;
    transitionStateTo(isGeneratorEngaged ? generatorOn : poweredOn);
  }

  vTaskDelay(10 / portTICK_PERIOD_MS);
}

void InputStateMachineTask::transitionStateTo(PackState newState) {
  cyclotronTask->onStateChanged(newState);
  sounds->onStateChanged(newState);

  currentPackState = newState;
}

