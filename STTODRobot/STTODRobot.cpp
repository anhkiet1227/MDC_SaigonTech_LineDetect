#include "STTODRobot.h"

void STTODRobot::init(int IN11, int IN21, int EN11, int IN12, int IN22, int EN22, int IN13, int IN23, int EN33)
{
  _IN1 = IN11;
  _IN2 = IN21;
  _EN1 = EN11;
  _IN3 = IN12;
  _IN4 = IN22;
  _EN2 = EN22;
  _IN5 = IN13;
  _IN6 = IN23;
  _EN3 = EN33;
}
void STTODRobot::stop_omni(void)
{  
  digitalWrite(_IN1, 0);   
  digitalWrite(_IN2, 0);
  analogWrite(_EN1, 0);
  digitalWrite(_IN3, 0);   
  digitalWrite(_IN4, 0);
  analogWrite(_EN2, 0);
  digitalWrite(_IN5, 0);   
  digitalWrite(_IN6, 0);
  analogWrite(_EN3, 0);
}

void STTODRobot::rotate_omni(boolean typeRot, int PWM_rot)
{
  if (typeRot == false){
    digitalWrite(_IN1, 0);   
    digitalWrite(_IN2, 1);
    analogWrite(_EN1, PWM_rot);
    digitalWrite(_IN3, 0);   
    digitalWrite(_IN4, 1);
    analogWrite(_EN2, PWM_rot);
    digitalWrite(_IN5, 0);   
    digitalWrite(_IN6, 1);
    analogWrite(_EN3, PWM_rot);
  }
  else {
    digitalWrite(_IN1, 1);   
    digitalWrite(_IN2, 0);
    analogWrite(_EN1, PWM_rot);
    digitalWrite(_IN3, 1);   
    digitalWrite(_IN4, 0);
    analogWrite(_EN2, PWM_rot);
    digitalWrite(_IN5, 1);   
    digitalWrite(_IN6, 0);
    analogWrite(_EN3, PWM_rot);    
  }
}	

void STTODRobot::move_omni(int angle, int PWM)
{
  _sine = sin(angle * PI / 180.0);
  _cosine = cos(angle * PI / 180.0);
  _phi3 = _sine;
  _phi1 = -(sqrt(3) * _cosine + _sine) * 0.5;
  _phi2 = (sqrt(3) * _cosine - _sine) * 0.5;
  _maxPhi = abs(_phi1);
  if (_maxPhi < abs(_phi2))
    _maxPhi = abs(_phi2);
  if (_maxPhi < abs(_phi3))
    _maxPhi = abs(_phi3);
  _phi1 = _phi1 * (PWM / _maxPhi);
  _phi2 = _phi2 * (PWM  / _maxPhi);
  _phi3 = _phi3 * (PWM  / _maxPhi);
  if ( _phi1 >= 0){
    if (_phi1 <= 255 & _phi1 >=  0){
      _phi1 = _phi1;
    }
    else{
      if (_phi1>255){
        _phi1 = 255;  
      }
      else 
        _phi1 = 0; 
    }
    digitalWrite(_IN1, 0);   
    digitalWrite(_IN2, 1);
    analogWrite(_EN1, _phi1);
  }
  else {
    _phi1 = -_phi1;
    if (_phi1 <= 255 & _phi1 >= 0){
      _phi1 = _phi1;
    }
    else{
      if (_phi1>255){
        _phi1 = 255;  
      }
      else 
        _phi1 = 0; 
    }
    digitalWrite(_IN1, 1);   
    digitalWrite(_IN2, 0);
    analogWrite(_EN1, _phi1);
  }
  if (_phi2 >= 0){
    if (_phi2 <= 255 & _phi2 >=  0){
      _phi2 = _phi2;
    }
    else{
      if (_phi2>255){
        _phi2 = 255;  
      }
      else 
        _phi2 = 0; 
    }
    digitalWrite(_IN3, 0);   
    digitalWrite(_IN4, 1);
    analogWrite(_EN2, _phi2);
  }
  else {
    _phi2 = - _phi2;
    if (_phi2 <= 255 & _phi2 >= 0){
      _phi2 = _phi2;
    }
    else{
      if (_phi2>255){
        _phi2 = 255;  
      }
      else 
        _phi2 = 0; 
    }
    digitalWrite(_IN3, 1);   
    digitalWrite(_IN4, 0);
    analogWrite(_EN2, _phi2);
  }
  if (_phi3 >= 0){
    if (_phi3 <= 255 & _phi3 >=  0){
      _phi3 = _phi3;
    }
    else{
      if (_phi3>255){
        _phi3 = 255;  
      }
      else 
        _phi3 = 0; 
    }
    digitalWrite(_IN5, 0);   
    digitalWrite(_IN6, 1);
    analogWrite(_EN3, _phi3);
  }
  else {
    _phi3 = -_phi3;
    if (_phi3 <= 255 & _phi3 >= 0){
      _phi3 = _phi3;
    }
    else{
      if (_phi3>255){
        _phi3 = 255;  
      }
      else 
        _phi3 = 0; 
    }
    digitalWrite(_IN5, 1);   
    digitalWrite(_IN6, 0);
    analogWrite(_EN3, _phi3);
  }
}