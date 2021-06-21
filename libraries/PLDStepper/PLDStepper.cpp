#include "PLDStepper.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

PLDStepper::PLDStepper(int dir_pin, int step_pin, float rotation_speed, int direction, int steps_per_rev){
    this->dir_pin = dir_pin;
    this->step_pin = step_pin;
    this->rotation_speed = rotation_speed;
    this->direction = direction;
    this->steps_per_rev = steps_per_rev;
    this->curr_angle = 0;
    this->stop_raster_requested = false;
    this->home_counter = 0;
    pinMode(dir_pin, OUTPUT);
    pinMode(step_pin, OUTPUT);
    digitalWrite(dir_pin, direction);
    pinMode(4, INPUT_PULLUP); //IR Sensor pin
    this->delay_micros, this->delay_micros_old = (1/(((float)steps_per_rev/360)*this->rotation_speed))*1000000;
    this->delay_micros_half = this->delay_micros / 5;
}

void PLDStepper::setDirection(int direction){
    this->direction = direction;
    digitalWrite(this->dir_pin, direction);
}

void PLDStepper::beginRotate(){
    this->prev_time = micros();
    this->rotating = true;
}

void PLDStepper::checkStepRot(float angle_rotate_to){
    if(((micros() - this->prev_time) >= this->delay_micros) && this->rotating == true){
        digitalWrite(this->step_pin, HIGH);
        digitalWrite(this->step_pin, LOW);
        this->curr_angle += .0225;
        resetAngle();
        this->prev_time = micros();
        if((this->curr_angle > (angle_rotate_to - .0225)) && (this->curr_angle < (angle_rotate_to + .0225))){
            this->rotating = false;
        }
    }
}

void PLDStepper::resetAngle(){
    if(this->curr_angle >= 360){
        this->curr_angle = 0;
    }
}

void PLDStepper::setRotationSpeed(float rot_speed){
    if(rot_speed <= 90 && rot_speed >= .1){
        this->rotation_speed = rot_speed;
        this->delay_micros, this->delay_micros_old = (1/(((float)steps_per_rev/360)*this->rotation_speed))*1000000;
        this->delay_micros_half = this->delay_micros / 5;
    }
}

void PLDStepper::beginContinuousRotate(){
    this->prev_time = micros();
    this->c_rotating = true;
}

void PLDStepper::checkStepCRot(){
    if(((micros() - this->prev_time) >= this->delay_micros) && (this->c_rotating == true)){
        digitalWrite(this->step_pin, HIGH);
        digitalWrite(this->step_pin, LOW);
        this->curr_angle += .0225;
        resetAngle();
        this->prev_time = micros();
    }
}

void PLDStepper::stopContinuousRotate(){
    this->c_rotating = false;
}

void PLDStepper::beginRaster(){
    this->prev_time = micros();
    this->rastering = true;
    this->base_raster_angle = this->curr_angle;
}

void PLDStepper::checkStepRast(float raster_angle){
    float direction_rotate = raster_angle/2;
    if(((micros() - this->prev_time) >= this->delay_micros) && this->rastering == true){
        digitalWrite(this->step_pin, HIGH);
        digitalWrite(this->step_pin, LOW);
        if(this->direction == 0)
            this->curr_angle += .0225;
        else if(this->direction == 1)
            this->curr_angle -= .0225;
        this->prev_time = micros();
        if((this->curr_angle - this->base_raster_angle) >= direction_rotate)
            setDirection(COUNTER_CLOCKWISE);
        else if((this->base_raster_angle - this->curr_angle) >= direction_rotate)
            setDirection(CLOCKWISE);
    }
}

void PLDStepper::beginHome(){
    this->prev_time = micros();
    this->homing = true;
}

void PLDStepper::checkStepHome(){
    if(((micros() - this->prev_time) >= this->delay_micros) && (this->homing == true)){
        if((digitalRead(4) == HIGH) || (this->home_counter > steps_per_rev)){
            this->homing = false;
            this->home_counter = 0;
            this->curr_angle = 0;
            return;
        }
        digitalWrite(this->step_pin, HIGH);
        digitalWrite(this->step_pin, LOW);
        this->curr_angle += .0225;
        this->prev_time = micros();
        resetAngle();
        this->home_counter++;
    }
}

void PLDStepper::step(){
    if(this->rastering == false){
        digitalWrite(this->step_pin, HIGH);
        digitalWrite(this->step_pin, LOW);
        this->curr_angle += .0225;
        resetAngle();
    }
}