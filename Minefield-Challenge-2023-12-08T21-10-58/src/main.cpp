/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       Eric Lind                                                 */
/*    Created:      Wed Sep 25 2019                                           */
/*    Description:  MineField Robots (Potentiometer)                          */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// ClawMotor            motor         1               
// Potentiometer        pot           A               
// Controller1          controller                    
// DriveL               motor         5               
// DriveR               motor         2               
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"

using namespace vex;
void ArmHome();
void ArmFloor();
void ArmHigh();

bool isArm = false;

#define POTLOW 80
#define POTMID 150
#define POTHIGH 235
#define ROBOTS "cool"

int main() {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
  ArmHome();

  Controller1.ButtonRight.pressed(ArmFloor);
  Controller1.ButtonUp.pressed(ArmHigh);
  Controller1.ButtonLeft.pressed(ArmHome);

  while(ROBOTS == "cool"){
    Brain.Screen.print(Potentiometer.angle(degrees));
    Brain.Screen.clearScreen();
    Brain.Screen.newLine();

    float drive = 0;
    float turn = 0;
    float speedratio = 0.22;

    if(Controller1.ButtonR1.pressing()){
      speedratio = 0.5;
    }
   
    if(Controller1.Axis3.position(percent) > 5 || Controller1.Axis3.position(percent) < -5){drive = Controller1.Axis3.position(percent);}
    if(Controller1.Axis1.position(percent) > 5 || Controller1.Axis1.position(percent) < -5){turn = Controller1.Axis1.position(percent);}
    
    DriveL.spin(fwd, (drive+turn)*speedratio, percent);
    DriveR.spin(fwd, (drive-turn)*speedratio, percent);

    if(Controller1.ButtonL1.pressing() && Potentiometer.angle(degrees) > POTLOW){
      ClawMotor.spin(reverse);
    }
    else if(Controller1.ButtonL2.pressing() && Potentiometer.angle(degrees) < POTHIGH){
      ClawMotor.spin(forward);
    }
    else if (!isArm){
      ClawMotor.stop();
    }
  }
}

void ArmHome(){
  while(Potentiometer.angle(degrees) > POTLOW){
    isArm = true;
    ClawMotor.spin(reverse);
  }
  isArm = false;
}

void ArmFloor(){
  while(Potentiometer.angle(degrees) < POTHIGH){
    isArm = true;
    ClawMotor.spin(forward);
  }
  isArm = false;
}

void ArmHigh(){
  while(abs((Potentiometer.angle(degrees))-POTMID)>5){
    isArm = true;
    ClawMotor.spin(reverse, ((Potentiometer.angle(degrees)-POTMID)), percent);
  }
  isArm = false;
}
