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

    this->init();
}

PololuDualG2HighPowerMotorShield::PololuDualG2HighPowerMotorShield(
    int m1dir,
    int m1pwm,
    int m2dir,
    int m2pwm,
    int writeResolution)
{

    PololuDualG2HighPowerMotorShield(m1dir, m1pwm, m2dir, m2pwm);

    this->m_max_pwm_output = DEFAULT_MAX_12_BIT_SPEED_VALUE;
    this->m_min_pwm_output = DEFAULT_MIN_12_BIT_SPEED_VALUE;

    this->m_write_resolution = writeResolution;

#if defined(__SAM3X8E__)
    analogWriteResolution(writeResolution);
#endif // __SAM3X8E

}

void PololuDualG2HighPowerMotorShield::init() {

    pinMode(this->m_m1dir, OUTPUT);
    pinMode(this->m_m1pwm, OUTPUT);
    pinMode(this->m_m2dir, OUTPUT);
    pinMode(this->m_m2pwm, OUTPUT);
}

// speed values should be -255 to 0 to 255
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
        analogWrite(this->m_m1dir, 0);
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
        analogWrite(this->m_m2dir, 0);
    }
}

void PololuDualG2HighPowerMotorShield::setMaxPwmOutput(int maxOutput) {

    if (maxOutput < 0) return;

    this->m_max_pwm_output = maxOutput;
    this->m_min_pwm_output = -maxOutput;
}