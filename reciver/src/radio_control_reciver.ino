#define pwm_pin_1 2
#define pwm_pin_2 3
#define pwm_pin_3 4
#define pwm_pin_4 5
#define pwm_pin_5 6
#define ESD_pin 9
#define ppm_pin 8
#define ppm_high_time 100

#include "Arduino.h"
#include "math.h"
#include "Servo.h"

unsigned long int time = 0;
String inString = ""; // string to hold input
Servo pwm_channel_1, pwm_channel_2, pwm_channel_3, pwm_channel_4, pwm_channel_5, pwm_channel_6;
int last_pwm_pin_1_status = 0, last_pwm_pin_2_status = 0, last_pwm_pin_3_status = 0, last_pwm_pin_4_status = 0, last_pwm_pin_5_status = 0;
void setup()
{
  pwm_channel_1.attach(pwm_pin_1);
  pwm_channel_2.attach(pwm_pin_2);
  pwm_channel_3.attach(pwm_pin_3);
  pwm_channel_4.attach(pwm_pin_4);
  pwm_channel_5.attach(pwm_pin_5);
  pinMode(ESD_pin, 1);
  pinMode(ppm_pin, 1);
  Serial.begin(57600);
}

void loop()
{
  ppm_maker();
  // Read serial input:
  while (Serial.available() > 0)
  {
    int inChar = Serial.read();
    if (isDigit(inChar))
    {
      // convert the incoming byte to a char and add it to the string:
      inString += (char)inChar;
    }
    check_inchar(inChar);
  }
}
void ppm_maker(void)//salam
{
  int initial_time = micros();
  time = micros();
  int pwm_pin_1_status = digitalRead(pwm_pin_1);
  if (last_pwm_pin_1_status != pwm_pin_1_status)
  {
    digitalWrite(ppm_pin, HIGH);
    while (micros() - time < ppm_high_time)
      ;
    digitalWrite(ppm_pin, LOW);
    last_pwm_pin_1_status = pwm_pin_1_status;
  }
  time = micros();
  int pwm_pin_2_status = digitalRead(pwm_pin_2);
  if (last_pwm_pin_2_status != pwm_pin_2_status)
  {
    if (pwm_pin_2_status == 0)
    {
      digitalWrite(ppm_pin, HIGH);
      while (micros() - time < ppm_high_time)
        ;
      digitalWrite(ppm_pin, LOW);
    }
    last_pwm_pin_2_status = pwm_pin_2_status;
  }
  time = micros();
  int pwm_pin_3_status = digitalRead(pwm_pin_3);
  if (last_pwm_pin_3_status != pwm_pin_3_status)
  {
    if (pwm_pin_3_status == 0)
    {
      digitalWrite(ppm_pin, HIGH);
      while (micros() - time < ppm_high_time)
        ;
      digitalWrite(ppm_pin, LOW);
    }
    last_pwm_pin_3_status = pwm_pin_3_status;
  }
  time = micros();
  int pwm_pin_4_status = digitalRead(pwm_pin_4);
  if (last_pwm_pin_4_status != pwm_pin_4_status)
  {
    if (pwm_pin_4_status == 0)
    {
      digitalWrite(ppm_pin, HIGH);
      while (micros() - time < ppm_high_time)
        ;
      digitalWrite(ppm_pin, LOW);
    }
    last_pwm_pin_4_status = pwm_pin_4_status;
  }
  time = micros();
  int pwm_pin_5_status = digitalRead(pwm_pin_5);
  if (last_pwm_pin_5_status != pwm_pin_5_status)
  {
    if (pwm_pin_5_status == 0)
    {
      digitalWrite(ppm_pin, HIGH);
      while (micros() - time < ppm_high_time)
        ;
      digitalWrite(ppm_pin, LOW);
    }
    last_pwm_pin_5_status = pwm_pin_5_status;
  }
  while (micros() - initial_time < 25000)
    ;
}
void check_inchar(int inChar)
{
  if (inChar == 'T')
  {
    // Serial.println();
    // Serial.print("Trottle=");
    // Serial.println(inString.toInt());
    // analogWrite(11, inString.toInt() / 4);
    int val = map(inString.toInt(), 0, 1023, 0, 180);
    pwm_channel_1.write(val);
    inString = "";
  }
  if (inChar == 'P')
  {
    // Serial.println();
    // Serial.print("Pitch=");
    // Serial.println(inString.toInt());
    // analogWrite(10, inString.toInt() / 4);
    int val = map(inString.toInt(), 0, 1023, 0, 180);
    pwm_channel_2.write(val);
    inString = "";
  }
  if (inChar == 'R')
  {
    // Serial.println();
    // Serial.print("Roll=");
    // Serial.println(inString.toInt());
    // analogWrite(9, inString.toInt() / 4);
    int val = map(inString.toInt(), 0, 1023, 0, 180);
    pwm_channel_3.write(val);
    inString = "";
  }
  if (inChar == 'Y')
  {
    // Serial.println();
    // Serial.print("Yaw=");
    // Serial.println(inString.toInt());
    // analogWrite(6, inString.toInt() / 4);
    int val = map(inString.toInt(), 0, 1023, 0, 180);
    pwm_channel_4.write(val);
    inString = "";
  }
  if (inChar == 'E')
  {
    // Serial.println();
    // Serial.print("ESD=");
    // Serial.println(inString.toInt());
    digitalWrite(ESD_pin, inString.toInt());
    inString = "";
  }
  if (inChar == 'D')
  {
    // Serial.println();
    // Serial.print("PID=");
    // Serial.println(inString.toInt());
    // analogWrite(3, inString.toInt() / 4);
    int val = map(inString.toInt(), 0, 1023, 0, 180);
    pwm_channel_5.write(val);
    inString = "";
  }
}
