//     Best viewed in a monospace font.
//
//     Keeps the fan duty cycle in a range according
//     to the current temperature defined by the
//     rombus below.
//
//     ^ duty
//     | 
//     |
//     |
//     |
//     |              
//     |           |<---DT--->|     D=TEMP_DELTA
//     |           A'---------A     A=(TEMP_MAX,DUTY_MAX)
//     |          /          /
//     |         /          /
//     |        /          /
//     |       /          /
//     |      B----------B'         B=(TEMP_MIN,DUTY_MIN)
//     |
// <---+-------------------------->
//     |                       temp
//     v

#include "dmath.h"
#include "GetTemp.h"
#include "UpdateFan.h"

const double TEMP_MIN =  15.0;
const double TEMP_MAX = 25.0;
const double TEMP_DELTA = 3.0;
const double DUTY_MIN = 0.0;
const double DUTY_MAX = 1.0;

double temp;
double duty;

void setup()
{
    Serial.begin(9600);
    temp = GetTemp();
    duty = dconstrainmap(temp,TEMP_MIN,TEMP_MAX,DUTY_MIN,DUTY_MAX);
}

void loop()
{
  temp = GetTemp();

  double duty0 = dconstrainmap(temp,
			       TEMP_MIN,TEMP_MAX-TEMP_DELTA,
			       DUTY_MIN,DUTY_MAX);

  double duty1 = dconstrainmap(temp,
			       TEMP_MIN+TEMP_DELTA,TEMP_MAX,
			       DUTY_MIN,DUTY_MAX);

  duty = dconstrain(duty,duty0,duty1);

  UpdateFan(duty);
  
  Serial.print("temp="); Serial.print(temp);
  Serial.print(" duty0="); Serial.print(duty0);
  Serial.print(" duty1="); Serial.print(duty1);
  Serial.print(" duty="); Serial.print(duty);
  Serial.println();
  
  delay(1000);
}
