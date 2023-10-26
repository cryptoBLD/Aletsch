#include <Adafruit_LSM303_Accel.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>
#include <SD.h>

Adafruit_LSM303_Accel_Unified accel = Adafruit_LSM303_Accel_Unified();
unsigned long sysTime;

void setup(void) {
  Serial.begin(9600);
  delay(1000);

  /* Initialise the sensor */
  if (!accel.begin()) {
    /* There was a problem detecting the ADXL345 ... check your connections */
    Serial.println("Ooops, no LSM303 detected ... Check your wiring!");
  }

  /* Display some basic information on this sensor */

  accel.setRange(LSM303_RANGE_8G);
  accel.setMode(LSM303_MODE_NORMAL);
}

void loop() {
  double* accelArray = getAcceleration();
  Serial.print("Time: ");
  Serial.println(millis());
  Serial.print("X: ");
  Serial.print(accelArray[0]);
  Serial.print(" ");
  Serial.print("Y: ");
  Serial.print(accelArray[1]);
  Serial.print(" ");
  Serial.print("Z: ");
  Serial.print(accelArray[2]);
  Serial.println("m/s^2");
  Serial.println(" ");
  delay(196);
}

double* getAcceleration() {
  static double accelArray[3];
  sensors_event_t event;
  accel.getEvent(&event);

  accelArray[0] = event.acceleration.x;
  accelArray[1] = event.acceleration.y;
  accelArray[2] = event.acceleration.z;
  return accelArray;
}