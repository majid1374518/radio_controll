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

const int BUFFER_SIZE = 14;
char buf[BUFFER_SIZE];
unsigned long int time = 0;
uint16_t inChar;
uint16_t input1, input2, input3, input4, input5, input6, input7, input8, input9, input10, input11, input12;
uint16_t check1, check2, check3, check4, check5, check6, check7, check8, check9, check10, check11, check12;
uint16_t joystick1, joystick2, joystick3, joystick4, joystick5, joystick6;
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
  // Read serial input:
  while (Serial.available())
  {
    // reading the incoming data with the function below
    Serial.readBytesUntil('\r', buf, BUFFER_SIZE);
    // we put each byte in a integer
    input1 = buf[1];
    check1 = input1;
    input2 = buf[2];
    check2 = input2;
    input3 = buf[3];
    check3 = input3;
    input4 = buf[4];
    check4 = input4;
    input5 = buf[5];
    check5 = input5;
    input6 = buf[6];
    check6 = input6;
    input7 = buf[7];
    check7 = input7;
    input8 = buf[8];
    check8 = input8;
    input9 = buf[9];
    check9 = input9;
    input10 = buf[10];
    check10 = input10;
    input11 = buf[11];
    check11 = input11;
    input12 = buf[12];
    check12 = input12;
    // with this variables we extract binary '1' for even bytes and binary '0' for odd bytes
    check1 = (check1 >> 7) & 0x01;
    check2 = (check2 >> 7) & 0x01;
    check3 = (check3 >> 7) & 0x01;
    check4 = (check4 >> 7) & 0x01;
    check5 = (check5 >> 7) & 0x01;
    check6 = (check6 >> 7) & 0x01;
    check7 = (check7 >> 7) & 0x01;
    check8 = (check8 >> 7) & 0x01;
    check9 = (check9 >> 7) & 0x01;
    check10 = (check10 >> 7) & 0x01;
    check11 = (check11 >> 7) & 0x01;
    check12 = (check12 >> 7) & 0x01;
    // with the check bit for each byte, we control the data loss with isshown below:
    if ((check1 & ~check2) && (check3 & ~check4) && (check5 & ~check6) && (check7 & ~check8) && (check9 & ~check10) && (check11 & ~check12))
    {
      Serial.println("ok");
      // we use these variables to check whitch joystick has been moved
      joystick1 = input1;
      joystick2 = input3;
      joystick3 = input5;
      joystick4 = input7;
      joystick5 = input9;
      joystick6 = input11;
      joystick1 = (joystick1 >> 4) & 0x07;
      joystick2 = (joystick2 >> 4) & 0x07;
      joystick3 = (joystick3 >> 4) & 0x07;
      joystick4 = (joystick4 >> 4) & 0x07;
      joystick5 = (joystick5 >> 4) & 0x07;
      joystick6 = (joystick6 >> 4) & 0x07;
      if (uint8_t(joystick1) == trottle)
      {
        inChar = trottle;
        input1 = (input1 >> 0) & 0x07;
        input2 = (input2 >> 0) & 0x7F;
        // we use this equation to extract the 10 bit value that has been sent from transmitter
        input1 = 127 * input1 + input2;
        check_inchar(inChar, input1);
      }
      if (uint8_t(joystick2) == pitch)
      {
        inChar = pitch;
        input3 = (input1 >> 0) & 0x07;
        input4 = (input2 >> 0) & 0x7F;
        input3 = 127 * input3 + input4;
        check_inchar(inChar, input3);
      }
      if (uint8_t(joystick3) == roll)
      {
        inChar = roll;
        input5 = (input5 >> 0) & 0x07;
        input6 = (input6 >> 8) & 0xFF;
        input5 = 127 * input5 + input6;
        check_inchar(inChar, input5);
      }
      if (uint8_t(joystick4) == yaw)
      {
        inChar = yaw;
        input7 = (input7 >> 0) & 0x07;
        input8 = (input8 >> 8) & 0xFF;
        input7 = 127 * input7 + input8;
        check_inchar(inChar, input7);
      }
      if (uint8_t(joystick5) == esd)
      {
        inChar = esd;
        input9 = (input9 >> 0) & 0x07;
        input10 = (input10 >> 8) & 0xFF;
        input9 = 127 * input9 + input10;
        check_inchar(inChar, input9);
      }
      if (uint8_t(joystick6) == pid)
      {
        inChar = pid;
        input11 = (input11 >> 0) & 0x07;
        input12 = (input12 >> 8) & 0xFF;
        input11 = 127 * input11 + input12;
        check_inchar(inChar, input11);
      }
    }
    ppm_maker();
  }
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
void check_inchar(unsigned int IN1, unsigned int IN2)
{
  if (IN1 == trottle)
  {
    int val = map(IN2, 0, 1023, 0, 180);
    pwm_channel_1.write(val);
  }
  if (IN1 == pitch)
  {
    int val = map(IN2, 0, 1023, 0, 180);
    pwm_channel_2.write(val);
  }
  if (IN1 == roll)
  {
    int val = map(IN2, 0, 1023, 0, 180);
    pwm_channel_3.write(val);
  }
  if (IN1 == yaw)
  {
    int val = map(IN2, 0, 1023, 0, 180);
    pwm_channel_4.write(val);
  }
  if (IN1 == esd)
  {
    digitalWrite(ESD_pin, IN2);
  }
  if (IN1 == pid)
  {
    int val = map(IN2, 0, 1023, 0, 180);
    pwm_channel_5.write(val);
  }
}