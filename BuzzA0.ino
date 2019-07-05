// Tone generation for the Adafruit Playground Express
// Based on stochastic synthesis methods (Xenakis 1971)
// Programmed by Andrew R. Brown 2019
// License: CC-BY

#include <Adafruit_CircuitPlayground.h>
unsigned long usec = micros();
int state = 0;
float dur = 2000; // corelates to frequency
float gain = 50;
float duty = 0.25; // PWM duty cycle, passed as argument to buzz below
int pin = A0;

void setup() {
  CircuitPlayground.begin();
  Serial.begin(115200);
}

void loop() {
  if (micros() > usec && CircuitPlayground.slideSwitch()) {
    // volume gainVari (0-100, 500 max), 
    // duration (pitch) Variation (0.0 - 10.0, 100 max), 
    // duty cycle variation (0.0 - 1.0, larger vals possible).
    buzz(2, 1.0, 0.1); 
  }
}

void buzz (int gainVari, float durVari, float dutyVari) {
  if (state == 0) {
    gain += (random(gainVari * 2 + 1) - gainVari) / 4.0;
    gain = min(120, max(10, gain));
    dur *= 1 + (random(durVari * 1000 + 1) - durVari * 500) * 0.00001;
    dur = min(20000, max(400, dur));
//    Serial.println(random(durVari * 1000 + 1) - durVari * 500);
    duty += (random(2001) - 1000) * 0.00001 * dutyVari;
    duty = min(0.5, max(0.01, duty));
    analogWrite(pin, gain);
    state = 1;
    usec += dur  * duty;
  } else {
    analogWrite(pin, 0);
    state = 0;
    usec += dur * (1.0 - duty);
  }
}
