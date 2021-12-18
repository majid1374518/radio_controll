/*
  String to Integer conversion

  Reads a serial input string until it sees a newline, then converts the string
  to a number if the characters are digits.

  The circuit:
  - No external components needed.

  created 29 Nov 2010
  by Tom Igoe

  This example code is in the public domain.

  https://www.arduino.cc/en/Tutorial/BuiltInExamples/StringToInt
*/

String inString = "";    // string to hold input

void setup() {
  // Open serial communications and wait for port to open:
  pinMode(2, 1);
    Serial.begin(57600);
    while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  // send an intro:
  Serial.println("\n\nString toInt():");
  Serial.println();
}

void loop() {
  // Read serial input:
  while (Serial.available() > 0) {
    int inChar = Serial.read();
    if (isDigit(inChar)) {
      // convert the incoming byte to a char and add it to the string:
      inString += (char)inChar;
    }
    check_inchar(inChar);

  }
}
void check_inchar(int inChar)
{
  if (inChar == 'T') {
    //      Serial.println();
    //      Serial.print("Trottle=");
    //      Serial.println(inString.toInt());
    analogWrite(11, inString.toInt() / 4);
    inString = "";
  }
  if (inChar == 'P') {
    //      Serial.println();
    //      Serial.print("Pitch=");
    //      Serial.println(inString.toInt());
    analogWrite(10, inString.toInt() / 4);
    inString = "";
  }
  if (inChar == 'R') {
    //      Serial.println();
    //      Serial.print("Roll=");
    //      Serial.println(inString.toInt());
    analogWrite(9, inString.toInt() / 4);
    inString = "";
  }
  if (inChar == 'Y') {
    //      Serial.println();
    //      Serial.print("Yaw=");
    //      Serial.println(inString.toInt());
    analogWrite(6, inString.toInt() / 4);
    inString = "";
  }
  if (inChar == 'E') {
    //      Serial.println();
    //      Serial.print("ESD=");
    //      Serial.println(inString.toInt());
    digitalWrite(2, inString.toInt());
    inString = "";
  }
  if (inChar == 'D') {
    //      Serial.println();
    //      Serial.print("PID=");
    //      Serial.println(inString.toInt());
    analogWrite(3, inString.toInt() / 4);
    inString = "";
  }
}
