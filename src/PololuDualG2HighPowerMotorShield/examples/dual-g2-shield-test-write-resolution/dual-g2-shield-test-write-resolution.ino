#include <PololuDualG2HighPowerMotorShield.h>

// Motor control pins
#define MOTOR1_DIR_PIN 2
#define MOTOR1_PWM_PIN 3

#define MOTOR2_DIR_PIN 6
#define MOTOR2_PWM_PIN 7

PololuDualG2HighPowerMotorShield motorController(MOTOR1_DIR_PIN, MOTOR1_PWM_PIN, MOTOR2_DIR_PIN, MOTOR2_PWM_PIN, 12);

void setup() {

    motorController.init();
}

void loop() {

    int speedLeft = 0;
    int speedRight = 0;
    
    motorController.setSpeed1(speedLeft);
    motorController.setSpeed2(speedRight);
}