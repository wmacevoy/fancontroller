#include <OneWire.h>
#include <DallasTemperature.h>
#include <AStar32U4.h>

#define USE_CONFIG 1
#define USE_TEMP   1
#define USE_FAN_SPEED 1
#define USE_FAN_POWER 1
#define USE_LCD 0

#if USE_CONFIG
#include "Config.h"
#endif

#if USE_TEMP
#include "Temp.h"
#endif

#if USE_FAN_SPEED
#include "FanSpeed.h"
#endif

#if USE_FAN_POWER
#include "FanPower.h"
#endif

#if USE_CONFIG
Config config;
#endif


#if USE_TEMP
const uint8_t oneWireBus = 12; // pin number
const uint8_t resolution = 12; // bits
Temp temp(config,oneWireBus,resolution);
#endif

Stream &out = Serial;
const long baud = 115200L;


uint32_t timeout = 0;

#if USE_LCD
AStar32U4LCD lcd;
#endif

#if USE_FAN_SPEED
const uint8_t fanSpeedPin = 2;
FanSpeed fanSpeed(fanSpeedPin);
#endif

#if USE_FAN_POWER
const uint8_t fanPowerPin = 13;
FanPower fanPower(fanPowerPin);
#endif

void setup() {
     Serial.begin(baud);
     while (!Serial) {}

#if USE_FAN_SPEED
     fanSpeed.setup();
#endif

#if USE_FAN_POWER
     fanPower.setup();
#endif
}

void loop() {
#if USE_TEMP
  temp.loop();
#endif

#if USE_FAN_POWER
  fanPower.set(1); // 255*(1+sin(millis()/(2*M_PI*5000.0)))/2.0);
#endif

  if (int32_t(millis()-timeout) > 0) {
    timeout += 1000;

#if USE_FAN_SPEED
    out.print(fanSpeed);
    out.print(" ");
#endif
#if USE_FAN_POWER
    out.print(fanPower);
    out.print(" ");
#endif
#if USE_TEMP
    out.print(temp);
    out.print(" ");
#endif
    out.println();

#if USE_LCD
    lcd.clear();
#if USE_FAN_SPEED
    lcd.gotoXY(0,0);
    lcd.print(fanSpeed);
#endif

#if USE_TEMP
    lcd.gotoXY(0,1);
    lcd.print(temp);
#endif

#endif
  }
}
