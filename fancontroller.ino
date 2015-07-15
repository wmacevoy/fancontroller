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

#include "dmath.h"
#include "Temp.h"
#include "Fan.h"

const double TEMP_MIN =  15.0;
const double TEMP_MAX = 25.0;
const double TEMP_DELTA = 3.0;
const double DUTY_MIN = 0.0;
const double DUTY_MAX = 1.0;
const unsigned long BAUD = 9600L;

double temp;
double duty;

void setup()
{
  FanSetup();
  temp = TempReadC();
  duty = dconstrainmap(temp,TEMP_MIN,TEMP_MAX,DUTY_MIN,DUTY_MAX);

  if (BAUD > 0) {
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
    Serial.println(DUTY_MIN,2);
    Serial.print("/");
    Serial.println(DUTY_MAX,2);
    Serial.print("/");
    Serial.print(duty,2);
    Serial.println();
  }
}

void loop()
{
  temp = TempReadC();

  double duty0 = dconstrainmap(temp,
			       TEMP_MIN,TEMP_MAX-TEMP_DELTA,
			       DUTY_MIN,DUTY_MAX);

  double duty1 = dconstrainmap(temp,
			       TEMP_MIN+TEMP_DELTA,TEMP_MAX,
			       DUTY_MIN,DUTY_MAX);

  duty = dconstrain(duty,duty0,duty1);

  FanUpdate(duty);

  if (BAUD > 0) {
    Serial.print("loop:");
    Serial.print(" temp="); Serial.print(temp);
    Serial.print(" duty min/max/value="); 
    Serial.print(duty0);
    Serial.print("/");
    Serial.print(duty1);
    Serial.print("/");
    Serial.print(duty);
    Serial.println();
  }

  delay(1000);
}
