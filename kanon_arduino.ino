#include <Stepper.h>

const int stepsPerRevolution = 2048;  // 28BYJ-48

// ================== Viola ==================
const int motorPin1_vla = 23;
const int motorPin2_vla = 25;
const int motorPin3_vla = 27;
const int motorPin4_vla = 29;

const int TRIG_vla = 9;
const int ECHO_vla = 8;


// ================== Sensor2 ==================
const int motorPin1_2 = 30;
const int motorPin2_2 = 32;
const int motorPin3_2 = 34;
const int motorPin4_2 = 36;

const int TRIG_2 = 3;
const int ECHO_2 = 2;


// ================== Sensor3 ==================
const int motorPin1_3 = 39;
const int motorPin2_3 = 41;
const int motorPin3_3 = 43;
const int motorPin4_3 = 45;

const int TRIG_3 = 6;
const int ECHO_3 = 5;


// ================== Sensor4 ==================
const int motorPin1_4 = 52;
const int motorPin2_4 = 50;
const int motorPin3_4 = 48;
const int motorPin4_4 = 46;

const int TRIG_4 = 11;
const int ECHO_4 = 12;


// ================== 音速 ==================
const float temperature = 17.0;
const double speed_of_sound = 331.5 + 0.6 * temperature;

const float threshold = 10.0; // cm


// ================== Stepper ==================
Stepper stepper1(stepsPerRevolution, motorPin1_vla, motorPin3_vla, motorPin2_vla, motorPin4_vla);
Stepper stepper2(stepsPerRevolution, motorPin1_2, motorPin3_2, motorPin2_2, motorPin4_2);
Stepper stepper3(stepsPerRevolution, motorPin1_3, motorPin3_3, motorPin2_3, motorPin4_3);
Stepper stepper4(stepsPerRevolution, motorPin1_4, motorPin3_4, motorPin2_4, motorPin4_4);


bool rotated1 = false;
bool rotated2 = false;
bool rotated3 = false;
bool rotated4 = false;


void setup() {

  Serial.begin(9600);

  pinMode(TRIG_vla, OUTPUT);
  pinMode(ECHO_vla, INPUT);

  pinMode(TRIG_2, OUTPUT);
  pinMode(ECHO_2, INPUT);

  pinMode(TRIG_3, OUTPUT);
  pinMode(ECHO_3, INPUT);

  pinMode(TRIG_4, OUTPUT);
  pinMode(ECHO_4, INPUT);

  stepper1.setSpeed(10);
  stepper2.setSpeed(10);
  stepper3.setSpeed(10);
  stepper4.setSpeed(10);
}


double measureDistance(int trigPin, int echoPin) {

  double duration;
  double distance;

  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);

  if (duration > 0) {
    duration = duration / 2;
    distance = duration * speed_of_sound * 100 / 1000000;
  }

  return distance;
}


void loop() {

  double d1 = measureDistance(TRIG_vla, ECHO_vla);
  double d2 = measureDistance(TRIG_2, ECHO_2);
  double d3 = measureDistance(TRIG_3, ECHO_3);
  double d4 = measureDistance(TRIG_4, ECHO_4);


  // ================== Motor1 ==================
  if (d1 <= threshold && !rotated1) {
    stepper1.step(-3072);
    rotated1 = true;
  } 
  else if (d1 > threshold) {
    rotated1 = false;
  }


  // ================== Motor2 ==================
  if (d2 <= threshold && !rotated2) {
    stepper2.step(-3072);
    rotated2 = true;
  } 
  else if (d2 > threshold) {
    rotated2 = false;
  }


  // ================== Motor3 ==================
  if (d3 <= threshold && !rotated3) {
    stepper3.step(-3072);
    rotated3 = true;
  } 
  else if (d3 > threshold) {
    rotated3 = false;
  }


  // ================== Motor4 ==================
  if (d4 <= threshold && !rotated4) {
    stepper4.step(-3072);
    rotated4 = true;
  } 
  else if (d4 > threshold) {
    rotated4 = false;
  }


  Serial.print(d1); Serial.print(",");
  Serial.print(d2); Serial.print(",");
  Serial.print(d3); Serial.print(",");
  Serial.println(d4);

  delay(100);
}