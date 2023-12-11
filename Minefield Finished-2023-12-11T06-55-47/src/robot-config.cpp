#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
motor ClawMotor = motor(PORT1, ratio18_1, true);
pot Potentiometer = pot(Brain.ThreeWirePort.A);
controller Controller1 = controller(primary);
motor DriveL = motor(PORT5, ratio18_1, false);
motor DriveR = motor(PORT2, ratio18_1, true);

// VEXcode generated functions
// define variable for remote controller enable/disable
bool RemoteControlCodeEnabled = true;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void vexcodeInit( void ) {
  Brain.Screen.print("Left Joystick: Drive Forward/Back");
    Brain.Screen.newLine();
  Brain.Screen.print("Right Joystick: Turn Left/Right");
    Brain.Screen.newLine();
  Brain.Screen.print("Button R1: Boost Speed");
    Brain.Screen.newLine();
  Brain.Screen.print("Button L1: Arm Move Upwards");
    Brain.Screen.newLine();
  Brain.Screen.print("Button L2: Arm Move Downwards");
    Brain.Screen.newLine();
  Brain.Screen.print("Left Button: Arm Home");
    Brain.Screen.newLine();
  Brain.Screen.print("Up Button: Arm High");
    Brain.Screen.newLine();
  Brain.Screen.print("Right Button: Arm Down");
}