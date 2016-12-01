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
    transitionStateTo(initial);
  }

  for(;;) {
    loop();
    vTaskDelay(10 / portTICK_PERIOD_MS);
  }
}

void InputStateMachineTask::loop() {
  bool generatorPinHigh = digitalRead(generatorPin);
  bool armPinHigh = digitalRead(armPin);
  bool firePinHigh = digitalRead(firePin);
  
  if (generatorPinHigh) {
    if (!isGeneratorEngaged) {
      isGeneratorEngaged = true;
      transitionStateTo(generatorOn);
      return;
    }
  } else if (isGeneratorEngaged) {
    isGeneratorEngaged = false;
    transitionStateTo(poweredOn);
    return;
  }

  if (armPinHigh) {
    if (!isArmed) {
      isArmed = true;

      if (!isGeneratorEngaged) {
        transitionStateTo(shutDown);
        return;
      }
      
      transitionStateTo(arming);
      vTaskDelay(5000 / portTICK_PERIOD_MS);
      transitionStateTo(armed);
      
      return;
    }
  } else if (isArmed) {
    isArmed = false;
    transitionStateTo(isGeneratorEngaged ? generatorOn : poweredOn);

    return;
  }

  if (firePinHigh) {
    if (!isFiring) {
      isFiring = true;
      
      if (!isArmed || !isGeneratorEngaged) {
        transitionStateTo(shutDown);
        return;
      }

      transitionStateTo(firing);
      return;
    }
  } else if (isFiring) {
    isFiring = false;
    transitionStateTo(!isArmed || !isGeneratorEngaged ? initial : endingFiring);
    vTaskDelay(2000 / portTICK_PERIOD_MS);

    return;
  }

  if (!isGeneratorEngaged && !isArmed && !isFiring) {
    transitionStateTo(initial);
  }
}

void InputStateMachineTask::transitionStateTo(PackState newState) {
  if (currentPackState == newState) return;
  
  digitalWrite(13, HIGH);
  vTaskDelay(50 / portTICK_PERIOD_MS);
  digitalWrite(13, LOW);
  
  cyclotronTask->onStateChanged(newState);
  sounds->onStateChanged(newState);

  currentPackState = newState;
}

