int Emergency_shut_down_pin = 2;
#include "Arduino.h"
void setup()
{
  Serial.begin(57600);

  pinMode(Emergency_shut_down_pin, INPUT);
}

void loop() 
{
  int Trottle = analogRead(A5);
  int Pitch = analogRead(A4);
  int Roll = analogRead(A3);
  int Yaw = analogRead(A2);
  int Esd = digitalRead(Emergency_shut_down_pin);
  int PID_tuner =  analogRead(A1);
  //String p1 =  "\t";
  //Serial.println(Trottle + p1 + Pitch + p1 + Roll + p1 + Yaw + p1 + Esd + p1 + PID_tuner);
  Serial.println(String(Trottle) +'T' + String(Pitch) + 'P' + String(Roll) + 'R' + String(Yaw) + 'Y' + String(Esd) +  'E' + String(PID_tuner) + 'D');
  delay(1000);
}
