int Emergency_shut_down_pin = 2;
#include "Arduino.h"
#include "string.h"

String instring = "";
int C;
String outstring;

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
  int PID_tuner = analogRead(A1);
  instring = (String(Trottle) + 'T' + String(Pitch) + 'P' + String(Roll) + 'R' + String(Yaw) + 'Y' + String(Esd) + 'E' + String(PID_tuner) + 'D');
  convertor(instring);
  Serial.println(outstring);
  delay(500);
}

String convertor(String input)
{
  C = input.length();   //calculate the length of the string
  return outstring = (input + 'N' + String(C));   //add the length of the string with 2 control charecters before and after that
}