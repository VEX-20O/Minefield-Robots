/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       Eric Lind                                                 */
/*    Created:      Wed Dec 6 2023                                            */
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

//Function Prototypes
void ArmHome();
void ArmFloor();
void ArmHigh();

bool isArm = false;

#define DEADBAND 5 //Percent Controller Deadband
#define SPDPROP 0.22 //Normal Driving Constant
#define SPDBOST 0.5 //Fast Driving Constant
#define POTLOW 80 //Potentiometer Reading of Arm Above Ground
#define POTMID 150 //Potentiometer Reading of Arm "Straight Up"
#define POTHIGH 235 //Potentiometer Reading of Arm Fully Retracted
#define ROBOTS "cool"

//Control List Printing in "robot-config.cpp"

int main() {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
  ArmHome(); //Calibrate

  //Callback function definitions for arm positions
  Controller1.ButtonRight.pressed(ArmFloor);
  Controller1.ButtonUp.pressed(ArmHigh);
  Controller1.ButtonLeft.pressed(ArmHome);

  while(ROBOTS == "cool"){ //while(true) but better
    
    //Per-iteration variables
    float drive = 0;
    float turn = 0;
    float speedratio = SPDPROP;

    //Change to Boot Speed Constant for Cycle
    if(Controller1.ButtonR1.pressing()){
      speedratio = SPDBOST;
    }

    //Record Controller Axis Values if > deadband
    if(Controller1.Axis3.position(percent) > DEADBAND || Controller1.Axis3.position(percent) < DEADBAND * -1){drive = Controller1.Axis3.position(percent);}
    if(Controller1.Axis1.position(percent) > DEADBAND || Controller1.Axis1.position(percent) < DEADBAND * -1){turn = Controller1.Axis1.position(percent);}
    
    //Arcade Drive Code
    DriveL.spin(fwd, (drive+turn)*speedratio, percent);
    DriveR.spin(fwd, (drive-turn)*speedratio, percent);

    //Manual Claw Movement, with coded hardstops
    if(Controller1.ButtonL1.pressing() && Potentiometer.angle(degrees) > POTLOW){
      ClawMotor.spin(reverse);
    }
    else if(Controller1.ButtonL2.pressing() && Potentiometer.angle(degrees) < POTHIGH){
      ClawMotor.spin(forward);
    }
    else if (!isArm){ //Nessesary to be an Elif due to claw move functions
      ClawMotor.stop();
    }
  }
}

//Move Arm to Retract
void ArmHome(){
  if(!isArm){ //Check if Another move function is running
    while(Potentiometer.angle(degrees) > POTLOW){
      isArm = true; //Arm currently moving
      ClawMotor.spin(reverse);
    }
    isArm = false; //Arm no longer moving, movement stopped by elif in main
  }
} 

void ArmFloor(){
  if(!isArm){ //Check if Another move function is running
    while(Potentiometer.angle(degrees) < POTHIGH){
      isArm = true; //Arm currently moving
      ClawMotor.spin(forward);
    }
    isArm = false; //Arm no longer moving, movement stopped by elif in main
  }
}

void ArmHigh(){
  if(!isArm){ //Check if Another move function is running
    while(abs((Potentiometer.angle(degrees))-POTMID)>5){ //see if arm is outside of error for mid position (either direction)
      isArm = true; //Arm currently moving
      ClawMotor.spin(reverse, ((Potentiometer.angle(degrees)-POTMID)), percent); //Inadvertant p control
    }
    isArm = false; //Arm no longer moving, movement stopped by elif in main
  }
}