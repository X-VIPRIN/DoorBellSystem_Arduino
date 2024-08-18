/*
Door alarm system for arduino.
When a door or system opens and its detector moves from the senser, a alarm is triggered.

By Colton Paul Badock, X-Viprin Software - 2024.
*/

#include <SR04.h> //Ultrasonic sensor library.


const int passiveBuzzerAlarm_pin = 2; //Pin of the alarm's passive buzzer.
const int sonicSensorTrigPin = 3; //Pin for the trig of the sonic sensor.
const int sonicSensorEchoPin = 4; //Pin for the echo pin of the sonic sensor.

int detectorDistance = 0; //Distance of the detector in cm from the module.

SR04 sonicSensor = SR04(sonicSensorEchoPin, sonicSensorTrigPin);

//Entry point
void setup() {
  Serial.begin(9600);
}

//Program infinte loop.
void loop() {
  detectorDistance = getDetectorDistance(); //Get the detectors distance from the sonic sensor.

  //If the detector is more than 10 CM from the module, sound the alarm for 3 seconds.
  if (detectorDistance > 10 && detectorDistance < 30) {
    playWelcomeTone();
  }
}

//Plays one procedure of the alarm. (Plays alarm once, causes entire thread to pause on call)
void runAlarmSequence() {
  tone(passiveBuzzerAlarm_pin, 3000, 500);
  delay(500);
  noTone(passiveBuzzerAlarm_pin);
  tone(passiveBuzzerAlarm_pin, 2000, 500);
  delay(500);
  noTone(passiveBuzzerAlarm_pin);
  tone(passiveBuzzerAlarm_pin, 1000, 500);
  delay(500);
  noTone(passiveBuzzerAlarm_pin);
}

//Gets the detectors distance from the module, returns said distance.
int getDetectorDistance() {
  int distance = 0; //Holds the distance of the detector to the module.

  distance = sonicSensor.Distance(); //Get the detectors distance from the sonic sensor in CM.

  return distance; //Returns said value.
}

//Plays a welcome tone when called, (Pauses the current thread)
void playWelcomeTone() {
  for (int freq = 200; freq < 3000; freq += 200) {
    tone(passiveBuzzerAlarm_pin, freq, 100);
    delay(100);
    noTone(passiveBuzzerAlarm_pin);
  }
}





