  // Gendynish
//#include <Adafruit_CircuitPlayground.h>

int p1 = 0; // Playground Express 0 = A6, 1 = A7, 2 = A5, 3 = A4, 12 = speaker
int p2 = 3;
unsigned long period1 = 200; // length of one cycle (frequency)
float duty1 = 0.5; //0.999; // PWM duty cycle
unsigned long ms = micros();
unsigned long t1 = ms; // start time of current cycle (pin 1)
unsigned long t1h = (unsigned long) (t1 + period1 * duty1); // calculate the duty cycle pin change time
unsigned long t1l = t1 + period1;
bool p1high = true; // current state of pin
int pChange1 = 100; // speed of pitch change in microseconds, smaller is facter 1 +
int jumpMax1 = 0; // random walk step size, 0+

void setup() {
  //Serial.begin(9600);
  //Serial.println(t1);
  //Serial.println((unsigned long) (t1 + period1 * duty1));
  Serial.println(pow(800,1.6)); // 10 - 200
  pinMode(p1, OUTPUT);
  pinMode(p2, OUTPUT);
  randomSeed(analogRead(0));

  //CircuitPlayground.begin();
}

void loop() {
  ms = micros();
  if (ms > t1l && p1high) { // completed a duty cycle (period)
    digitalWrite(p1, LOW);
    p1high = false;
    //period1 = (unsigned long) random(100, 300); // make noise
    //period1 = (unsigned long) (randomWalkPeriod(period1, jumpMax1, pChange1, 45, 700));
    //duty1 = randomWalkDuty(duty1, 0.5);
    //if (ms % 500 == 0) Serial.println(duty1);// FIX
    setT1();  
  } else if (ms > t1h && !p1high) { // change
    digitalWrite(p1, HIGH);
    p1high = true;
  }
}

void setT1() {
  t1 += pow(period1, 1.6);
  t1h = (unsigned long) (t1 + period1 * duty1);
  t1l = t1 + period1;
}

int randomWalkPeriod(unsigned long curr, int range, int pChange, int minVal, int maxVal) {
  int r = random(range * -1, range + 1);
  //int r = (random(range * -1, range + 1) + random(range * -1, range + 1)) * 0.5; // gauss
  if (random(curr) > 40 && random(pChange) < 1) { // slow down rate of update
    r = curr + r;
  } else r = curr; // no change
  if (r > maxVal) r = maxVal - (r - maxVal); // lowest pitch
  if (r < minVal) r = minVal + (minVal - r); // highest pitch
  return r; //min(200, max(10, curr + r));
}

int randomWalkDuty(float curr, float range) {
  float r = random(range * 1000 * -1, range * 1000 + 1) * 0.001;
  r = curr + r;
  if (r > 1.0) r = 1.0 - (r - 1.0); // reflect across highest value
  if (r < 0) r = 0 + (0 - r); // reflect across lowest value
  return r;
}

