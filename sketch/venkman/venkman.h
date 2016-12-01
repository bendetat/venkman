#ifndef VENKMAN_H
#define VENKMAN_H

enum PackState {
  initial,
  poweredOn,
  generatorOn,
  arming,
  armed,
  firing,
  endingFiring,
  shutDown,
  invalidState
};

#endif
