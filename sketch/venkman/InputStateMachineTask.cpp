#include <Arduino.h>
#include <Arduino_FreeRTOS.h>
#include "venkman.h"
#include "InputStateMachineTask.h"

InputStateMachineTask::InputStateMachineTask(CyclotronTask* cyclotronTask, Sounds* sounds) {
  generatorPin = 11;
  armPin = 10;
  firePin = 8;
  inputIndicatorPin = 12;
  generatorEngaged = false;
  armed = false;
  firing = false;
  currentPackState = poweredOn;
  cyclotronTask = cyclotronTask;
  sounds = sounds;
}

void InputStateMachineTask::start() {
  pinMode(generatorPin, INPUT);
  pinMode(armPin, INPUT);
  pinMode(firePin, INPUT);
  pinMode(inputIndicatorPin, OUTPUT);

  generatorEngaged = digitalRead(generatorPin);
  armed = digitalRead(armPin);
  firing = digitalRead(firePin);

  if (generatorEngaged || armed || firing) {
    transitionStateTo(invalidState);
  } else {
    transitionStateTo(poweredOn);
  }

  for(;;) loop();
}

void InputStateMachineTask::loop() {
  if (digitalRead(generatorPin)) {
    if (!generatorEngaged) {
      generatorEngaged = true;
      transitionStateTo(generatorOn);
    }
  } else if (generatorEngaged) {
    generatorEngaged = false;
    transitionStateTo(poweredOn);
  }

  if (digitalRead(armPin)) {
    if (!armed) {
      armed = true;
      transitionStateTo(arming);
    }
  } else if (armed) {
    armed = false;
    transitionStateTo(generatorEngaged ? generatorOn : poweredOn);
  }

  //digitalWrite(inputIndicatorPin, generatorEngaged || armed || firing);
  vTaskDelay(10 / portTICK_PERIOD_MS);
}

void InputStateMachineTask::transitionStateTo(PackState newState) {
  cyclotronTask->onStateChanged(newState);
  sounds->onStateChanged(newState);

  currentPackState = newState;
}

