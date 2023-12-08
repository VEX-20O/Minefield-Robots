/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       VEX                                                       */
/*    Created:      Wed Sep 25 2019                                           */
/*    Description:  Clawbot Template (Drivetrain, No Gyro)                    */
/*                                                                            */
/*    Name:                                                                   */
/*    Date:                                                                   */
/*    Class:                                                                  */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// ClawMotor            motor         1               
// Potentiometer        pot           A               
// Controller1          controller                    
// DriveL               motor         2               
// DriveR               motor         3               
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"

using namespace vex;

#define POTLOW 80
#define POTHIGH 235
#define TYLER "idiot"

int main() {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();

  while(TYLER == "idiot"){
    Brain.Screen.print(Potentiometer.angle(degrees));
    Brain.Screen.clearScreen();
    Brain.Screen.newLine();

    float drive = 0;
    float turn = 0;

    if(Controller1.Axis3.position(percent) > 5 || Controller1.Axis3.position(percent) < -5){drive = Controller1.Axis3.position(percent);}
    if(Controller1.Axis1.position(percent) > 5 || Controller1.Axis1.position(percent) < -5){turn = Controller1.Axis1.position(percent);}
    
    DriveL.spin(

  }
}
