#include <PLDStepper.h>
#include <SoftwareSerial.h>
#include <Arduino.h>

PLDStepper rotate_motor(7, 6, 10, 0, 16000);
PLDStepper raster_motor(2, 3, 10, 0, 16000);

char command;
float angle_rotate_to = -1;
float new_rot_speed = -1;
float angle_rotate_to1 = -1;
float new_rot_speed1 = -1;
float raster_angle = -1;

//Status bits
int homing_bit = 8;
int rastering_bit = 13;
int rotating_bit = A4;

void setup() {
    Serial.begin(9600);
    
    //MS pins
    pinMode(9, OUTPUT);
    pinMode(10, OUTPUT);
    pinMode(11, OUTPUT);
    digitalWrite(9, HIGH);
    digitalWrite(10, HIGH);
    digitalWrite(11, HIGH);

    //MS pins
    pinMode(A3, OUTPUT);
    pinMode(A2, OUTPUT);
    pinMode(A1, OUTPUT);
    digitalWrite(A3, HIGH);
    digitalWrite(A2, HIGH);
    digitalWrite(A1, HIGH);

    //Status bigs
    pinMode(homing_bit, OUTPUT);
    pinMode(rastering_bit, OUTPUT);
    pinMode(rotating_bit, OUTPUT);
    digitalWrite(homing_bit, LOW);
    digitalWrite(rastering_bit, LOW);
    digitalWrite(rotating_bit, LOW);

}

void loop() {

    //Check for any commands received
    if(Serial.available() > 0){
        Serial.readBytes(&command, 1);
    }

    switch(command){
        case ',':{
            angle_rotate_to = Serial.parseFloat(SKIP_NONE, ',');
            rotate_motor.beginRotate();
            break;
        }case '#':{
            new_rot_speed = Serial.parseFloat(SKIP_NONE, '.');
            rotate_motor.setRotationSpeed(new_rot_speed);
            break;
        }case 'g':{
            rotate_motor.beginContinuousRotate();
            digitalWrite(rotating_bit, HIGH);
            break;
        }case 'r':{
            rotate_motor.stopContinuousRotate();
            break;
        }case 's':{
            raster_angle = Serial.parseFloat(SKIP_NONE, 's');
            raster_motor.beginRaster(); 
            digitalWrite(rastering_bit, HIGH);
            break;
        }case 'h':{
            raster_motor.stop_raster_requested = true;
            digitalWrite(rastering_bit, LOW);
            break;
        }case '`':{
            new_rot_speed1 = Serial.parseFloat(SKIP_NONE, '`');
            raster_motor.setRotationSpeed(new_rot_speed1);
            break;
        }case 'o':{
            raster_motor.beginHome();
            digitalWrite(homing_bit, HIGH);
            break;
        }case 't':{
            angle_rotate_to1 = Serial.parseFloat(SKIP_NONE, 't');
            raster_motor.beginRotate();
            break;
        }case '>':{
            raster_motor.step();
            break;
        }case '<':{
            raster_motor.setDirection(1);
            raster_motor.step();
            raster_motor.setDirection(0);
            break;
        }default:
            break;
    }

    //Check rotation step
    if((angle_rotate_to1 != -1) && (raster_motor.rastering == false) && (raster_motor.rotating == true))
        raster_motor.checkStepRot(angle_rotate_to1);
    else
        angle_rotate_to1 = -1;
    

    //Check homing step
    if(raster_motor.homing == true)
        raster_motor.checkStepHome();
    else
        digitalWrite(homing_bit, LOW);  

    //Check continuous rotation step
    if(rotate_motor.c_rotating == true){
        rotate_motor.checkStepCRot();
        angle_rotate_to = -1;
        if(raster_motor.direction == 1)
            rotate_motor.delay_micros = rotate_motor.delay_micros_half;
        else
            rotate_motor.delay_micros = rotate_motor.delay_micros_old;
    }else
        digitalWrite(rotating_bit, LOW);  
    
    //Check roation step
    if(angle_rotate_to != -1 && rotate_motor.c_rotating == false)
        rotate_motor.checkStepRot(angle_rotate_to);
    else
        angle_rotate_to = -1;
    
    //Check if rastering stop was requested
    if(raster_motor.stop_raster_requested == true){
        if(abs(raster_motor.curr_angle - raster_motor.base_raster_angle) < .01){
        raster_motor.rastering = false;
        raster_motor.stop_raster_requested = false;
        raster_motor.setDirection(0);
        }
    }

    //Check for rastering step
    if((raster_angle != -1) && (raster_motor.rastering == true))
        raster_motor.checkStepRast(raster_angle);
    else
        raster_angle = -1;

    command = 'n';
}
