// Sound synthesis generation for the Adafruit Playground Express analog output
// Based on stochastic synthesis methods (Xenakis 1971)
// Monophonic version of the Gendynish algorithm published in 2018
// academic article outlining process published at ISEA 2019
// Programmed by Andrew R. Brown 2019
// License: CC-BY
// Left button randomises paramters and their degree of variability (pitch, amplitude, timbre, rougness)
// LeDs show values for pitch, pitch change, amp and amp change, timbre (dutyCycle) and time change
// Right button resets to a basic square wave tone
// Hold right button to have accellerometer vary pitch and amplitude
// 

#include <Adafruit_CircuitPlayground.h>
unsigned long usec = micros();
unsigned long tempUSec = micros();
int state = 0;
int period = 2000; // time in usecs, corelates to frequency
float dutyCycle = 0.5; // PWM duty cycle
int gain = 40;
float deviateDuty = 0.0;
float deviatePitch = 0.0;
float deviateGain = 0.0;
int minPeriod = 350;
int maxPeriod = 22000;
int minGain = 10;
int maxGain = 250; // 150
int pin = A0;
bool leftButtonPressed;
bool rightButtonPressed;
unsigned long debounce = micros();
float x, y;
bool buzzing = false;
int red, green, blue;
float periodJitter = 0.0; //(0.0 - 1.0, can be higher)
float deviateJitter = 0.0;

void setup() {
  CircuitPlayground.begin();
  Serial.begin(115200);
  setPixels();
}

void loop() {
  tempUSec = micros();
  if (CircuitPlayground.slideSwitch() && tempUSec > usec) {
    buzz(); //volume gain (0-255), duty cycle (0.0 - 0.5), jitter (0.0 - 0.1, 1.0 max)
  } 
  leftButtonPressed = CircuitPlayground.leftButton();
  rightButtonPressed = CircuitPlayground.rightButton();
  if (leftButtonPressed && tempUSec > debounce) {
    debounce = tempUSec + 150000;
    randomiseParameters();
    buzzing = true;
  }
  if (rightButtonPressed && tempUSec > debounce) {
    debounce = tempUSec + 150000;
    if (rightButtonPressed && buzzing == false) {
      x = CircuitPlayground.motionX();
      if (x > 3) {
        period = max(period * 0.98, minPeriod);
      }
      if (x < -3) {
        period = min(period * 1.02, maxPeriod);
      }
      y = CircuitPlayground.motionY();
      if (y < -3) {
        gain = max(gain * 0.9, minGain);
      }
      if (y > 3) {
        gain = min(gain * 1.1, maxGain);
      }
    } else {
      resetParameters();
      buzzing = false;
    }
  }
}

void buzz() {
  float temp = random(periodJitter * 1000) * 0.0001; // adds pitch jitter
  if (state == 0) {
      analogWrite(pin, gain);
      state = 1;
      usec += period * (1 + temp) * dutyCycle;
    } else {
      analogWrite(pin, 0);
      state = 0;
      usec += period * (1 + temp) * (1.0 - dutyCycle);
      updateAudioParams();
    }
}

void updateAudioParams() {
  period = randomWalkInt(period, deviatePitch, minPeriod, maxPeriod);
  periodJitter += (random(2001) - 1000) * 0.001 * deviateJitter;
  periodJitter = min(1.0, max(0.0, periodJitter));
  gain = randomWalkInt(gain, deviateGain, minGain, maxGain);
  dutyCycle += (random(2001) - 1000) * 0.00001 * deviateDuty;
  dutyCycle = min(0.5, max(0.01, dutyCycle));
}

void randomiseParameters() {
  period = max(minPeriod, (random(maxPeriod - minPeriod))); //pow(random(maxPeriod), 2));
  deviatePitch = pow(random(12), 2) * 0.1;
  dutyCycle = random(11) * 0.05 + 0.1;
  deviateDuty = random(4) * 0.1;
  gain = random(100) + 50;
  deviateGain = random(10) * 0.5;
  periodJitter = 0; //random(200) * 0.001;
  deviateJitter = pow(random(6) * 0.1, 2.5); 
  setPixels(); // update led's
}

void resetParameters() {
  period = 2000;
  deviatePitch = 0;
  dutyCycle = 0.5;
  deviateDuty = 0;
  gain = 40;
  deviateGain = 0;
  periodJitter = 0.0;
  deviateJitter = 0.0;
  setPixels(); // update led's
}

void setPixels() {
  CircuitPlayground.setPixelColor(0, map(period, minPeriod, maxPeriod, 200, 20), 0, 0); // red
  CircuitPlayground.setPixelColor(1, map(deviatePitch, 0, 11, 15, 100), map(deviatePitch, 0, 11, 15, 100), 0); // yellow
  CircuitPlayground.setPixelColor(3, 0, 0, map(dutyCycle * 1000, 0, 600, 20, 255)); // blue
  CircuitPlayground.setPixelColor(4, 0, map(deviateDuty * 1000, 0, 30, 15, 100), map(deviateDuty * 1000, 0, 30, 15, 120)); // aqua
  CircuitPlayground.setPixelColor(6, 0, map(gain, 50, 150, 20, 255), 0); // green
  CircuitPlayground.setPixelColor(7, map(deviateGain * 10, 0, 20, 15, 100), 0, map(deviateGain * 10, 0, 20, 15, 120)); // purple
}

int randomWalkInt(int curr, float devPercent, int minimum, int maximum) {
  if (curr == 0) {
    curr += random(devPercent + 1);
  } else {
    curr += random(floor(devPercent * 0.01 * curr * -1), ceil(devPercent * 0.01 * curr) + 1);
  }
  if (curr > maximum) curr = round(maximum - (maximum - minimum) * 0.01);
  if (curr < minimum) curr = round(minimum + (maximum - minimum) * 0.01);
  return curr;
}

// still suspect about htis function working as expected
float randomWalkFloat(float curr, float devPercent, float minimum, float maximum) {
  curr += (random(devPercent * 100) - devPercent * 50) * 0.01;
  if (curr > maximum) curr = maximum; //round(maximum - (maximum - minimum) * 0.01);
  if (curr < minimum) curr = minimum; //round(minimum + (maximum - minimum) * 0.01);
  return curr;
}
