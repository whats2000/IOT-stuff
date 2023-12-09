#ifndef Controller_h
#define Controller_h

#include "Arduino.h"

class Controller {
  public:
    Controller(int pinX, int pinY, int deadzone, int buttonUp, int buttonRight, int buttonDown, int buttonLeft, int buttonE, int buttonF);
    void setup();
    void update();
    void printDebugValues();
    int getX();
    int getY();
    int getButtonState(int buttonPin);

  private:
    int _pinX, _pinY;
    int _deadzone;
    int _centerX, _centerY;
    bool _centerSet;
    int _buttonUp, _buttonRight, _buttonDown, _buttonLeft, _buttonE, _buttonF;
    int _xValue, _yValue;
    int applyDeadzone(int value);
};

#endif
