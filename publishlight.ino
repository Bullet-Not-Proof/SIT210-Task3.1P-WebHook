// This #include statement was automatically added by the Particle IDE.
#include <OneWire.h>
#include <BH1750.h>

BH1750 lightMeter(0x23, Wire);
//BH1750Lib lightMeter;

int lux;

void getLux(){
    lightMeter.make_forced_measurement();
    lux = lightMeter.get_light_level();
    //lux = lightMeter.lightLevel();
}

int getHandler(String command) {
    
    getLux();
    return 1;
}

void setup() {
    lightMeter.begin();
    lightMeter.set_sensor_mode(BH1750::forced_mode_high_res2);
    Particle.variable("lux", lux);
    Particle.function("get lux", getHandler);
}

void loop() {
    digitalWrite(D7, HIGH);
    getLux();
    Particle.publish("lux", String(lux));

    delay(1000);
    digitalWrite(D7, LOW);

    delay(4000);
}