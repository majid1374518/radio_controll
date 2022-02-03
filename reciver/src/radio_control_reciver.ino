#define pwm_pin_1 2
#define pwm_pin_2 3
#define pwm_pin_3 4
#define pwm_pin_4 5
#define pwm_pin_5 6
#define ESD_pin 9
#define ppm_pin 8
#define ppm_high_time 100
#define trottle 0
#define pitch 1
#define roll 2
#define yaw 3
#define esd 4
#define pid 5

#include "Arduino.h"
#include "math.h"
#include "Servo.h"

unsigned long int time = 0;
uint16_t inChar1, inChar2, inChar3;
int input2, input3, input4;
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
    uint16_t input1 = Serial.read();
    input2 = input1;
    input3 = input1;
    input4 = input1;
    input3 = (input3 >> 7) & 0x01;
    input4 = (input4 >> 15) & 0x01;
    input4 = ~input4;
    if (input3 & input4)
    {
      input2 = (input2 >> 4) & 0x07;
      if (uint8_t(input2) == trottle)
      {
        inChar1 = trottle;
        inChar2 = input1;
        inChar3 = input1;
        inChar2 = (inChar2 >> 0) & 0x07;
        inChar3 = (inChar3 >> 8) & 0xFF;
        inChar2 = 127 * inChar2 + inChar3;
        check_inchar(inChar1);
      }
      if (uint8_t(input2) == pitch)
      {
        inChar1 = pitch;
        inChar2 = input1;
        inChar3 = input1;
        inChar2 = (inChar2 >> 0) & 0x07;
        inChar3 = (inChar3 >> 8) & 0xFF;
        inChar2 = 127 * inChar2 + inChar3;
        check_inchar(inChar1);
      }
      if (uint8_t(input2) == roll)
      {
        inChar1 = roll;
        inChar2 = input1;
        inChar3 = input1;
        inChar2 = (inChar2 >> 0) & 0x07;
        inChar3 = (inChar3 >> 8) & 0xFF;
        inChar2 = 127 * inChar2 + inChar3;
        check_inchar(inChar1);
      }
      if (uint8_t(input2) == yaw)
      {
        inChar1 = yaw;
        inChar2 = input1;
        inChar3 = input1;
        inChar2 = (inChar2 >> 0) & 0x07;
        inChar3 = (inChar3 >> 8) & 0xFF;
        inChar2 = 127 * inChar2 + inChar3;
        check_inchar(inChar1);
      }
      if (uint8_t(input2) == esd)
      {
        inChar1 = esd;
        inChar2 = input1;
        inChar3 = input1;
        inChar2 = (inChar2 >> 0) & 0x07;
        inChar3 = (inChar3 >> 8) & 0xFF;
        inChar2 = 127 * inChar2 + inChar3;
        check_inchar(inChar1);
      }
      if (uint8_t(input2) == pid)
      {
        inChar1 = pid;
        inChar2 = input1;
        inChar3 = input1;
        inChar2 = (inChar2 >> 0) & 0x07;
        inChar3 = (inChar3 >> 8) & 0xFF;
        inChar2 = 127 * inChar2 + inChar3;
        check_inchar(inChar1);
      }
    }
    // convert the incoming byte to a char and add it to the string:
    // inString += (char)inChar1;
    // if (inChar != 'N')
    //{
    //   length_inString += (char)inChar;
    // }
    // if (inChar == 'N')
    //{
    //   original_inString = length_inString;
    //   length_inString = "";
    // }
  }
  // Serial.println("ORIGINAL STRING=" + original_inString);
  // Serial.println("STRING LENGTH=" + length_inString);
  // delay(500);
  // check_received_string(original_inString, length_inString);
  // length_inString = "";
  // original_inString = "";
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
void check_inchar(unsigned int inChar)
{
  if (inChar == trottle)
  {
    int val = map(inChar2, 0, 1023, 0, 180);
    pwm_channel_1.write(val);
  }
  if (inChar == pitch)
  {
    int val = map(inChar2, 0, 1023, 0, 180);
    pwm_channel_2.write(val);
  }
  if (inChar == roll)
  {
    int val = map(inChar2, 0, 1023, 0, 180);
    pwm_channel_3.write(val);
  }
  if (inChar == yaw)
  {
    int val = map(inChar2, 0, 1023, 0, 180);
    pwm_channel_4.write(val);
  }
  if (inChar == esd)
  {
    digitalWrite(ESD_pin, inChar2);
  }
  if (inChar == pid)
  {
    int val = map(inChar2, 0, 1023, 0, 180);
    pwm_channel_5.write(val);
  }
}
// void check_received_string(String input1, String input2) // check the length of the original string
//{

// int L = input1.length(); // convert the length string into the integer
// if (L != input2.toInt()) // compare the length of the original string and the extracted length
//{
//   if they are not equal, we read the serial input again
//  digitalWrite(ESD_pin, 1);
//  delay(10);
//  digitalWrite(ESD_pin, 0);
//}
//}