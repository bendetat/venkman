#ifndef CYCLOTRONTASK_H
#define CYCLOTRONTASK_H

#include <Arduino.h>
#include "venkman.h"
#include "Lights.h"

class CyclotronTask {
  private:
    Lights* lights;
    void loop();
    void setCyclotronSequence(byte newSequence[]);
  public:
    CyclotronTask(Lights* lights);
    void start();
    void onStateChanged(PackState newState);
};

#endif
