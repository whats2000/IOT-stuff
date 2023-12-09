#include "Controller.h"

Controller::Controller(int pinX, int pinY, int deadzone, int buttonUp, int buttonRight, int buttonDown, int buttonLeft, int buttonE, int buttonF) {
  _pinX = pinX;
  _pinY = pinY;
  _deadzone = deadzone;
  _centerSet = false;
  _buttonUp = buttonUp;
  _buttonRight = buttonRight;
  _buttonDown = buttonDown;
  _buttonLeft = buttonLeft;
  _buttonE = buttonE;
  _buttonF = buttonF;
}

void Controller::setup() {
  _centerX = analogRead(_pinX);
  _centerY = analogRead(_pinY);
  _centerSet = true;
  Serial.println("Center set!");

  pinMode(_buttonUp, INPUT_PULLUP);
  pinMode(_buttonRight, INPUT_PULLUP);
  pinMode(_buttonDown, INPUT_PULLUP);
  pinMode(_buttonLeft, INPUT_PULLUP);
  pinMode(_buttonE, INPUT_PULLUP);
  pinMode(_buttonF, INPUT_PULLUP);
}

void Controller::update() {
  _xValue = applyDeadzone(analogRead(_pinX) - _centerX);
  _yValue = applyDeadzone(analogRead(_pinY) - _centerY);
}

void Controller::printDebugValues() {
  Serial.print("X: ");
  Serial.print(_xValue);
  Serial.print(" | Y: ");
  Serial.print(_yValue);

  Serial.print("Up: ");
  Serial.print(digitalRead(_buttonUp));
  Serial.print(" | Right: ");
  Serial.print(digitalRead(_buttonRight));
  Serial.print(" | Down: ");
  Serial.print(digitalRead(_buttonDown));
  Serial.print(" | Left: ");
  Serial.print(digitalRead(_buttonLeft));
  Serial.print(" | E: ");
  Serial.print(digitalRead(_buttonE));
  Serial.print(" | F: ");
  Serial.println(digitalRead(_buttonF));
}

int Controller::applyDeadzone(int value) {
  return (abs(value) < _deadzone) ? 0 : value;
}

int Controller::getX() {
  return _xValue;
}

int Controller::getY() {
  return _yValue;
}

int Controller::getButtonState(int buttonPin) {
  return digitalRead(buttonPin);
}
