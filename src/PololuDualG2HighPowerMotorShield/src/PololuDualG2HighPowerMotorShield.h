#ifndef POLOLU_DUAL_G2_HIGH_POWER_MOTOR_SHIELD_H
#define POLOLU_DUAL_G2_HIGH_POWER_MOTOR_SHIELD_H

#include <Arduino.h>

/**
 * A wrapping class to operate a PololuDualG2HighPowerMotorShield motor driver
 *  https://www.pololu.com/product/2515
 *  https://www.pololu.com/docs/0J72/4.b
 * 
 * Without consideration to the current sensing capabilities of this family of
 * motor drivers, this library can interface with any shield. For testing purposes,
 * we'll interface to 18v18.
 * 
 * Expected logic connections:
 * 
 *  VDD     5v
 * 
 * Uno pwm pins:
 *   3, 5, 6, 9, 10, 11, 490 Hz (pins 5 and 6: 980 Hz)
 *
 * Due pwm pins:
 *   2-13, 1000 Hz
 *   use analogWriteResolution to set higher resolution. i.e. "12" for 12-bit -> 4096 bit resolution 
 *   pins DAC0 and DAC1 are "true" analog. 
*/

#define PIN_NOT_CONNECTED -1
#define DEFAULT_MAX_SPEED_VALUE 255
#define DEFAULT_MIN_SPEED_VALUE -255
#define DEFAULT_MAX_12_BIT_SPEED_VALUE 4095
#define DEFAULT_MIN_12_BIT_SPEED_VALUE -4095

class PololuDualG2HighPowerMotorShield {

    public:
        PololuDualG2HighPowerMotorShield(
            int m1dir,
            int m1pwm,
            int m2dir,
            int m2pwm
        );

        // See https://www.arduino.cc/reference/en/language/functions/zero-due-mkr-family/analogwriteresolution/
        // for details on the analogWriteResolution() method available in the Due
        // and other boards. The maximum number of bits for the write resolution is
        // 12 for the Due. With a value of 12, possible values for analogWrite are
        // between 0 and 4095. Sketches utilizing this constructor will function as
        // expected when compiling for the Arduino Due target; otherwise, the call
        // to analogWriteResolution() is not executed.

        PololuDualG2HighPowerMotorShield(
            int m1dir,
            int m1pwm,
            int m2dir,
            int m2pwm,
            int writeResolution // num bits max is 12
        );

        void setSpeed1(int speed);
        void setSpeed2(int speed);

        void setMaxPwmOutput(int maxOutput);

        // TODO: Add support for the following
        // MxCS (output from shield): current sense
        // MxFLT (output from shield): fault inidication
        // MxSLP (input to shield): These pins are pulled high, enabling the driver
        //  by default. Driving these pins low puts the motor driver channels into
        //  a low-current sleep mode and disables the motor outputs (setting them to
        //  high impedance).
        // MxVREF 

    private:

        void init();

        int m_m1dir;
        int m_m1pwm;
        int m_m2dir;
        int m_m2pwm;

        int m_max_pwm_output;       // The maximum value to use when setting pwm signals
        int m_min_pwm_output;       // The minimum value to use when setting pwm signals. Typically
                                    // the negative of m_max_pwm_output

        int m_write_resolution;     // The number of bits to use when invoking analogWriteResolution()
};

#endif // POLOLU_DUAL_G2_HIGH_POWER_MOTOR_SHIELD_H