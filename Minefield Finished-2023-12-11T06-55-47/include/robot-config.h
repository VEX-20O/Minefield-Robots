using namespace vex;

extern brain Brain;

// VEXcode devices
extern motor ClawMotor;
extern pot Potentiometer;
extern controller Controller1;
extern motor DriveL;
extern motor DriveR;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );