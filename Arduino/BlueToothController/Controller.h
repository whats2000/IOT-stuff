// Ensure the header file is included only once in the compilation process
#ifndef Controller_h
#define Controller_h

#include "Arduino.h"  // Include the main Arduino header

// Define the Controller class
class Controller {
  public:
    // Constructor: Initializes the controller with joystick pins, deadzone, and button pins
    Controller(int pinX, int pinY, int deadzone, int buttonUp, int buttonRight, int buttonDown, int buttonLeft, int buttonE, int buttonF);
    
    // Setup function to initialize joystick center values and button pins
    void setup();
    
    // Update function to read the current state of the joystick and buttons
    void update();
    
    // Function to print debug values of joystick and buttons to the Serial monitor
    void printDebugValues();
    
    // Getter function to get the current X value of the joystick
    int getX();
    
    // Getter function to get the current Y value of the joystick
    int getY();
    
    // Getter function to get the state of a specific button
    int getButtonState(int buttonPin);

  private:
    // Private variables to store joystick pins, deadzone value, and center values
    int _pinX, _pinY;  // Joystick analog pin numbers
    int _deadzone;     // Deadzone value for joystick
    int _centerX, _centerY;  // Center values for the joystick
    bool _centerSet;   // Flag to check if center is set

    // Button pin numbers
    int _buttonUp, _buttonRight, _buttonDown, _buttonLeft, _buttonE, _buttonF;
    
    // Current joystick values
    int _xValue, _yValue;  

    // Private method to apply deadzone to a joystick value
    int applyDeadzone(int value);
};

#endif  // End of the header guard
