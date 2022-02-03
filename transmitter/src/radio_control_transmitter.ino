int Emergency_shut_down_pin = 2;
#include "Arduino.h"
#include "string.h"
#include "stdio.h"

#define trottle 0
#define pitch 1
#define roll 2
#define yaw 3
#define esd 4
#define pid 5
#define count 6

String instring = "";
int C;
String outstring;
char T, P, R, Y, E, D;

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
  bit_maker(Trottle, Pitch, Roll, Yaw, Esd, PID_tuner);
  // if (0 <= Trottle < 256)
  // {
  //   T = char(Trottle);
  // }
  // if (0 <= Pitch < 256)
  // {
  //   P = char(Pitch);
  // }
  // if (0 <= Roll < 256)
  // {
  //   R = char(Roll);
  // }
  // if (0 <= Yaw < 256)
  // {
  //   Y = char(Yaw);
  // }
  // E = char(Esd);
  // if (0 <= PID_tuner < 256)
  // {
  //   D = char(PID_tuner);
  // }
  // else if (256 <= Trottle < 1023)
  // {
  //   /* code */
  // }
  // else if (256 <= Pitch < 1023)
  // {
  //   /* code */
  // }
  // else if (256 <= Roll < 1023)
  // {
  //   /* code */
  // }
  // else if (256 <= Yaw < 1023)
  // {
  //   /* code */
  // }
  // else if (256 <= PID_tuner < 1023)
  // {
  //   /* code */
  // }
  // instring = (T + P + R + Y + E + D);
  // // convertor(instring);
  // Serial.println(instring);
  // delay(2);
}

void bit_maker(int trottle_in, int pitch_in, int roll_in, int yaw_in, int esd_in, int pid_in)
{
  char data_packet[12];
  data_packet[0] = 1 << 7 | char(trottle_in / 127) | trottle << 4;
  data_packet[1] = 0 << 7 | char(trottle_in % 127);
  data_packet[2] = 1 << 7 | char(pitch_in / 127) | pitch << 4;
  data_packet[3] = 0 << 7 | char(pitch_in % 127);
  data_packet[4] = 1 << 7 | char(roll_in / 127) | roll << 4;
  data_packet[5] = 0 << 7 | char(roll_in % 127);
  data_packet[6] = 1 << 7 | char(yaw_in / 127) | yaw << 4;
  data_packet[7] = 0 << 7 | char(yaw_in % 127);
  data_packet[8] = 1 << 7 | char(esd_in / 127) | esd << 4;
  data_packet[9] = 0 << 7 | char(esd_in % 127);
  data_packet[10] = 1 << 7 | char(pid_in / 127) | pid << 4;
  data_packet[11] = 0 << 7 | char(pid_in % 127);
  for (int i = 0; i < 12; i++)
  {
    Serial.print(data_packet[i]);
  }
  // Serial.println(trottle_in);
  // Serial.println(pitch_in);
  // Serial.println(roll_in);
  // Serial.println(yaw_in);
  // Serial.println(esd_in);
  // Serial.println(pid_in);
}