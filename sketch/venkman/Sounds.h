#ifndef SOUNDTASK_H
#define SOUNDTASK_H

#include "venkman.h"

class Sounds {
  private:
    int idleSampleIndex;
    int humSampleIndex;
    int armingSampleIndex;
    
  public:
    Sounds();
    void onStateChanged(PackState newState);
};

#endif
