#ifndef _GPIO_H
#define _GPIO_H

#include <stdbool.h>

class GPIO {
public: 
  enum Direction { In, Out };
  enum Edge { Rising, Falling, Both, None };
  enum Status { Low, High, Error };

  GPIO(int bcm_pin);
  bool Init();
  bool Dispose();
  bool SetDirection(enum Direction direction);
  bool SetEdge(enum Edge edge);
  enum Status GetStatus();
};

#endif // _GPIO_H
