#include "PololuDualG2HighPowerMotorShield.h"

PololuDualG2HighPowerMotorShield::PololuDualG2HighPowerMotorShield(
    int m1dir,
    int m1pwm,
    int m2dir,
    int m2pwm)
{
    this->m_m1dir = m1dir;
    this->m_m1pwm = m1pwm;
    this->m_m2dir = m2dir;
    this->m_m2pwm = m2pwm;

    this->m_max_pwm_output = DEFAULT_MAX_SPEED_VALUE;
    this->m_min_pwm_output = DEFAULT_MIN_SPEED_VALUE;

    this->m_write_resolution = 8;
}

PololuDualG2HighPowerMotorShield::PololuDualG2HighPowerMotorShield(
    int m1dir,
    int m1pwm,
    int m2dir,
    int m2pwm,
    int analogWriteResolution)
{

    this->m_m1dir = m1dir;
    this->m_m1pwm = m1pwm;
    this->m_m2dir = m2dir;
    this->m_m2pwm = m2pwm;

    int writeResolution = analogWriteResolution;
    if (writeResolution > MAX_ANALOG_WRITE_RESOLUTION) {
        writeResolution = MAX_ANALOG_WRITE_RESOLUTION;
    }
    this->m_write_resolution = writeResolution;

    int max_pwm_output_resolution = (1 << writeResolution) - 1;
    if (max_pwm_output_resolution > DEFAULT_MAX_12_BIT_SPEED_VALUE) {
        max_pwm_output_resolution = DEFAULT_MAX_12_BIT_SPEED_VALUE;
    }
    this->m_max_pwm_output = max_pwm_output_resolution;
    this->m_min_pwm_output = -max_pwm_output_resolution;
}

void PololuDualG2HighPowerMotorShield::init() {

    pinMode(this->m_m1dir, OUTPUT);
    pinMode(this->m_m1pwm, OUTPUT);
    pinMode(this->m_m2dir, OUTPUT);
    pinMode(this->m_m2pwm, OUTPUT);

#if defined(__SAM3X8E__)
    analogWriteResolution(this->m_write_resolution);
#endif // __SAM3X8E
}

// speed values should be -255 to 0 to 255 when write resolution is 8
// Convention is the following:
// speed = + -> direction = 1
// speed = - -> direction = 0

void PololuDualG2HighPowerMotorShield::setSpeed1(int speed) {

    int speedValue = constrain(speed, this->m_min_pwm_output, this->m_max_pwm_output);
    int outputSpeedValue = abs(speedValue);

    if (speedValue >= 0) {
        analogWrite(this->m_m1pwm, outputSpeedValue);
        digitalWrite(this->m_m1dir, 1);
    } else {
        analogWrite(this->m_m1pwm, outputSpeedValue);
        digitalWrite(this->m_m1dir, 0);
    }
}

void PololuDualG2HighPowerMotorShield::setSpeed2(int speed) {

    int speedValue = constrain(speed, this->m_min_pwm_output, this->m_max_pwm_output);
    int outputSpeedValue = abs(speedValue);

    if (speedValue >= 0) {
        analogWrite(this->m_m2pwm, outputSpeedValue);
        digitalWrite(this->m_m2dir, 1);
    } else {
        analogWrite(this->m_m2pwm, outputSpeedValue);
        digitalWrite(this->m_m2dir, 0);
    }
}

void PololuDualG2HighPowerMotorShield::setMaxPwmOutput(int maxOutput) {

    if (maxOutput < 0) return;

    this->m_max_pwm_output = maxOutput;
    this->m_min_pwm_output = -maxOutput;
}