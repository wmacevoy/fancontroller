#include <OneWire.h>
#include <DallasTemperature.h>
#include <AStar32U4.h>

#include "Config.h"
#include "Temp.h"
#include "FanSpeed.h"
#include "FanPower.h"

Config config;
const uint8_t oneWireBus = 12; // pin number
const uint8_t resolution = 12; // bits

Stream &out = Serial;
const long baud = 115200L;

Temp temp(config,oneWireBus,resolution);

uint32_t timeout = 0;

AStar32U4LCD lcd;

const uint8_t fanSpeedPin = 2;
FanSpeed fanSpeed(fanSpeedPin);

const uint8_t fanPowerPin = 13;
FanPower fanPower(fanPowerPin);

void setup() {
     Serial.begin(baud);
     while (!Serial) ; 
     fanSpeed.setup();
     fanSpeed.enable();
     fanPower.setup();
}

void loop() {
  temp.loop();
  fanPower.set(255*(1+sin(millis()/(2*M_PI*30000.0)))/2.0);
  if (int32_t(millis()-timeout) > 0) {
    timeout += 1000;
    out.print(fanSpeed);
    out.print(" ");
    out.print(fanPower);
    out.print(" ");
    out.print(temp);
    out.println();
    lcd.clear();
    lcd.gotoXY(0,0);
    lcd.print(fanSpeed);
    lcd.gotoXY(0,1);
    lcd.print(temp);
  }
}
