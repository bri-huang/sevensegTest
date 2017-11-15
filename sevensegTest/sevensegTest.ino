/*
  Test code for controlling large 7-segment displays
  By: B. Huang
  Date: 11/2/2017
*/

//GPIO declarations
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
byte segmentLatch = 13;
byte segmentClock = 12;
byte segmentData = 11;
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
byte num1 = 0;

byte num2 = 0; 

byte num3 = 0; 

void setup()
{
  Serial.begin(9600);
  Serial.println("Large Digit Driver Example");

  pinMode(segmentClock, OUTPUT);
  pinMode(segmentData, OUTPUT);
  pinMode(segmentLatch, OUTPUT);

  digitalWrite(segmentClock, LOW);
  digitalWrite(segmentData, LOW);
  digitalWrite(segmentLatch, LOW);

  int x = 0;

//  while (1)
//  {
//    showNumber(x,x,x);
//    x=x+1;  //x++
//    Serial.println(x);
//    delay(500);
//  }
}

void loop()
{
//  showNumber(36); //Test pattern
//  showNumber(15); //Test pattern
//  showNumber(10); //Test pattern
  showNumber(num1,num2,num3);
  delay(100);
  num3++; 
  /*if(num3 >= 100)
  {
    num2++; 
  }
  else{num3++;}

  if(num3 > 100)
  {
    num3 == 0;
  }
  else
  {
    ;
  }
  if(num2 >=59) 
  {
    num3++; 
  }
  else
  {
    ;
  }
  if(num2 > 59)
  {
    num2 == 0; 
  }
  else 
  {
    ;
  }*/
  }

void showCount()
{
  for (int x = 0; x < 999; x++)
  {
    showNumber(x);
    delay(100);
  }
}
/********************************************************************************/
void showNumber(byte value)
{
  byte digit1 = value % 10;
  byte digit2 = (value % 100) / 10;
//  byte digit3 = value / 100;
  digitalWrite(segmentLatch, LOW);
  shiftOut(segmentData, segmentClock, MSBFIRST, segments(digit1));
  shiftOut(segmentData, segmentClock, MSBFIRST, segments(digit2));
//  shiftOut(segmentData, segmentClock, MSBFIRST, segments(digit3));
  digitalWrite(segmentLatch, HIGH);
}
/********************************************************************************/
void showNumber(byte value1, byte value2, byte value3)
{
  byte digit1; 
  byte digit2;

  digitalWrite(segmentLatch, LOW);

  digit1 = value3 % 10;
  digit2 = (value3 % 100) / 10;
  shiftOut(segmentData, segmentClock, MSBFIRST, segments(digit1));
  shiftOut(segmentData, segmentClock, MSBFIRST, segments(digit2));
  
  digit1 = value2 % 10;
  digit2 = (value2 % 100) / 10;
  shiftOut(segmentData, segmentClock, MSBFIRST, segments(digit1));
  shiftOut(segmentData, segmentClock, MSBFIRST, segments(digit2));

  digit1 = value1 % 10;
  digit2 = (value1 % 100) / 10;
  shiftOut(segmentData, segmentClock, MSBFIRST, segments(digit1));
  shiftOut(segmentData, segmentClock, MSBFIRST, segments(digit2));
  
  digitalWrite(segmentLatch, HIGH);
}

/********************************************************************************/
void postNumber(byte value)
{
  byte segments = 0;
  digitalWrite(segmentLatch, LOW);
  shiftOut(segmentData, segmentClock, MSBFIRST, segments);
  digitalWrite(segmentLatch, HIGH); //Register moves storage register on the rising edge of RCK
}

/********************************************************************************/
//Given a number, or '-', shifts it out to the display
byte segments(byte number)
{
  //    -  A
  //   / / F/B
  //    -  G
  //   / / E/C
  //    -. D/DP

#define a  1<<0
#define b  1<<6
#define c  1<<5
#define d  1<<4
#define e  1<<3
#define f  1<<1
#define g  1<<2
#define dp 1<<7

  byte data;

  switch (number)
  {
    case 1:
      data = b | c;
      break;
    case 2:
      data = a | b | d | e | g;
      break;
    case 3:
      data = a | b | c | d | g;
      break;
    case 4:
      data = f | g | b | c;
      break;
    case 5:
      data = a | f | g | c | d;
      break;
    case 6:
      data = a | f | g | e | c | d;
      break;
    case 7:
      data = a | b | c;
      break;
    case 8:
      data = a | b | c | d | e | f | g;
      break;
    case 9:
      data = a | b | c | d | f | g;
      break;
    case 0:
      data = a | b | c | d | e | f;
      break;
    case ' ':
      data = 0;
      break;
    case 'c':
      data = g | e | d;
      break;
    case '-':
      data = g;
      break;
  }

  //  if (decimal) segments |= dp;

  return data;
}
