//     Best viewed in a monospace font.
//
//     Keeps the fan duty cycle in a range according
//     to the current temperature defined by the
//     rombus below.
//
//     setup - initial duty is along the A-B diagonal.
//     loop  - duty is shifted down/up on the left/right
//             side just enough to stay in the rombus.
//     
//     if the romubus is a rectangle, then this is a
//     degenerate case called a schmitt trigger.
//     
//
//     ^ duty
//     | 
//     |
//     |
//     |
//     |              
//     |           |<---D--->|     D=TEMP_DELTA
//     |           B'--------B---- B=(TEMP_MAX,DUTY_MAX)
//     |          /         /
//     |         /         /
//     |        /         /
//     |       /         /
//     |  ----A---------A'         A=(TEMP_MIN,DUTY_MIN)
//     |
// <---+-------------------------->
//     |                       temp
//     v

#include <AStar32U4Prime.h>



#include "dmath.h"
#include "Temp.h"
#include "Fan.h"

AStar32U4PrimeLCD lcd;


const unsigned long BAUD = 9600L;
const double TEMP_MIN =  28.0;
const double TEMP_MAX =  32.0;
const double TEMP_DELTA = 4.0;
const double FAN_MIN = 0.0;
const double FAN_MAX = 1.0;
const bool   SCHMITT = dabs(TEMP_MIN+TEMP_DELTA-TEMP_MAX)<1e-6;

void LCDSetup()
{
  lcd.clear();
}

void LCDLoop()
{
  lcd.clear();
  lcd.print(temp); lcd.print("C");
  lcd.gotoXY(0,1);
  lcd.print(fan*100.0); lcd.print("%");
}

void SerialSetup()
{
    Serial.begin(BAUD);
    Serial.print("setup:");
    Serial.print(" temp MIN/MAX/DELTA/value="); 
    Serial.print(TEMP_MIN,1);
    Serial.print("/");
    Serial.print(TEMP_MAX,1);
    Serial.print("/");
    Serial.print(TEMP_DELTA,1);
    Serial.print("/");
    Serial.print(temp,1);
    Serial.print(" delta MIN/MAX/value=");
    Serial.println(FAN_MIN,2);
    Serial.print("/");
    Serial.println(FAN_MAX,2);
    Serial.print("/");
    Serial.print(fan,2);
    Serial.println();  
}

void SchmittSetup()
{
  if (temp < (TEMP_MIN + TEMP_MAX) / 2.0) {
    fan = FAN_MIN;
  } else {
    fan = FAN_MAX;
  }
}

void HisteresisSetup()
{
    fan = dconstrainmap(temp,TEMP_MIN,TEMP_MAX,FAN_MIN,FAN_MAX);
}


void setup()
{
  FanSetup();
  TempSetup();

  if (SCHMITT) {
    SchmittSetup();
  } else {
    HisteresisSetup();
  }

  if (BAUD > 0) {
    SerialSetup();
  }
  LCDSetup();
}

void SchmittLoop()
{
   if (fan == FAN_MAX) {
     if (temp <= TEMP_MIN) {
       fan = FAN_MIN;
     }
   } else {
     if (temp >= TEMP_MAX) {
       fan = FAN_MAX;      
     }
   }  
}

void HysteresisLoop()
{
  double fan0 = dconstrainmap(temp,
			       TEMP_MIN,TEMP_MAX-TEMP_DELTA,
			       FAN_MIN,FAN_MAX);
  
  double fan1 = dconstrainmap(temp,
			       TEMP_MIN+TEMP_DELTA,TEMP_MAX,
			       FAN_MIN,FAN_MAX);
  fan = dconstrain(fan,fan0,fan1);
}

void SerialLoop()
{
  Serial.print("loop:");
  Serial.print(" temp="); Serial.print(temp);
  Serial.print(" fan=");  Serial.print(fan);
  Serial.println();
}

void loop()
{
  TempUpdate();

  if (SCHMITT) {
    SchmittLoop();
  } else {
    HysteresisLoop();
  }

  FanUpdate();

  if (BAUD > 0) {
    SerialLoop();
  }
  LCDLoop();
  delay(1000);
}
