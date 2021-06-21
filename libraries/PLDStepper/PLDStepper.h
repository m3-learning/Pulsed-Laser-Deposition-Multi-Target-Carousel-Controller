#ifndef pld_stepper_h
#define pld_stepper_h

#include "Arduino.h"
#include <stdbool.h>

#define CLOCKWISE 0
#define COUNTER_CLOCKWISE 1

//Target location relative to home position. These can be adjusted per system
#define TARGET1 14
#define TARGET2 74
#define TARGET3 134
#define TARGET4 194
#define TARGET5 254
#define TARGET6 314

/***
 * This class contains all functions needed control the Neccera Multi-Target Carousel for a Pulsed Laser Deposition (PLD) System. PCB Schematics are provided for
 * that allows direct control of the Carousel stepper motors with this class or another software.
 * @author Ryan Forelli
 * @version 2.3
 * Date of creation: April 21, 2021
 * Last Date Modified: June 2, 2021
 */

class PLDStepper{
    private:
        int steps_per_rev;    //Number of steps per revolution
        int dir_pin;          //Direction pin on A4988
        int step_pin;         //Step pin on A4988
        float rotation_speed; //Rotation speed in deg/s
        long prev_time;       //Keep track of last time motor stepped
    public:
        PLDStepper(int dir_pin, int step_pin, float rotation_speed, int direction, int steps_per_rev);
        int direction;                               //Current motor direction
        bool homing;                                 //Homing
        long home_counter;                           //Counter to stop homing sequence in case of sensor failure
        bool stop_raster_requested;                  //Raster stop requested
        bool rastering;                              //Rastering
        float base_raster_angle;                     //Original angle rastering began from
        bool rotating;                               //Motor rotating (angle rotation)
        bool c_rotating;                             //Continuousing rotating
        float curr_angle;                            //Current angle of stepper
        long delay_micros;                           //Current step delay
        long delay_micros_old;                       //Original step delay
        long delay_micros_half;                      //Half step delay
        void setDirection(int direction);            //Set the direction of the motor
        void setRotationSpeed(float rotation_speed); //Set rotation speed
        void resetAngle();                           //Reset rangle to 0 after a full turn
        void beginRotate();                          //Begin rotation of target rotation motor
        void beginRaster();                          //Begin rastering
        void beginHome();                            //Begin homing raster motor
        void beginContinuousRotate();                //Begin continuous rotation        
        void checkStepHome();                        //Check if raster motor should step during while homing
        void checkStepCRot();                        //Check if target rotation motor should step during continuous rotation
        void checkStepRast(float raster_angle);      //Check if raster motor should step
        void checkStepRot(float angle_rotate_to);    //Check if target rotation motor should step
        void stopContinuousRotate();                 //Stop continuous rotation
        void step();                                 //Step motor
};

#endif