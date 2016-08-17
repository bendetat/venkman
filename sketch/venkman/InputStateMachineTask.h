#ifndef INPUTSTATEMACHINETASK_H
#define INPUTSTATEMACHINETASK_H

#include "venkman.h"
#include "CyclotronTask.h"
#include "Sounds.h"

class InputStateMachineTask {
  private:
    int generatorPin;
    int armPin;
    int firePin;
    int inputIndicatorPin;
    bool generatorEngaged;
    bool armed;
    bool firing;
    PackState currentPackState;
    CyclotronTask* cyclotronTask;
    Sounds* sounds;
    void loop();
  public:
    InputStateMachineTask(CyclotronTask* cyclotronTask, Sounds* sounds);
    void start();
    void transitionStateTo(PackState newState);
};

#endif
