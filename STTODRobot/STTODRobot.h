#ifndef STTODRobot_h
#define STTODRobot_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#elif defined(WIRING)
#include "Wiring.h"
#else
#include "WProgram.h"
#include "pins_arduino.h"
#endif


class STTODRobot {
  public:
//    STTODRobot();
    
    void init(int IN11, int IN21, int EN11, int IN12, int IN22, int EN22, int IN13, int IN23, int EN33);
    void move_omni (int angle, int PWM);
    void rotate_omni(boolean typeRot, int PWM_rot);
    void stop_omni(void);

 
  private:
    int _IN1;
    int _IN2;
    int _EN1;
    int _IN3;
    int _IN4;
    int _EN2;
    int _IN5;
    int _IN6;
    int _EN3;
    double _maxPhi;
    double _phi1, _phi2, _phi3;
    double _sine, _cosine;
};

#endif