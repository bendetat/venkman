#include <Arduino_FreeRTOS.h>
#include <croutine.h>
#include <event_groups.h>
#include <FreeRTOSConfig.h>
#include <FreeRTOSVariant.h>
#include <list.h>
#include <mpu_wrappers.h>
#include <portable.h>
#include <portmacro.h>
#include <projdefs.h>
#include <queue.h>
#include <semphr.h>
#include <StackMacros.h>
#include <task.h>
#include <timers.h>
#include "venkman.h"
#include "CyclotronTask.h"
#include "InputStateMachineTask.h"

CyclotronTask* cyclotronTask;
InputStateMachineTask* inputStateMachineTask;

void setup () {
  Lights* lights = new Lights();
  Sounds* sounds = new Sounds();
  
  cyclotronTask = new CyclotronTask(lights);
  inputStateMachineTask = new InputStateMachineTask(cyclotronTask, sounds);
  
  xTaskCreate(wrapCyclotronTask, (const portCHAR *)"Cyclotron", 128, NULL, 1, NULL);
  xTaskCreate(wrapInputStateMachineTask, (const portCHAR *)"Input", 128, NULL, 1, NULL);
}

void wrapCyclotronTask(void* parm) {
  cyclotronTask->start();
}
void wrapInputStateMachineTask(void* parm) {
  inputStateMachineTask->start();
}

void loop () {
}



 

