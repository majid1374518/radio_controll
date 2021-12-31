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
String inString = "";          // string to hold input
String original_inString = ""; // input without length assign to this variable
String length_inString = "";   // lengh of the input assign here
Servo pwm_channel_1, pwm_channel_2, pwm_channel_3, pwm_channel_4, pwm_channel_5, pwm_channel_6;
int last_pwm_pin_1_status = 0, last_pwm_pin_2_status = 0, last_pwm_pin_3_status = 0, last_pwm_pin_4_status = 0, last_pwm_pin_5_status = 0;
void setup()
{
  pwm_channel_1.attach(pwm_pin_1);
  pwm_channel_2.attach(pwm_pin_2);
  pwm_channel_3.attach(pwm_pin_3);
  pwm_channel_4.attach(pwm_pin_4);
  pwm_channel_5.attach(pwm_pin_5);
  pinMode(ESD_pin, OUTPUT);
  pinMode(ppm_pin, OUTPUT);
  pinMode(10, OUTPUT);
  Serial.begin(57600);
}

void loop()
{

  ppm_maker();

  // Read serial input:
  while (Serial.available())
  {
    int inChar = Serial.read();
    if (isDigit(inChar))
    {
      // convert the incoming byte to a char and add it to the string:
      inString += (char)inChar;
    }
    if (inChar != 'N')
    {
      length_inString += (char)inChar;
    }
    if (inChar == 'N')
    {
      original_inString = length_inString;
      length_inString = "";
    }
    check_inchar(inChar);
  }
  Serial.println("ORIGINAL STRING=" + original_inString);
  Serial.println("STRING LENGTH=" + length_inString);
  delay(500);
  check_received_string(original_inString, length_inString);
  length_inString = "";
  original_inString = "";
}
void ppm_maker(void)
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
    int val = map(inString.toInt(), 0, 1023, 0, 180);
    pwm_channel_1.write(val);
    inString = "";
  }
  if (inChar == 'P')
  {
    int val = map(inString.toInt(), 0, 1023, 0, 180);
    pwm_channel_2.write(val);
    inString = "";
  }
  if (inChar == 'R')
  {
    int val = map(inString.toInt(), 0, 1023, 0, 180);
    pwm_channel_3.write(val);
    inString = "";
  }
  if (inChar == 'Y')
  {
    int val = map(inString.toInt(), 0, 1023, 0, 180);
    pwm_channel_4.write(val);
    inString = "";
  }
  if (inChar == 'E')
  {
    digitalWrite(ESD_pin, inString.toInt());
    inString = "";
  }
  if (inChar == 'D')
  {
    int val = map(inString.toInt(), 0, 1023, 0, 180);
    pwm_channel_5.write(val);
    inString = "";
  }
}
void check_received_string(String input1, String input2) // check the length of the original string
{

  int L = input1.length(); // convert the length string into the integer
  if (L != input2.toInt()) // compare the length of the original string and the extracted length
  {
    //  if they are not equal, we read the serial input again
    digitalWrite(ESD_pin, 1);
    delay(10);
    digitalWrite(ESD_pin, 0);
  }
}