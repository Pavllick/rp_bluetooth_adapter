#ifndef _GPIO_H
#define _GPIO_H

#include <stdbool.h>

enum Direction { In, Out };
enum Edge { Rising, Falling, Both, None };
enum Status { Low, High, Error };

bool Init(int pin);
bool SetDirection(int pin, enum Direction direction);
bool SetEdge(int pin, enum Edge edge);

enum Status GetStatus(int pin);

#endif // _GPIO_H
