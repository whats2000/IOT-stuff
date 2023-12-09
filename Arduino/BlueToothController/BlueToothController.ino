#include "Controller.h"

#define PIN_ANALOG_X A0
#define PIN_ANALOG_Y A1
#define DEADZONE 2
#define BUTTON_UP 2
#define BUTTON_RIGHT 3
#define BUTTON_DOWN 4
#define BUTTON_LEFT 5
#define BUTTON_E 6
#define BUTTON_F 7

Controller controller(PIN_ANALOG_X, PIN_ANALOG_Y, DEADZONE, BUTTON_UP, BUTTON_RIGHT, BUTTON_DOWN, BUTTON_LEFT, BUTTON_E, BUTTON_F);

void setup() {
  Serial.begin(9600);
  controller.setup();
}

void loop() {
  controller.update();
  
  int x = controller.getX();
  int y = controller.getY();
  int enter = controller.getButtonState(BUTTON_DOWN);
  int esc = controller.getButtonState(BUTTON_RIGHT);
  int shift = controller.getButtonState(BUTTON_LEFT);
  int fire = controller.getButtonState(BUTTON_UP);

  // Print the joystick and button states in a formatted string
  Serial.print("X:");
  Serial.print(x);
  Serial.print(",Y:");
  Serial.print(y);
  Serial.print(",Enter:");
  Serial.print(enter);
  Serial.print(",Esc:");
  Serial.print(esc);
  Serial.print(",Shift:");
  Serial.print(shift);
  Serial.print(",Fire:");
  Serial.println(fire);

  delay(100);
}
